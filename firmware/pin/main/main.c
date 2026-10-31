/*
 * Plurality Pin firmware.
 *
 * Current state: all screens from the LVGL Editor (see main/ui and
 * tools/sync_ui.py), swipe navigation between them (nav.c), a running clock
 * on the Watch screen, and the web dashboard (web.c, dashboard/index.html):
 * members and front history in flash (store.c), the current fronter on the
 * fronter screen in each member's display mode (fronter.c).
 *
 * Images live in the "assets" flash partition, mapped into memory (assets.c).
 * Fonts are pre-rendered bitmaps in main/ui/fonts.
 *
 * Time: the board has no clock chip, so it starts at the time this firmware
 * was built and is corrected from the internet (NTP) once Wi-Fi connects (wifi.c).
 */

#include <string.h>
#include <time.h>
#include <sys/time.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "esp_heap_caps.h"
#include "nvs_flash.h"
#include "photos.h"
#include "lvgl.h"
#include "assets.h"
#include "auth.h"
#include "boot.h"
#include "brightness.h"
#include "connect.h"
#include "button.h"
#include "settings.h"
#include "storage_info.h"
#include "status.h"
#include "display.h"
#include "fronter.h"
#include "textpic.h"
#include "nav.h"
#include "pksync.h"
#include "store.h"
#include "web.h"
#include "wifi.h"
#include "ui/plurality_pin.h"

static const char *TAG = "pin";

/* Local time zone, POSIX format: Hong Kong, UTC+8, no daylight saving */
#define TIME_ZONE "HKT-8"

/* 1: time every screen at startup and log the results (see nav_benchmark) */
#define RUN_BENCHMARK 0

/* ---------- clock ---------- */

typedef struct {
    lv_obj_t *day;
    lv_obj_t *date;
    lv_obj_t *time;
} watch_labels_t;

static watch_labels_t watch;            /* all NULL while the Watch screen isn't shown */

/* Only touch a label when its text really changes: redrawing the 150 px clock
 * digits every second would waste time and power. */
static void set_text_if_changed(lv_obj_t *label, const char *text)
{
    if (strcmp(lv_label_get_text(label), text) != 0) {
        lv_label_set_text(label, text);
    }
}

static void clock_update(lv_timer_t *timer)
{
    if (!watch.time) {
        return;
    }

    time_t now = time(NULL);
    struct tm tm;
    localtime_r(&now, &tm);

    char buf[16];
    strftime(buf, sizeof(buf), "%A", &tm);
    set_text_if_changed(watch.day, buf);
    strftime(buf, sizeof(buf), "%d/%m/%y", &tm);
    set_text_if_changed(watch.date, buf);
    strftime(buf, sizeof(buf), "%H:%M", &tm);
    set_text_if_changed(watch.time, buf);
}

static void set_time_from_build(void)
{
    struct tm tm = {0};
    strptime(__DATE__ " " __TIME__, "%b %d %Y %H:%M:%S", &tm);
    struct timeval tv = { .tv_sec = mktime(&tm) };
    settimeofday(&tv, NULL);
}

static void watch_deleted(lv_event_t *e)
{
    memset(&watch, 0, sizeof(watch));
}

static void on_screen(const char *name, lv_obj_t *scr)
{
    if (strcmp(name, "settings") == 0) {
        settings_attach(scr);
        return;
    }
    if (strcmp(name, "namecard_mode") == 0) {
        fronter_attach(scr, STORE_MODE_CARD);
        return;
    }
    if (strcmp(name, "connect") == 0) {
        connect_attach(scr);
        return;
    }
    if (strcmp(name, "image_mode_full") == 0) {
        fronter_attach(scr, STORE_MODE_IMAGE);
        return;
    }
    if (strcmp(name, "image_mode_with_text") == 0) {
        fronter_attach(scr, STORE_MODE_IMAGE_TEXT);
        return;
    }
    if (strcmp(name, "watch") != 0) {
        return;
    }
    /* The generated screen doesn't name its labels, so find them by position
     * (see watch.xml): screen > column > [row > [day, date], time] */
    lv_obj_t *column = lv_obj_get_child(scr, 0);
    lv_obj_t *row = lv_obj_get_child(column, 0);
    watch.day = lv_obj_get_child(row, 0);
    watch.date = lv_obj_get_child(row, 1);
    watch.time = lv_obj_get_child(column, 1);
    lv_obj_add_event_cb(scr, watch_deleted, LV_EVENT_DELETE, NULL);
    clock_update(NULL);
}

/* ---------- LVGL ---------- */

static uint32_t tick_cb(void)
{
    return esp_timer_get_time() / 1000;
}

static void memory_report(lv_timer_t *timer)
{
    time_t now = time(NULL);
    struct tm tm;
    localtime_r(&now, &tm);
    char clock[24];
    strftime(clock, sizeof(clock), "%Y-%m-%d %H:%M:%S", &tm);
    ESP_LOGI(TAG, "%s, free heap %u bytes, lowest so far %u bytes", clock,
             (unsigned)heap_caps_get_free_size(MALLOC_CAP_DEFAULT),
             (unsigned)heap_caps_get_minimum_free_size(MALLOC_CAP_DEFAULT));
}

/* The boot screen has faded in: start the real UI */
static void boot_done(void)
{
    nav_init(on_screen);
#if RUN_BENCHMARK
    /* After the SD card is mounted (photos live there) */
    lv_timer_t *bench = lv_timer_create((lv_timer_cb_t)nav_benchmark, 6000, NULL);
    lv_timer_set_repeat_count(bench, 1);
#endif
    button_init();
    lv_timer_create(clock_update, 1000, NULL);
    lv_timer_create((lv_timer_cb_t)fronter_poll, 250, NULL);
    lv_timer_create(memory_report, 10000, NULL);
}

static void lvgl_task(void *arg)
{
    plurality_pin_init("");             /* asset path unused: fonts are built in, images mapped */
    brightness_init();
    status_init();
    boot_show(boot_done);

    while (1) {
        uint32_t wait_ms = lv_timer_handler();
        if (wait_ms < 5) {
            wait_ms = 5;
        } else if (wait_ms > 30) {
            wait_ms = 30;
        }
        vTaskDelay(pdMS_TO_TICKS(wait_ms));
    }
}

static void nvs_init(void)
{
    /* Flash key-value storage, used by Wi-Fi and brightness.c */
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK(err);
}

void app_main(void)
{
    setenv("TZ", TIME_ZONE, 1);
    tzset();
    set_time_from_build();              /* the build time is local time */
    nvs_init();
    assets_init();
    photos_init();
    store_init();

    lv_init();
    lv_tick_set_cb(tick_cb);
    textpic_init();                     /* draws text pictures straight from their files */

    display_init();                     /* brightness is set by brightness_init() */
    wifi_start();
    auth_init();                        /* dashboard password, before the web server */
    web_start();
    pksync_start();                     /* PluralKit -> pin front sync */
    storage_info_start();               /* after the display: the SD card shares its SPI bus */

    /* All LVGL calls happen in this one task from here on (its stack is bigger
     * than app_main's, which drawing needs) */
    xTaskCreate(lvgl_task, "lvgl", 16384, NULL, 5, NULL);
}
