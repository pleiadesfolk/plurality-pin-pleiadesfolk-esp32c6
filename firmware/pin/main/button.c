/*
 * BOOT button (the side button):
 *   press        - switch to the next member of the Quick Switch list. Swiping
 *                  left/right on the fronter screen steps forward/back the
 *                  same way (nav.c).
 *   two presses  - nobody fronting
 *   three presses,
 *   or hold      - Clock screen, or back to the fronter from it
 *   Presses count as one go when each comes within TAP_GAP_MS of the last;
 *   the action happens once no more come.
 *   A switch shows straight away but is only saved after SAVE_AFTER_MS with
 *   no more presses or swipes, so stepping past members doesn't log them.
 *   hold RESET_MS - also removes the dashboard password (for when it's
 *                  forgotten; someone holding the pin could take it apart anyway)
 *
 * Schematic: Key2 connects GPIO9 to ground, with a 10k pull-up, so it reads 0
 * while pressed. (The vendor BSP says GPIO0, but GPIO0 is the battery
 * measurement.) It's polled from an LVGL timer, so the switch and the screen
 * change happen in the LVGL task.
 */

#include "driver/gpio.h"
#include "esp_log.h"
#include "button.h"
#include "nav.h"
#include "store.h"
#include "auth.h"

static const char *TAG = "button";

#define BUTTON_GPIO     GPIO_NUM_9
#define POLL_MS         20
#define STABLE_POLLS    2               /* must read the same twice in a row (debounce) */
#define TAP_GAP_MS      350             /* a press this soon after the last: part of the same go */
#define LONG_MS         600             /* held this long: a hold, not a press */
#define WARN_MS         4000            /* holding: say what's about to happen */
#define RESET_MS        10000           /* holding: remove the dashboard password */
#define SAVE_AFTER_MS   5000            /* a switch is saved once it's been left this long */

static lv_timer_t *save_timer;

static void save_switch(lv_timer_t *timer)
{
    save_timer = NULL;
    if (store_save_preview()) {
        ESP_LOGI(TAG, "switch saved");
    }
}

/* (Re)start the wait before the switch is saved */
static void save_later(void)
{
    if (save_timer) {
        lv_timer_reset(save_timer);
        return;
    }
    save_timer = lv_timer_create(save_switch, SAVE_AFTER_MS, NULL);
    lv_timer_set_repeat_count(save_timer, 1);
}

void button_switch(int direction)
{
    char name[48], msg[64];
    int next = store_step_button_member(direction, name, sizeof(name));
    if (next < 0) {
        nav_toast("No members yet - import them on the dashboard");
        return;
    }
    uint16_t member = (uint16_t)next;
    if (store_preview_switch(&member, 1) != ESP_OK) {
        nav_toast("Couldn't switch");
        return;
    }
    save_later();
    ESP_LOGI(TAG, "switching to %s", name);
    nav_show_fronter();
    snprintf(msg, sizeof(msg), "Switched to %s", name);
    nav_toast(msg);
}

static void switch_to_nobody(void)
{
    if (!store_front_is(NULL, 0)) {
        if (store_preview_switch(NULL, 0) != ESP_OK) {
            nav_toast("Couldn't switch");
            return;
        }
        save_later();
    }
    ESP_LOGI(TAG, "switching to nobody fronting");
    nav_show_fronter();
    nav_toast("Nobody fronting");
}

static void taps_done(int taps)
{
    if (taps == 1) {
        button_switch(+1);
    } else if (taps == 2) {
        switch_to_nobody();
    } else {
        nav_toggle_clock();
    }
}

static void poll(lv_timer_t *timer)
{
    static int last = 1, count, stable = 1;
    static uint32_t held_ms;
    static int taps;                    /* presses so far in this go */
    static int tap_wait_ms;             /* time left for another press to join them */
    int level = gpio_get_level(BUTTON_GPIO);
    count = level == last ? count + 1 : 0;
    last = level;
    if (count == STABLE_POLLS && level != stable) {
        stable = level;
        if (level == 0) {
            held_ms = 0;
        } else if (held_ms < LONG_MS) { /* released: a press */
            taps++;
            tap_wait_ms = TAP_GAP_MS;
        }
    }
    if (taps && stable == 1) {
        tap_wait_ms -= POLL_MS;
        if (tap_wait_ms <= 0) {         /* no more presses came */
            taps_done(taps);
            taps = 0;
        }
    }
    if (stable == 0 && held_ms <= RESET_MS) {
        held_ms += POLL_MS;
        if (held_ms == LONG_MS) {
            taps = 0;                   /* a hold ends a go of presses without them */
            nav_toggle_clock();
        } else if (held_ms == WARN_MS && auth_password_set()) {
            nav_toast("Keep holding to remove the dashboard password");
        } else if (held_ms == RESET_MS && auth_password_set()) {
            auth_reset();
            nav_toast("Dashboard password removed");
        }
    }
}

void button_init(void)
{
    const gpio_config_t cfg = {
        .pin_bit_mask = 1ULL << BUTTON_GPIO,
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,   /* the board has one too; harmless */
    };
    gpio_config(&cfg);
    lv_timer_create(poll, POLL_MS, NULL);
}
