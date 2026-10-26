#pragma once

#include "lvgl.h"

/** Called right after a screen has been created and shown. */
typedef void (*nav_screen_cb_t)(const char *name, lv_obj_t *screen);

/**
 * Show the first screen and start reacting to swipes and taps:
 *   left / right   - next / previous main screen
 *   down           - pull-down menu (from the namecard screen only)
 *   up             - close the pull-down menu
 *   menu buttons   - Status -> front history, Settings -> settings,
 *                    Connect to pin -> connect
 *   right          - back to the menu from a page opened by a menu button
 */
void nav_init(nav_screen_cb_t on_screen);

/** Open every screen once and log how long creating and drawing it takes. */
void nav_benchmark(void);
