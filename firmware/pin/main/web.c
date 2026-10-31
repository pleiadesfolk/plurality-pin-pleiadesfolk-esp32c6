/*
 * Web server for the dashboard.
 *
 *   GET  /                 the dashboard page (dashboard/index.html, built in)
 *   GET  /fonts/NAME.ttf   fonts for drawing text pictures in the browser
 *                          (served by the pin, so they work without internet)
 *   GET  /api/state        system, members, current front (store_send_state)
 *   PUT  /api/members      replace the member list (JSON)
 *   PUT  /api/switches     replace front history (raw store_switch_t records)
 *   GET  /api/switches     front history, same format
 *   POST /api/front        record a switch now: {"members": [index, ...]}
 *   PUT  /api/card?id=ID&kind=K  picture for member ID; K = card (default),
 *                          label, full or side (see store_picture_t)
 *   GET  /api/card?id=ID&kind=K  the same picture back (for the dashboard's previews)
 *   GET  /api/photos       which members have photos, free fast slots (store_photos_json)
 *   DELETE /api/member?index=N  delete member N (also from front history)
 *   GET  /api/wifi         saved Wi-Fi networks (no passwords) and the pin's address
 *   PUT  /api/wifi         replace the saved networks (see wifi_set_networks_json)
 *   GET  /api/wifi/scan    networks in range (see wifi_scan_json)
 *   GET/PUT /api/pk        PluralKit sync status / settings (see pksync.h)
 *   GET  /api/pk/switches?before=T&limit=N  PluralKit's switches before unix time T
 *                          (newest first, as PluralKit sends them), asked with the pin's token
 *   POST /api/pk/switches  {"timestamp": unix, "members": [PluralKit ids]}: log a
 *                          switch in PluralKit (needs the token; for "Sync with PluralKit")
 *   DELETE /api/pk/switches?id=ID  delete switch ID in PluralKit (needs the token)
 *   GET  /api/battery      battery log (raw status_log_entry_t records, oldest first)
 *   DELETE /api/battery    clear the battery log
 *
 * Login (auth.h): once a dashboard password is set, every /api/ route except
 * these needs the session cookie ("pin_session", SameSite=Strict, so other
 * websites can't make the phone send requests with it):
 *   GET  /api/auth         {"password": set?, "logged_in": bool}
 *   POST /api/login        {"password"} -> session cookie
 *   POST /api/logout       end this session
 *   PUT  /api/password     {"password": new, "" = remove} (needs a session if one is set)
 * The page itself and the fonts are always served (the page shows the login).
 */

#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "esp_log.h"
#include "esp_http_server.h"
#include "cJSON.h"
#include "status.h"
#include "photos.h"
#include "store.h"
#include "wifi.h"
#include "pksync.h"
#include "auth.h"
#include "web.h"

static const char *TAG = "web";

#define MAX_JSON_BYTES  (64 * 1024)
#define CHUNK           2048

extern const char index_html_start[] asm("_binary_index_html_start");
extern const char index_html_end[]   asm("_binary_index_html_end");
#define FONT(sym) extern const uint8_t sym##_start[] asm("_binary_" #sym "_start"); \
                  extern const uint8_t sym##_end[] asm("_binary_" #sym "_end");
FONT(PlaywriteUSTrad_Regular_ttf)
FONT(Inter_Medium_ttf)
FONT(Inter_SemiBold_ttf)
FONT(Inter_Bold_ttf)
FONT(IBMPlexMono_Regular_ttf)
FONT(IBMPlexMono_Medium_ttf)
FONT(IBMPlexMono_SemiBold_ttf)

static const struct {
    const char *uri;
    const uint8_t *start, *end;
} fonts[] = {
#define FONT_FILE(name, sym) { "/fonts/" name, sym##_start, sym##_end }
    FONT_FILE("PlaywriteUSTrad-Regular.ttf", PlaywriteUSTrad_Regular_ttf),
    FONT_FILE("Inter-Medium.ttf", Inter_Medium_ttf),
    FONT_FILE("Inter-SemiBold.ttf", Inter_SemiBold_ttf),
    FONT_FILE("Inter-Bold.ttf", Inter_Bold_ttf),
    FONT_FILE("IBMPlexMono-Regular.ttf", IBMPlexMono_Regular_ttf),
    FONT_FILE("IBMPlexMono-Medium.ttf", IBMPlexMono_Medium_ttf),
    FONT_FILE("IBMPlexMono-SemiBold.ttf", IBMPlexMono_SemiBold_ttf),
};

