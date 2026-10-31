/*
 * Wi-Fi: join one of the saved networks (station mode), reconnect forever if
 * it drops, and set the clock from the internet once connected. It can be
 * turned off on the Settings screen; that choice is kept in NVS.
 *
 * Saved networks: a list in NVS, managed from the dashboard (e.g. home Wi-Fi
 * and a phone's hotspot). wifi_credentials.h only provides the first entry
 * when the list doesn't exist yet. To connect, the pin scans and joins the
 * first saved network (in list order) that's in range; after a drop it scans
 * again, so it moves to whichever network is around. A network can be
 * switched off ("skip") on the dashboard: kept, but not joined.
 *
 * Runs in ESP-IDF's own Wi-Fi/event tasks. The UI only polls wifi_get_state()
 * from the LVGL task (status.c), so no LVGL calls happen here.
 *
 * The ESP32-C6 only has 2.4 GHz Wi-Fi: a 5 GHz-only network won't be found
 * (iPhone hotspot: turn on "Maximize Compatibility").
 */

#include <string.h>
#include <time.h>
#include <sys/time.h>
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/timers.h"
#include "esp_log.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "esp_netif_sntp.h"
#include "nvs.h"
#include "cJSON.h"
#include "wifi.h"

#if __has_include("wifi_credentials.h")
#include "wifi_credentials.h"
#else
#include "wifi_credentials.example.h"   /* empty: no first network */
#endif

static const char *TAG = "pin_wifi";   /* "wifi" is the driver's own (quietened) tag */

#define RETRY_DELAY_MS      5000        /* wait between reconnect attempts */
#define FAILS_BEFORE_FAILED 3           /* show "failed" after this many attempts in a row */
#define NTP_SERVER          "pool.ntp.org"
#define MAX_SCAN            20

#define NVS_NAMESPACE   "pin"
#define NVS_KEY_ON      "wifi_on"
#define NVS_KEY_NETS    "wifi_nets"

typedef struct {
    char ssid[33];
    char password[65];
    uint8_t flags;                      /* NET_* (one byte, so saved lists keep their layout) */
} network_t;

#define NET_SKIP    0x02                /* switched off: don't join it for now (0x01 was "share") */

static network_t nets[WIFI_MAX_NETWORKS];
static int net_count;
static SemaphoreHandle_t lock;          /* guards nets and the current connection's details */

static volatile wifi_state_t state = WIFI_OFF;
static int fails;
static TimerHandle_t retry_timer;
static bool sntp_started;
static volatile bool clock_set;         /* the clock has been set from the internet */
static bool started;                    /* the driver is initialised */
static volatile bool enabled = true;
static int current = -1;                /* network being joined / joined, index into nets */
static char current_ssid[33];
static esp_ip4_addr_t current_ip;

/* Scans requested by the dashboard (wifi_scan_json) */
static volatile bool scanning;          /* a scan is running */
static volatile bool list_wanted;       /* the dashboard is waiting for this scan's results */
static SemaphoreHandle_t list_ready;
static char *list_json;                 /* the results, handed to wifi_scan_json() */

/* ---------- saved networks ---------- */

static void save_networks(void)
{
    nvs_handle_t nvs;
    if (nvs_open(NVS_NAMESPACE, NVS_READWRITE, &nvs) == ESP_OK) {
        nvs_set_blob(nvs, NVS_KEY_NETS, nets, sizeof(network_t) * net_count);
        nvs_commit(nvs);
        nvs_close(nvs);
    }
}

static void load_networks(void)
{
    nvs_handle_t nvs;
    size_t size = sizeof(nets);
    bool found = false;
    if (nvs_open(NVS_NAMESPACE, NVS_READONLY, &nvs) == ESP_OK) {
        found = nvs_get_blob(nvs, NVS_KEY_NETS, nets, &size) == ESP_OK;
        nvs_close(nvs);
    }
    if (found) {
        net_count = size / sizeof(network_t);
    } else if (strlen(WIFI_SSID) > 0) {
        /* First start: the network from wifi_credentials.h */
        net_count = 1;
        strlcpy(nets[0].ssid, WIFI_SSID, sizeof(nets[0].ssid));
        strlcpy(nets[0].password, WIFI_PASSWORD, sizeof(nets[0].password));
        nets[0].flags = 0;
        save_networks();
    }
    ESP_LOGI(TAG, "%d saved network(s)", net_count);
}

/* ---------- connecting ---------- */

static void time_synced(struct timeval *tv)
{
    time_t now = tv->tv_sec;
    struct tm tm;
    localtime_r(&now, &tm);
    char buf[24];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &tm);
    ESP_LOGI(TAG, "clock set from the internet: %s", buf);
    clock_set = true;
}

