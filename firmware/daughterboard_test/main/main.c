/*
 * Daughterboard test for the plurality pin.
 *
 * Tests the button/LED daughterboard (hardware/electronics/badgebuttonboard)
 * fitted to the Waveshare ESP32-C6-Touch-AMOLED-1.64, and shows the results
 * on the screen. Everything is also logged to the serial monitor.
 *
 *   Up button    GPIO6   active low (the upper button)
 *   Down button  GPIO3   active low (the lower button)
 *   LED     GPIO2   red channel only, active low (pin low = lit)
 *
 * The test runs in three parts:
 *
 *   1. Pin check (automatic, at power-up). Drives each of the three pins low
 *      in turn and reads the others back, to catch solder bridges between
 *      them and pins stuck to GND or 3V3. The result shows at the top right.
 *   2. LED check (watch the LED). Off, on, off, on, then a fade up and down.
 *      The red dot on the screen shows what the LED should be doing.
 *   3. Button check (press the buttons). Each button has a card that lights
 *      while it's held and counts presses; the LED lights while either is
 *      held. Once both have been pressed PASS_PRESSES times the screen shows
 *      PASS. Holding both for a second runs the LED check again.
 *
 * The display code (software rotation to landscape) is the same as
 * firmware/pin/main/display.c, cut down: no touch, no shared SD card bus.
 * The board support package comes from firmware/pin/components.
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/ledc.h"
#include "esp_err.h"
#include "esp_heap_caps.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_ops.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "lvgl.h"
#include "bsp/esp-bsp.h"

static const char *TAG = "dbtest";

/* ---------- pins ---------- */

#define BTN_UP_GPIO     GPIO_NUM_6      /* upper button */
#define BTN_DOWN_GPIO   GPIO_NUM_3      /* lower button */
#define LED_GPIO        GPIO_NUM_2

/* ---------- timing ---------- */

#define POLL_MS         10
#define STABLE_POLLS    2       /* level must hold for 20 ms to count (debounce) */
#define STUCK_MS        5000    /* held this long: warn that the button may be stuck */
#define COMBO_MS        1000    /* both held this long: run the LED check again */
#define PASS_PRESSES    5       /* presses needed on each button to pass */

/* The tick is 100 Hz: a delay shorter than one tick would be no delay at all */
_Static_assert(pdMS_TO_TICKS(POLL_MS) >= 1, "POLL_MS is shorter than one FreeRTOS tick");

/* ---------- colours ---------- */

#define COL_BG          0x000000
#define COL_CARD        0x262626
#define COL_DIM         0x9A9A9A
#define COL_TEXT        0xFFFFFF
#define COL_GOOD        0x3DDC84
#define COL_BAD         0xFF5252
#define COL_WARN        0xFFC107
#define COL_LED         0xFF2020

static const uint32_t card_lit[2] = { 0x2F80ED, 0xF2994A };

/* ======================================================================
 * Display: LVGL draws a 456x280 landscape screen, the flush callback turns
 * each strip 90 degrees for the portrait panel (see firmware/pin display.c).
 * ====================================================================== */

#define PANEL_W         BSP_LCD_H_RES   /* 280 */
#define PANEL_H         BSP_LCD_V_RES   /* 456 */
#define SCREEN_W        PANEL_H         /* 456 */
#define SCREEN_H        PANEL_W         /* 280 */
#define FLIP_180        0               /* same as the pin firmware */
#define BUF_LINES       40

static esp_lcd_panel_handle_t panel;
static esp_lcd_panel_io_handle_t panel_io;
static uint16_t *rotate_buf;

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
            rotate_buf[(py - py1) * pw + (px - px1)] = (c >> 8) | (c << 8);   /* high byte first */
        }
    }
    esp_lcd_panel_draw_bitmap(panel, px1, py1, px1 + pw, py1 + w, rotate_buf);
}

static bool flush_done_cb(esp_lcd_panel_io_handle_t io, esp_lcd_panel_io_event_data_t *edata, void *user_ctx)
{
    lv_display_flush_ready((lv_display_t *)user_ctx);
    return false;
}

/* The panel only accepts windows that start on an even pixel and have an even size */
static void rounder_cb(lv_event_t *e)
{
    lv_area_t *area = lv_event_get_param(e);
    area->x1 &= ~1;
    area->y1 &= ~1;
    area->x2 |= 1;
    area->y2 |= 1;
}

