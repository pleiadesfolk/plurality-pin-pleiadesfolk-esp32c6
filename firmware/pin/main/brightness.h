#pragma once

#include "lvgl.h"

/**
 * Apply the saved brightness and follow the brightness_percent subject (set by
 * the Settings slider from now on). Call after plurality_pin_init() and
 * after NVS has been initialised (main.c).
 */
void brightness_init(void);

/** Make the Settings screen's thin brightness slider easier to touch. */
void brightness_attach(lv_obj_t *settings_screen);
