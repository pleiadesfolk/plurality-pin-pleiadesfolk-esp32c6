/*
 * PluralKit -> pin front sync (see pksync.h). Two ways in:
 *
 * Relay (relay/pk_relay.py on an always-on computer): PluralKit pushes each
 * switch to the relay, and the pin keeps a request waiting there
 * (GET <relay>/front?since=<seq>, answered as soon as the front changes or
 * after ~50 s): {"seq", "time", "members": ["abcde", ...]}. The home address
 * (plain HTTP on the home network, cheap) is tried first; away from home, the
 * internet address (HTTPS through a tunnel). Each route keeps its connection
 * open between requests, so only the first one pays for setting it up.
 *
 * Direct: GET https://api.pluralkit.me/v2/systems/<ref>/fronters once a
 * minute, {"timestamp": "2026-10-31T15:37:00.123456Z", "members": [{"id"}..]}
 * (204: no switches). <ref> is the system ID, or "@me" with the token in the
 * Authorization header. Used when there's no relay, or it can't be reached.
 *
 * Time zone: with the token, the pin also reads the system's time zone from
 * PluralKit (GET /systems/@me/settings, "timezone": "Asia/Hong_Kong") at
 * start and every few hours, turns it into a POSIX TZ string (timezones.c)
 * and hands it to zone.c (used unless one is picked on the dashboard).
 *
 * A TLS session holds ~40 KB of RAM while open. The token and the relay
 * secret are kept in NVS ("pin"/"pk_ref", "pk_secret") and never logged or
 * sent anywhere but PluralKit / the relay.
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_log.h"
#include "esp_http_client.h"
#include "esp_crt_bundle.h"
#include "esp_event.h"
#include "esp_timer.h"
#include "esp_netif.h"
#include "nvs.h"
#include "cJSON.h"
#include "lvgl.h"
#include "pksync.h"
#include "store.h"
#include "zone.h"
#include "wifi.h"

static const char *TAG = "pksync";

#define NVS_NAMESPACE   "pin"
#define REF_MAX         96              /* tokens are 64 characters */
#define URL_MAX         96
#define POLL_MS         60000           /* direct checks */
#define RELAY_RETRY_MS  30000           /* after the relay couldn't be reached */
#define RELAY_WAIT_MS   65000           /* the relay answers within ~50 s */
#define HOME_PROBE_MS   3000            /* is the home address reachable from here? */
#define RESPONSE_MAX    (32 * 1024)     /* fronters come with their full member details (~1-2 KB each) */
#define TZ_CHECK_MS     (6 * 3600 * 1000)  /* PluralKit time zone: checked this often */
#define USER_AGENT      "plurality-pin (ESP32 front display)"

typedef enum { ROUTE_HOME, ROUTE_NET, ROUTE_COUNT } route_t;
static const char *const ROUTE_KEYS[ROUTE_COUNT] = { "pk_home", "pk_net" };
static const char *const ROUTE_NAMES[ROUTE_COUNT] = { "home", "internet" };

static SemaphoreHandle_t lock;          /* guards the settings and the status below */
static char ref[REF_MAX];               /* direct: system ID or token; "" = off */
static char relay_url[ROUTE_COUNT][URL_MAX];
static char relay_secret[REF_MAX];
static uint32_t checked, synced, relay_seen;
static int relay_via = -1;              /* route of the last good relay answer */
static char error[64], relay_error[64];
static TaskHandle_t task;
static volatile bool settings_changed, network_changed;

static esp_http_client_handle_t relay_client[ROUTE_COUNT];   /* kept open between requests */
static int relay_seq = -1;
static int home_tries = 1;              /* home probes before taking the internet route */

static bool is_system_id(const char *s)
{
    size_t n = strlen(s);
    if (n < 5 || n > 6) {
        return false;
    }
    for (size_t i = 0; i < n; i++) {
        if (!isalpha((unsigned char)s[i])) {
            return false;
        }
    }
    return true;
}

static void set_text(char *dst, size_t size, const char *text)
{
    xSemaphoreTake(lock, portMAX_DELAY);
    bool same = strcmp(dst, text) == 0;
    strlcpy(dst, text, size);
    xSemaphoreGive(lock);
    if (text[0] && !same) {
        ESP_LOGW(TAG, "%s", text);
    }
}

