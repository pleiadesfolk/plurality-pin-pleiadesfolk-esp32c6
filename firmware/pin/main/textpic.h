#pragma once

#include <stdbool.h>
#include "lvgl.h"

/*
 * Text pictures (namecard text, the name beside a photo) drawn straight from
 * their file, one line at a time, so they need almost no RAM. The file format
 * is store_card_header_t (store.h): 4-bit alpha text + an optional emoji patch.
 */

typedef struct {
    lv_image_dsc_t dsc;                 /* give &dsc to lv_image_set_src(); must stay first */
    char path[64];
    uint16_t stride;                    /* bytes per row of 4-bit alpha */
    /* emoji colour patch, kept in RAM (small) */
    uint8_t *patch_pixels;
    lv_image_dsc_t patch_dsc;
    uint16_t patch_x, patch_y;
} textpic_t;

/** Register the line-by-line decoder with LVGL. Call once after lv_init(). */
void textpic_init(void);

/** Read the header (and patch) of the text picture at `path` into `t`; false if unusable. */
bool textpic_open(textpic_t *t, const char *path);

/** Free what textpic_open() allocated. Unset any image showing it first. */
void textpic_close(textpic_t *t);
