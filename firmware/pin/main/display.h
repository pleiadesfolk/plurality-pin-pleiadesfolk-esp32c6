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

typedef void (*display_swipe_cb_t)(lv_dir_t dir);

/** Call cb with LV_DIR_LEFT/RIGHT/TOP/BOTTOM when the user swipes across the screen. */
void display_set_swipe_cb(display_swipe_cb_t cb);

typedef struct {
    int64_t rotate_us;                  /* time spent rotating strips in software */
    uint32_t flushes;                   /* strips sent to the panel */
    uint32_t pixels;                    /* pixels sent to the panel */
} display_stats_t;

/** Drawing statistics since the previous call (for performance testing). */
display_stats_t display_take_stats(void);

/** Panel brightness, 0-100 %. */
void display_set_brightness(uint8_t percent);
