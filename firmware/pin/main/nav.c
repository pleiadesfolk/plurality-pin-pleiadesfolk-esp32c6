/*
 * Moving between screens.
 *
 * Only one screen exists at a time: each is created from the Editor's
 * generated <name>_create() function when shown and deleted when left, so RAM
 * use doesn't grow with the number of screens.
 *
 * Three places you can be:
 *   MAIN  - the main screens, swipe left/right between them
 *   MENU  - the pull-down menu, opened by swiping down on the namecard screen
 *   PAGE  - a screen opened by one of the menu's buttons
 */

#include <string.h>
#include "nav.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "esp_heap_caps.h"
#include "display.h"
#include "ui/plurality_pin.h"

static const char *TAG = "nav";

typedef struct {
    const char *name;
    lv_obj_t *(*create)(void);
} screen_t;

static const screen_t watch_screen          = { "watch",                  watch_create };
static const screen_t namecard_screen       = { "namecard_mode",          namecard_mode_create };
static const screen_t image_full_screen     = { "image_mode_full",        image_mode_full_create };
static const screen_t image_text_screen     = { "image_mode_with_text",   image_mode_with_text_create };
static const screen_t status_screen         = { "status",                 status_create };
static const screen_t connect_screen        = { "connect",                connect_create };
static const screen_t connect_wi_fi_screen  = { "connect_wi_fi",          connect_wi_fi_create };
static const screen_t menu_screen           = { "pull_down_menu_initial", pull_down_menu_initial_create };
static const screen_t front_history_screen  = { "front_history",          front_history_create };
static const screen_t settings_screen       = { "settings",               settings_create };

/* Swipe left/right moves through these */
static const screen_t *const main_screens[] = {
    &watch_screen,
    &namecard_screen,
    &image_full_screen,
    &image_text_screen,
    &front_history_screen,
    &connect_screen,
    &connect_wi_fi_screen,
};
#define MAIN_COUNT (sizeof(main_screens) / sizeof(main_screens[0]))

typedef enum { AT_MAIN, AT_MENU, AT_PAGE } place_t;

static nav_screen_cb_t screen_cb;
static place_t place;
static int main_index;                  /* which main screen, also where the menu closes to */
static lv_obj_t *toast;

static void show(const screen_t *screen);

/* ---------- screen name toast (for testing) ---------- */

static void hide_toast(lv_timer_t *timer)
{
    lv_obj_add_flag(toast, LV_OBJ_FLAG_HIDDEN);
}

static void show_toast(const char *text)
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

static void open_page(lv_event_t *e)
{
    place = AT_PAGE;
    show(lv_event_get_user_data(e));
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
    make_button(lv_obj_get_child(lv_obj_get_child(buttons, 2), 0), &connect_screen);       /* Connect to pin */
}

/* ---------- switching ---------- */

static void show(const screen_t *screen)
{
    uint32_t t0 = lv_tick_get();
    lv_obj_t *scr = screen->create();
    if (screen == &menu_screen) {
        wire_menu(scr);
    }
    /* Instant switch; the old screen is deleted once the new one is shown */
    lv_screen_load_anim(scr, LV_SCREEN_LOAD_ANIM_NONE, 0, 0, true);

    if (screen_cb) {
        screen_cb(screen->name, scr);
    }
    show_toast(screen->name);
    ESP_LOGI(TAG, "%s (created in %u ms), free heap %u bytes", screen->name,
             (unsigned)lv_tick_elaps(t0), (unsigned)heap_caps_get_free_size(MALLOC_CAP_DEFAULT));
}

static void on_swipe(lv_dir_t dir)
{
    switch (place) {
    case AT_MAIN:
        if (dir == LV_DIR_LEFT) {
            main_index = (main_index + 1) % MAIN_COUNT;
            show(main_screens[main_index]);
        } else if (dir == LV_DIR_RIGHT) {
            main_index = (main_index + MAIN_COUNT - 1) % MAIN_COUNT;
            show(main_screens[main_index]);
        } else if (dir == LV_DIR_BOTTOM && main_screens[main_index] == &namecard_screen) {
            place = AT_MENU;
            show(&menu_screen);
        }
        break;
    case AT_MENU:
        if (dir == LV_DIR_TOP) {
            place = AT_MAIN;
            show(main_screens[main_index]);
        }
        break;
    case AT_PAGE:
        if (dir == LV_DIR_RIGHT) {
            place = AT_MENU;
            show(&menu_screen);
        }
        break;
    }
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
}
