/*
 * Device status shown on the Settings, Status and pull-down menu screens.
 *
 * - Battery: measured through the board's 200k/100k divider on GPIO0 (vendor
 *   BSP's bat_adc_read()) and turned into a rough percentage. Single readings
 *   jump around (the divider is weak, and the voltage dips while the radio
 *   sends), so each measurement is the median of several, those are averaged
 *   over about a minute, and on battery the percentage only ever goes down.
 *   Once a minute the reading is also added to a log in flash
 *   (STATUS_BATTERY_LOG), so a full run from charged to empty can be looked at
 *   afterwards on the dashboard - even after the battery ran flat.
 *   On USB power
 *   that pin reads the charger (~4.9 V) instead of the battery, so then we only
 *   know "USB is plugged in" (usb_power, shown as "Charging") and keep showing
 *   the last battery reading. Measured: 4.90 V on USB, 4.08 V on battery.
 * - Time and date: from the system clock (build time until NTP sets it, wifi.c).
 * - Wi-Fi: polled from wifi.c every second. On the Status screen the icon
 *   shows it (green: connected, grey: connecting, crossed out: off or
 *   failing), and tapping the card moves to the next saved network.
 * - Storage: SD card and the pin's own storage, measured by storage_info.c.
 * - Power mode: Active, or Low battery when running on a low battery.
 *   ("Power saving", power_state 2, is for when power saving exists.)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include "esp_log.h"
#include "bsp/esp-bsp.h"
#include "nav.h"
#include "power.h"
#include "status.h"
#include "storage_info.h"
#include "wifi.h"
#include "ui/plurality_pin.h"

static const char *TAG = "status";

#define BATTERY_PERIOD_MS   10000
#define BATTERY_SAMPLES     16
#define BATTERY_SMOOTHING   0.2f        /* weight of a new measurement: ~1 minute to settle */
#define BATTERY_SETTLE      3           /* measurements after unplugging before it only goes down */
/* A Li-ion cell never goes above ~4.2 V. Higher means we're on USB power and
 * reading the charger's output (measured 4.84-4.90 V, with or without a battery). */
#define USB_POWER_VOLTS     POWER_USB_VOLTS
#define LOW_BATTERY_PERCENT 15
#define LOG_EVERY           6           /* battery updates per log entry: once a minute */
#define LOG_MAX_ENTRIES     (4 * 24 * 60)   /* 4 days; then the older half is dropped */

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

static int compare_floats(const void *a, const void *b)
{
    float x = *(const float *)a, y = *(const float *)b;
    return (x > y) - (x < y);
}

/* Median of several readings: one-off dips and spikes don't count */
static float battery_volts(void)
{
    float v[BATTERY_SAMPLES];
    for (int i = 0; i < BATTERY_SAMPLES; i++) {
        v[i] = bat_adc_read();
    }
    qsort(v, BATTERY_SAMPLES, sizeof(v[0]), compare_floats);
    return (v[BATTERY_SAMPLES / 2 - 1] + v[BATTERY_SAMPLES / 2]) / 2;
}

static void set_string(lv_subject_t *subject, const char *text);

static void set_int(lv_subject_t *subject, int value)
{
    if (lv_subject_get_int(subject) != value) {
        lv_subject_set_int(subject, value);
    }
}

/* ---------- battery log ---------- */

static void log_trim(void)
{
    /* Keep the newer half: copy it to a new file, then swap it in */
    FILE *in = fopen(STATUS_BATTERY_LOG, "rb");
    FILE *out = in ? fopen(STATUS_BATTERY_LOG ".tmp", "wb") : NULL;
    status_log_entry_t e;
    bool ok = out && fseek(in, LOG_MAX_ENTRIES / 2 * sizeof(e), SEEK_SET) == 0;
    while (ok && fread(&e, sizeof(e), 1, in) == 1) {
        ok = fwrite(&e, sizeof(e), 1, out) == 1;
    }
    if (in) {
        fclose(in);
    }
    if (out && fclose(out) == 0 && ok) {
        unlink(STATUS_BATTERY_LOG);
        rename(STATUS_BATTERY_LOG ".tmp", STATUS_BATTERY_LOG);
    } else {
        unlink(STATUS_BATTERY_LOG ".tmp");
    }
}

static void log_add(float volts, bool usb)
{
    struct stat st;
    if (stat(STATUS_BATTERY_LOG, &st) == 0 && st.st_size >= LOG_MAX_ENTRIES * sizeof(status_log_entry_t)) {
        log_trim();
    }
    status_log_entry_t e = { .time = (uint32_t)time(NULL), .millivolts = (uint16_t)(volts * 1000 + 0.5f), .usb = usb };
    FILE *f = fopen(STATUS_BATTERY_LOG, "ab");
    if (f) {
        fwrite(&e, sizeof(e), 1, f);
        fclose(f);
    }
}

void status_battery_log_clear(void)
{
    unlink(STATUS_BATTERY_LOG);
}