/* "2026-10-31T15:37:00.123456Z" (or +00:00) -> unix seconds; 0 if unreadable */
static uint32_t parse_time(const char *s)
{
    int y, mo, d, h, mi, sec;
    if (!s || sscanf(s, "%d-%d-%dT%d:%d:%d", &y, &mo, &d, &h, &mi, &sec) != 6) {
        return 0;
    }
    /* days since 1970-01-01 (Howard Hinnant's days_from_civil) */
    y -= mo <= 2;
    int era = (y >= 0 ? y : y - 399) / 400;
    unsigned yoe = (unsigned)(y - era * 400);
    unsigned doy = (153 * (mo + (mo > 2 ? -3 : 9)) + 2) / 5 + d - 1;
    unsigned doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;
    long days = (long)era * 146097 + (long)doe - 719468;
    return (uint32_t)(days * 86400 + h * 3600 + mi * 60 + sec);
}

/*
 * Take a front from PluralKit (`members`: ids as strings, or member objects
 * with "id") if it's newer than the pin's own front, has someone the pin knows
 * (or nobody at all), and differs from what's shown.
 */
/* PluralKit member ids (strings, or objects with "id") -> the pin's indexes */
static int member_indexes(const cJSON *members_json, uint16_t *members, int *unknown)
{
    int count = 0;
    *unknown = 0;
    const cJSON *m;
    cJSON_ArrayForEach(m, members_json) {
        const char *id = cJSON_IsString(m) ? m->valuestring : cJSON_GetStringValue(cJSON_GetObjectItem(m, "id"));
        int index = store_member_index(id ?: "");
        if (index < 0) {
            (*unknown)++;
        } else if (count < STORE_FRONT_MAX) {
            members[count++] = (uint16_t)index;
        }
    }
    return count;
}

static void apply(uint32_t when, const cJSON *members_json)
{
    uint16_t members[STORE_FRONT_MAX];
    int unknown;
    int count = member_indexes(members_json, members, &unknown);
    if (!when || when <= store_front_time() || (count == 0 && unknown > 0) || store_front_is(members, count)) {
        return;
    }
    if (store_add_switch_at(when, members, count) == ESP_OK) {
        ESP_LOGI(TAG, "new front from PluralKit: %d member(s)%s", count, unknown ? " (some aren't on the pin)" : "");
        xSemaphoreTake(lock, portMAX_DELAY);
        synced = when;
        xSemaphoreGive(lock);
    }
}

/* ---------- reading answers ---------- */

typedef struct {
    char *body;
    int len, size;
} response_t;

/* Collect the body as it arrives (esp_http_client_perform's events) */
static esp_err_t on_event(esp_http_client_event_t *e)
{
    response_t *r = e->user_data;
    if (e->event_id == HTTP_EVENT_ON_DATA && r) {
        if (r->len + e->data_len > r->size) {
            int size = r->size ? r->size : 2048;
            while (size < r->len + e->data_len) {
                size *= 2;
            }
            char *bigger = size <= RESPONSE_MAX ? realloc(r->body, size + 1) : NULL;
            if (!bigger) {
                return ESP_FAIL;
            }
            r->body = bigger;
            r->size = size;
        }
        memcpy(r->body + r->len, e->data, e->data_len);
        r->len += e->data_len;
        r->body[r->len] = 0;
    }
    return ESP_OK;
}

/* ---------- "check now" (double tap) ---------- */

static void (*refresh_done)(pksync_refresh_t);
static volatile bool refreshing;

static void refresh_report(void *result)
{
    refreshing = false;
    refresh_done((pksync_refresh_t)(intptr_t)result);
}

