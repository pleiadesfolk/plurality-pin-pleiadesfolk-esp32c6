/*
 * BOOT button: switch to the next member of the button shortlist.
 * Swiping left/right on the fronter screen steps forward/back the same way (nav.c).
 * Held for RESET_MS: removes the dashboard password (for when it's forgotten;
 * someone holding the pin could take it apart anyway).
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
#define WARN_MS         4000            /* holding: say what's about to happen */
#define RESET_MS        10000           /* holding: remove the dashboard password */

void button_switch(int direction)
{
    char name[48], msg[64];
    int next = store_step_button_member(direction, name, sizeof(name));
    if (next < 0) {
        nav_toast("No members yet - import them on the dashboard");
        return;
    }
    uint16_t member = (uint16_t)next;
    if (store_add_switch(&member, 1) != ESP_OK) {
        nav_toast("Couldn't switch");
        return;
    }
    ESP_LOGI(TAG, "switched to %s", name);
    nav_show_fronter();
    snprintf(msg, sizeof(msg), "Switched to %s", name);
    nav_toast(msg);
}

static void poll(lv_timer_t *timer)
{
    static int last = 1, count, stable = 1;
    static uint32_t held_ms;
    int level = gpio_get_level(BUTTON_GPIO);
    count = level == last ? count + 1 : 0;
    last = level;
    if (count == STABLE_POLLS && level != stable) {
        stable = level;
        held_ms = 0;
        if (level == 0) {
            button_switch(+1);
        }
    }
    if (stable == 0 && held_ms <= RESET_MS) {
        held_ms += POLL_MS;
        if (held_ms == WARN_MS && auth_password_set()) {
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
