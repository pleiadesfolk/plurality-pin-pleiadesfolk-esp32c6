#pragma once

#include "lvgl.h"

/** Called right after a screen has been created and shown. */
typedef void (*nav_screen_cb_t)(const char *name, lv_obj_t *screen);

/**
 * Show the first screen (the fronter) and start reacting to swipes and taps:
 *   press and hold - switch mode: page dots appear, then swipe left/right
 *                    slides between fronter, Clock and Front history; tap (or
 *                    wait 3 s) to finish
 *   left / right   - on the fronter screen: next / previous fronter (like the
 *                    side button); on the other main screens: next / previous screen
 *   down           - pull-down menu (from the fronter screen only)
 *   up (in menu)   - close the pull-down menu
 *   menu buttons   - Status -> status, Settings -> settings,
 *                    Connect to pin -> the dashboard's QR code
 *   right          - back a step, or to the menu from a page opened by a menu button
 */
void nav_init(nav_screen_cb_t on_screen);

/** Go to the screen showing the current fronter (in their display mode); also
 *  called when the new fronter's mode needs a different screen. */
void nav_show_fronter(void);

/** Show a short message at the bottom of the screen for a moment. */
void nav_toast(const char *text);

/** Open every screen once and log how long creating and drawing it takes. */
void nav_benchmark(void);
