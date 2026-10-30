/*
 * Moving between screens.
 *
 * Only one screen exists at a time: each is created from the Editor's
 * generated <name>_create() function when shown and deleted when left, so RAM
 * use doesn't grow with the number of screens.
 *
 * Three places you can be:
 *   MAIN  - the main screens: the fronter (namecard), Clock, Front history.
 *           Press and hold starts "switch mode": dots show where you are and
 *           swiping left/right slides between the main screens; a tap or 3 s
 *           without swiping ends it. Outside switch mode, swiping left/right
 *           on the fronter screen switches to the next/previous fronter (on
 *           Clock and Front history it still moves between screens).
 *           (The image screens join once members can use image mode.)
 *   MENU  - the pull-down menu, opened by swiping down on the fronter screen
 *   PAGE  - a screen opened by one of the menu's buttons. Connect to pin
 *           opens a two-step sequence (pin Wi-Fi, then web dashboard),
 *           swipe left/right between its steps.
 */

#include <string.h>
#include "nav.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "esp_heap_caps.h"
#include "button.h"
#include "display.h"
#include "ui/plurality_pin.h"

static const char *TAG = "nav";

typedef struct {
    const char *name;                   /* the Editor's screen name (used in code) */
    const char *title;                  /* shown to the user */
    lv_obj_t *(*create)(void);
} screen_t;

static const screen_t watch_screen          = { "watch",                  "Clock",              watch_create };
static const screen_t namecard_screen       = { "namecard_mode",          "Namecard",           namecard_mode_create };
static const screen_t image_full_screen     = { "image_mode_full",        "Image",              image_mode_full_create };
static const screen_t image_text_screen     = { "image_mode_with_text",   "Image with name",    image_mode_with_text_create };
static const screen_t status_screen         = { "status",                 "Status",             status_create };
static const screen_t connect_screen        = { "connect",                "Open the dashboard", connect_create };
static const screen_t connect_wi_fi_screen  = { "connect_wi_fi",          "Connect to the pin", connect_wi_fi_create };
static const screen_t menu_screen           = { "pull_down_menu_initial", "Menu",               pull_down_menu_initial_create };
static const screen_t front_history_screen  = { "front_history",          "Front history",      front_history_create };
static const screen_t settings_screen       = { "settings",               "Settings",           settings_create };

/* Press-and-hold (and left/right away from the fronter screen) moves through these */
static const screen_t *const main_screens[] = {
    &namecard_screen,                   /* the fronter: first, shown at start */
    &watch_screen,
    &front_history_screen,
};
#define MAIN_COUNT (sizeof(main_screens) / sizeof(main_screens[0]))

typedef enum { AT_MAIN, AT_MENU, AT_PAGE } place_t;

static nav_screen_cb_t screen_cb;
static place_t place;
static int main_index;                  /* which main screen, also where the menu closes to */
static const screen_t *page;            /* which page, while AT_PAGE */
static lv_obj_t *toast;

static void show(const screen_t *screen);

/* ---------- toast: short message at the bottom (e.g. the screen's title) ---------- */

static void hide_toast(lv_timer_t *timer)
{
    lv_obj_add_flag(toast, LV_OBJ_FLAG_HIDDEN);
}

void nav_toast(const char *text)
{
    static lv_timer_t *timer;

    if (!toast) {
        toast = lv_label_create(lv_layer_top());
        lv_obj_set_style_bg_color(toast, lv_color_black(), 0);
        lv_obj_set_style_bg_opa(toast, LV_OPA_70, 0);
        lv_obj_set_style_text_color(toast, lv_color_white(), 0);
        lv_obj_set_style_text_font(toast, &lv_font_montserrat_14, 0);
        lv_obj_set_style_pad_hor(toast, 10, 0);
        lv_obj_set_style_pad_ver(toast, 4, 0);
        lv_obj_set_style_radius(toast, 10, 0);
        lv_obj_align(toast, LV_ALIGN_BOTTOM_MID, 0, -6);
        timer = lv_timer_create(hide_toast, 1500, NULL);
        lv_timer_set_auto_delete(timer, false);
    }
    lv_label_set_text(toast, text);
    lv_obj_remove_flag(toast, LV_OBJ_FLAG_HIDDEN);
    lv_timer_set_repeat_count(timer, 1);
    lv_timer_reset(timer);
    lv_timer_resume(timer);
}

/* ---------- menu buttons ---------- */

/* Connect to pin: step 1 join the pin's Wi-Fi, step 2 open the web dashboard */
static const screen_t *const connect_steps[] = { &connect_wi_fi_screen, &connect_screen };
#define CONNECT_STEPS (sizeof(connect_steps) / sizeof(connect_steps[0]))

static void open_page(lv_event_t *e)
{
    place = AT_PAGE;
    page = lv_event_get_user_data(e);
    show(page);
}

/* Index of the current page in connect_steps, or -1 if it isn't one of them */
static int connect_step(void)
{
    for (int i = 0; i < CONNECT_STEPS; i++) {
        if (connect_steps[i] == page) {
            return i;
        }
    }
    return -1;
}