static void battery_update(lv_timer_t *timer)
{
    static int updates;
    static bool measured;               /* a real battery reading has been taken */
    static int on_battery;              /* measurements since the last time on USB */
    static float smooth;
    float volts = battery_volts();
    last_volts = volts;
    bool usb = volts >= USB_POWER_VOLTS;
    set_int(&usb_power, usb);
    if (updates++ % LOG_EVERY == 0) {
        log_add(volts, usb);
    }

    /* On USB the battery can't be measured: keep the last reading (100 % if
     * the pin started on USB and there is none yet) */
    if (usb) {
        on_battery = 0;
        if (!measured) {
            set_int(&battery_percent, 100);
        }
    } else {
        /* Start afresh after USB (it may have charged); then average */
        smooth = on_battery++ ? smooth + (volts - smooth) * BATTERY_SMOOTHING : volts;
        int percent = volts_to_percent(smooth);
        /* Nothing charges it now, so once settled it can only go down */
        if (!measured || on_battery <= BATTERY_SETTLE || percent < lv_subject_get_int(&battery_percent)) {
            set_int(&battery_percent, percent);
        }
        measured = true;
    }
    power_battery_update(usb, smooth, on_battery > 1);
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

/* ---------- Status screen: Wi-Fi icon and card ---------- */

#define WIFI_GREY 0x8E8E93

static void free_points(lv_event_t *e)
{
    lv_free(lv_event_get_user_data(e));
}

static void wifi_icon_update(lv_observer_t *observer, lv_subject_t *subject)
{
    /* wifi_state: 0 off, 1 connecting, 2 connected, 3 failed */
    lv_obj_t *icon = lv_observer_get_target_obj(observer);
    bool tinted = lv_observer_get_user_data(observer) != NULL;
    int s = lv_subject_get_int(subject);
    if (tinted) {
        lv_obj_set_style_image_recolor_opa(icon, s == 2 ? LV_OPA_TRANSP : LV_OPA_COVER, 0);
    }
    lv_obj_set_style_image_opa(icon, s == 2 ? LV_OPA_COVER : s == 1 ? LV_OPA_40 : LV_OPA_60, 0);
    lv_obj_set_flag(lv_obj_get_child(icon, 0), LV_OBJ_FLAG_HIDDEN, s == 1 || s == 2);
}

void status_wifi_icon(lv_obj_t *icon, bool tinted)
{
    lv_color_t colour = tinted ? lv_color_hex(WIFI_GREY) : lv_color_hex(0xF2F2F7);
    if (tinted) {
        lv_obj_set_style_image_recolor(icon, colour, 0);
    }
    /* "Off": a line through the icon, corner to corner */
    lv_obj_update_layout(icon);
    int32_t w = lv_obj_get_width(icon), h = lv_obj_get_height(icon);
    lv_point_precise_t *points = lv_malloc(2 * sizeof(lv_point_precise_t));
    points[0] = (lv_point_precise_t){ 2, 2 };
    points[1] = (lv_point_precise_t){ w - 3, h - 3 };
    lv_obj_t *slash = lv_line_create(icon);
    lv_line_set_points(slash, points, 2);
    lv_obj_add_event_cb(slash, free_points, LV_EVENT_DELETE, points);
    lv_obj_set_pos(slash, 0, 0);
    lv_obj_set_style_line_width(slash, 2, 0);
    lv_obj_set_style_line_color(slash, colour, 0);
    lv_obj_set_style_line_rounded(slash, true, 0);
    lv_subject_add_observer_obj(&wifi_state, wifi_icon_update, icon, tinted ? (void *)1 : NULL);
}

static void wifi_card_tapped(lv_event_t *e)
{
    char ssid[33], text[64];
    switch (wifi_switch_next(ssid, sizeof(ssid))) {
    case ESP_OK:
        snprintf(text, sizeof(text), "Switching to %s", ssid);
        nav_toast(text);
        break;
    case ESP_ERR_NOT_FOUND:
        nav_toast("No other Wi-Fi network saved");
        break;
    default:
        nav_toast("Wi-Fi is off - turn it on in Settings");
        break;
    }
}

static void make_unclickable(lv_obj_t *obj)
{
    for (uint32_t i = 0; i < lv_obj_get_child_count(obj); i++) {
        lv_obj_t *child = lv_obj_get_child(obj, i);
        lv_obj_remove_flag(child, LV_OBJ_FLAG_CLICKABLE);
        make_unclickable(child);
    }
}

void status_attach(lv_obj_t *scr)
{
    /* Generated layout (see status.xml): screen > container > [card, column >
     * [row > [battery card, Wi-Fi card], row]]; Wi-Fi card > column > [column > icon, ...] */
    lv_obj_t *column = lv_obj_get_child(lv_obj_get_child(scr, 0), 1);
    lv_obj_t *card = lv_obj_get_child(lv_obj_get_child(column, 0), 1);
    status_wifi_icon(lv_obj_get_child(lv_obj_get_child(lv_obj_get_child(card, 0), 0), 0), true);

    make_unclickable(card);
    lv_obj_add_flag(card, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_opa(card, LV_OPA_60, LV_STATE_PRESSED);
    lv_obj_add_event_cb(card, wifi_card_tapped, LV_EVENT_CLICKED, NULL);
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
    battery_update(NULL);               /* the ADC is set up by power_boot_check() */
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
