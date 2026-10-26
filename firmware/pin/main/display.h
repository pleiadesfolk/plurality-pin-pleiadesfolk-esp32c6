#pragma once

#include <stdint.h>
#include "lvgl.h"

/* LVGL screen size: the 280x456 panel used in landscape */
#define SCREEN_W    456
#define SCREEN_H    280

/**
 * Start the panel and touch controller and register them with LVGL.
 * Call after lv_init().
 */
lv_display_t *display_init(void);

/** Panel brightness, 0-100 %. */
void display_set_brightness(uint8_t percent);
