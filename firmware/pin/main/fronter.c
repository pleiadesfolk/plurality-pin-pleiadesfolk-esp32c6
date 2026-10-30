/*
 * The fronter screen: shows the current fronter in their display mode.
 *
 *   namecard       namecard_mode.xml: gradient + namecard text picture
 *   image          image_mode_full.xml: 280x280 photo
 *   image with name image_mode_with_text.xml: member-coloured background,
 *                  name text picture, photo in a circle cut off by the right edge
 *
 * All pictures are drawn by the dashboard in the phone's browser and stored
 * per member by store.c (so any script and colour emoji work):
 *  - Text pictures are 4-bit alpha, read line by line from their file while
 *    drawing (textpic.c), tinted white. Emoji come as a small full-colour
 *    patch drawn on top.
 *  - Photos are LVGL .bin images in a flash slot (photos.c), mapped into
 *    memory and drawn straight from flash: fast, and no RAM. (Photos that
 *    didn't fit in a slot are read from their file instead, which is slow.)
 * Without a picture (e.g. before the first import) the generated label shows
 * plain text instead, in the screen's own font.
 */

#include <string.h>
#include <stdlib.h>
#include "esp_log.h"
#include "fronter.h"
#include "nav.h"
#include "store.h"
#include "textpic.h"
#include "photos.h"

static const char *TAG = "fronter";

/* A text picture shown in an image object, with its emoji patch as a child */
typedef struct {
    lv_obj_t *img, *patch;
    textpic_t pic;
} text_picture_t;

typedef struct {
    bool shown;
    store_mode_t mode;
    lv_obj_t *panel;                    /* background, coloured per member */
    lv_obj_t *label;                    /* generated text label (fallback) */
    lv_obj_t *photo;                    /* image modes: the photo */
    text_picture_t text;
    bool mapped;                        /* photo_dsc points into a mapped flash slot */
    esp_partition_mmap_handle_t map;
    lv_image_dsc_t photo_dsc;
} fronter_t;

static fronter_t fr;                    /* fr.shown is false while no fronter screen exists */

/* ---------- text pictures ---------- */

static void text_free(text_picture_t *t)
{
    if (t->img) {
        lv_image_set_src(t->img, NULL);
        lv_image_set_src(t->patch, NULL);
    }
    textpic_close(&t->pic);
}

/* Create the image objects for a text picture inside `parent` */
static void text_create(text_picture_t *t, lv_obj_t *parent)
{
    t->img = lv_image_create(parent);
    lv_obj_set_style_image_recolor(t->img, lv_color_white(), 0);
    lv_obj_set_style_image_recolor_opa(t->img, LV_OPA_COVER, 0);
    t->patch = lv_image_create(t->img);
}

/* Show the current fronter's `kind` text picture in t; false if there's none */
static bool text_load(text_picture_t *t, store_picture_t kind)
{
    text_free(t);
    char path[64];
    if (!store_front_picture_file(kind, path, sizeof(path)) || !textpic_open(&t->pic, path)) {
        return false;
    }
    lv_image_set_src(t->img, &t->pic.dsc);
    if (t->pic.patch_pixels) {
        lv_image_set_src(t->patch, &t->pic.patch_dsc);
        lv_obj_set_pos(t->patch, t->pic.patch_x, t->pic.patch_y);
        lv_obj_remove_flag(t->patch, LV_OBJ_FLAG_HIDDEN);
    } else {
        lv_obj_add_flag(t->patch, LV_OBJ_FLAG_HIDDEN);
    }
    return true;
}

