/*
 * Device status shown on the Settings, Status and pull-down menu screens.
 *
 * - Battery: measured through the board's 200k/100k divider on GPIO0 (vendor
 *   BSP's bat_adc_read()) and turned into a rough percentage. The board has no
 *   charge-status signal, so charging isn't shown.
 * - Time and date: from the system clock (build time until NTP sets it, wifi.c).
 * - Wi-Fi: polled from wifi.c every second.
 */

#include <string.h>
#include <time.h>
#include "esp_log.h"
#include "bsp/esp-bsp.h"
#include "status.h"
#include "wifi.h"
#include "ui/plurality_pin.h"

static const char *TAG = "status";

#define BATTERY_PERIOD_MS   10000
#define BATTERY_SAMPLES     8
/* A Li-ion cell never goes above ~4.2 V. Higher means no battery is attached and
 * we're reading the charger output on USB power (measured: 4.84 V). */
#define NO_BATTERY_VOLTS    4.4f

/* Typical single-cell Li-ion discharge curve: voltage -> charge left */
static const struct { float volts; int percent; } battery_curve[] = {
    { 4.20f, 100 }, { 4.10f, 90 }, { 4.00f, 80 }, { 3.90f, 65 }, { 3.80f, 50 },
    { 3.70f, 30 }, { 3.60f, 15 }, { 3.50f, 5 }, { 3.30f, 0 },
};
#define CURVE_LEN (sizeof(battery_curve) / sizeof(battery_curve[0]))

static int volts_to_percent(float v)
{
    if (v >= battery_curve[0].volts) {
        return 100;
    }
    for (int i = 1; i < CURVE_LEN; i++) {
        if (v >= battery_curve[i].volts) {
            /* straight line between the two nearest points */
            float hi_v = battery_curve[i - 1].volts, lo_v = battery_curve[i].volts;
            int hi_p = battery_curve[i - 1].percent, lo_p = battery_curve[i].percent;
            return lo_p + (int)((v - lo_v) / (hi_v - lo_v) * (hi_p - lo_p) + 0.5f);
        }
    }
    return 0;
}

static float battery_volts(void)
{
    float sum = 0;
    for (int i = 0; i < BATTERY_SAMPLES; i++) {
        sum += bat_adc_read();
    }
    return sum / BATTERY_SAMPLES;
}

static void battery_update(lv_timer_t *timer)
{
    /* With no battery (USB only) this shows 100 % */
    int percent = volts_to_percent(battery_volts());

    if (lv_subject_get_int(&battery_percent) != percent) {
        lv_subject_set_int(&battery_percent, percent);
    }
}

/* Only notify when the text changes, so bound labels aren't redrawn needlessly */
static void set_string(lv_subject_t *subject, const char *text)
{
    if (strcmp(lv_subject_get_string(subject), text) != 0) {
        lv_subject_copy_string(subject, text);
    }
}

static void wifi_update(void)
{
    switch (wifi_get_state()) {
    case WIFI_OFF:
        set_string(&wifi_status, "Off");
        set_string(&wifi_name, "Not set up");
        return;
    case WIFI_CONNECTING:
        set_string(&wifi_status, "Connecting");
        break;
    case WIFI_CONNECTED:
        set_string(&wifi_status, "Connected");
        break;
    case WIFI_FAILED:
        set_string(&wifi_status, "Failed");
        break;
    }
    set_string(&wifi_name, wifi_get_ssid());
}

/* Every second: clock text and Wi-Fi state */
static void clock_update(lv_timer_t *timer)
{
    wifi_update();

    time_t now = time(NULL);
    struct tm tm;
    localtime_r(&now, &tm);

    char buf[16];
    snprintf(buf, sizeof(buf), "%d:%02d", tm.tm_hour % 12 ? tm.tm_hour % 12 : 12, tm.tm_min);
    set_string(&time_text, buf);
    set_string(&ampm_text, tm.tm_hour < 12 ? "AM" : "PM");

    char day_month[12];
    strftime(day_month, sizeof(day_month), "%a %b", &tm);
    snprintf(buf, sizeof(buf), "%s %d", day_month, tm.tm_mday);
    set_string(&date_text, buf);
}

void status_init(void)
{
    ESP_ERROR_CHECK(bat_adc_init());
    battery_update(NULL);
    float volts = battery_volts();
    if (volts > NO_BATTERY_VOLTS) {
        ESP_LOGI(TAG, "no battery (%.2f V, USB power)", volts);
    } else {
        ESP_LOGI(TAG, "battery %.2f V = %d %%", volts, (int)lv_subject_get_int(&battery_percent));
    }
    lv_timer_create(battery_update, BATTERY_PERIOD_MS, NULL);

    clock_update(NULL);
    lv_timer_create(clock_update, 1000, NULL);

}