/* ---------- helpers ---------- */

static esp_err_t send_error(httpd_req_t *req, const char *status, const char *message)
{
    httpd_resp_set_status(req, status);
    httpd_resp_set_type(req, "text/plain");
    return httpd_resp_sendstr(req, message);
}

static esp_err_t send_ok(httpd_req_t *req)
{
    httpd_resp_set_type(req, "application/json");
    return httpd_resp_sendstr(req, "{\"ok\":true}");
}

/* Read a whole (small) request body as a string; free() the result */
static char *read_body(httpd_req_t *req)
{
    if (req->content_len > MAX_JSON_BYTES) {
        return NULL;
    }
    char *buf = malloc(req->content_len + 1);
    size_t got = 0;
    while (buf && got < req->content_len) {
        int n = httpd_req_recv(req, buf + got, req->content_len - got);
        if (n == HTTPD_SOCK_ERR_TIMEOUT) {
            continue;
        }
        if (n <= 0) {
            free(buf);
            return NULL;
        }
        got += n;
    }
    if (buf) {
        buf[got] = '\0';
    }
    return buf;
}

/* Stream a request body into begin/write/end functions without holding it in RAM */
static esp_err_t receive_stream(httpd_req_t *req, esp_err_t (*write)(const void *, size_t),
                                esp_err_t (*end)(bool))
{
    char *buf = malloc(CHUNK);
    size_t left = req->content_len;
    bool ok = buf != NULL;
    while (ok && left > 0) {
        int n = httpd_req_recv(req, buf, left < CHUNK ? left : CHUNK);
        if (n == HTTPD_SOCK_ERR_TIMEOUT) {
            continue;
        }
        ok = n > 0 && write(buf, n) == ESP_OK;
        left -= n > 0 ? n : 0;
    }
    free(buf);
    if (end(ok) != ESP_OK) {
        return send_error(req, "400 Bad Request", "upload rejected");
    }
    return send_ok(req);
}

/* ---------- handlers ---------- */

static esp_err_t get_index(httpd_req_t *req)
{
    httpd_resp_set_type(req, "text/html; charset=utf-8");
    return httpd_resp_send(req, index_html_start, index_html_end - index_html_start);
}

static esp_err_t get_font(httpd_req_t *req)
{
    for (int i = 0; i < sizeof(fonts) / sizeof(fonts[0]); i++) {
        if (strcmp(req->uri, fonts[i].uri) == 0) {
            httpd_resp_set_type(req, "font/ttf");
            httpd_resp_set_hdr(req, "Cache-Control", "max-age=86400");
            return httpd_resp_send(req, (const char *)fonts[i].start, fonts[i].end - fonts[i].start);
        }
    }
    return send_error(req, "404 Not Found", "no such font");
}

/* Collects small pieces into CHUNK-sized chunks of a chunked response */
typedef struct {
    httpd_req_t *req;
    char *buf;
    size_t used;
} chunker_t;

static bool chunk_out(const char *text, size_t len, void *ctx)
{
    chunker_t *c = ctx;
    while (len) {
        size_t n = len < CHUNK - c->used ? len : CHUNK - c->used;
        memcpy(c->buf + c->used, text, n);
        c->used += n;
        text += n;
        len -= n;
        if (c->used == CHUNK) {
            if (httpd_resp_send_chunk(c->req, c->buf, c->used) != ESP_OK) {
                return false;
            }
            c->used = 0;
        }
    }
    return true;
}

static esp_err_t get_state(httpd_req_t *req)
{
    chunker_t c = { .req = req, .buf = malloc(CHUNK) };
    if (!c.buf) {
        return send_error(req, "500 Internal Server Error", "out of memory");
    }
    /* Plus device readings (battery voltage, for checking the battery reading) */
    char extra[40];
    snprintf(extra, sizeof(extra), ",\"battery_volts\":%.3f", status_battery_volts());
    httpd_resp_set_type(req, "application/json");
    httpd_resp_set_hdr(req, "Cache-Control", "no-store");
    bool ok = store_send_state(chunk_out, &c, extra);
    if (ok && c.used) {
        ok = httpd_resp_send_chunk(req, c.buf, c.used) == ESP_OK;
    }
    free(c.buf);
    return ok ? httpd_resp_send_chunk(req, NULL, 0) : ESP_FAIL;
}