static void start_scan(void)
{
    if (!enabled || net_count == 0 || scanning) {
        return;
    }
    scanning = esp_wifi_scan_start(NULL, false) == ESP_OK;
    if (!scanning) {
        xTimerStart(retry_timer, 0);
    }
}

/* Networks in range, strongest first, one entry per name (caller holds the lock) */
static char *networks_found_json(const wifi_ap_record_t *aps, int n)
{
    cJSON *root = cJSON_CreateObject();
    cJSON *list = cJSON_AddArrayToObject(root, "found");
    for (int k = 0; k < n; k++) {               /* the driver sorts by signal already */
        const char *ssid = (const char *)aps[k].ssid;
        bool dup = !ssid[0];                    /* hidden networks have no name */
        for (int j = 0; j < k && !dup; j++) {
            dup = strcmp(ssid, (const char *)aps[j].ssid) == 0;
        }
        if (dup) {
            continue;
        }
        bool saved = false;
        for (int i = 0; i < net_count; i++) {
            saved |= strcmp(nets[i].ssid, ssid) == 0;
        }
        cJSON *item = cJSON_CreateObject();
        cJSON_AddStringToObject(item, "ssid", ssid);
        cJSON_AddNumberToObject(item, "rssi", aps[k].rssi);
        cJSON_AddBoolToObject(item, "open", aps[k].authmode == WIFI_AUTH_OPEN);
        cJSON_AddBoolToObject(item, "saved", saved);
        cJSON_AddItemToArray(list, item);
    }
    char *json = cJSON_PrintUnformatted(root);
    cJSON_Delete(root);
    return json;
}

static void retry(TimerHandle_t timer)
{
    start_scan();
}

/* The scan finished: report it to the dashboard if it asked; and unless
 * already connected, join the first saved network that's in range */
static void scan_done(void)
{
    scanning = false;
    uint16_t n = MAX_SCAN;
    wifi_ap_record_t *aps = calloc(MAX_SCAN, sizeof(wifi_ap_record_t));
    if (!aps || esp_wifi_scan_get_ap_records(&n, aps) != ESP_OK) {
        n = 0;
    }
    if (list_wanted) {
        xSemaphoreTake(lock, portMAX_DELAY);
        free(list_json);
        list_json = networks_found_json(aps, n);
        xSemaphoreGive(lock);
        list_wanted = false;
        xSemaphoreGive(list_ready);
    }
    if (state == WIFI_CONNECTED || !enabled) {
        free(aps);                      /* a scan for the dashboard: stay where we are */
        return;
    }
    wifi_config_t config = {0};
    xSemaphoreTake(lock, portMAX_DELAY);
    current = -1;
    for (int i = 0; i < net_count && current < 0; i++) {
        if (nets[i].flags & NET_SKIP) {
            continue;
        }
        for (int k = 0; k < n; k++) {
            if (strcmp((const char *)aps[k].ssid, nets[i].ssid) == 0) {
                current = i;
                break;
            }
        }
    }
    if (current >= 0) {
        strlcpy((char *)config.sta.ssid, nets[current].ssid, sizeof(config.sta.ssid));
        strlcpy((char *)config.sta.password, nets[current].password, sizeof(config.sta.password));
        strlcpy(current_ssid, nets[current].ssid, sizeof(current_ssid));
    }
    xSemaphoreGive(lock);
    free(aps);

    if (current >= 0) {
        ESP_LOGI(TAG, "joining %s", config.sta.ssid);
        esp_wifi_set_config(WIFI_IF_STA, &config);
        esp_wifi_connect();
    } else {
        fails++;
        state = fails >= FAILS_BEFORE_FAILED ? WIFI_FAILED : WIFI_CONNECTING;
        ESP_LOGW(TAG, "no saved network in range, looking again in %d s", RETRY_DELAY_MS / 1000);
        xTimerStart(retry_timer, 0);
    }
}

static void on_event(void *arg, esp_event_base_t base, int32_t id, void *data)
{
    if (base == WIFI_EVENT && id == WIFI_EVENT_STA_START) {
        start_scan();
    } else if (base == WIFI_EVENT && id == WIFI_EVENT_SCAN_DONE) {
        scan_done();
    } else if (base == WIFI_EVENT && id == WIFI_EVENT_STA_DISCONNECTED) {
        const wifi_event_sta_disconnected_t *event = data;
        current_ip.addr = 0;
        if (!enabled) {
            state = WIFI_DISABLED;          /* turned off on purpose: don't retry */
            return;
        }
        fails++;
        ESP_LOGW(TAG, "not connected (reason %d), looking again in %d s", event->reason, RETRY_DELAY_MS / 1000);
        state = fails >= FAILS_BEFORE_FAILED ? WIFI_FAILED : WIFI_CONNECTING;
        xTimerStart(retry_timer, 0);
    } else if (base == IP_EVENT && id == IP_EVENT_STA_GOT_IP) {
        const ip_event_got_ip_t *event = data;
        current_ip = event->ip_info.ip;
        ESP_LOGI(TAG, "connected to %s, IP " IPSTR, current_ssid, IP2STR(&current_ip));
        fails = 0;
        state = WIFI_CONNECTED;
        if (!sntp_started) {
            /* Sets the system clock in the background, and keeps it in sync */
            esp_sntp_config_t config = ESP_NETIF_SNTP_DEFAULT_CONFIG(NTP_SERVER);
            config.sync_cb = time_synced;
            esp_netif_sntp_init(&config);
            sntp_started = true;
        }
    }
}

