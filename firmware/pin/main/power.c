/*
 * Low-battery protection and the battery screen (see power.h).
 *
 * Measured on a full run (2026-11-01): 4.09 V when charged, slowly down to
 * ~3.4 V after 6 h 10 min, then it falls off a cliff (3.3 V 15 min later,
 * 2.6 V 15 min after that) and the pin restarts over and over. Sleeping at
 * LOW_VOLTS leaves ~15 minutes in hand and keeps the cell from being run flat.
 *
 * The battery screen's parts, in the Editor's order:
 *   0 an X ("no battery": unused - on USB the pin reads the charger either
 *     way, so it can't tell), 1 the battery outline, 2 the lightning bolt
 *     (charging), 3 the red bar (low battery, flashing).
 */

#include <stdlib.h>
#include "esp_log.h"
#include "esp_sleep.h"
#include "esp_wifi.h"
#include "esp_attr.h"
#include "bsp/esp-bsp.h"
#include "display.h"
#include "store.h"
#include "nav.h"
#include "power.h"

static const char *TAG = "power";

#define LOW_VOLTS           3.40f
#define LOW_SHOW_MS         10000       /* the flashing bar, before sleeping */
#define CHARGING_SHOW_MS    3000
#define FLASH_MS            500
#define WAKE_EVERY_US       (120ULL * 1000000)  /* look for USB this often while asleep */

enum { PART_X, PART_OUTLINE, PART_BOLT, PART_BAR };

RTC_DATA_ATTR static bool asleep_low;   /* kept through deep sleep; false after a power cut */
static bool woke_on_usb;
static bool showing;                    /* the battery screen is up */
static lv_obj_t *parts[4];
static lv_timer_t *flash_timer, *end_timer;

static float read_volts(void)
{
    float sum = 0;
    for (int i = 0; i < 8; i++) {
        sum += bat_adc_read();
    }
    return sum / 8;
}

static void sleep_now(void)
{
    asleep_low = true;
    esp_sleep_enable_timer_wakeup(WAKE_EVERY_US);
    esp_deep_sleep_start();
}

void power_boot_check(void)
{
    ESP_ERROR_CHECK(bat_adc_init());
    if (!asleep_low) {
        return;
    }
    if (read_volts() < POWER_USB_VOLTS) {
        sleep_now();                    /* still on the flat battery */
    }
    asleep_low = false;
    woke_on_usb = true;
    ESP_LOGI(TAG, "USB plugged in: starting after a low-battery sleep");
}

/* ---------- the battery screen ---------- */

static void set_part(int part, bool visible)
{
    if (parts[part]) {
        lv_obj_set_flag(parts[part], LV_OBJ_FLAG_HIDDEN, !visible);
    }
}

static void stop_timers(void)
{
    if (flash_timer) {
        lv_timer_delete(flash_timer);
        flash_timer = NULL;
    }
    if (end_timer) {
        lv_timer_delete(end_timer);
        end_timer = NULL;
    }
}

static void show_screen(void)
{
    if (!showing) {
        lv_obj_t *scr = nav_show_power();
        int n = lv_obj_get_child_count(scr);
        for (int i = 0; i < 4; i++) {
            parts[i] = i < n ? lv_obj_get_child(scr, i) : NULL;
        }
        showing = true;
    }
    stop_timers();
    set_part(PART_X, false);
    set_part(PART_OUTLINE, true);
}

static void charging_done(lv_timer_t *timer)
{
    end_timer = NULL;
    stop_timers();
    showing = false;
    nav_power_end();
}

static void show_charging(void)
{
    show_screen();
    set_part(PART_BAR, false);
    set_part(PART_BOLT, true);
    end_timer = lv_timer_create(charging_done, CHARGING_SHOW_MS, NULL);
    lv_timer_set_repeat_count(end_timer, 1);
}

static void flash(lv_timer_t *timer)
{
    if (parts[PART_BAR]) {
        lv_obj_set_flag(parts[PART_BAR], LV_OBJ_FLAG_HIDDEN, !lv_obj_has_flag(parts[PART_BAR], LV_OBJ_FLAG_HIDDEN));
    }
}

static void low_done(lv_timer_t *timer)
{
    end_timer = NULL;
    if (read_volts() >= POWER_USB_VOLTS) {
        show_charging();                /* plugged in just in time */
        return;
    }
    ESP_LOGW(TAG, "battery low: going to sleep until USB is plugged in");
    stop_timers();
    store_save_preview();               /* a side-button switch still waiting */
    display_sleep();
    esp_wifi_stop();
    sleep_now();
}

static void show_low(void)
{
    show_screen();
    set_part(PART_BOLT, false);
    set_part(PART_BAR, true);
    flash_timer = lv_timer_create(flash, FLASH_MS, NULL);
    end_timer = lv_timer_create(low_done, LOW_SHOW_MS, NULL);
    lv_timer_set_repeat_count(end_timer, 1);
}

void power_after_boot(void)
{
    if (woke_on_usb) {
        woke_on_usb = false;
        show_charging();
    }
}

void power_battery_update(bool usb, float volts, bool settled)
{
    if (showing && end_timer && flash_timer && usb) {
        show_charging();                /* low-battery screen up, and USB plugged in */
    } else if (!showing && !usb && settled && volts <= LOW_VOLTS) {
        ESP_LOGW(TAG, "battery low (%.2f V)", volts);
        show_low();
    }
}