static void make_unclickable(lv_obj_t *obj)
{
    for (uint32_t i = 0; i < lv_obj_get_child_count(obj); i++) {
        lv_obj_t *child = lv_obj_get_child(obj, i);
        lv_obj_remove_flag(child, LV_OBJ_FLAG_CLICKABLE);
        make_unclickable(child);
    }
}

/* Turn a generated tile into a button: the tile itself takes the tap (not the
 * row/icon inside it) and dims while pressed. */
static void make_button(lv_obj_t *tile, const screen_t *target)
{
    make_unclickable(tile);
    lv_obj_add_flag(tile, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_opa(tile, LV_OPA_60, LV_STATE_PRESSED);
    lv_obj_add_event_cb(tile, open_page, LV_EVENT_CLICKED, (void *)target);
}

static void wire_menu(lv_obj_t *scr)
{
    /* Generated layout (see pull_down_menu_initial.xml):
     * screen > [background, column > [status bar, column > [row > tile] x 3]] */
    lv_obj_t *buttons = lv_obj_get_child(lv_obj_get_child(scr, 1), 1);
    make_button(lv_obj_get_child(lv_obj_get_child(buttons, 0), 0), &status_screen);        /* Status */
    make_button(lv_obj_get_child(lv_obj_get_child(buttons, 1), 0), &settings_screen);      /* Settings */
    make_button(lv_obj_get_child(lv_obj_get_child(buttons, 2), 0), &connect_wi_fi_screen); /* Connect to pin */
}

/* ---------- switching ---------- */

#define SLIDE_MS            250         /* screen slide in switch mode */
#define SWITCH_TIMEOUT_MS   3000        /* switch mode ends after this long without a swipe */

/* Show `screen`; `anim` slides it in (LV_SCREEN_LOAD_ANIM_NONE: instant).
 * The old screen is deleted once the new one is in. */
static void show_anim(const screen_t *screen, lv_screen_load_anim_t anim)
{
    uint32_t t0 = lv_tick_get();
    lv_obj_t *scr = screen->create();
    if (screen == &menu_screen) {
        wire_menu(scr);
    }
    lv_screen_load_anim(scr, anim, anim == LV_SCREEN_LOAD_ANIM_NONE ? 0 : SLIDE_MS, 0, true);

    if (screen_cb) {
        screen_cb(screen->name, scr);
    }
    nav_toast(screen->title);
    ESP_LOGI(TAG, "%s (created in %u ms), free heap %u bytes", screen->name,
             (unsigned)lv_tick_elaps(t0), (unsigned)heap_caps_get_free_size(MALLOC_CAP_DEFAULT));
}

static void show(const screen_t *screen)
{
    show_anim(screen, LV_SCREEN_LOAD_ANIM_NONE);
}

/* ---------- switch mode: hold, then swipe between the main screens ---------- */

static bool switching;
static lv_obj_t *dots_row;
static lv_obj_t *dots[MAIN_COUNT];
static lv_timer_t *switch_timer;

static void switch_end(void)
{
    switching = false;
    lv_obj_add_flag(dots_row, LV_OBJ_FLAG_HIDDEN);
    lv_timer_pause(switch_timer);
}

static void switch_timeout(lv_timer_t *timer)
{
    switch_end();
}

static void update_dots(void)
{
    for (int i = 0; i < MAIN_COUNT; i++) {
        lv_obj_set_style_bg_opa(dots[i], i == main_index ? LV_OPA_COVER : LV_OPA_40, 0);
    }
}

static void switch_begin(void)
{
    if (!dots_row) {
        /* Page dots on the top layer, so they stay put while screens slide */
        dots_row = lv_obj_create(lv_layer_top());
        lv_obj_remove_style_all(dots_row);
        lv_obj_set_size(dots_row, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
        lv_obj_set_flex_flow(dots_row, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_pad_column(dots_row, 10, 0);
        lv_obj_set_style_pad_all(dots_row, 8, 0);
        lv_obj_set_style_radius(dots_row, LV_RADIUS_CIRCLE, 0);
        lv_obj_set_style_bg_color(dots_row, lv_color_black(), 0);
        lv_obj_set_style_bg_opa(dots_row, LV_OPA_60, 0);
        lv_obj_align(dots_row, LV_ALIGN_BOTTOM_MID, 0, -40);
        lv_obj_remove_flag(dots_row, LV_OBJ_FLAG_CLICKABLE);
        for (int i = 0; i < MAIN_COUNT; i++) {
            dots[i] = lv_obj_create(dots_row);
            lv_obj_remove_style_all(dots[i]);
            lv_obj_set_size(dots[i], 10, 10);
            lv_obj_set_style_radius(dots[i], LV_RADIUS_CIRCLE, 0);
            lv_obj_set_style_bg_color(dots[i], lv_color_white(), 0);
        }
        switch_timer = lv_timer_create(switch_timeout, SWITCH_TIMEOUT_MS, NULL);
        lv_timer_set_auto_delete(switch_timer, false);
    }
    switching = true;
    update_dots();
    lv_obj_remove_flag(dots_row, LV_OBJ_FLAG_HIDDEN);
    lv_timer_reset(switch_timer);
    lv_timer_set_repeat_count(switch_timer, 1);
    lv_timer_resume(switch_timer);
    nav_toast("Swipe to change screen, tap when done");
}

static void next_main_screen(int step)
{
    main_index = (main_index + MAIN_COUNT + step) % MAIN_COUNT;
    show_anim(main_screens[main_index],
              step > 0 ? LV_SCREEN_LOAD_ANIM_MOVE_LEFT : LV_SCREEN_LOAD_ANIM_MOVE_RIGHT);
    if (switching) {
        update_dots();
        lv_timer_reset(switch_timer);
        lv_timer_set_repeat_count(switch_timer, 1);
        lv_timer_resume(switch_timer);
    }
}

static void on_hold(void)
{
    if (place == AT_MAIN && !switching) {
        switch_begin();
    }
}

static void on_tap(void)
{
    if (switching) {
        switch_end();
    }
}

static void on_swipe(lv_dir_t dir)
{
    switch (place) {
    case AT_MAIN:
        if (switching) {
            if (dir == LV_DIR_LEFT) {
                next_main_screen(+1);
            } else if (dir == LV_DIR_RIGHT) {
                next_main_screen(-1);
            }
        } else if (main_screens[main_index] == &namecard_screen) {
            if (dir == LV_DIR_LEFT) {
                button_switch(+1);      /* next fronter, like the side button */
            } else if (dir == LV_DIR_RIGHT) {
                button_switch(-1);      /* previous fronter */
            } else if (dir == LV_DIR_BOTTOM) {
                place = AT_MENU;
                show(&menu_screen);
            }
        } else if (dir == LV_DIR_LEFT) {
            next_main_screen(+1);
        } else if (dir == LV_DIR_RIGHT) {
            next_main_screen(-1);
        }
        break;
    case AT_MENU:
        if (dir == LV_DIR_TOP) {
            place = AT_MAIN;
            show(main_screens[main_index]);
        }
        break;
    case AT_PAGE: {
        int step = connect_step();
        if (dir == LV_DIR_LEFT && step >= 0 && step + 1 < CONNECT_STEPS) {
            page = connect_steps[step + 1];
            show(page);
        } else if (dir == LV_DIR_RIGHT && step > 0) {
            page = connect_steps[step - 1];
            show(page);
        } else if (dir == LV_DIR_RIGHT) {
            place = AT_MENU;
            show(&menu_screen);
        }
        break;
    }
    }
}

void nav_show_fronter(void)
{
    if (place == AT_MAIN && main_screens[main_index] == &namecard_screen) {
        return;                         /* already there; the namecard updates itself */
    }
    for (int i = 0; i < MAIN_COUNT; i++) {
        if (main_screens[i] == &namecard_screen) {
            main_index = i;
        }
    }
    place = AT_MAIN;
    show(&namecard_screen);
}

void nav_benchmark(void)
{
    static const screen_t *const all[] = {
        &watch_screen, &namecard_screen, &image_full_screen, &image_text_screen, &status_screen,
        &connect_screen, &connect_wi_fi_screen, &menu_screen, &front_history_screen, &settings_screen,
    };

    for (int i = 0; i < sizeof(all) / sizeof(all[0]); i++) {
        int64_t t0 = esp_timer_get_time();
        lv_obj_t *scr = all[i]->create();
        if (all[i] == &menu_screen) {
            wire_menu(scr);
        }
        lv_screen_load_anim(scr, LV_SCREEN_LOAD_ANIM_NONE, 0, 0, true);
        int64_t t1 = esp_timer_get_time();
        display_take_stats();
        lv_refr_now(NULL);
        int64_t t2 = esp_timer_get_time();
        display_stats_t first = display_take_stats();

        lv_obj_invalidate(scr);         /* draw again, to see what the first draw cost extra */
        lv_refr_now(NULL);
        int64_t t3 = esp_timer_get_time();
        display_stats_t again = display_take_stats();

        ESP_LOGI(TAG, "bench %-24s create %3d ms | draw %4d ms (rotate %3d ms) | redraw %4d ms (rotate %3d ms) | %u px",
                 all[i]->name, (int)((t1 - t0) / 1000),
                 (int)((t2 - t1) / 1000), (int)(first.rotate_us / 1000),
                 (int)((t3 - t2) / 1000), (int)(again.rotate_us / 1000), (unsigned)first.pixels);
    }
}

void nav_init(nav_screen_cb_t on_screen)
{
    screen_cb = on_screen;
    place = AT_MAIN;
    main_index = 0;
    show(main_screens[main_index]);
    display_set_swipe_cb(on_swipe);
    display_set_hold_cb(on_hold);
    display_set_tap_cb(on_tap);
}