void wifi_start(void)
{
    lock = xSemaphoreCreateMutex();
    list_ready = xSemaphoreCreateBinary();
    load_networks();

    esp_log_level_set("wifi", ESP_LOG_WARN);       /* the driver logs a lot at info level */
    esp_log_level_set("wifi_init", ESP_LOG_WARN);
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_sta();

    wifi_init_config_t init = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&init));
    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, on_event, NULL));
    ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, on_event, NULL));
    retry_timer = xTimerCreate("wifi_retry", pdMS_TO_TICKS(RETRY_DELAY_MS), pdFALSE, NULL, retry);
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    started = true;

    nvs_handle_t nvs;
    uint8_t on = 1;
    if (nvs_open(NVS_NAMESPACE, NVS_READONLY, &nvs) == ESP_OK) {
        nvs_get_u8(nvs, NVS_KEY_ON, &on);
        nvs_close(nvs);
    }
    enabled = on;
    if (net_count == 0) {
        state = WIFI_OFF;
        ESP_LOGW(TAG, "no saved networks, Wi-Fi off");
        return;
    }
    if (!enabled) {
        state = WIFI_DISABLED;
        ESP_LOGI(TAG, "turned off in Settings");
        return;
    }

    state = WIFI_CONNECTING;
    ESP_ERROR_CHECK(esp_wifi_start());  /* STA_START then scans and joins */
    /* Power saving makes the radio nap between beacons: ~100 ms per round trip,
     * ~5 KB/s downloads, too slow for the dashboard. Costs battery; later this
     * could be switched back on while nobody uses the dashboard. */
    esp_wifi_set_ps(WIFI_PS_NONE);
}

void wifi_set_enabled(bool on)
{
    if (!started || on == enabled || net_count == 0) {
        return;
    }
    enabled = on;
    nvs_handle_t nvs;
    if (nvs_open(NVS_NAMESPACE, NVS_READWRITE, &nvs) == ESP_OK) {
        nvs_set_u8(nvs, NVS_KEY_ON, on);
        nvs_commit(nvs);
        nvs_close(nvs);
    }
    if (on) {
        /* Way back if every network nearby was switched off on the dashboard
         * (which is then unreachable): turning Wi-Fi on switches them all on */
        xSemaphoreTake(lock, portMAX_DELAY);
        for (int i = 0; i < net_count; i++) {
            nets[i].flags &= ~NET_SKIP;
        }
        save_networks();
        xSemaphoreGive(lock);
        fails = 0;
        state = WIFI_CONNECTING;
        esp_wifi_start();               /* STA_START then scans and joins */
        esp_wifi_set_ps(WIFI_PS_NONE);
        ESP_LOGI(TAG, "turned on, all saved networks switched on");
    } else {
        xTimerStop(retry_timer, 0);
        esp_wifi_stop();
        state = WIFI_DISABLED;
        ESP_LOGI(TAG, "turned off");
    }
}

bool wifi_is_enabled(void)
{
    return enabled;
}

wifi_state_t wifi_get_state(void)
{
    if (net_count == 0 && state != WIFI_DISABLED) {
        return WIFI_OFF;
    }
    return state;
}

const char *wifi_get_ssid(void)
{
    return current_ssid;
}

bool wifi_get_ip(char *buf, size_t size)
{
    esp_ip4_addr_t ip = current_ip;
    if (state != WIFI_CONNECTED || ip.addr == 0) {
        return false;
    }
    snprintf(buf, size, IPSTR, IP2STR(&ip));
    return true;
}

char *wifi_networks_json(void)
{
    cJSON *root = cJSON_CreateObject();
    cJSON *list = cJSON_AddArrayToObject(root, "networks");
    char ip[16] = "";
    wifi_get_ip(ip, sizeof(ip));
    xSemaphoreTake(lock, portMAX_DELAY);
    for (int i = 0; i < net_count; i++) {
        cJSON *item = cJSON_CreateObject();
        cJSON_AddStringToObject(item, "ssid", nets[i].ssid);   /* passwords never leave the pin */
        cJSON_AddBoolToObject(item, "skip", nets[i].flags & NET_SKIP);
        cJSON_AddBoolToObject(item, "current", i == current && state == WIFI_CONNECTED);
        cJSON_AddItemToArray(list, item);
    }
    xSemaphoreGive(lock);
    cJSON_AddStringToObject(root, "ip", ip);
    char *json = cJSON_PrintUnformatted(root);
    cJSON_Delete(root);
    return json;
}