static esp_err_t put_members(httpd_req_t *req)
{
    char *body = read_body(req);
    if (!body) {
        return send_error(req, "400 Bad Request", "body missing or too big");
    }
    esp_err_t err = store_set_members_json(body);
    free(body);
    if (err == ESP_ERR_INVALID_ARG) {
        return send_error(req, "400 Bad Request", "invalid member list");
    }
    return err == ESP_OK ? send_ok(req) : send_error(req, "500 Internal Server Error", "couldn't save the members - nothing was changed");
}

static esp_err_t put_switches(httpd_req_t *req)
{
    if (store_switches_begin() != ESP_OK) {
        return send_error(req, "500 Internal Server Error", "storage error");
    }
    return receive_stream(req, store_switches_write, store_switches_end);
}

/* Send a file as it is (an empty answer if it doesn't exist) */
static esp_err_t send_file(httpd_req_t *req, const char *path)
{
    FILE *f = fopen(path, "rb");
    httpd_resp_set_type(req, "application/octet-stream");
    httpd_resp_set_hdr(req, "Cache-Control", "no-store");
    if (!f) {
        return httpd_resp_send(req, NULL, 0);
    }
    char *buf = malloc(CHUNK);
    size_t n;
    while (buf && (n = fread(buf, 1, CHUNK, f)) > 0) {
        if (httpd_resp_send_chunk(req, buf, n) != ESP_OK) {
            break;
        }
    }
    free(buf);
    fclose(f);
    return httpd_resp_send_chunk(req, NULL, 0);
}

static esp_err_t get_switches(httpd_req_t *req)
{
    return send_file(req, STORE_SWITCHES_FILE);
}

static esp_err_t get_battery(httpd_req_t *req)
{
    return send_file(req, STATUS_BATTERY_LOG);
}

static esp_err_t delete_battery(httpd_req_t *req)
{
    status_battery_log_clear();
    return send_ok(req);
}

static esp_err_t post_front(httpd_req_t *req)
{
    char *body = read_body(req);
    cJSON *root = body ? cJSON_Parse(body) : NULL;
    free(body);
    const cJSON *list = cJSON_GetObjectItem(root, "members");
    if (!cJSON_IsArray(list)) {
        cJSON_Delete(root);
        return send_error(req, "400 Bad Request", "expected {\"members\": [...]}");
    }
    uint16_t members[STORE_FRONT_MAX];
    int count = 0;
    const cJSON *item;
    cJSON_ArrayForEach(item, list) {
        if (count < STORE_FRONT_MAX && cJSON_IsNumber(item)) {
            members[count++] = (uint16_t)item->valueint;
        }
    }
    cJSON_Delete(root);
    return store_add_switch(members, count) == ESP_OK ? send_ok(req)
           : send_error(req, "400 Bad Request", "unknown member");
}

/* Parse ?id=...&kind=... (kind defaults to card); false if missing or unknown */
static bool picture_query(httpd_req_t *req, char *id, size_t id_size, store_picture_t *kind)
{
    static const char *const kinds[] = { "card", "label", "full", "side" };
    char query[48], kind_name[8] = "card";
    if (httpd_req_get_url_query_str(req, query, sizeof(query)) != ESP_OK
            || httpd_query_key_value(query, "id", id, id_size) != ESP_OK) {
        return false;
    }
    httpd_query_key_value(query, "kind", kind_name, sizeof(kind_name));
    for (int i = 0; i < 4; i++) {
        if (strcmp(kind_name, kinds[i]) == 0) {
            *kind = (store_picture_t)i;
            return true;
        }
    }
    return false;
}