/* The relay's answer {"time","members",...}: make it the pin's front */
static pksync_refresh_t match_front(const char *body)
{
    cJSON *root = cJSON_Parse(body);
    uint32_t when = (uint32_t)cJSON_GetNumberValue(cJSON_GetObjectItem(root, "time"));
    uint16_t members[STORE_FRONT_MAX];
    int unknown;
    int count = member_indexes(cJSON_GetObjectItem(root, "members"), members, &unknown);
    cJSON_Delete(root);
    if (!when) {
        return PKSYNC_REFRESH_SAME;     /* PluralKit has no switches */
    }
    if (count == 0 && unknown > 0) {
        return PKSYNC_REFRESH_UNKNOWN;
    }
    int dropped;
    bool added;
    if (store_match_front(when, members, count, &dropped, &added) != ESP_OK) {
        return PKSYNC_REFRESH_FAILED;
    }
    return dropped || added ? PKSYNC_REFRESH_CHANGED : PKSYNC_REFRESH_SAME;
}

/* Its own connection: the sync task's one is busy waiting at the relay */
static void refresh_task(void *arg)
{
    char base[URL_MAX], secret[REF_MAX], url[URL_MAX + 16], auth[REF_MAX + 8];
    xSemaphoreTake(lock, portMAX_DELAY);
    route_t route = relay_via >= 0 ? (route_t)relay_via : relay_url[ROUTE_HOME][0] ? ROUTE_HOME : ROUTE_NET;
    strlcpy(base, relay_url[route], sizeof(base));
    strlcpy(secret, relay_secret, sizeof(secret));
    xSemaphoreGive(lock);
    size_t n = strlen(base);
    while (n && base[n - 1] == '/') {
        base[--n] = 0;
    }
    snprintf(url, sizeof(url), "%s/refresh", base);
    snprintf(auth, sizeof(auth), "Bearer %s", secret);

    pksync_refresh_t result = PKSYNC_REFRESH_FAILED;
    response_t r = { 0 };
    esp_http_client_config_t config = {
        .url = url,
        .method = HTTP_METHOD_POST,
        .crt_bundle_attach = esp_crt_bundle_attach,
        .timeout_ms = 30000,            /* through the internet the TLS set-up alone takes ~20 s */
        .user_agent = USER_AGENT,
        .event_handler = on_event,
        .user_data = &r,
    };
    esp_http_client_handle_t c = esp_http_client_init(&config);
    if (c) {
        esp_http_client_set_header(c, "Authorization", auth);
        if (esp_http_client_perform(c) == ESP_OK && esp_http_client_get_status_code(c) == 200 && r.body) {
            result = match_front(r.body);
        } else {
            ESP_LOGW(TAG, "check now: the relay (%s) answered %d", ROUTE_NAMES[route], esp_http_client_get_status_code(c));
        }
        esp_http_client_cleanup(c);
    }
    free(r.body);
    lv_async_call(refresh_report, (void *)(intptr_t)result);
    vTaskDelete(NULL);
}

