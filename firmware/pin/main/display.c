/*
 * Display and touch glue for the Waveshare ESP32-C6-Touch-AMOLED-1.64.
 *
 * The CO5300 panel can't rotate reliably in hardware (MADCTL MV garbles the
 * picture), so the panel stays in its native portrait mode (280x456) and we
 * rotate in software: LVGL draws a 456x280 landscape screen, and the flush
 * callback turns each drawn strip 90 degrees before sending it to the panel.
 * Touch coordinates get the same rotation.
 *
 * Tested in firmware/landscape_test. The vendor BSP is used only to create the
 * panel and touch drivers.
 */

#include <string.h>
#include "display.h"
#include "esp_timer.h"
#include "esp_heap_caps.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_touch.h"
#include "bsp/esp-bsp.h"
#include "bsp/touch.h"

/* Panel (physical, portrait) */
#define PANEL_W         BSP_LCD_H_RES   /* 280 */
#define PANEL_H         BSP_LCD_V_RES   /* 456 */

_Static_assert(SCREEN_W == PANEL_H && SCREEN_H == PANEL_W, "screen is the panel turned sideways");

/* Set to 1 if the picture comes out upside down */
#define FLIP_180        0

#define BUF_LINES       40              /* height of one LVGL draw strip */

static esp_lcd_panel_handle_t panel;
static esp_lcd_panel_io_handle_t panel_io;
static esp_lcd_touch_handle_t touch;
static uint16_t *rotate_buf;            /* DMA buffer holding the rotated strip */
static display_stats_t stats;

/* ---------- display ---------- */

/* Map a logical (landscape) pixel to a physical (portrait) pixel. */
static inline void to_panel(int x, int y, int *px, int *py)
{
#if FLIP_180
    *px = PANEL_W - 1 - y;
    *py = x;
#else
    *px = y;
    *py = PANEL_H - 1 - x;
#endif
}

static void flush_cb(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map)
{
    int64_t t0 = esp_timer_get_time();
    const uint16_t *src = (const uint16_t *)px_map;
    const int w = lv_area_get_width(area);
    const int h = lv_area_get_height(area);

    /* Physical rectangle covered by this strip (corners map to corners). */
    int ax, ay, bx, by;
    to_panel(area->x1, area->y1, &ax, &ay);
    to_panel(area->x2, area->y2, &bx, &by);
    const int px1 = ax < bx ? ax : bx;
    const int py1 = ay < by ? ay : by;
    const int pw = h;                   /* rotated: width and height swap */

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            int px, py;
            to_panel(area->x1 + x, area->y1 + y, &px, &py);
            uint16_t c = src[y * w + x];
            /* Panel wants the high byte first */
            rotate_buf[(py - py1) * pw + (px - px1)] = (c >> 8) | (c << 8);
        }
    }

    stats.rotate_us += esp_timer_get_time() - t0;
    stats.flushes++;
    stats.pixels += w * h;

    /* Asynchronous: flush_done_cb tells LVGL when the transfer has finished. */
    esp_lcd_panel_draw_bitmap(panel, px1, py1, px1 + pw, py1 + w, rotate_buf);
}

display_stats_t display_take_stats(void)
{
    display_stats_t s = stats;
    memset(&stats, 0, sizeof(stats));
    return s;
}

static bool flush_done_cb(esp_lcd_panel_io_handle_t io, esp_lcd_panel_io_event_data_t *edata, void *user_ctx)
{
    lv_display_flush_ready((lv_display_t *)user_ctx);
    return false;
}

/* The panel only accepts windows that start on an even pixel and have an even size. */
static void rounder_cb(lv_event_t *e)
{
    lv_area_t *area = lv_event_get_param(e);
    area->x1 &= ~1;
    area->y1 &= ~1;
    area->x2 |= 1;
    area->y2 |= 1;
}

/* ---------- touch ---------- */

#define SWIPE_MIN_DISTANCE  60          /* px the finger must travel to count as a swipe */

static display_swipe_cb_t swipe_cb;

static void swipe_async(void *dir)
{
    swipe_cb((lv_dir_t)(uintptr_t)dir);
}

