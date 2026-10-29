/*
 * The namecard screen shows the current fronter.
 *
 * Text: a picture drawn by the dashboard in the phone's browser (so any
 * script and colour emoji work), stored per member by store.c. The text part
 * is 4-bit alpha; it's expanded to 8-bit alpha in RAM (LVGL draws that
 * directly, tinted white) only while the namecard is on screen. Emoji come as
 * a small full-colour patch drawn on top.
 * Without a picture (e.g. before the first import) the generated label shows
 * the plain text instead, in the screen's own font.
 *
 * Background: the screen's gradient panel, coloured from the member's colour.
 */

#include <string.h>
#include <stdlib.h>
#include "esp_log.h"
#include "namecard.h"
#include "store.h"

static const char *TAG = "namecard";

typedef struct {
    lv_obj_t *panel;                    /* gradient background */
    lv_obj_t *label;                    /* generated text label (fallback) */
    lv_obj_t *card;                     /* card picture */
    lv_obj_t *patch;                    /* emoji colour patch, child of card */
    uint8_t *card_pixels;               /* A8, owned */
    uint8_t *patch_pixels;              /* RGB565A8, owned */
    lv_image_dsc_t card_dsc, patch_dsc;
} namecard_t;

static namecard_t nc;                   /* all NULL while the namecard isn't shown */

static void free_pixels(void)
{
    free(nc.card_pixels);
    free(nc.patch_pixels);
    nc.card_pixels = nc.patch_pixels = NULL;
}

static void deleted(lv_event_t *e)
{
    free_pixels();
    memset(&nc, 0, sizeof(nc));
}

static lv_color_t darken(uint32_t rgb, int percent)
{
    int r = ((rgb >> 16) & 0xFF) * (100 - percent) / 100;
    int g = ((rgb >> 8) & 0xFF) * (100 - percent) / 100;
    int b = (rgb & 0xFF) * (100 - percent) / 100;
    return lv_color_make(r, g, b);
}

/* Expand the stored card (see store_card_header_t) into LVGL images; false if unusable */
static bool load_card(void)
{
    size_t size;
    uint8_t *file = store_load_front_card(&size);
    if (!file) {
        return false;
    }
    const store_card_header_t *h = (const store_card_header_t *)file;
    size_t a4_stride = (h->w + 1) / 2;
    size_t a4_size = a4_stride * h->h;
    size_t patch_size = (size_t)h->patch_w * h->patch_h * 3;
    if (memcmp(h->magic, "PC1", 4) != 0 || size < sizeof(*h) + a4_size + patch_size) {
        ESP_LOGW(TAG, "card picture is damaged");
        free(file);
        return false;
    }

    nc.card_pixels = malloc((size_t)h->w * h->h);
    nc.patch_pixels = patch_size ? malloc(patch_size) : NULL;
    if (!nc.card_pixels || (patch_size && !nc.patch_pixels)) {
        ESP_LOGW(TAG, "not enough memory for the card picture");
        free(file);
        free_pixels();
        return false;
    }

    /* 4-bit alpha -> 8-bit alpha (0xF -> 0xFF) */
    const uint8_t *a4 = file + sizeof(*h);
    for (int y = 0; y < h->h; y++) {
        const uint8_t *src = a4 + y * a4_stride;
        uint8_t *dst = nc.card_pixels + y * h->w;
        for (int x = 0; x < h->w; x++) {
            uint8_t v = x & 1 ? src[x / 2] & 0x0F : src[x / 2] >> 4;
            dst[x] = v * 17;
        }
    }
    if (patch_size) {
        memcpy(nc.patch_pixels, a4 + a4_size, patch_size);
    }

    nc.card_dsc = (lv_image_dsc_t) {
        .header = { .magic = LV_IMAGE_HEADER_MAGIC, .cf = LV_COLOR_FORMAT_A8,
                    .w = h->w, .h = h->h, .stride = h->w },
        .data = nc.card_pixels,
        .data_size = (uint32_t)h->w * h->h,
    };
    lv_image_set_src(nc.card, &nc.card_dsc);

    if (patch_size) {
        nc.patch_dsc = (lv_image_dsc_t) {
            .header = { .magic = LV_IMAGE_HEADER_MAGIC, .cf = LV_COLOR_FORMAT_RGB565A8,
                        .w = h->patch_w, .h = h->patch_h, .stride = h->patch_w * 2 },
            .data = nc.patch_pixels,
            .data_size = patch_size,
        };
        lv_image_set_src(nc.patch, &nc.patch_dsc);
        lv_obj_set_pos(nc.patch, h->patch_x, h->patch_y);
        lv_obj_remove_flag(nc.patch, LV_OBJ_FLAG_HIDDEN);
    } else {
        lv_obj_add_flag(nc.patch, LV_OBJ_FLAG_HIDDEN);
    }
    free(file);
    return true;
}

static void refresh(void)
{
    char text[128];
    uint32_t color;
    bool changed;
    store_get_front_card(text, sizeof(text), &color, &changed);

    lv_obj_set_style_bg_color(nc.panel, darken(color, 60), 0);
    lv_obj_set_style_bg_grad_color(nc.panel, lv_color_hex(color), 0);

    /* Drop the old picture first, so old and new aren't in RAM together */
    lv_image_set_src(nc.card, NULL);
    lv_image_set_src(nc.patch, NULL);
    free_pixels();

    if (load_card()) {
        lv_obj_add_flag(nc.label, LV_OBJ_FLAG_HIDDEN);
        lv_obj_remove_flag(nc.card, LV_OBJ_FLAG_HIDDEN);
    } else {
        lv_label_set_text(nc.label, text);
        lv_obj_remove_flag(nc.label, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(nc.card, LV_OBJ_FLAG_HIDDEN);
    }
}

void namecard_attach(lv_obj_t *scr)
{
    /* Generated layout (see namecard_mode.xml): screen > [panel, container > label] */
    nc.panel = lv_obj_get_child(scr, 0);
    lv_obj_t *box = lv_obj_get_child(scr, 1);
    nc.label = lv_obj_get_child(box, 0);

    /* Same place as the label: left edge, vertically centred in the text box */
    nc.card = lv_image_create(box);
    lv_obj_align(nc.card, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_image_recolor(nc.card, lv_color_white(), 0);
    lv_obj_set_style_image_recolor_opa(nc.card, LV_OPA_COVER, 0);
    nc.patch = lv_image_create(nc.card);

    lv_obj_add_event_cb(scr, deleted, LV_EVENT_DELETE, NULL);
    refresh();
}

void namecard_poll(void)
{
    char text[8];
    uint32_t color;
    bool changed;
    /* Always called, so the change flag is consumed even while the namecard isn't shown */
    store_get_front_card(text, sizeof(text), &color, &changed);
    if (changed && nc.panel) {
        refresh();
    }
}