static esp_err_t get_card(httpd_req_t *req)
{
    char id[16], path[64];
    store_picture_t kind;
    if (!picture_query(req, id, sizeof(id), &kind)) {
        return send_error(req, "404 Not Found", "no such picture");
    }
    if (kind >= STORE_PICTURE_FULL) {       /* photos normally live in a flash slot */
        size_t len;
        esp_partition_mmap_handle_t map;
        const void *p = photos_map(id, kind == STORE_PICTURE_SIDE ? PHOTO_SIDE : PHOTO_FULL, &len, &map);
        if (p) {
            httpd_resp_set_type(req, "application/octet-stream");
            httpd_resp_set_hdr(req, "Cache-Control", "no-store");
            esp_err_t err = httpd_resp_send(req, p, len);
            photos_unmap(map);
            return err;
        }
    }
    if (!store_picture_file(id, kind, path, sizeof(path))) {
        return send_error(req, "404 Not Found", "no such picture");
    }
    FILE *f = fopen(path, "rb");
    if (!f) {
        return send_error(req, "404 Not Found", "no such picture");
    }
    httpd_resp_set_type(req, "application/octet-stream");
    httpd_resp_set_hdr(req, "Cache-Control", "no-store");
    char *buf = malloc(CHUNK);
    size_t n;
    while (buf && (n = fread(buf, 1, CHUNK, f)) > 0) {
        if (httpd_resp_send_chunk(req, buf, n) != ESP_OK) {
            break;
        }
    }
    free(buf);
    fclose(f);
    return httpd_resp_send_chunk(req, NULL, 0);
}

static esp_err_t put_card(httpd_req_t *req)
{
    char id[16];
    store_picture_t kind;
    if (!picture_query(req, id, sizeof(id), &kind)) {
        return send_error(req, "400 Bad Request", "invalid id or kind");
    }
    esp_err_t err = store_picture_begin(id, kind);
    if (err == ESP_ERR_NO_MEM) {
        return send_error(req, "507 Insufficient Storage", "all the fast photo slots are in use");
    } else if (err != ESP_OK) {
        return send_error(req, "400 Bad Request", "couldn't store that picture");
    }
    return receive_stream(req, store_picture_write, store_picture_end);
}

static esp_err_t get_photos(httpd_req_t *req)
{
    char *json = store_photos_json();
    if (!json) {
        return send_error(req, "500 Internal Server Error", "out of memory");
    }
    httpd_resp_set_type(req, "application/json");
    httpd_resp_set_hdr(req, "Cache-Control", "no-store");
    esp_err_t err = httpd_resp_sendstr(req, json);
    free(json);
    return err;
}

static esp_err_t delete_member(httpd_req_t *req)
{
    char query[32], value[8];
    if (httpd_req_get_url_query_str(req, query, sizeof(query)) != ESP_OK
            || httpd_query_key_value(query, "index", value, sizeof(value)) != ESP_OK) {
        return send_error(req, "400 Bad Request", "missing index");
    }
    return store_delete_member(atoi(value)) == ESP_OK ? send_ok(req)
           : send_error(req, "400 Bad Request", "could not delete member");
}

static esp_err_t get_wifi(httpd_req_t *req)
{
    char *json = wifi_networks_json();
    if (!json) {
        return send_error(req, "500 Internal Server Error", "out of memory");
    }
    httpd_resp_set_type(req, "application/json");
    httpd_resp_set_hdr(req, "Cache-Control", "no-store");
    esp_err_t err = httpd_resp_sendstr(req, json);
    free(json);
    return err;
}

static esp_err_t get_wifi_scan(httpd_req_t *req)
{
    char *json = wifi_scan_json();
    if (!json) {
        return send_error(req, "503 Service Unavailable", "the pin can't scan right now - try again in a moment");
    }
    httpd_resp_set_type(req, "application/json");
    httpd_resp_set_hdr(req, "Cache-Control", "no-store");
    esp_err_t err = httpd_resp_sendstr(req, json);
    free(json);
    return err;
}

static esp_err_t get_pk(httpd_req_t *req)
{
    char *json = pksync_status_json();
    if (!json) {
        return send_error(req, "500 Internal Server Error", "out of memory");
    }
    httpd_resp_set_type(req, "application/json");
    esp_err_t err = httpd_resp_sendstr(req, json);
    free(json);
    return err;
}

/* {"ref", "home", "net", "secret"}: any of them; missing = keep, "" = clear (see pksync_set) */
static esp_err_t put_pk(httpd_req_t *req)
{
    char *body = read_body(req);
    cJSON *root = body ? cJSON_Parse(body) : NULL;
    free(body);
    const char *ref = cJSON_GetStringValue(cJSON_GetObjectItem(root, "ref"));
    const char *home = cJSON_GetStringValue(cJSON_GetObjectItem(root, "home"));
    const char *net = cJSON_GetStringValue(cJSON_GetObjectItem(root, "net"));
    const char *secret = cJSON_GetStringValue(cJSON_GetObjectItem(root, "secret"));
    esp_err_t err = root ? pksync_set(ref, home, net, secret) : ESP_ERR_INVALID_ARG;
    cJSON_Delete(root);
    return err == ESP_OK ? send_ok(req)
           : send_error(req, "400 Bad Request",
                        "expected a system ID (5-6 letters) or token, addresses starting http:// or https://, no spaces");
}

