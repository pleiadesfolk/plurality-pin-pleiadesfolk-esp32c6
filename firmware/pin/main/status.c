/*
 * Device status shown on the Settings, Status and pull-down menu screens.
 *
 * - Battery: measured through the board's 200k/100k divider on GPIO0 (vendor
 *   BSP's bat_adc_read()) and turned into a rough percentage. On USB power
 *   that pin reads the charger (~4.9 V) instead of the battery, so then we only
 *   know "USB is plugged in" (usb_power, shown as "Charging") and keep showing
 *   the last battery reading. Measured: 4.90 V on USB, 4.08 V on battery.
 * - Time and date: from the system clock (build time until NTP sets it, wifi.c).
 * - Wi-Fi: polled from wifi.c every second.
 * - Storage: SD card and the pin's own storage, measured by storage_info.c.
 * - Power mode: Active, or Low battery when running on a low battery.
 *   ("Power saving", power_state 2, is for when power saving exists.)
 */

#include <string.h>
#include <time.h>
#include "esp_log.h"
#include "bsp/esp-bsp.h"
#include "status.h"
#include "storage_info.h"
#include "wifi.h"
#include "ui/plurality_pin.h"

static const char *TAG = "status";

#define BATTERY_PERIOD_MS   10000
#define BATTERY_SAMPLES     8
/* A Li-ion cell never goes above ~4.2 V. Higher means we're on USB power and
 * reading the charger's output (measured 4.84-4.90 V, with or without a battery). */
#define USB_POWER_VOLTS     4.4f
#define LOW_BATTERY_PERCENT 15

static volatile float last_volts;       /* for status_battery_volts() */

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

static void set_string(lv_subject_t *subject, const char *text);

static void set_int(lv_subject_t *subject, int value)
{
    if (lv_subject_get_int(subject) != value) {
        lv_subject_set_int(subject, value);
    }
}

static void battery_update(lv_timer_t *timer)
{
    static bool measured;               /* a real battery reading has been taken */
    float volts = battery_volts();
    last_volts = volts;
    bool usb = volts >= USB_POWER_VOLTS;
    set_int(&usb_power, usb);

    /* On USB the battery can't be measured: keep the last reading (100 % if
     * the pin started on USB and there is none yet) */
    if (!usb) {
        set_int(&battery_percent, volts_to_percent(volts));
        measured = true;
    } else if (!measured) {
        set_int(&battery_percent, 100);
    }
    int percent = lv_subject_get_int(&battery_percent);

    bool low = !usb && percent <= LOW_BATTERY_PERCENT;
    set_int(&power_state, low ? 1 : 0);
    set_string(&power_mode_text, low ? "Low battery" : "Active");
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
    /* wifi_state: 0 off, 1 connecting, 2 connected, 3 failed (globals.xml) */
    switch (wifi_get_state()) {
    case WIFI_OFF:
        set_int(&wifi_state, 0);
        set_string(&wifi_status, "Off");
        set_string(&wifi_name, "Not set up");
        return;
    case WIFI_DISABLED:
        set_int(&wifi_state, 0);
        set_string(&wifi_status, "Off");
        set_string(&wifi_name, "Turned off");
        return;
    case WIFI_CONNECTING:
        set_int(&wifi_state, 1);
        set_string(&wifi_status, "Connecting");
        break;
    case WIFI_CONNECTED:
        set_int(&wifi_state, 2);
        set_string(&wifi_status, "Connected");
        break;
    case WIFI_FAILED:
        set_int(&wifi_state, 3);
        set_string(&wifi_status, "Failed");
        break;
    }
    set_string(&wifi_name, wifi_get_ssid());
}

/* "19.8 / 32 GB", "0.3 / 4.4 MB": both numbers in the unit that suits the total */
static void format_usage(char *buf, size_t size, const storage_usage_t *u)
{
    double scale = u->total >= 1000000000ULL ? 1e9 : 1e6;
    const char *unit = scale == 1e9 ? "GB" : "MB";
    double used = u->used / scale, total = u->total / scale;
    snprintf(buf, size, total >= 10 ? "%.1f / %.0f %s" : "%.1f / %.1f %s", used, total, unit);
}

static void storage_update(void)
{
    storage_usage_t sd, pin;
    storage_info_get(&sd, &pin);
    char buf[32];

    if (sd.present && sd.total) {
        format_usage(buf, sizeof(buf), &sd);
        set_string(&sd_text, buf);
        set_int(&sd_percent, (int)(sd.used * 100 / sd.total));
    } else {
        set_string(&sd_text, "No card");
        set_int(&sd_percent, 0);
    }
    if (pin.present && pin.total) {
        format_usage(buf, sizeof(buf), &pin);
        set_string(&pin_storage_text, buf);
        set_int(&pin_storage_percent, (int)(pin.used * 100 / pin.total));
    }
}

/* Every second: clock text, Wi-Fi state and storage */
static void clock_update(lv_timer_t *timer)
{
    wifi_update();
    storage_update();

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
    if (last_volts > USB_POWER_VOLTS) {
        ESP_LOGI(TAG, "on USB power (%.2f V)", last_volts);
    } else {
        ESP_LOGI(TAG, "battery %.2f V = %d %%", last_volts, (int)lv_subject_get_int(&battery_percent));
    }
    lv_timer_create(battery_update, BATTERY_PERIOD_MS, NULL);

    clock_update(NULL);
    lv_timer_create(clock_update, 1000, NULL);
}

float status_battery_volts(void)
{
    return last_volts;
}
