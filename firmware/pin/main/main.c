/*
 * Plurality Pin firmware.
 *
 * Current state: all screens from the LVGL Editor (see main/ui and
 * tools/sync_ui.py), swipe navigation between them (nav.c), and a running
 * clock on the Watch screen.
 *
 * Images live in the "assets" flash partition, mapped into memory (assets.c).
 * Fonts are pre-rendered bitmaps in main/ui/fonts.
 *
 * There is no time source yet (no Wi-Fi/NTP, no RTC found on the board), so the
 * clock starts at the time this firmware was built.
 */

#include <string.h>
#include <time.h>
#include <sys/time.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "esp_heap_caps.h"
#include "lvgl.h"
#include "assets.h"
#include "brightness.h"
#include "status.h"
#include "display.h"
#include "nav.h"
#include "ui/plurality_pin.h"

static const char *TAG = "pin";

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
        brightness_attach(scr);
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
    ESP_LOGI(TAG, "free heap %u bytes, lowest so far %u bytes",
             (unsigned)heap_caps_get_free_size(MALLOC_CAP_DEFAULT),
             (unsigned)heap_caps_get_minimum_free_size(MALLOC_CAP_DEFAULT));
}

static void lvgl_task(void *arg)
{
    plurality_pin_init("");             /* asset path unused: fonts are built in, images mapped */
    brightness_init();
    status_init();
#if RUN_BENCHMARK
    nav_benchmark();
#endif
    nav_init(on_screen);
    lv_timer_create(clock_update, 1000, NULL);
    lv_timer_create(memory_report, 10000, NULL);

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

void app_main(void)
{
    set_time_from_build();
    assets_init();

    lv_init();
    lv_tick_set_cb(tick_cb);

    display_init();                     /* brightness is set by brightness_init() */

    /* All LVGL calls happen in this one task from here on (its stack is bigger
     * than app_main's, which drawing needs) */
    xTaskCreate(lvgl_task, "lvgl", 16384, NULL, 5, NULL);
}