/* Passing PluralKit's answer on: same status, same body */
static bool pk_answered;                /* PluralKit's status has been passed on */

static esp_err_t pk_status(int status, void *req)
{
    static char text[32];
    pk_answered = true;
    snprintf(text, sizeof(text), "%d PluralKit", status);
    httpd_resp_set_status(req, text);
    httpd_resp_set_type(req, "application/json");
    return ESP_OK;
}

static esp_err_t pk_data(const char *data, int len, void *req)
{
    return httpd_resp_send_chunk(req, data, len);
}

static esp_err_t pk_failed(httpd_req_t *req, esp_err_t err)
{
    return send_error(req, err == ESP_ERR_INVALID_STATE ? "409 Conflict" : err == ESP_ERR_NOT_SUPPORTED ? "403 Forbidden"
                      : "502 Bad Gateway",
                      err == ESP_ERR_INVALID_STATE ? "save your PluralKit token on the Import tab first"
                      : err == ESP_ERR_NOT_SUPPORTED ? "changing PluralKit needs your token, not just the system ID"
                      : "couldn't reach PluralKit");
}

/* "2026-11-01T02:00:00Z" for unix time t */
static void iso_time(time_t t, char *buf, size_t size)
{
    struct tm tm;
    gmtime_r(&t, &tm);
    strftime(buf, size, "%Y-%m-%dT%H:%M:%SZ", &tm);
}

static esp_err_t get_pk_switches(httpd_req_t *req)
{
    char query[64] = "", value[16], path[96], when[24] = "";
    httpd_req_get_url_query_str(req, query, sizeof(query));
    int limit = httpd_query_key_value(query, "limit", value, sizeof(value)) == ESP_OK ? atoi(value) : 100;
    limit = limit < 1 ? 1 : limit > 100 ? 100 : limit;
    if (httpd_query_key_value(query, "before", value, sizeof(value)) == ESP_OK && atoll(value) > 0) {
        iso_time((time_t)atoll(value), when, sizeof(when));
    }
    snprintf(path, sizeof(path), "/switches?limit=%d%s%s", limit, when[0] ? "&before=" : "", when);
    pk_answered = false;
    esp_err_t err = pksync_pk_request("GET", path, NULL, pk_status, pk_data, req);
    return pk_answered ? httpd_resp_send_chunk(req, NULL, 0) : pk_failed(req, err);
}

static esp_err_t post_pk_switch(httpd_req_t *req)
{
    char *body = read_body(req);
    cJSON *root = body ? cJSON_Parse(body) : NULL;
    free(body);
    const cJSON *when = cJSON_GetObjectItem(root, "timestamp");
    const cJSON *members = cJSON_GetObjectItem(root, "members");
    if (!cJSON_IsNumber(when) || !cJSON_IsArray(members)) {
        cJSON_Delete(root);
        return send_error(req, "400 Bad Request", "expected {\"timestamp\": unix time, \"members\": [ids]}");
    }
    char iso[24];
    iso_time((time_t)when->valuedouble, iso, sizeof(iso));
    cJSON *out = cJSON_CreateObject();
    cJSON_AddStringToObject(out, "timestamp", iso);
    cJSON_AddItemToObject(out, "members", cJSON_Duplicate(members, true));
    char *json = cJSON_PrintUnformatted(out);
    cJSON_Delete(out);
    cJSON_Delete(root);
    if (!json) {
        return send_error(req, "500 Internal Server Error", "out of memory");
    }
    pk_answered = false;
    esp_err_t err = pksync_pk_request("POST", "/switches", json, pk_status, pk_data, req);
    free(json);
    return pk_answered ? httpd_resp_send_chunk(req, NULL, 0) : pk_failed(req, err);
}