static uint32_t tick_cb(void)
{
    return esp_timer_get_time() / 1000;
}

static void display_init(void)
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

    const esp_lcd_panel_io_callbacks_t cbs = { .on_color_trans_done = flush_done_cb };
    ESP_ERROR_CHECK(esp_lcd_panel_io_register_event_callbacks(panel_io, &cbs, disp));

    /* CO5300 "write display brightness" (0x51), sent as a QSPI command */
    uint8_t level = 255;
    esp_lcd_panel_io_tx_param(panel_io, (0x02 << 24) | (0x51 << 8), &level, 1);
}

static void lvgl_task(void *arg)
{
    for (;;) {
        uint32_t wait_ms = lv_timer_handler();
        if (wait_ms < 5) {
            wait_ms = 5;
        } else if (wait_ms > 30) {
            wait_ms = 30;
        }
        vTaskDelay(pdMS_TO_TICKS(wait_ms));
    }
}

/* ======================================================================
 * Screen. Built in app_main, then only touched from LVGL timers.
 * ====================================================================== */

typedef struct {
    lv_obj_t *box, *name, *gpio, *state, *count, *edges;
} card_t;

static card_t cards[2];
static lv_obj_t *pins_label;
static lv_obj_t *led_dot;
static lv_obj_t *led_label;
static lv_obj_t *bottom_label;

static lv_obj_t *label(lv_obj_t *parent, const lv_font_t *font, uint32_t colour)
{
    lv_obj_t *l = lv_label_create(parent);
    lv_obj_set_style_text_font(l, font, 0);
    lv_obj_set_style_text_color(l, lv_color_hex(colour), 0);
    lv_label_set_text(l, "");
    return l;
}

static void card_build(card_t *c, lv_align_t align, int x, const char *name, const char *gpio)
{
    c->box = lv_obj_create(lv_screen_active());
    lv_obj_remove_style_all(c->box);
    lv_obj_set_size(c->box, 204, 150);
    lv_obj_set_style_radius(c->box, 18, 0);
    lv_obj_set_style_bg_opa(c->box, LV_OPA_COVER, 0);
    lv_obj_set_style_bg_color(c->box, lv_color_hex(COL_CARD), 0);
    lv_obj_align(c->box, align, x, 48);

    c->name = label(c->box, &lv_font_montserrat_28, COL_TEXT);
    lv_label_set_text(c->name, name);
    lv_obj_align(c->name, LV_ALIGN_TOP_MID, 0, 10);

    c->gpio = label(c->box, &lv_font_montserrat_14, COL_DIM);
    lv_label_set_text(c->gpio, gpio);
    lv_obj_align(c->gpio, LV_ALIGN_TOP_RIGHT, -12, 6);

    c->state = label(c->box, &lv_font_montserrat_20, COL_DIM);
    lv_obj_align(c->state, LV_ALIGN_TOP_MID, 0, 50);
    c->count = label(c->box, &lv_font_montserrat_20, COL_TEXT);
    lv_obj_align(c->count, LV_ALIGN_TOP_MID, 0, 82);
    c->edges = label(c->box, &lv_font_montserrat_14, COL_DIM);
    lv_obj_align(c->edges, LV_ALIGN_TOP_MID, 0, 118);
}