void pksync_refresh_now(void (*done)(pksync_refresh_t result))
{
    xSemaphoreTake(lock, portMAX_DELAY);
    bool relay = relay_secret[0] && (relay_url[ROUTE_HOME][0] || relay_url[ROUTE_NET][0]);
    xSemaphoreGive(lock);
    if (!relay) {
        done(PKSYNC_REFRESH_NO_RELAY);
    } else if (refreshing) {
        done(PKSYNC_REFRESH_BUSY);
    } else {
        refreshing = true;
        refresh_done = done;
        if (xTaskCreate(refresh_task, "pk_refresh", 8192, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS) {
            refreshing = false;
            done(PKSYNC_REFRESH_FAILED);
        }
    }
}

/* ---------- direct from PluralKit ---------- */

static void check_direct(void)
{
    char my_ref[REF_MAX];
    xSemaphoreTake(lock, portMAX_DELAY);
    strlcpy(my_ref, ref, sizeof(my_ref));
    xSemaphoreGive(lock);
    if (!my_ref[0]) {
        return;
    }
    bool token = !is_system_id(my_ref);
    char url[64 + REF_MAX];
    snprintf(url, sizeof(url), "https://api.pluralkit.me/v2/systems/%s/fronters", token ? "@me" : my_ref);
    response_t r = { 0 };
    esp_http_client_config_t config = {
        .url = url,
        .crt_bundle_attach = esp_crt_bundle_attach,
        .timeout_ms = 15000,
        .user_agent = USER_AGENT,
        .event_handler = on_event,
        .user_data = &r,
    };
    esp_http_client_handle_t client = esp_http_client_init(&config);
    int status = -1;
    if (client) {
        if (token) {
            esp_http_client_set_header(client, "Authorization", my_ref);
        }
        if (esp_http_client_perform(client) == ESP_OK) {
            status = esp_http_client_get_status_code(client);
        }
        esp_http_client_cleanup(client);
    }

    if (status != 200 && status != 204) {
        char text[64];
        snprintf(text, sizeof(text),
                 status == 401 ? "PluralKit didn't accept the token"
                 : status == 403 ? "this system's front is private - use a token"
                 : status == 404 ? "PluralKit doesn't know this system"
                 : status < 0 ? "couldn't reach PluralKit" : "PluralKit answered %d", status);
        set_text(error, sizeof(error), text);
        free(r.body);
        return;
    }
    cJSON *root = status == 200 && r.body ? cJSON_Parse(r.body) : NULL;
    free(r.body);
    if (status == 200 && !root) {
        set_text(error, sizeof(error), "unexpected answer from PluralKit");
        return;
    }
    set_text(error, sizeof(error), "");
    xSemaphoreTake(lock, portMAX_DELAY);
    checked = (uint32_t)time(NULL);
    xSemaphoreGive(lock);
    if (root) {
        apply(parse_time(cJSON_GetStringValue(cJSON_GetObjectItem(root, "timestamp"))),
              cJSON_GetObjectItem(root, "members"));
        cJSON_Delete(root);
    }
}

/* ---------- on behalf of the dashboard ---------- */

/* One connection to PluralKit, kept open between the dashboard's requests (a
 * sync sends many in a row; a new TLS session each time takes seconds) and
 * closed once they stop, as it holds ~40 KB */
#define PK_IDLE_US      (15 * 1000000)

static SemaphoreHandle_t pk_lock;
static esp_http_client_handle_t pk_client;
static esp_timer_handle_t pk_idle;

typedef struct {
    pksync_status_cb_t on_status;
    pksync_data_cb_t on_data;
    void *ctx;
    bool status_sent;
    esp_err_t err;
} pk_request_t;

static void pk_close(void *arg)
{
    if (xSemaphoreTake(pk_lock, 0) == pdTRUE) {     /* busy: it'll be closed after the next one */
        if (pk_client) {
            esp_http_client_cleanup(pk_client);
            pk_client = NULL;
        }
        xSemaphoreGive(pk_lock);
    }
}

static void pk_send_status(pk_request_t *r, esp_http_client_handle_t client)
{
    if (!r->status_sent) {
        r->status_sent = true;
        r->err = r->on_status(esp_http_client_get_status_code(client), r->ctx);
    }
}

static esp_err_t pk_event(esp_http_client_event_t *e)
{
    pk_request_t *r = e->user_data;
    if (e->event_id == HTTP_EVENT_ON_DATA && r) {
        pk_send_status(r, e->client);
        if (r->err == ESP_OK) {
            r->err = r->on_data(e->data, e->data_len, r->ctx);
        }
    }
    return ESP_OK;
}

esp_err_t pksync_pk_request(const char *method, const char *path, const char *body,
                            pksync_status_cb_t on_status, pksync_data_cb_t on_data, void *ctx)
{
    char my_ref[REF_MAX];
    xSemaphoreTake(lock, portMAX_DELAY);
    strlcpy(my_ref, ref, sizeof(my_ref));
    xSemaphoreGive(lock);
    if (!my_ref[0]) {
        return ESP_ERR_INVALID_STATE;
    }
    bool token = !is_system_id(my_ref);
    esp_http_client_method_t how = strcmp(method, "POST") == 0 ? HTTP_METHOD_POST
                                   : strcmp(method, "DELETE") == 0 ? HTTP_METHOD_DELETE : HTTP_METHOD_GET;
    if (how != HTTP_METHOD_GET && !token) {
        return ESP_ERR_NOT_SUPPORTED;   /* changing anything needs the token */
    }
    char url[160];
    snprintf(url, sizeof(url), "https://api.pluralkit.me/v2/systems/%s%s", token ? "@me" : my_ref, path);

    xSemaphoreTake(pk_lock, portMAX_DELAY);
    esp_timer_stop(pk_idle);
    pk_request_t r = { .on_status = on_status, .on_data = on_data, .ctx = ctx };
    esp_err_t err = ESP_FAIL;
    for (int attempt = 0; attempt < 2 && err != ESP_OK && !r.status_sent; attempt++) {
        bool fresh = !pk_client;
        if (fresh) {
            esp_http_client_config_t config = {
                .url = url,
                .crt_bundle_attach = esp_crt_bundle_attach,
                .timeout_ms = 20000,
                .user_agent = USER_AGENT,
                .event_handler = pk_event,
                .keep_alive_enable = true,
            };
            pk_client = esp_http_client_init(&config);
            if (!pk_client) {
                err = ESP_ERR_NO_MEM;
                break;
            }
        }
        esp_http_client_set_url(pk_client, url);
        esp_http_client_set_method(pk_client, how);
        esp_http_client_set_user_data(pk_client, &r);
        if (token) {
            esp_http_client_set_header(pk_client, "Authorization", my_ref);
        }
        if (body) {
            esp_http_client_set_header(pk_client, "Content-Type", "application/json");
        } else {
            esp_http_client_delete_header(pk_client, "Content-Type");
        }
        esp_http_client_set_post_field(pk_client, body, body ? strlen(body) : 0);
        err = esp_http_client_perform(pk_client);
        esp_http_client_set_post_field(pk_client, NULL, 0);
        esp_http_client_set_user_data(pk_client, NULL);
        if (err != ESP_OK) {
            esp_http_client_cleanup(pk_client);     /* start afresh; a kept connection may have gone stale */
            pk_client = NULL;
            if (fresh) {
                break;
            }
        }
    }
    if (err == ESP_OK && pk_client) {
        pk_send_status(&r, pk_client);  /* answers without a body (e.g. 204) */
        esp_timer_start_once(pk_idle, PK_IDLE_US);
    }
    xSemaphoreGive(pk_lock);
    return err != ESP_OK ? err : r.err;
}

/* ---------- through the relay ---------- */

static void relay_close(route_t route)
{
    if (relay_client[route]) {
        esp_http_client_cleanup(relay_client[route]);
        relay_client[route] = NULL;
    }
}

/* One request to the relay on `route` (kept-open connection); status, -1 if unreachable */
static int relay_get(route_t route, const char *path, int timeout_ms, response_t *r)
{
    char base[URL_MAX], secret[REF_MAX], url[URL_MAX + 32], auth[REF_MAX + 8];
    xSemaphoreTake(lock, portMAX_DELAY);
    strlcpy(base, relay_url[route], sizeof(base));
    strlcpy(secret, relay_secret, sizeof(secret));
    xSemaphoreGive(lock);
    size_t n = strlen(base);
    while (n && base[n - 1] == '/') {
        base[--n] = 0;
    }
    snprintf(url, sizeof(url), "%s%s", base, path);
    snprintf(auth, sizeof(auth), "Bearer %s", secret);

    if (!relay_client[route]) {
        esp_http_client_config_t config = {
            .url = url,
            .crt_bundle_attach = esp_crt_bundle_attach,     /* used for https:// only */
            .timeout_ms = timeout_ms,
            .user_agent = USER_AGENT,
            .event_handler = on_event,
            .keep_alive_enable = true,
        };
        relay_client[route] = esp_http_client_init(&config);
        if (!relay_client[route]) {
            return -1;
        }
    }
    esp_http_client_handle_t c = relay_client[route];
    esp_http_client_set_url(c, url);
    esp_http_client_set_timeout_ms(c, timeout_ms);
    esp_http_client_set_header(c, "Authorization", auth);
    esp_http_client_set_user_data(c, r);
    esp_err_t err = esp_http_client_perform(c);
    esp_http_client_set_user_data(c, NULL);
    if (err != ESP_OK) {
        relay_close(route);             /* start afresh next time */
        return -1;
    }
    return esp_http_client_get_status_code(c);
}

/* Wait at the relay for the next front. False if it couldn't be used. */
static bool relay_wait(void)
{
    bool have_home, have_net;
    xSemaphoreTake(lock, portMAX_DELAY);
    have_home = relay_url[ROUTE_HOME][0] != 0;
    have_net = relay_url[ROUTE_NET][0] != 0;
    xSemaphoreGive(lock);

    /* Home when it answers quickly (we're on the home network), else internet */
    route_t route = ROUTE_NET;
    for (int i = 0; have_home && route == ROUTE_NET && i < home_tries; i++) {
        if (i) {
            vTaskDelay(pdMS_TO_TICKS(1000));
        }
        response_t probe = { 0 };
        int status = relay_client[ROUTE_HOME] ? 200     /* it worked last time */
                     : relay_get(ROUTE_HOME, "/health", HOME_PROBE_MS, &probe);
        free(probe.body);
        if (status == 200) {
            route = ROUTE_HOME;
        }
    }
    home_tries = 1;
    if (route == ROUTE_NET && !have_net) {
        set_text(relay_error, sizeof(relay_error), "the relay's home address isn't reachable from here");
        return false;
    }
    if (route == ROUTE_HOME) {
        relay_close(ROUTE_NET);         /* free the TLS session while at home */
    }

    char path[32];
    snprintf(path, sizeof(path), "/front?since=%d", relay_seq);
    response_t r = { 0 };
    int status = relay_get(route, path, RELAY_WAIT_MS, &r);
    if (status != 200) {
        set_text(relay_error, sizeof(relay_error),
                 status == 401 ? "the relay didn't accept the secret"
                 : status < 0 ? (route == ROUTE_HOME ? "lost the relay at home" : "couldn't reach the relay")
                 : "unexpected answer from the relay");
        free(r.body);
        return false;
    }
    cJSON *root = r.body ? cJSON_Parse(r.body) : NULL;
    free(r.body);
    const cJSON *seq = cJSON_GetObjectItem(root, "seq");
    if (!cJSON_IsNumber(seq)) {
        cJSON_Delete(root);
        set_text(relay_error, sizeof(relay_error), "unexpected answer from the relay");
        return false;
    }
    set_text(relay_error, sizeof(relay_error), "");
    xSemaphoreTake(lock, portMAX_DELAY);
    relay_seen = (uint32_t)time(NULL);
    bool new_route = relay_via != (int)route;
    relay_via = route;
    xSemaphoreGive(lock);
    if (new_route) {
        ESP_LOGI(TAG, "using the relay's %s address", ROUTE_NAMES[route]);
    }
    if (seq->valueint != relay_seq) {
        relay_seq = seq->valueint;
        apply((uint32_t)cJSON_GetNumberValue(cJSON_GetObjectItem(root, "time")), cJSON_GetObjectItem(root, "members"));
    }
    cJSON_Delete(root);
    return true;
}

/* ---------- time zone ---------- */

typedef struct {
    int status;
    int len;
    char body[1024];                    /* system settings are ~300 bytes */
} small_response_t;

static esp_err_t small_status(int status, void *ctx)
{
    ((small_response_t *)ctx)->status = status;
    return ESP_OK;
}

static esp_err_t small_data(const char *data, int len, void *ctx)
{
    small_response_t *r = ctx;
    if (r->len + len >= sizeof(r->body)) {
        return ESP_ERR_NO_MEM;
    }
    memcpy(r->body + r->len, data, len);
    r->len += len;
    r->body[r->len] = 0;
    return ESP_OK;
}

/* Read the system's time zone from PluralKit; true if it was answered */
static bool check_timezone(void)
{
    xSemaphoreTake(lock, portMAX_DELAY);
    bool token = ref[0] && !is_system_id(ref);
    xSemaphoreGive(lock);
    if (!token) {
        return true;                    /* the settings are private: needs the token */
    }
    small_response_t *r = calloc(1, sizeof(*r));
    if (!r) {
        return false;
    }
    esp_err_t err = pksync_pk_request("GET", "/settings", NULL, small_status, small_data, r);
    if (err != ESP_OK || r->status != 200) {
        ESP_LOGW(TAG, "time zone: PluralKit answered %d (%s)", r->status, esp_err_to_name(err));
        free(r);
        return false;
    }
    cJSON *root = cJSON_Parse(r->body);
    free(r);
    const cJSON *zone = cJSON_GetObjectItem(root, "timezone");
    if (cJSON_IsString(zone)) {
        zone_from_pluralkit(zone->valuestring);
    }
    cJSON_Delete(root);
    return true;
}

/* ---------- task ---------- */

static void sync_task(void *arg)
{
    uint32_t last_direct = 0, last_timezone = 0;
    while (1) {
        if (settings_changed) {
            settings_changed = false;
            last_timezone = 0;          /* the token may have changed */
            relay_close(ROUTE_HOME);
            relay_close(ROUTE_NET);
            relay_seq = -1;
            last_direct = 0;
        }
        if (network_changed) {
            /* New network (e.g. home Wi-Fi -> hotspot): the old connections
             * are dead, and the home address may or may not be reachable now.
             * Ask afresh straight away, in case a switch came in meanwhile. */
            network_changed = false;
            relay_close(ROUTE_HOME);
            relay_close(ROUTE_NET);
            relay_seq = -1;
            home_tries = 3;             /* the first moments on a network can be patchy */
        }
        bool relay;
        xSemaphoreTake(lock, portMAX_DELAY);
        relay = relay_secret[0] && (relay_url[ROUTE_HOME][0] || relay_url[ROUTE_NET][0]);
        xSemaphoreGive(lock);
        if (wifi_get_state() != WIFI_CONNECTED || !wifi_clock_set()) {
            relay_close(ROUTE_HOME);
            relay_close(ROUTE_NET);
            ulTaskNotifyTake(pdTRUE, pdMS_TO_TICKS(5000));
            continue;
        }
        uint32_t ms = xTaskGetTickCount() * portTICK_PERIOD_MS;
        if ((!last_timezone || ms - last_timezone >= TZ_CHECK_MS) && check_timezone()) {
            last_timezone = ms ? ms : 1;
        }
        if (relay && relay_wait()) {
            continue;                   /* straight back to waiting */
        }
        /* No relay, or it can't be reached: check PluralKit directly now and then */
        uint32_t now = xTaskGetTickCount() * portTICK_PERIOD_MS;
        if (!last_direct || now - last_direct >= POLL_MS) {
            check_direct();
            last_direct = now ? now : 1;
        }
        ulTaskNotifyTake(pdTRUE, pdMS_TO_TICKS(relay ? RELAY_RETRY_MS : POLL_MS));
    }
}

/* Joined a network (ESP-IDF's event task): wake the sync instead of letting it
 * sit out a retry delay */
static void on_got_ip(void *arg, esp_event_base_t base, int32_t id, void *data)
{
    network_changed = true;
    xTaskNotifyGive(task);
}

static void load_str(nvs_handle_t nvs, const char *key, char *dst, size_t size)
{
    if (nvs_get_str(nvs, key, dst, &size) != ESP_OK) {
        dst[0] = 0;
    }
}

void pksync_start(void)
{
    lock = xSemaphoreCreateMutex();
    nvs_handle_t nvs;
    if (nvs_open(NVS_NAMESPACE, NVS_READONLY, &nvs) == ESP_OK) {
        load_str(nvs, "pk_ref", ref, sizeof(ref));
        load_str(nvs, "pk_secret", relay_secret, sizeof(relay_secret));
        for (int i = 0; i < ROUTE_COUNT; i++) {
            load_str(nvs, ROUTE_KEYS[i], relay_url[i], sizeof(relay_url[i]));
        }
        nvs_close(nvs);
    }
    ESP_LOGI(TAG, "direct: %s; relay: %s", !ref[0] ? "off" : is_system_id(ref) ? "system ID" : "token",
             relay_secret[0] ? "on" : "off");
    /* TLS needs a big stack. Lowest priority: setting up a TLS session is
     * seconds of maths, which mustn't hold up anything else (or the watchdog) */
    xTaskCreate(sync_task, "pksync", 8192, NULL, tskIDLE_PRIORITY, &task);
    pk_lock = xSemaphoreCreateMutex();
    const esp_timer_create_args_t idle = { .callback = pk_close, .name = "pk_idle" };
    esp_timer_create(&idle, &pk_idle);
    esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, on_got_ip, NULL);
}