static esp_err_t delete_pk_switch(httpd_req_t *req)
{
    char query[80] = "", id[48], path[64];
    httpd_req_get_url_query_str(req, query, sizeof(query));
    bool ok = httpd_query_key_value(query, "id", id, sizeof(id)) == ESP_OK && id[0];
    for (char *c = id; ok && *c; c++) {
        ok = isalnum((unsigned char)*c) || *c == '-';   /* PluralKit switch ids are UUIDs */
    }
    if (!ok) {
        return send_error(req, "400 Bad Request", "expected ?id=<switch id>");
    }
    snprintf(path, sizeof(path), "/switches/%s", id);
    pk_answered = false;
    esp_err_t err = pksync_pk_request("DELETE", path, NULL, pk_status, pk_data, req);
    return pk_answered ? httpd_resp_send_chunk(req, NULL, 0) : pk_failed(req, err);
}

/* ---------- login ---------- */

#define COOKIE_NAME     "pin_session"
#define COOKIE_AGE      (400 * 24 * 3600)   /* about as long as browsers allow */

/* The session token from the Cookie header, or "" */
static void session_token(httpd_req_t *req, char *token)
{
    token[0] = 0;
    char cookies[512];
    if (httpd_req_get_hdr_value_str(req, "Cookie", cookies, sizeof(cookies)) != ESP_OK) {
        return;
    }
    for (char *p = cookies; (p = strstr(p, COOKIE_NAME "=")); p++) {
        if (p == cookies || p[-1] == ' ' || p[-1] == ';') {
            strlcpy(token, p + strlen(COOKIE_NAME "="), AUTH_TOKEN_LEN + 1);
            token[strcspn(token, "; ")] = 0;
            return;
        }
    }
}

static bool logged_in(httpd_req_t *req)
{
    char token[AUTH_TOKEN_LEN + 1];
    session_token(req, token);
    return auth_session_ok(token);
}

/* Every protected route goes through here; user_ctx is the real handler */
static esp_err_t guarded(httpd_req_t *req)
{
    if (!logged_in(req)) {
        return send_error(req, "401 Unauthorized", "log in first");
    }
    return ((esp_err_t (*)(httpd_req_t *))req->user_ctx)(req);
}

/* Give the phone a session cookie (token "" clears it) */
static void set_cookie(httpd_req_t *req, const char *token, char *buf, size_t size)
{
    snprintf(buf, size, COOKIE_NAME "=%s; Path=/; Max-Age=%d; HttpOnly; SameSite=Strict",
             token, token[0] ? COOKIE_AGE : 0);
    httpd_resp_set_hdr(req, "Set-Cookie", buf);
}

static esp_err_t get_auth(httpd_req_t *req)
{
    char json[64];
    snprintf(json, sizeof(json), "{\"password\":%s,\"logged_in\":%s}",
             auth_password_set() ? "true" : "false", logged_in(req) ? "true" : "false");
    httpd_resp_set_type(req, "application/json");
    return httpd_resp_sendstr(req, json);
}

static esp_err_t post_login(httpd_req_t *req)
{
    char *body = read_body(req);
    cJSON *root = body ? cJSON_Parse(body) : NULL;
    free(body);
    const char *password = cJSON_GetStringValue(cJSON_GetObjectItem(root, "password"));
    char token[AUTH_TOKEN_LEN + 1], cookie[128];
    esp_err_t err = password ? auth_login(password, token) : ESP_ERR_INVALID_ARG;
    cJSON_Delete(root);
    if (err == ESP_ERR_INVALID_STATE) {
        return send_error(req, "429 Too Many Requests", "too many wrong passwords - wait 30 seconds");
    }
    if (err != ESP_OK) {
        return send_error(req, "401 Unauthorized", "wrong password");
    }
    set_cookie(req, token, cookie, sizeof(cookie));
    return send_ok(req);
}

static esp_err_t post_logout(httpd_req_t *req)
{
    char token[AUTH_TOKEN_LEN + 1], cookie[128];
    session_token(req, token);
    auth_logout(token);
    set_cookie(req, "", cookie, sizeof(cookie));
    return send_ok(req);
}

static esp_err_t put_password(httpd_req_t *req)
{
    char *body = read_body(req);
    cJSON *root = body ? cJSON_Parse(body) : NULL;
    free(body);
    const char *password = cJSON_GetStringValue(cJSON_GetObjectItem(root, "password"));
    char token[AUTH_TOKEN_LEN + 1] = "", cookie[128];
    esp_err_t err = password ? auth_set_password(password, token) : ESP_ERR_INVALID_ARG;
    cJSON_Delete(root);
    if (err != ESP_OK) {
        return send_error(req, "400 Bad Request", "the password must be 4 to 64 characters");
    }
    set_cookie(req, token, cookie, sizeof(cookie));
    return send_ok(req);
}