/* Show the text picture, or the plain-text fallback in the generated label */
static void text_or_label(store_picture_t kind, const char *fallback)
{
    if (text_load(&fr.text, kind)) {
        lv_obj_add_flag(fr.label, LV_OBJ_FLAG_HIDDEN);
        lv_obj_remove_flag(fr.text.img, LV_OBJ_FLAG_HIDDEN);
    } else {
        lv_label_set_text(fr.label, fallback);
        lv_obj_remove_flag(fr.label, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(fr.text.img, LV_OBJ_FLAG_HIDDEN);
    }
}

/* ---------- photos ---------- */

static void photo_free(void)
{
    if (fr.photo) {
        lv_image_set_src(fr.photo, NULL);
    }
    if (fr.mapped) {
        photos_unmap(fr.map);
        fr.mapped = false;
    }
}

/* Show the current fronter's photo of `kind` in fr.photo; false if there's none */
static bool photo_load(store_picture_t kind)
{
    photo_free();
    char id[16], src[64];
    size_t len;
    const uint8_t *p = NULL;
    if (store_front_id(id, sizeof(id))) {
        p = photos_map(id, kind == STORE_PICTURE_SIDE ? PHOTO_SIDE : PHOTO_FULL, &len, &fr.map);
    }
    if (p) {
        lv_image_header_t h;
        memcpy(&h, p, sizeof(h));
        size_t bytes = (size_t)h.h * h.stride * (h.cf == LV_COLOR_FORMAT_RGB565A8 ? 3 : 2) / 2;
        if (h.magic == LV_IMAGE_HEADER_MAGIC && h.w && h.h && sizeof(h) + bytes <= len) {
            fr.mapped = true;
            fr.photo_dsc = (lv_image_dsc_t) { .header = h, .data = p + sizeof(h), .data_size = bytes };
            lv_image_set_src(fr.photo, &fr.photo_dsc);
            return true;
        }
        photos_unmap(fr.map);           /* damaged slot */
    }
    if (store_front_image_src(kind, src, sizeof(src))) {
        lv_image_set_src(fr.photo, src);   /* in a file: slow */
        return true;
    }
    return false;
}

/* ---------- screens ---------- */

static lv_color_t darken(uint32_t rgb, int percent)
{
    int r = ((rgb >> 16) & 0xFF) * (100 - percent) / 100;
    int g = ((rgb >> 8) & 0xFF) * (100 - percent) / 100;
    int b = (rgb & 0xFF) * (100 - percent) / 100;
    return lv_color_make(r, g, b);
}

static void refresh(void)
{
    char text[128];
    uint32_t color;
    bool changed;
    store_get_front_card(text, sizeof(text), &color, &changed);

    switch (fr.mode) {
    case STORE_MODE_CARD:
        lv_obj_set_style_bg_color(fr.panel, darken(color, 60), 0);
        lv_obj_set_style_bg_grad_color(fr.panel, lv_color_hex(color), 0);
        text_or_label(STORE_PICTURE_CARD, text);
        break;

    case STORE_MODE_IMAGE:
        if (photo_load(STORE_PICTURE_FULL)) {
            lv_obj_add_flag(fr.label, LV_OBJ_FLAG_HIDDEN);
        } else {
            lv_label_set_text(fr.label, "No image yet - add one on the dashboard");
            lv_obj_remove_flag(fr.label, LV_OBJ_FLAG_HIDDEN);
        }
        break;

    case STORE_MODE_IMAGE_TEXT: {
        lv_obj_set_style_bg_color(fr.panel, lv_color_hex(color), 0);
        char label[64];
        store_front_label(label, sizeof(label));
        text_or_label(STORE_PICTURE_LABEL, label);
        photo_load(STORE_PICTURE_SIDE);
        break;
    }
    }
}

static void deleted(lv_event_t *e)
{
    text_free(&fr.text);
    if (fr.mapped) {
        photos_unmap(fr.map);           /* the image object is already gone */
    }
    memset(&fr, 0, sizeof(fr));
}

void fronter_attach(lv_obj_t *scr, store_mode_t mode)
{
    memset(&fr, 0, sizeof(fr));
    fr.mode = mode;

    switch (mode) {
    case STORE_MODE_CARD: {
        /* namecard_mode.xml: screen > [panel, container > label] */
        fr.panel = lv_obj_get_child(scr, 0);
        lv_obj_t *box = lv_obj_get_child(scr, 1);
        fr.label = lv_obj_get_child(box, 0);
        text_create(&fr.text, box);
        lv_obj_align(fr.text.img, LV_ALIGN_LEFT_MID, 0, 0);  /* where the label is */
        break;
    }
    case STORE_MODE_IMAGE: {
        /* image_mode_full.xml: screen > container > [rotated panel, image]; the
         * image is replaced by the member's photo, and a label is added for
         * when there's no photo */
        lv_obj_t *box = lv_obj_get_child(scr, 0);
        fr.photo = lv_obj_get_child(box, 1);
        fr.label = lv_label_create(scr);
        lv_obj_set_style_text_color(fr.label, lv_color_hex(0x333333), 0);
        lv_obj_center(fr.label);
        break;
    }
    case STORE_MODE_IMAGE_TEXT: {
        /* image_mode_with_text.xml: screen > [container > panel, column > label,
         * container > image (350 px circle, mostly off-screen)] */
        fr.panel = lv_obj_get_child(lv_obj_get_child(scr, 0), 0);
        lv_obj_t *column = lv_obj_get_child(scr, 1);
        fr.label = lv_obj_get_child(column, 0);
        text_create(&fr.text, column);              /* the column centres it */
        /* The stored photo is just the circle's visible part, already cut */
        lv_obj_add_flag(lv_obj_get_child(lv_obj_get_child(scr, 2), 0), LV_OBJ_FLAG_HIDDEN);
        fr.photo = lv_image_create(scr);
        lv_obj_set_pos(fr.photo, 228, 0);
        break;
    }
    }
    fr.shown = true;
    lv_obj_add_event_cb(scr, deleted, LV_EVENT_DELETE, NULL);
    refresh();
}

void fronter_poll(void)
{
    char text[8];
    uint32_t color;
    bool changed;
    /* Always called, so the change flag is consumed even while no fronter screen is shown */
    store_get_front_card(text, sizeof(text), &color, &changed);
    if (!changed || !fr.shown) {
        return;
    }
    if (store_front_mode() != fr.mode) {
        nav_show_fronter();             /* a different screen for the new fronter's mode */
    } else {
        refresh();
    }
}