static bool printable(const char *s, size_t max)
{
    size_t n = strlen(s);
    for (size_t i = 0; i < n; i++) {
        if (!isgraph((unsigned char)s[i])) {
            return false;
        }
    }
    return n < max;
}

static bool valid_url(const char *s)
{
    return !s[0] || (printable(s, URL_MAX) && (strncmp(s, "http://", 7) == 0 || strncmp(s, "https://", 8) == 0));
}

esp_err_t pksync_set(const char *new_ref, const char *home, const char *net, const char *secret)
{
    if ((new_ref && (!printable(new_ref, REF_MAX) || (new_ref[0] && strlen(new_ref) < 5)))
            || (home && !valid_url(home)) || (net && !valid_url(net))
            || (secret && !printable(secret, REF_MAX))) {
        return ESP_ERR_INVALID_ARG;
    }
    const char *values[] = { new_ref, home, net, secret };
    const char *keys[] = { "pk_ref", ROUTE_KEYS[ROUTE_HOME], ROUTE_KEYS[ROUTE_NET], "pk_secret" };
    nvs_handle_t nvs;
    esp_err_t err = nvs_open(NVS_NAMESPACE, NVS_READWRITE, &nvs);
    if (err != ESP_OK) {
        return err;
    }
    for (int i = 0; i < 4 && err == ESP_OK; i++) {
        if (!values[i]) {
            continue;                   /* not given: keep */
        }
        err = values[i][0] ? nvs_set_str(nvs, keys[i], values[i]) : nvs_erase_key(nvs, keys[i]);
        if (err == ESP_ERR_NVS_NOT_FOUND) {
            err = ESP_OK;               /* removing what wasn't there */
        }
    }
    if (err == ESP_OK) {
        err = nvs_commit(nvs);
    }
    nvs_close(nvs);
    if (err != ESP_OK) {
        return err;
    }
    xSemaphoreTake(lock, portMAX_DELAY);
    if (new_ref) {
        strlcpy(ref, new_ref, sizeof(ref));
        checked = 0;
        error[0] = 0;
    }
    if (home) {
        strlcpy(relay_url[ROUTE_HOME], home, sizeof(relay_url[ROUTE_HOME]));
    }
    if (net) {
        strlcpy(relay_url[ROUTE_NET], net, sizeof(relay_url[ROUTE_NET]));
    }
    if (secret) {
        strlcpy(relay_secret, secret, sizeof(relay_secret));
    }
    if (home || net || secret) {
        relay_seen = 0;
        relay_via = -1;
        relay_error[0] = 0;
    }
    xSemaphoreGive(lock);
    ESP_LOGI(TAG, "settings changed");
    settings_changed = true;
    xTaskNotifyGive(task);              /* use them straight away (or after the current wait) */
    return ESP_OK;
}

