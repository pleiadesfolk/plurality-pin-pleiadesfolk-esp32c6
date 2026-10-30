/*
 * Wi-Fi: join the network from wifi_credentials.h (station mode), reconnect
 * forever if it drops, and set the clock from the internet once connected.
 * It can be turned off on the Settings screen; that choice is kept in NVS.
 *
 * Runs in ESP-IDF's own Wi-Fi/event tasks. The UI only polls wifi_get_state()
 * from the LVGL task (status.c), so no LVGL calls happen here.
 *
 * The ESP32-C6 only has 2.4 GHz Wi-Fi: a 5 GHz-only network won't be found.
 */

#include <string.h>
#include <time.h>
#include <sys/time.h>
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
#include "esp_log.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "esp_netif_sntp.h"
#include "nvs.h"
#include "wifi.h"

#if __has_include("wifi_credentials.h")
#include "wifi_credentials.h"
#else
#include "wifi_credentials.example.h"   /* empty: Wi-Fi stays off */
#endif

static const char *TAG = "pin_wifi";   /* "wifi" is the driver's own (quietened) tag */

#define RETRY_DELAY_MS      5000        /* wait between reconnect attempts */
#define FAILS_BEFORE_FAILED 3           /* show "failed" after this many attempts in a row */
#define NTP_SERVER          "pool.ntp.org"

static volatile wifi_state_t state = WIFI_OFF;
static int fails;
static TimerHandle_t retry_timer;
static bool sntp_started;
static bool configured;                 /* a network is set and the driver is initialised */
static volatile bool enabled = true;

#define NVS_NAMESPACE   "pin"
#define NVS_KEY         "wifi_on"

static void time_synced(struct timeval *tv)
{
    time_t now = tv->tv_sec;
    struct tm tm;
    localtime_r(&now, &tm);
    char buf[24];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &tm);
    ESP_LOGI(TAG, "clock set from the internet: %s", buf);
}

static void retry(TimerHandle_t timer)
{
    if (enabled) {
        esp_wifi_connect();
    }
}

static void on_event(void *arg, esp_event_base_t base, int32_t id, void *data)
{
    if (base == WIFI_EVENT && id == WIFI_EVENT_STA_START) {
        esp_wifi_connect();
    } else if (base == WIFI_EVENT && id == WIFI_EVENT_STA_DISCONNECTED) {
        const wifi_event_sta_disconnected_t *event = data;
        if (!enabled) {
            state = WIFI_DISABLED;          /* turned off on purpose: don't retry */
            return;
        }
        fails++;
        ESP_LOGW(TAG, "not connected (reason %d), retrying in %d s", event->reason, RETRY_DELAY_MS / 1000);
        state = fails >= FAILS_BEFORE_FAILED ? WIFI_FAILED : WIFI_CONNECTING;
        xTimerStart(retry_timer, 0);
    } else if (base == IP_EVENT && id == IP_EVENT_STA_GOT_IP) {
        const ip_event_got_ip_t *event = data;
        ESP_LOGI(TAG, "connected to %s, IP " IPSTR, WIFI_SSID, IP2STR(&event->ip_info.ip));
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
    if (strlen(WIFI_SSID) == 0) {
        ESP_LOGW(TAG, "no network set in wifi_credentials.h, Wi-Fi off");
        return;
    }

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

    wifi_config_t config = {0};
    strlcpy((char *)config.sta.ssid, WIFI_SSID, sizeof(config.sta.ssid));
    strlcpy((char *)config.sta.password, WIFI_PASSWORD, sizeof(config.sta.password));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &config));

    configured = true;
    nvs_handle_t nvs;
    uint8_t on = 1;
    if (nvs_open(NVS_NAMESPACE, NVS_READONLY, &nvs) == ESP_OK) {
        nvs_get_u8(nvs, NVS_KEY, &on);
        nvs_close(nvs);
    }
    enabled = on;
    if (!enabled) {
        state = WIFI_DISABLED;
        ESP_LOGI(TAG, "turned off in Settings");
        return;
    }

    state = WIFI_CONNECTING;
    ESP_ERROR_CHECK(esp_wifi_start());
    /* Power saving makes the radio nap between beacons: ~100 ms per round trip,
     * ~5 KB/s downloads, too slow for the dashboard. Costs battery; later this
     * could be switched back on while nobody uses the dashboard. */
    esp_wifi_set_ps(WIFI_PS_NONE);
    ESP_LOGI(TAG, "connecting to %s", WIFI_SSID);
}

void wifi_set_enabled(bool on)
{
    if (!configured || on == enabled) {
        return;
    }
    enabled = on;
    nvs_handle_t nvs;
    if (nvs_open(NVS_NAMESPACE, NVS_READWRITE, &nvs) == ESP_OK) {
        nvs_set_u8(nvs, NVS_KEY, on);
        nvs_commit(nvs);
        nvs_close(nvs);
    }
    if (on) {
        fails = 0;
        state = WIFI_CONNECTING;
        esp_wifi_start();               /* STA_START then connects */
        esp_wifi_set_ps(WIFI_PS_NONE);
        ESP_LOGI(TAG, "turned on, connecting to %s", WIFI_SSID);
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
    return state;
}

const char *wifi_get_ssid(void)
{
    return WIFI_SSID;
}
