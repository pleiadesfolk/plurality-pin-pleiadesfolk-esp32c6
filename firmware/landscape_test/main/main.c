/*
 * Landscape test for the Waveshare ESP32-C6-Touch-AMOLED-1.64.
 *
 * The CO5300 panel can't rotate reliably in hardware (MADCTL MV garbles the
 * picture), so the panel stays in its native portrait mode (280x456) and we
 * rotate in software: LVGL draws a 456x280 landscape screen, and the flush
 * callback turns each drawn strip 90 degrees before sending it to the panel.
 * Touch coordinates get the same rotation.
 *
 * We use the vendor BSP only to create the panel and touch drivers; the LVGL
 * glue (display, flush, touch input, tick, task) is our own.
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "esp_heap_caps.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_touch.h"
#include "lvgl.h"
#include "bsp/esp-bsp.h"
#include "bsp/touch.h"

static const char *TAG = "landscape";

/* Panel (physical, portrait) */
#define PANEL_W         BSP_LCD_H_RES   /* 280 */
#define PANEL_H         BSP_LCD_V_RES   /* 456 */

/* LVGL screen (logical, landscape) */
#define SCREEN_W        PANEL_H         /* 456 */
#define SCREEN_H        PANEL_W         /* 280 */

/* Set to 1 if the picture comes out upside down */
#define FLIP_180        0

#define BUF_LINES       40              /* height of one LVGL draw strip */

static esp_lcd_panel_handle_t panel;
static esp_lcd_panel_io_handle_t panel_io;
static esp_lcd_touch_handle_t touch;
static uint16_t *rotate_buf;            /* DMA buffer holding the rotated strip */

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

    /* Asynchronous: flush_done_cb tells LVGL when the transfer has finished. */
    esp_lcd_panel_draw_bitmap(panel, px1, py1, px1 + pw, py1 + w, rotate_buf);
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

static void touch_read_cb(lv_indev_t *indev, lv_indev_data_t *data)
{
    esp_lcd_touch_point_data_t point;
    uint8_t count = 0;

    esp_lcd_touch_read_data(touch);
    esp_lcd_touch_get_data(touch, &point, &count, 1);

    if (count == 0) {
        data->state = LV_INDEV_STATE_RELEASED;
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
}

/* ---------- LVGL plumbing ---------- */

static uint32_t tick_cb(void)
{
    return esp_timer_get_time() / 1000;
}

static void set_brightness(uint8_t percent)
{
    /* CO5300 "write display brightness" (0x51), sent as a QSPI command */
    uint8_t level = percent * 255 / 100;
    esp_lcd_panel_io_tx_param(panel_io, (0x02 << 24) | (0x51 << 8), &level, 1);
}

static lv_display_t *display_init(void)
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

    return disp;
}

static void touch_init(void)
{
    bsp_display_cfg_t cfg = {0};        /* no swap/mirror: we rotate in touch_read_cb */
    ESP_ERROR_CHECK(bsp_touch_new(&cfg, &touch));

    lv_indev_t *indev = lv_indev_create();
    lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(indev, touch_read_cb);
}

/* ---------- test screen ---------- */

static lv_obj_t *touch_dot;
static lv_obj_t *coord_label;
static lv_obj_t *count_label;
static int tap_count;

static void corner(lv_obj_t *parent, lv_align_t align, lv_color_t color, const char *text)
{
    lv_obj_t *box = lv_obj_create(parent);
    lv_obj_remove_style_all(box);
    lv_obj_set_size(box, 56, 56);
    lv_obj_set_style_bg_color(box, color, 0);
    lv_obj_set_style_bg_opa(box, LV_OPA_COVER, 0);
    lv_obj_align(box, align, 0, 0);
    lv_obj_remove_flag(box, LV_OBJ_FLAG_CLICKABLE);

    lv_obj_t *label = lv_label_create(box);
    lv_label_set_text(label, text);
    lv_obj_set_style_text_color(label, lv_color_black(), 0);
    lv_obj_set_style_text_font(label, &lv_font_montserrat_20, 0);
    lv_obj_center(label);
}

static void screen_touch_cb(lv_event_t *e)
{
    lv_point_t p;
    lv_indev_get_point(lv_indev_active(), &p);

    if (lv_event_get_code(e) == LV_EVENT_RELEASED) {
        lv_obj_add_flag(touch_dot, LV_OBJ_FLAG_HIDDEN);
    } else {
        lv_obj_remove_flag(touch_dot, LV_OBJ_FLAG_HIDDEN);
        lv_obj_set_pos(touch_dot, p.x - 15, p.y - 15);
    }
    lv_label_set_text_fmt(coord_label, "x=%d  y=%d", (int)p.x, (int)p.y);
}

static void button_cb(lv_event_t *e)
{
    tap_count++;
    lv_label_set_text_fmt(count_label, "Tapped %d", tap_count);
}

