/*
 * An LVGL image decoder for text pictures (see textpic.h).
 *
 * LVGL's own decoder would expand the whole 4-bit picture into an 8-bit copy
 * in RAM before drawing (~80 KB for a namecard), which leaves too little for
 * Wi-Fi and the web server. This one tells LVGL the picture is 8-bit alpha,
 * hands it no decoded copy, and when asked for each line (get_area) reads that
 * line of 4-bit alpha from the file and expands it into a one-line buffer.
 * LVGL then draws it tinted (the image's recolour style).
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "esp_log.h"
#include "store.h"
#include "textpic.h"
#include "lvgl_private.h"            /* decoder internals: lv_image_decoder_dsc_t */

static const char *TAG = "textpic";

/* Marks a textpic_t source; LVGL's own decoders don't look at USER flags */
#define TEXTPIC_FLAG LV_IMAGE_FLAGS_USER1

typedef struct {
    FILE *f;
    lv_draw_buf_t *line;                /* one decoded line, A8 */
    uint8_t *raw;                       /* one line of 4-bit alpha from the file */
} decoder_state_t;

static bool is_textpic(lv_image_decoder_dsc_t *dsc)
{
    return dsc->src_type == LV_IMAGE_SRC_VARIABLE
           && (((const lv_image_dsc_t *)dsc->src)->header.flags & TEXTPIC_FLAG);
}

static lv_result_t info_cb(lv_image_decoder_t *decoder, lv_image_decoder_dsc_t *dsc, lv_image_header_t *header)
{
    if (!is_textpic(dsc)) {
        return LV_RESULT_INVALID;
    }
    *header = ((const lv_image_dsc_t *)dsc->src)->header;   /* already set up as A8 */
    header->flags &= ~TEXTPIC_FLAG;
    return LV_RESULT_OK;
}

static lv_result_t open_cb(lv_image_decoder_t *decoder, lv_image_decoder_dsc_t *dsc)
{
    const textpic_t *t = (const textpic_t *)dsc->src;
    decoder_state_t *st = calloc(1, sizeof(*st));
    if (!st) {
        return LV_RESULT_INVALID;
    }
    st->f = fopen(t->path, "rb");
    if (st->f) {
        /* Lines are read one after another: a bigger buffer means far fewer
         * trips to the filesystem than the default 128 bytes */
        setvbuf(st->f, NULL, _IOFBF, 4096);
    }
    st->raw = malloc(t->stride);
    st->line = lv_draw_buf_create(t->dsc.header.w, 1, LV_COLOR_FORMAT_A8, LV_STRIDE_AUTO);
    if (!st->f || !st->raw || !st->line) {
        if (st->f) {
            fclose(st->f);
        }
        free(st->raw);
        if (st->line) {
            lv_draw_buf_destroy(st->line);
        }
        free(st);
        return LV_RESULT_INVALID;
    }
    dsc->user_data = st;
    dsc->decoded = NULL;                /* no whole picture: LVGL asks line by line */
    return LV_RESULT_OK;
}

static lv_result_t get_area_cb(lv_image_decoder_t *decoder, lv_image_decoder_dsc_t *dsc,
                               const lv_area_t *full_area, lv_area_t *decoded_area)
{
    const textpic_t *t = (const textpic_t *)dsc->src;
    decoder_state_t *st = dsc->user_data;

    /* Same protocol as LVGL's bin decoder: first call starts at the top, then one line per call */
    if (decoded_area->y1 == LV_COORD_MIN) {
        *decoded_area = *full_area;
        decoded_area->y2 = decoded_area->y1;
    } else {
        decoded_area->y1++;
        decoded_area->y2++;
    }
    if (decoded_area->y1 > full_area->y2) {
        return LV_RESULT_INVALID;
    }

    long offset = sizeof(store_card_header_t) + (long)decoded_area->y1 * t->stride;
    if (fseek(st->f, offset, SEEK_SET) != 0 || fread(st->raw, 1, t->stride, st->f) != t->stride) {
        return LV_RESULT_INVALID;
    }
    lv_draw_buf_t *line = lv_draw_buf_reshape(st->line, LV_COLOR_FORMAT_A8,
                                              lv_area_get_width(decoded_area), 1, LV_STRIDE_AUTO);
    if (!line) {
        return LV_RESULT_INVALID;
    }
    uint8_t *out = line->data;
    for (int32_t x = decoded_area->x1; x <= decoded_area->x2; x++) {
        uint8_t v = x & 1 ? st->raw[x / 2] & 0x0F : st->raw[x / 2] >> 4;
        *out++ = v * 17;                /* 0xF -> 0xFF */
    }
    dsc->decoded = line;
    return LV_RESULT_OK;
}

static void close_cb(lv_image_decoder_t *decoder, lv_image_decoder_dsc_t *dsc)
{
    decoder_state_t *st = dsc->user_data;
    if (st) {
        fclose(st->f);
        free(st->raw);
        lv_draw_buf_destroy(st->line);
        free(st);
    }
}

void textpic_init(void)
{
    lv_image_decoder_t *d = lv_image_decoder_create();
    lv_image_decoder_set_info_cb(d, info_cb);
    lv_image_decoder_set_open_cb(d, open_cb);
    lv_image_decoder_set_get_area_cb(d, get_area_cb);
    lv_image_decoder_set_close_cb(d, close_cb);
}

bool textpic_open(textpic_t *t, const char *path)
{
    memset(t, 0, sizeof(*t));
    FILE *f = fopen(path, "rb");
    if (!f) {
        return false;
    }
    store_card_header_t h;
    bool ok = fread(&h, sizeof(h), 1, f) == 1 && memcmp(h.magic, "PC1", 4) == 0 && h.w && h.h;
    size_t patch_size = ok ? (size_t)h.patch_w * h.patch_h * 3 : 0;
    if (ok && patch_size) {
        t->patch_pixels = malloc(patch_size);
        ok = t->patch_pixels
             && fseek(f, sizeof(h) + (long)((h.w + 1) / 2) * h.h, SEEK_SET) == 0
             && fread(t->patch_pixels, 1, patch_size, f) == patch_size;
    }
    fclose(f);
    if (!ok) {
        ESP_LOGW(TAG, "%s is unusable", path);
        textpic_close(t);
        return false;
    }

    strlcpy(t->path, path, sizeof(t->path));
    t->stride = (h.w + 1) / 2;
    t->dsc = (lv_image_dsc_t) {
        .header = { .magic = LV_IMAGE_HEADER_MAGIC, .cf = LV_COLOR_FORMAT_A8, .flags = TEXTPIC_FLAG,
                    .w = h.w, .h = h.h, .stride = h.w },
        .data = (const uint8_t *)t,     /* not read: the decoder reads the file */
        .data_size = 1,
    };
    if (patch_size) {
        t->patch_dsc = (lv_image_dsc_t) {
            .header = { .magic = LV_IMAGE_HEADER_MAGIC, .cf = LV_COLOR_FORMAT_RGB565A8,
                        .w = h.patch_w, .h = h.patch_h, .stride = h.patch_w * 2 },
            .data = t->patch_pixels,
            .data_size = patch_size,
        };
        t->patch_x = h.patch_x;
        t->patch_y = h.patch_y;
    }
    return true;
}

void textpic_close(textpic_t *t)
{
    free(t->patch_pixels);
    memset(t, 0, sizeof(*t));
}