static esp_err_t put_wifi(httpd_req_t *req)
{
    char *body = read_body(req);
    if (!body) {
        return send_error(req, "400 Bad Request", "body missing or too big");
    }
    esp_err_t err = wifi_set_networks_json(body);
    free(body);
    return err == ESP_OK ? send_ok(req)
           : send_error(req, "400 Bad Request", "invalid network list (names up to 32 bytes, passwords 8-63 characters or none)");
}

/* ---------- start ---------- */

void web_start(void)
{
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    config.stack_size = 8192;           /* JSON handling needs more than the default */
    config.max_uri_handlers = 30;
    config.lru_purge_enable = true;     /* phones keep connections open; recycle them */
    config.uri_match_fn = httpd_uri_match_wildcard;   /* for the fonts route */
    config.recv_wait_timeout = 10;

    httpd_handle_t server;
    if (httpd_start(&server, &config) != ESP_OK) {
        ESP_LOGE(TAG, "could not start the web server");
        return;
    }

    static const httpd_uri_t routes[] = {
        { .uri = "/",              .method = HTTP_GET,  .handler = get_index },
        { .uri = "/fonts/*",       .method = HTTP_GET,  .handler = get_font },
        { .uri = "/api/state",     .method = HTTP_GET,  .handler = guarded, .user_ctx = get_state },
        { .uri = "/api/members",   .method = HTTP_PUT,  .handler = guarded, .user_ctx = put_members },
        { .uri = "/api/switches",  .method = HTTP_PUT,  .handler = guarded, .user_ctx = put_switches },
        { .uri = "/api/switches",  .method = HTTP_GET,  .handler = guarded, .user_ctx = get_switches },
        { .uri = "/api/front",     .method = HTTP_POST, .handler = guarded, .user_ctx = post_front },
        { .uri = "/api/card",      .method = HTTP_PUT,  .handler = guarded, .user_ctx = put_card },
        { .uri = "/api/card",      .method = HTTP_GET,  .handler = guarded, .user_ctx = get_card },
        { .uri = "/api/photos",    .method = HTTP_GET,  .handler = guarded, .user_ctx = get_photos },
        { .uri = "/api/member",    .method = HTTP_DELETE, .handler = guarded, .user_ctx = delete_member },
        { .uri = "/api/wifi",      .method = HTTP_GET,  .handler = guarded, .user_ctx = get_wifi },
        { .uri = "/api/wifi",      .method = HTTP_PUT,  .handler = guarded, .user_ctx = put_wifi },
        { .uri = "/api/wifi/scan", .method = HTTP_GET,  .handler = guarded, .user_ctx = get_wifi_scan },
        { .uri = "/api/pk",        .method = HTTP_GET,  .handler = guarded, .user_ctx = get_pk },
        { .uri = "/api/pk",        .method = HTTP_PUT,  .handler = guarded, .user_ctx = put_pk },
        { .uri = "/api/pk/switches", .method = HTTP_GET, .handler = guarded, .user_ctx = get_pk_switches },
        { .uri = "/api/pk/switches", .method = HTTP_POST, .handler = guarded, .user_ctx = post_pk_switch },
        { .uri = "/api/pk/switches", .method = HTTP_DELETE, .handler = guarded, .user_ctx = delete_pk_switch },
        { .uri = "/api/battery",   .method = HTTP_GET,  .handler = guarded, .user_ctx = get_battery },
        { .uri = "/api/battery",   .method = HTTP_DELETE, .handler = guarded, .user_ctx = delete_battery },
        { .uri = "/api/auth",      .method = HTTP_GET,  .handler = get_auth },
        { .uri = "/api/login",     .method = HTTP_POST, .handler = post_login },
        { .uri = "/api/logout",    .method = HTTP_POST, .handler = post_logout },
        { .uri = "/api/password",  .method = HTTP_PUT,  .handler = guarded, .user_ctx = put_password },
    };
    for (int i = 0; i < sizeof(routes) / sizeof(routes[0]); i++) {
        httpd_register_uri_handler(server, &routes[i]);
    }
    ESP_LOGI(TAG, "dashboard ready");
}