/* Swipes are detected here from raw touch data rather than with LVGL gestures,
 * which are swallowed whenever a screen contains something scrollable. */
static void detect_swipe(bool pressed, lv_point_t point)
{
    static bool was_pressed;
    static lv_point_t start, last;

    if (pressed) {
        if (!was_pressed) {
            start = point;
        }
        last = point;
    } else if (was_pressed && swipe_cb) {
        int dx = last.x - start.x;
        int dy = last.y - start.y;
        lv_dir_t dir = LV_DIR_NONE;
        if (LV_ABS(dx) > SWIPE_MIN_DISTANCE && LV_ABS(dx) > 2 * LV_ABS(dy)) {
            dir = dx > 0 ? LV_DIR_RIGHT : LV_DIR_LEFT;
        } else if (LV_ABS(dy) > SWIPE_MIN_DISTANCE && LV_ABS(dy) > 2 * LV_ABS(dx)) {
            dir = dy > 0 ? LV_DIR_BOTTOM : LV_DIR_TOP;
        }
        /* Called later, outside of input processing, so the callback may change screens */
        if (dir != LV_DIR_NONE) {
            lv_async_call(swipe_async, (void *)(uintptr_t)dir);
        }
    }
    was_pressed = pressed;
}

static void touch_read_cb(lv_indev_t *indev, lv_indev_data_t *data)
{
    esp_lcd_touch_point_data_t point;
    uint8_t count = 0;

    esp_lcd_touch_read_data(touch);
    esp_lcd_touch_get_data(touch, &point, &count, 1);

    if (count == 0) {
        data->state = LV_INDEV_STATE_RELEASED;
        detect_swipe(false, data->point);
        return;
    }
    /* Inverse of to_panel(): physical portrait point -> logical landscape point */
#if FLIP_180
    data->point.x = point.y;
    data->point.y = PANEL_W - 1 - point.x;
#else
    data->point.x = PANEL_H - 1 - point.y;
    data->point.y = point.x;
#endif
    data->state = LV_INDEV_STATE_PRESSED;
    detect_swipe(true, data->point);
}

/* ---------- public ---------- */

void display_set_swipe_cb(display_swipe_cb_t cb)
{
    swipe_cb = cb;
}

void display_set_brightness(uint8_t percent)
{
    /* CO5300 "write display brightness" (0x51), sent as a QSPI command */
    uint8_t level = percent * 255 / 100;
    esp_lcd_panel_io_tx_param(panel_io, (0x02 << 24) | (0x51 << 8), &level, 1);
}

lv_display_t *display_init(void)
{
    bsp_display_config_t disp_config = {0};
    ESP_ERROR_CHECK(bsp_display_new(&disp_config, &panel, &panel_io));

    lv_display_t *disp = lv_display_create(SCREEN_W, SCREEN_H);
    lv_display_set_color_format(disp, LV_COLOR_FORMAT_RGB565);

    const size_t buf_size = SCREEN_W * BUF_LINES * sizeof(uint16_t);
    void *buf1 = heap_caps_malloc(buf_size, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
    void *buf2 = heap_caps_malloc(buf_size, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
    rotate_buf = heap_caps_malloc(buf_size, MALLOC_CAP_DMA);
    assert(buf1 && buf2 && rotate_buf);
    lv_display_set_buffers(disp, buf1, buf2, buf_size, LV_DISPLAY_RENDER_MODE_PARTIAL);

    lv_display_set_flush_cb(disp, flush_cb);
    lv_display_add_event_cb(disp, rounder_cb, LV_EVENT_INVALIDATE_AREA, NULL);

    const esp_lcd_panel_io_callbacks_t cbs = {
        .on_color_trans_done = flush_done_cb,
    };
    ESP_ERROR_CHECK(esp_lcd_panel_io_register_event_callbacks(panel_io, &cbs, disp));

    /* Touch: no swap/mirror in the driver, we rotate in touch_read_cb */
    bsp_display_cfg_t touch_cfg = {0};
    ESP_ERROR_CHECK(bsp_touch_new(&touch_cfg, &touch));

    lv_indev_t *indev = lv_indev_create();
    lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(indev, touch_read_cb);
    lv_indev_set_display(indev, disp);

    return disp;
}