char *wifi_scan_json(void)
{
    if (!started || !enabled || wifi_get_state() == WIFI_OFF) {
        return NULL;
    }
    xSemaphoreTake(list_ready, 0);      /* forget an old, unclaimed result */
    list_wanted = true;
    if (!scanning) {
        /* While joining a network the driver refuses to scan; the caller retries */
        scanning = esp_wifi_scan_start(NULL, false) == ESP_OK;
        if (!scanning) {
            list_wanted = false;
            return NULL;
        }
    }
    if (xSemaphoreTake(list_ready, pdMS_TO_TICKS(10000)) != pdTRUE) {
        list_wanted = false;
        return NULL;
    }
    xSemaphoreTake(lock, portMAX_DELAY);
    char *json = list_json;
    list_json = NULL;
    xSemaphoreGive(lock);
    return json;
}

esp_err_t wifi_set_networks_json(const char *json)
{
    cJSON *root = cJSON_Parse(json);
    const cJSON *list = cJSON_GetObjectItem(root, "networks");
    if (!cJSON_IsArray(list) || cJSON_GetArraySize(list) > WIFI_MAX_NETWORKS) {
        cJSON_Delete(root);
        return ESP_ERR_INVALID_ARG;
    }
    network_t *fresh = calloc(WIFI_MAX_NETWORKS, sizeof(network_t));
    if (!fresh) {
        cJSON_Delete(root);
        return ESP_ERR_NO_MEM;
    }
    int n = 0;
    esp_err_t err = ESP_OK;
    xSemaphoreTake(lock, portMAX_DELAY);
    const cJSON *item;
    cJSON_ArrayForEach(item, list) {
        const cJSON *ssid = cJSON_GetObjectItem(item, "ssid");
        const cJSON *password = cJSON_GetObjectItem(item, "password");
        size_t ssid_len = cJSON_IsString(ssid) ? strlen(ssid->valuestring) : 0;
        if (ssid_len == 0 || ssid_len > 32) {
            err = ESP_ERR_INVALID_ARG;
            break;
        }
        network_t *net = &fresh[n++];
        strlcpy(net->ssid, ssid->valuestring, sizeof(net->ssid));
        net->flags = cJSON_IsTrue(cJSON_GetObjectItem(item, "skip")) ? NET_SKIP : 0;
        if (cJSON_IsString(password)) {
            size_t len = strlen(password->valuestring);
            if (len != 0 && (len < 8 || len > 63)) {    /* WPA2: 8-63 characters, or none */
                err = ESP_ERR_INVALID_ARG;
                break;
            }
            strlcpy(net->password, password->valuestring, sizeof(net->password));
        } else {
            /* No password given: keep the one already saved for this network */
            for (int i = 0; i < net_count; i++) {
                if (strcmp(nets[i].ssid, net->ssid) == 0) {
                    strlcpy(net->password, nets[i].password, sizeof(net->password));
                }
            }
        }
    }
    bool leave = false;                 /* the network we're on was removed or switched off */
    if (err == ESP_OK) {
        /* Keep pointing at the network we're on, if it's still in the list */
        int moved = -1;
        for (int i = 0; i < n; i++) {
            if (current >= 0 && strcmp(fresh[i].ssid, current_ssid) == 0) {
                moved = i;
            }
        }
        leave = current >= 0 && (moved < 0 || (fresh[moved].flags & NET_SKIP));
        memcpy(nets, fresh, sizeof(network_t) * WIFI_MAX_NETWORKS);
        net_count = n;
        current = moved;
        save_networks();
    }
    xSemaphoreGive(lock);
    free(fresh);
    cJSON_Delete(root);
    if (err == ESP_OK) {
        ESP_LOGI(TAG, "%d saved network(s)", net_count);
        if (leave && state == WIFI_CONNECTED) {
            ESP_LOGI(TAG, "leaving %s (removed or switched off)", current_ssid);
            esp_wifi_disconnect();          /* then the disconnect event scans for another */
        } else if (state != WIFI_CONNECTED && enabled) {
            if (state == WIFI_OFF) {        /* the first network was just added */
                state = WIFI_CONNECTING;
                esp_wifi_start();
                esp_wifi_set_ps(WIFI_PS_NONE);
            } else {
                start_scan();               /* maybe a new network is in range */
            }
        }
    }
    return err;
}

bool wifi_clock_set(void)
{
    return clock_set;
}