static void build_test_screen(void)
{
    lv_obj_t *scr = lv_screen_active();
    lv_obj_set_style_bg_color(scr, lv_color_hex(0x202020), 0);
    lv_obj_remove_flag(scr, LV_OBJ_FLAG_SCROLLABLE);

    /* 2px white frame on the outermost pixels: shows any edge that is cut off */
    lv_obj_t *frame = lv_obj_create(scr);
    lv_obj_remove_style_all(frame);
    lv_obj_set_size(frame, SCREEN_W, SCREEN_H);
    lv_obj_set_style_border_color(frame, lv_color_white(), 0);
    lv_obj_set_style_border_width(frame, 2, 0);
    lv_obj_remove_flag(frame, LV_OBJ_FLAG_CLICKABLE);

    corner(scr, LV_ALIGN_TOP_LEFT, lv_color_hex(0xFF4040), "TL");
    corner(scr, LV_ALIGN_TOP_RIGHT, lv_color_hex(0x40FF40), "TR");
    corner(scr, LV_ALIGN_BOTTOM_LEFT, lv_color_hex(0x4080FF), "BL");
    corner(scr, LV_ALIGN_BOTTOM_RIGHT, lv_color_hex(0xFFCC00), "BR");

    lv_obj_t *up = lv_label_create(scr);
    lv_label_set_text(up, LV_SYMBOL_UP " UP " LV_SYMBOL_UP);
    lv_obj_set_style_text_color(up, lv_color_white(), 0);
    lv_obj_set_style_text_font(up, &lv_font_montserrat_20, 0);
    lv_obj_align(up, LV_ALIGN_TOP_MID, 0, 14);

    lv_obj_t *title = lv_label_create(scr);
    lv_label_set_text(title, "Landscape 456 x 280");
    lv_obj_set_style_text_color(title, lv_color_white(), 0);
    lv_obj_set_style_text_font(title, &lv_font_montserrat_28, 0);
    lv_obj_align(title, LV_ALIGN_CENTER, 0, -40);

    coord_label = lv_label_create(scr);
    lv_label_set_text(coord_label, "Touch anywhere");
    lv_obj_set_style_text_color(coord_label, lv_color_hex(0xAAAAAA), 0);
    lv_obj_set_style_text_font(coord_label, &lv_font_montserrat_20, 0);
    lv_obj_align(coord_label, LV_ALIGN_CENTER, 0, 0);

    lv_obj_t *btn = lv_button_create(scr);
    lv_obj_set_size(btn, 160, 56);
    lv_obj_align(btn, LV_ALIGN_BOTTOM_MID, 0, -20);
    lv_obj_add_event_cb(btn, button_cb, LV_EVENT_CLICKED, NULL);
    count_label = lv_label_create(btn);
    lv_label_set_text(count_label, "Tap me");
    lv_obj_set_style_text_font(count_label, &lv_font_montserrat_20, 0);
    lv_obj_center(count_label);

    /* Spinner keeps redrawing, so a frozen screen is obvious */
    lv_obj_t *spinner = lv_spinner_create(scr);
    lv_obj_set_size(spinner, 40, 40);
    lv_obj_align(spinner, LV_ALIGN_RIGHT_MID, -70, 0);

    touch_dot = lv_obj_create(scr);
    lv_obj_remove_style_all(touch_dot);
    lv_obj_set_size(touch_dot, 30, 30);
    lv_obj_set_style_radius(touch_dot, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_bg_color(touch_dot, lv_color_hex(0xFF00FF), 0);
    lv_obj_set_style_bg_opa(touch_dot, LV_OPA_COVER, 0);
    lv_obj_add_flag(touch_dot, LV_OBJ_FLAG_HIDDEN);
    lv_obj_remove_flag(touch_dot, LV_OBJ_FLAG_CLICKABLE);

    lv_obj_add_event_cb(scr, screen_touch_cb, LV_EVENT_PRESSING, NULL);
    lv_obj_add_event_cb(scr, screen_touch_cb, LV_EVENT_RELEASED, NULL);
}

static void lvgl_task(void *arg)
{
    while (1) {
        uint32_t wait_ms = lv_timer_handler();
        if (wait_ms < 5) {
            wait_ms = 5;
        } else if (wait_ms > 30) {
            wait_ms = 30;
        }
        vTaskDelay(pdMS_TO_TICKS(wait_ms));
    }
}

void app_main(void)
{
    lv_init();
    lv_tick_set_cb(tick_cb);

    display_init();
    touch_init();
    set_brightness(100);

    build_test_screen();
    ESP_LOGI(TAG, "Test screen ready, free heap: %u bytes", (unsigned)esp_get_free_heap_size());

    /* All LVGL calls happen in this one task from here on */
    xTaskCreate(lvgl_task, "lvgl", 8192, NULL, 5, NULL);
}