char *pksync_status_json(void)
{
    cJSON *root = cJSON_CreateObject();
    xSemaphoreTake(lock, portMAX_DELAY);
    bool system = is_system_id(ref);
    cJSON_AddBoolToObject(root, "set", ref[0] != 0);
    cJSON_AddBoolToObject(root, "token", ref[0] && !system);
    cJSON_AddStringToObject(root, "system", system ? ref : "");
    cJSON_AddNumberToObject(root, "checked", checked);
    cJSON_AddNumberToObject(root, "synced", synced);
    cJSON_AddStringToObject(root, "error", error);
    cJSON_AddStringToObject(root, "relay_home", relay_url[ROUTE_HOME]);
    cJSON_AddStringToObject(root, "relay_net", relay_url[ROUTE_NET]);
    cJSON_AddBoolToObject(root, "relay_secret", relay_secret[0] != 0);
    cJSON_AddNumberToObject(root, "relay_seen", relay_seen);
    cJSON_AddStringToObject(root, "relay_via", relay_via >= 0 ? ROUTE_NAMES[relay_via] : "");
    cJSON_AddStringToObject(root, "relay_error", relay_error);
    xSemaphoreGive(lock);
    char *text = cJSON_PrintUnformatted(root);
    cJSON_Delete(root);
    return text;
}
