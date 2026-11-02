/*
 * Boot screen: fades in from black, following how far startup has got.
 *
 * The fade level heads for the larger of
 *   - progress: 1/3 for the screen, +1/3 SD card mounted, +1/3 Wi-Fi connected
 *     (or Wi-Fi off / no network saved, so there's nothing to wait for)
 *   - time: elapsed / BOOT_MAX_MS, so it finishes even without SD or Wi-Fi
 * but never faster than a full fade in BOOT_MIN_MS, so it stays a smooth fade
 * when everything is quick or a step (Wi-Fi connecting) suddenly completes.
 *
 * Fading uses the plain `opa` style on the screen's content (multiplied into
 * every child, no extra layer buffer) and mixes the background colour with
 * black, since the screen itself has nothing behind it to blend with.
 */

#include "boot.h"
#include "esp_log.h"
#include "storage_info.h"
#include "wifi.h"
#include "ui/plurality_pin.h"

#define BOOT_MAX_MS     6000            /* fully in by now, whatever is still missing */
#define BOOT_MIN_MS     1500            /* fastest possible fade */
#define HOLD_MS         500             /* stay fully in this long before moving on */
#define STEP_MS         30
#define MAX_STEP        (255 * STEP_MS / BOOT_MIN_MS)   /* most the level moves per step */

static const char *TAG = "boot";

static lv_obj_t *screen;
static lv_color_t background;           /* the design's background colour */
static uint32_t start, full_at;
static int level;                       /* 0 (black) .. 255 (as designed) */
static void (*done_cb)(void);

static int progress(void)
{
    int steps = 1;                      /* the screen is up */
    if (storage_info_sd_ready()) {
        steps++;
    }
    wifi_state_t wifi = wifi_get_state();
    if (wifi == WIFI_CONNECTED || wifi == WIFI_OFF || wifi == WIFI_DISABLED
        || wifi == WIFI_SETUP) {
        steps++;
    }
    return steps * 255 / 3;
}

static void apply(void)
{
    lv_obj_set_style_bg_color(screen, lv_color_mix(background, lv_color_black(), level), 0);
    for (uint32_t i = 0; i < lv_obj_get_child_count(screen); i++) {
        lv_obj_set_style_opa(lv_obj_get_child(screen, i), level, 0);
    }
}

static void step(lv_timer_t *timer)
{
    uint32_t elapsed = lv_tick_elaps(start);
    if (level == 255) {
        if (lv_tick_elaps(full_at) >= HOLD_MS) {
            lv_timer_delete(timer);
            ESP_LOGI(TAG, "done after %u ms", (unsigned)elapsed);
            done_cb();
        }
        return;
    }
    int by_time = elapsed >= BOOT_MAX_MS ? 255 : (int)(elapsed * 255 / BOOT_MAX_MS);
    int target = progress() > by_time ? progress() : by_time;
    if (target > level + MAX_STEP) {
        target = level + MAX_STEP;
    }
    if (target > level) {
        level = target;
        apply();
        if (level == 255) {
            full_at = lv_tick_get();
        }
    }
}

void boot_show(void (*done)(void))
{
    done_cb = done;
    screen = boot_screen_create();
    background = lv_obj_get_style_bg_color(screen, 0);
    level = 0;
    apply();
    lv_screen_load(screen);
    start = lv_tick_get();
    lv_timer_create(step, STEP_MS, NULL);
}