static void ui_build(void)
{
    lv_obj_t *scr = lv_screen_active();
    lv_obj_set_style_bg_color(scr, lv_color_hex(COL_BG), 0);
    lv_obj_remove_flag(scr, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_t *title = label(scr, &lv_font_montserrat_20, COL_TEXT);
    lv_label_set_text(title, "Daughterboard test");
    lv_obj_align(title, LV_ALIGN_TOP_LEFT, 22, 14);

    pins_label = label(scr, &lv_font_montserrat_20, COL_DIM);
    lv_obj_align(pins_label, LV_ALIGN_TOP_RIGHT, -22, 14);

    card_build(&cards[0], LV_ALIGN_TOP_LEFT, 16, LV_SYMBOL_UP " Up", "GPIO6");
    card_build(&cards[1], LV_ALIGN_TOP_RIGHT, -16, LV_SYMBOL_DOWN " Down", "GPIO3");

    led_dot = lv_obj_create(scr);
    lv_obj_remove_style_all(led_dot);
    lv_obj_set_size(led_dot, 26, 26);
    lv_obj_set_style_radius(led_dot, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_bg_color(led_dot, lv_color_hex(COL_LED), 0);
    lv_obj_set_style_bg_opa(led_dot, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_color(led_dot, lv_color_hex(COL_LED), 0);
    lv_obj_set_style_border_width(led_dot, 2, 0);
    lv_obj_align(led_dot, LV_ALIGN_TOP_LEFT, 22, 212);

    led_label = label(scr, &lv_font_montserrat_20, COL_TEXT);
    lv_obj_align_to(led_label, led_dot, LV_ALIGN_OUT_RIGHT_MID, 12, 0);

    bottom_label = label(scr, &lv_font_montserrat_14, COL_DIM);
    lv_obj_align(bottom_label, LV_ALIGN_BOTTOM_MID, 0, -12);
}

static void ui_led_text(const char *text)
{
    lv_label_set_text(led_label, text);
    lv_obj_align_to(led_label, led_dot, LV_ALIGN_OUT_RIGHT_MID, 12, 0);
}

/* ======================================================================
 * LED (red channel, active low, PWM so it can fade)
 * ====================================================================== */

#define LED_CHANNEL     LEDC_CHANNEL_0
#define LED_MAX_DUTY    ((1u << 10) - 1)

static void led_init(void)
{
    const ledc_timer_config_t timer = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .duty_resolution = LEDC_TIMER_10_BIT,
        .timer_num = LEDC_TIMER_0,
        .freq_hz = 5000,
        .clk_cfg = LEDC_AUTO_CLK,
    };
    ESP_ERROR_CHECK(ledc_timer_config(&timer));
    const ledc_channel_config_t ch = {
        .gpio_num = LED_GPIO,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = LED_CHANNEL,
        .timer_sel = LEDC_TIMER_0,
        .duty = 0,
        .flags.output_invert = 1,       /* active low: duty is brightness */
    };
    ESP_ERROR_CHECK(ledc_channel_config(&ch));
}

/* 0..255; the dot on the screen shows the same */
static void led_set(uint8_t level)
{
    ledc_set_duty(LEDC_LOW_SPEED_MODE, LED_CHANNEL, level * LED_MAX_DUTY / 255);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LED_CHANNEL);
    if (led_dot) {
        lv_obj_set_style_bg_opa(led_dot, level, 0);
    }
}

typedef struct {
    int ms;
    uint8_t from, to;
    const char *text;
} led_step_t;

static const led_step_t led_steps[] = {
    { 1000,   0,   0, "LED should be off" },
    { 1000, 255, 255, "LED should be on" },
    { 1000,   0,   0, "LED should be off" },
    { 1000, 255, 255, "LED should be on" },
    { 1500,   0, 255, "LED fading up smoothly" },
    { 1500, 255,   0, "LED fading down smoothly" },
};
#define NUM_LED_STEPS (int)(sizeof(led_steps) / sizeof(led_steps[0]))

static int led_step = -1;               /* -1: LED check not running */
static int64_t led_step_start_us;

static void led_check_start(void)
{
    ESP_LOGI(TAG, "LED check: watch the LED, it should match the dot on the screen");
    led_step = 0;
    led_step_start_us = esp_timer_get_time();
    ui_led_text(led_steps[0].text);
    ESP_LOGI(TAG, "  %s", led_steps[0].text);
}

static void buttons_show_on_led(void);

/* Called every POLL_MS from the LVGL timer */
static void led_check_tick(void)
{
    if (led_step < 0) {
        return;
    }
    int elapsed = (int)((esp_timer_get_time() - led_step_start_us) / 1000);
    if (elapsed >= led_steps[led_step].ms) {
        led_step++;
        led_step_start_us = esp_timer_get_time();
        elapsed = 0;
        if (led_step == NUM_LED_STEPS) {
            led_step = -1;
            ui_led_text("LED lights while a button is held");
            ESP_LOGI(TAG, "LED check done. If the LED didn't match the dot, check D1,");
            ESP_LOGI(TAG, "its 1k resistor and the GPIO2 connection.");
            buttons_show_on_led();
            return;
        }
        ui_led_text(led_steps[led_step].text);
        ESP_LOGI(TAG, "  %s", led_steps[led_step].text);
    }
    const led_step_t *s = &led_steps[led_step];
    led_set((uint8_t)(s->from + (s->to - s->from) * elapsed / s->ms));
}

/* ======================================================================
 * Pin check
 * ====================================================================== */

typedef struct {
    gpio_num_t gpio;
    const char *name;
    bool is_button;
} pin_t;

static const pin_t pins[] = {
    { LED_GPIO,   "LED (GPIO2)",  false },
    { BTN_UP_GPIO,   "Up button (GPIO6)",   true  },
    { BTN_DOWN_GPIO, "Down button (GPIO3)", true  },
};
#define NUM_PINS (int)(sizeof(pins) / sizeof(pins[0]))

static int pin_faults;

/*
 * All pins start as inputs with pull-ups, so with nothing wrong they all read
 * high (the LED pin is also pulled up through the LED, the buttons through
 * their 10k resistors). Then each pin is driven low on its own: it should
 * read back low, and no other pin should follow it. The button lines have
 * 100n capacitors, so they get time to settle. Pressing a button during the
 * check gives false faults.
 */
static void pin_check(void)
{
    int idle[NUM_PINS];
    uint64_t mask = 0;

    ESP_LOGI(TAG, "Pin check: don't press the buttons");
    for (int i = 0; i < NUM_PINS; i++) {
        mask |= 1ULL << pins[i].gpio;
    }
    const gpio_config_t in = {
        .pin_bit_mask = mask,
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    ESP_ERROR_CHECK(gpio_config(&in));
    vTaskDelay(pdMS_TO_TICKS(20));

    for (int i = 0; i < NUM_PINS; i++) {
        idle[i] = gpio_get_level(pins[i].gpio);
        if (idle[i] == 0) {
            pin_faults++;
            if (pins[i].is_button) {
                ESP_LOGE(TAG, "  %s reads pressed with nothing touching it:"
                         " held down, or shorted to GND", pins[i].name);
            } else {
                ESP_LOGE(TAG, "  %s reads low with nothing driving it: shorted to GND?",
                         pins[i].name);
            }
        }
    }

    for (int i = 0; i < NUM_PINS; i++) {
        gpio_set_level(pins[i].gpio, 0);
        gpio_set_direction(pins[i].gpio, GPIO_MODE_INPUT_OUTPUT);
        vTaskDelay(pdMS_TO_TICKS(10));

        if (gpio_get_level(pins[i].gpio) != 0) {
            pin_faults++;
            ESP_LOGE(TAG, "  %s won't go low when driven: shorted to 3V3?", pins[i].name);
        }
        for (int j = 0; j < NUM_PINS; j++) {
            if (j != i && idle[j] == 1 && gpio_get_level(pins[j].gpio) == 0) {
                pin_faults++;
                ESP_LOGE(TAG, "  %s goes low with %s: the two are shorted together",
                         pins[j].name, pins[i].name);
            }
        }

        gpio_set_direction(pins[i].gpio, GPIO_MODE_INPUT);
        vTaskDelay(pdMS_TO_TICKS(20));
    }

    if (pin_faults == 0) {
        ESP_LOGI(TAG, "Pin check passed: no shorts between the pins or to GND/3V3.");
    } else {
        ESP_LOGE(TAG, "Pin check found %d fault(s), listed above.", pin_faults);
    }
}

/* ======================================================================
 * Buttons
 * ====================================================================== */

typedef struct {
    gpio_num_t gpio;
    const char *name;
    volatile uint32_t raw_edges;    /* every edge the pin makes, counted in the ISR */
    uint32_t edges_at_release;      /* raw_edges at the end of the last press */
    int last_level;
    int same_polls;
    int stable;                     /* debounced level: 1 released, 0 pressed */
    int64_t pressed_at_us;
    int presses;
    uint32_t max_edges;             /* most raw edges seen in one press */
    bool stuck;
    bool ignore_release;            /* already down when the check started */
} button_t;

static button_t buttons[2] = {
    { .gpio = BTN_UP_GPIO,   .name = "Up (GPIO6)"   },     /* cards[0], left */
    { .gpio = BTN_DOWN_GPIO, .name = "Down (GPIO3)" },     /* cards[1], right */
};

static bool passed;

static void IRAM_ATTR edge_isr(void *arg)
{
    ((button_t *)arg)->raw_edges++;
}

static void buttons_init(void)
{
    const gpio_config_t cfg = {
        .pin_bit_mask = (1ULL << BTN_UP_GPIO) | (1ULL << BTN_DOWN_GPIO),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,   /* the daughterboard has 10k pull-ups too */
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_ANYEDGE,
    };
    ESP_ERROR_CHECK(gpio_config(&cfg));
    esp_err_t err = gpio_install_isr_service(0);
    if (err != ESP_ERR_INVALID_STATE) {     /* already installed is fine */
        ESP_ERROR_CHECK(err);
    }
    for (int i = 0; i < 2; i++) {
        button_t *b = &buttons[i];
        ESP_ERROR_CHECK(gpio_isr_handler_add(b->gpio, edge_isr, b));
        b->stable = b->last_level = gpio_get_level(b->gpio);
        b->edges_at_release = b->raw_edges;
        b->pressed_at_us = esp_timer_get_time();
        b->ignore_release = b->stable == 0;     /* its press started unseen */
        if (b->stable == 0) {
            ESP_LOGW(TAG, "%s already reads pressed: let go, or it's stuck/shorted to GND",
                     b->name);
        }
    }
}

static void card_update(int i)
{
    const button_t *b = &buttons[i];
    const card_t *c = &cards[i];
    const bool down = b->stable == 0;

    lv_obj_set_style_bg_color(c->box, lv_color_hex(down ? card_lit[i] : COL_CARD), 0);
    lv_obj_set_style_text_color(c->name, lv_color_hex(down ? 0x000000 : COL_TEXT), 0);
    lv_obj_set_style_text_color(c->gpio, lv_color_hex(down ? 0x000000 : COL_DIM), 0);

    lv_label_set_text(c->state, b->stuck ? "STUCK?" : down ? "PRESSED" : "released");
    lv_obj_set_style_text_color(c->state,
        lv_color_hex(b->stuck ? COL_BAD : down ? 0x000000 : COL_DIM), 0);

    if (b->presses >= PASS_PRESSES) {
        lv_label_set_text_fmt(c->count, LV_SYMBOL_OK " %d presses", b->presses);
        lv_obj_set_style_text_color(c->count, lv_color_hex(down ? 0x000000 : COL_GOOD), 0);
    } else {
        lv_label_set_text_fmt(c->count, "%d / %d presses", b->presses, PASS_PRESSES);
        lv_obj_set_style_text_color(c->count, lv_color_hex(down ? 0x000000 : COL_TEXT), 0);
    }

    if (b->presses == 0) {
        lv_label_set_text(c->edges, "");
    } else {
        lv_label_set_text_fmt(c->edges, "bounce: up to %lu edges/press", (unsigned long)b->max_edges);
        lv_obj_set_style_text_color(c->edges,
            lv_color_hex(down ? 0x000000 : b->max_edges > 2 ? COL_WARN : COL_DIM), 0);
    }
}

static void bottom_update(void)
{
    if (passed) {
        lv_label_set_text(bottom_label, "PASS: both buttons work. Check the LED matched the dot.");
        lv_obj_set_style_text_color(bottom_label, lv_color_hex(COL_GOOD), 0);
    } else {
        lv_label_set_text_fmt(bottom_label, "Press each button %d times. Hold both to rerun the LED check.",
                              PASS_PRESSES);
        lv_obj_set_style_text_color(bottom_label, lv_color_hex(COL_DIM), 0);
    }
}

static void buttons_show_on_led(void)
{
    if (led_step < 0) {
        led_set(buttons[0].stable == 0 || buttons[1].stable == 0 ? 255 : 0);
    }
}

static void on_press(button_t *b)
{
    b->pressed_at_us = esp_timer_get_time();
    ESP_LOGI(TAG, "%s pressed", b->name);
}

static void on_release(button_t *b)
{
    uint32_t edges = b->raw_edges - b->edges_at_release;
    int held_ms = (int)((esp_timer_get_time() - b->pressed_at_us) / 1000);
    b->edges_at_release = b->raw_edges;
    b->stuck = false;
    if (b->ignore_release) {
        b->ignore_release = false;
        return;
    }
    b->presses++;
    if (edges > b->max_edges) {
        b->max_edges = edges;
    }
    if (edges > 2) {
        ESP_LOGW(TAG, "%s released after %d ms: %d/%d presses, %lu raw edges (bounced)",
                 b->name, held_ms, b->presses, PASS_PRESSES, (unsigned long)edges);
    } else {
        ESP_LOGI(TAG, "%s released after %d ms: %d/%d presses, %lu raw edges",
                 b->name, held_ms, b->presses, PASS_PRESSES, (unsigned long)edges);
    }

    if (!passed && buttons[0].presses >= PASS_PRESSES && buttons[1].presses >= PASS_PRESSES) {
        passed = true;
        ESP_LOGI(TAG, "=== BUTTON CHECK PASSED ===");
        for (int i = 0; i < 2; i++) {
            ESP_LOGI(TAG, "  %s: %d presses, at most %lu raw edges in one press",
                     buttons[i].name, buttons[i].presses, (unsigned long)buttons[i].max_edges);
        }
        if (buttons[0].max_edges > 2 || buttons[1].max_edges > 2) {
            ESP_LOGW(TAG, "Some presses bounced (more than 2 raw edges). The debounce hides");
            ESP_LOGW(TAG, "this, but steady bouncing can mean a weak joint or a missing 100n.");
        }
        bottom_update();
    }
}

/* Debounce one button; true when its debounced level changed */
static bool poll_button(button_t *b)
{
    int level = gpio_get_level(b->gpio);
    b->same_polls = level == b->last_level ? b->same_polls + 1 : 0;
    b->last_level = level;
    if (b->same_polls == STABLE_POLLS && level != b->stable) {
        b->stable = level;
        return true;
    }
    return false;
}

/* LVGL timer, every POLL_MS */
static void poll_cb(lv_timer_t *timer)
{
    static int64_t both_since_us;
    static bool combo_done;
    const int64_t now = esp_timer_get_time();

    for (int i = 0; i < 2; i++) {
        button_t *b = &buttons[i];
        if (poll_button(b)) {
            if (b->stable == 0) {
                on_press(b);
            } else {
                on_release(b);
            }
            card_update(i);
            buttons_show_on_led();
        }
        if (b->stable == 0 && !b->stuck && now - b->pressed_at_us > STUCK_MS * 1000LL) {
            b->stuck = true;
            ESP_LOGW(TAG, "%s has read pressed for %d s: stuck, or shorted to GND?",
                     b->name, STUCK_MS / 1000);
            card_update(i);
        }
    }

    if (buttons[0].stable == 0 && buttons[1].stable == 0) {
        if (both_since_us == 0) {
            both_since_us = now;
        } else if (!combo_done && now - both_since_us > COMBO_MS * 1000LL) {
            combo_done = true;
            ESP_LOGI(TAG, "Both buttons held: running the LED check again");
            led_check_start();
        }
    } else {
        both_since_us = 0;
        combo_done = false;
    }

    led_check_tick();
}

/* ======================================================================
 * main
 * ====================================================================== */

void app_main(void)
{
    ESP_LOGI(TAG, "Plurality pin daughterboard test");
    ESP_LOGI(TAG, "  buttons: Up GPIO6, Down GPIO3 (active low)");
    ESP_LOGI(TAG, "  LED:     GPIO2, red only (active low)");

    pin_check();
    led_init();
    led_set(0);
    buttons_init();

    lv_init();
    lv_tick_set_cb(tick_cb);
    display_init();
    ui_build();

    if (pin_faults == 0) {
        lv_label_set_text(pins_label, LV_SYMBOL_OK " Pins OK");
        lv_obj_set_style_text_color(pins_label, lv_color_hex(COL_GOOD), 0);
    } else {
        lv_label_set_text_fmt(pins_label, LV_SYMBOL_WARNING " %d pin fault%s",
                              pin_faults, pin_faults == 1 ? "" : "s");
        lv_obj_set_style_text_color(pins_label, lv_color_hex(COL_BAD), 0);
    }
    for (int i = 0; i < 2; i++) {
        card_update(i);
    }
    bottom_update();
    led_check_start();

    lv_timer_create(poll_cb, POLL_MS, NULL);
    /* All LVGL calls happen in this one task from here on */
    xTaskCreate(lvgl_task, "lvgl", 8192, NULL, 5, NULL);
}
