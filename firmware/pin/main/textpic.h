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
    /* where there's any ink (text or emoji), for spreading a gradient over it */
    uint16_t ink_x0, ink_y0, ink_x1, ink_y1;
    /* gradient text: one colour per column (or row, if vertical); NULL: alpha only */
    lv_color_t *colors;
    bool vertical;
} textpic_t;

/** Register the line-by-line decoder with LVGL. Call once after lv_init(). */
void textpic_init(void);

/** Read the header (and patch) of the text picture at `path` into `t`; false if unusable. */
bool textpic_open(textpic_t *t, const char *path);

/**
 * Colour the text from a table instead of the image's recolour style: entry i
 * colours column i of the picture (row i if `vertical`), so there are
 * dsc.header.w (or .h) entries. Returns the table for the caller to fill, or
 * NULL if out of memory. Call before lv_image_set_src(); to change the colours
 * later, refill the table and invalidate the image. Emoji keep their colours.
 */
lv_color_t *textpic_colors(textpic_t *t, bool vertical);

/** Free what textpic_open() allocated. Unset any image showing it first. */
void textpic_close(textpic_t *t);
