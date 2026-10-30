/**
 * @file status_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "status_gen.h"
#include "../plurality_pin.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/***********************
 *  STATIC VARIABLES
 **********************/

/***********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

lv_obj_t * status_create(void)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if PLURALITY_PIN_CHECK_COMPILE_TARGET(PLURALITY_PIN_TARGET_ALL)
    if (plurality_pin_check_target(PLURALITY_PIN_TARGET_ALL)) {
        lv_obj_t * lv_obj_0 = lv_obj_create(NULL);
        lv_obj_set_name_static(lv_obj_0, "status_#");
        lv_obj_set_style_bg_color(lv_obj_0, lv_color_hex(0x333333), 0);
        lv_obj_set_flag(lv_obj_0, LV_OBJ_FLAG_SCROLLABLE, false);
        lv_obj_set_style_pad_all(lv_obj_0, 0, 0);

        lv_obj_add_style(lv_obj_0, &style_screen_base_global, 0);
        lv_obj_t * container_0 = container_create(lv_obj_0);
        lv_obj_set_x(container_0, 8);
        lv_obj_set_y(container_0, 10);
        lv_obj_set_width(container_0, 440);
        lv_obj_set_height(container_0, 260);
        lv_obj_t * card_0 = card_create(container_0);
        lv_obj_set_align(card_0, LV_ALIGN_CENTER);
        lv_obj_set_x(card_0, 0);
        lv_obj_set_y(card_0, 0);
        lv_obj_set_width(card_0, 440);
        lv_obj_set_height(card_0, 260);
        lv_obj_set_style_bg_color(card_0, lv_color_hex(0x2C2C2C), 0);
        lv_obj_set_style_radius(card_0, 16, 0);

        lv_obj_t * column_0 = column_create(container_0, 0, 0, 0, 0, 10, 0, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
        lv_obj_set_align(column_0, LV_ALIGN_CENTER);
        lv_obj_set_x(column_0, 0);
        lv_obj_set_y(column_0, 0);
        lv_obj_set_width(column_0, 414);
        lv_obj_set_height(column_0, 200);
        lv_obj_t * row_0 = row_create(column_0, 0, 0, 0, 0, 10, 0, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_width(row_0, lv_pct(100));
        lv_obj_set_height(row_0, 95);
        lv_obj_t * card_1 = card_create(row_0);
        lv_obj_set_flex_flow(card_1, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_flex_cross_place(card_1, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(card_1, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(card_1, 12, 0);
        lv_obj_set_style_pad_column(card_1, 12, 0);
        lv_obj_set_width(card_1, 255);
        lv_obj_set_height(card_1, 95);
        lv_obj_set_style_bg_color(card_1, lv_color_hex(0x787878), 0);
        lv_obj_set_style_bg_opa(card_1, 10, 0);
        lv_obj_set_style_radius(card_1, 10, 0);
        lv_obj_t * card_2 = card_create(card_1);
        lv_obj_set_flex_flow(card_2, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_main_place(card_2, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_cross_place(card_2, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(card_2, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(card_2, 0, 0);
        lv_obj_set_style_pad_row(card_2, 0, 0);
        lv_obj_set_width(card_2, 50);
        lv_obj_set_height(card_2, 50);
        lv_obj_set_style_bg_color(card_2, lv_color_hex(0xFFFFFF), 0);
        lv_obj_set_style_bg_opa(card_2, 2, 0);
        lv_obj_set_style_border_color(card_2, lv_color_hex(0xFFFFFF), 0);
        lv_obj_set_style_border_opa(card_2, 6, 0);
        lv_obj_set_style_border_width(card_2, 1, 0);
        lv_obj_set_style_radius(card_2, 10, 0);
        lv_obj_t * image_0 = image_create(card_2);
        lv_obj_set_width(image_0, 22);
        lv_obj_set_height(image_0, 22);
        lv_image_set_src(image_0, image_vec_34_869);
        lv_obj_set_flag(image_0, LV_OBJ_FLAG_SCROLLABLE, false);

        lv_obj_t * column_1 = column_create(card_1, 0, 0, 0, 0, 2, 1, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
        lv_obj_set_width(column_1, 0);
        lv_obj_set_height(column_1, LV_SIZE_CONTENT);
        lv_obj_t * label_0 = label_create(column_1);
        lv_label_set_text(label_0, "Battery");
        lv_obj_set_style_text_font(label_0, font_inter_semi_bold_12, 0);
        lv_obj_set_style_text_color(label_0, lv_color_hex(0xFFFFFF), 0);
        lv_obj_set_style_text_opa(label_0, 126, 0);

        lv_obj_t * row_1 = row_create(column_1, 0, 0, 0, 0, 8, 0, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
        lv_obj_set_width(row_1, lv_pct(100));
        lv_obj_set_height(row_1, LV_SIZE_CONTENT);
        lv_obj_t * label_1 = label_create(row_1);
        lv_label_set_text(label_1, "82");
        lv_label_bind_text(label_1, &battery_percent, "%d");
        lv_obj_set_style_text_font(label_1, font_inter_bold_28, 0);
        lv_obj_set_style_text_color(label_1, lv_color_hex(0xFFFFFF), 0);

        lv_obj_t * label_2 = label_create(row_1);
        lv_label_set_text(label_2, "%");
        lv_obj_set_style_text_font(label_2, font_inter_semi_bold_16, 0);
        lv_obj_set_style_text_color(label_2, lv_color_hex(0xFFFFFF), 0);
        lv_obj_set_style_text_opa(label_2, 126, 0);

        lv_obj_t * card_3 = card_create(column_1);
        lv_obj_set_flex_flow(card_3, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_flex_cross_place(card_3, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(card_3, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_hor(card_3, 8, 0);
        lv_obj_set_style_pad_ver(card_3, 4, 0);
        lv_obj_set_style_pad_column(card_3, 6, 0);
        lv_obj_set_width(card_3, LV_SIZE_CONTENT);
        lv_obj_set_height(card_3, LV_SIZE_CONTENT);
        lv_obj_set_style_bg_color(card_3, lv_color_hex(0xFFFFFF), 0);
        lv_obj_set_style_bg_opa(card_3, 2, 0);
        lv_obj_set_style_radius(card_3, 999, 0);
        lv_obj_bind_flag_if_eq(card_3, &usb_power, LV_OBJ_FLAG_HIDDEN, 0);
        lv_obj_t * image_1 = image_create(card_3);
        lv_obj_set_width(image_1, 14);
        lv_obj_set_height(image_1, 14);
        lv_image_set_src(image_1, image_vec_34_872);
        lv_obj_set_flag(image_1, LV_OBJ_FLAG_SCROLLABLE, false);

        lv_obj_t * label_3 = label_create(card_3);
        lv_label_set_text(label_3, "Charging");
        lv_obj_set_style_text_font(label_3, font_inter_semi_bold_12, 0);
        lv_obj_set_style_text_color(label_3, lv_color_hex(0xFFFFFF), 0);

        lv_obj_t * card_4 = card_create(row_0);
        lv_obj_set_flex_flow(card_4, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_main_place(card_4, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_cross_place(card_4, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(card_4, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_hor(card_4, 12, 0);
        lv_obj_set_style_pad_ver(card_4, 8, 0);
        lv_obj_set_style_pad_row(card_4, 2, 0);
        lv_obj_set_width(card_4, 149);
        lv_obj_set_height(card_4, lv_pct(100));
        lv_obj_set_style_bg_color(card_4, lv_color_hex(0x787878), 0);
        lv_obj_set_style_bg_opa(card_4, 10, 0);
        lv_obj_set_style_radius(card_4, 10, 0);
        lv_obj_t * column_2 = column_create(card_4, 0, 0, 0, 0, 3, 1, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
        lv_obj_set_width(column_2, lv_pct(100));
        lv_obj_set_height(column_2, 0);
        lv_obj_t * column_3 = column_create(column_2, 0, 0, 0, 0, 0, 0, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
        lv_obj_set_width(column_3, 25);
        lv_obj_set_height(column_3, 25);
        lv_obj_t * image_2 = image_create(column_3);
        lv_obj_set_width(image_2, 25);
        lv_obj_set_height(image_2, 25);
        lv_image_set_src(image_2, image_vec_23_372);
        lv_obj_set_flag(image_2, LV_OBJ_FLAG_SCROLLABLE, false);

        lv_obj_t * row_2 = row_create(column_2, 0, 0, 0, 0, 10, 0, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_width(row_2, 125);
        lv_obj_set_height(row_2, 15);
        lv_obj_t * label_4 = label_create(row_2);
        lv_obj_set_width(label_4, 0);
        lv_obj_set_height(label_4, lv_pct(100));
        lv_obj_set_flex_grow(label_4, 1);
        lv_label_set_text(label_4, "Wi-Fi");
        lv_obj_set_style_text_font(label_4, font_inter_semi_bold_14, 0);
        lv_obj_set_style_text_color(label_4, lv_color_hex(0x757575), 0);
        lv_label_set_long_mode(label_4, LV_LABEL_LONG_MODE_CLIP);

        lv_obj_t * label_5 = label_create(row_2);
        lv_obj_set_height(label_5, lv_pct(100));
        lv_label_set_text(label_5, "Connected");
        lv_label_bind_text(label_5, &wifi_status, NULL);
        lv_obj_set_style_text_font(label_5, font_inter_semi_bold_14, 0);
        lv_obj_set_style_text_align(label_5, LV_TEXT_ALIGN_RIGHT, 0);
        lv_label_set_long_mode(label_5, LV_LABEL_LONG_MODE_DOTS);
        lv_obj_bind_style(label_5, &style_state_off, 0, &wifi_state, 0);
        lv_obj_bind_style(label_5, &style_state_off, 0, &wifi_state, 1);
        lv_obj_bind_style(label_5, &style_state_on, 0, &wifi_state, 2);
        lv_obj_bind_style(label_5, &style_state_warn, 0, &wifi_state, 3);

        lv_obj_t * label_6 = label_create(column_2);
        lv_obj_set_height(label_6, 15);
        lv_label_set_text(label_6, "wifi network name");
        lv_label_bind_text(label_6, &wifi_name, NULL);
        lv_obj_set_style_text_font(label_6, font_inter_semi_bold_14, 0);
        lv_obj_set_style_text_color(label_6, lv_color_hex(0xF3F3F3), 0);
        lv_obj_set_width(label_6, 124);
        lv_label_set_long_mode(label_6, LV_LABEL_LONG_MODE_DOTS);

        lv_obj_t * row_3 = row_create(column_0, 0, 0, 0, 0, 10, 0, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_width(row_3, lv_pct(100));
        lv_obj_set_height(row_3, 95);
        lv_obj_t * card_5 = card_create(row_3);
        lv_obj_set_flex_flow(card_5, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_pad_hor(card_5, 12, 0);
        lv_obj_set_style_pad_ver(card_5, 10, 0);
        lv_obj_set_style_pad_row(card_5, 10, 0);
        lv_obj_set_width(card_5, 283);
        lv_obj_set_height(card_5, 95);
        lv_obj_set_style_bg_color(card_5, lv_color_hex(0x787880), 0);
        lv_obj_set_style_bg_opa(card_5, 7, 0);
        lv_obj_set_style_radius(card_5, 10, 0);
        lv_obj_t * column_4 = column_create(card_5, 0, 0, 0, 0, 10, 0, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
        lv_obj_set_width(column_4, lv_pct(100));
        lv_obj_set_height(column_4, 75);
        lv_obj_t * column_5 = column_create(column_4, 0, 0, 0, 0, 4, 0, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
        lv_obj_set_width(column_5, lv_pct(100));
        lv_obj_set_height(column_5, LV_SIZE_CONTENT);
        lv_obj_t * row_4 = row_create(column_5, 0, 0, 0, 0, 0, 0, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_width(row_4, lv_pct(100));
        lv_obj_set_height(row_4, LV_SIZE_CONTENT);
        lv_obj_t * label_7 = label_create(row_4);
        lv_label_set_text(label_7, "SD card");
        lv_obj_set_style_text_font(label_7, font_inter_medium_11, 0);
        lv_obj_set_style_text_color(label_7, lv_color_hex(0x757575), 0);

        lv_obj_t * label_8 = label_create(row_4);
        lv_label_set_text(label_8, "19.8 / 32 GB");
        lv_label_bind_text(label_8, &sd_text, NULL);
        lv_obj_set_style_text_font(label_8, font_inter_semi_bold_13, 0);
        lv_obj_set_style_text_color(label_8, lv_color_hex(0xF3F3F3), 0);

        lv_obj_t * lv_bar_0 = lv_bar_create(column_5);
        lv_obj_set_width(lv_bar_0, lv_pct(100));
        lv_obj_set_height(lv_bar_0, 6);
        lv_bar_set_min_value(lv_bar_0, 0);
        lv_bar_set_max_value(lv_bar_0, 100);
        lv_bar_bind_value(lv_bar_0, &sd_percent);
        lv_obj_set_style_bg_color(lv_bar_0, lv_color_hex(0x404045), 0);
        lv_obj_set_style_bg_opa(lv_bar_0, 255, 0);
        lv_obj_set_style_radius(lv_bar_0, 3, 0);
        lv_obj_set_style_bg_color(lv_bar_0, lv_color_hex(0x668FFF), LV_PART_INDICATOR);
        lv_obj_set_style_radius(lv_bar_0, 3, LV_PART_INDICATOR);

        lv_obj_t * column_6 = column_create(column_4, 0, 0, 0, 0, 4, 0, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
        lv_obj_set_width(column_6, lv_pct(100));
        lv_obj_set_height(column_6, LV_SIZE_CONTENT);
        lv_obj_t * row_5 = row_create(column_6, 0, 0, 0, 0, 0, 0, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_width(row_5, lv_pct(100));
        lv_obj_set_height(row_5, LV_SIZE_CONTENT);
        lv_obj_t * label_9 = label_create(row_5);
        lv_label_set_text(label_9, "Pin storage");
        lv_obj_set_style_text_font(label_9, font_inter_medium_11, 0);
        lv_obj_set_style_text_color(label_9, lv_color_hex(0x757575), 0);

        lv_obj_t * label_10 = label_create(row_5);
        lv_label_set_text(label_10, "0.3 / 4.4 MB");
        lv_label_bind_text(label_10, &pin_storage_text, NULL);
        lv_obj_set_style_text_font(label_10, font_inter_semi_bold_13, 0);
        lv_obj_set_style_text_color(label_10, lv_color_hex(0xF3F3F3), 0);

        lv_obj_t * lv_bar_1 = lv_bar_create(column_6);
        lv_obj_set_width(lv_bar_1, lv_pct(100));
        lv_obj_set_height(lv_bar_1, 6);
        lv_bar_set_min_value(lv_bar_1, 0);
        lv_bar_set_max_value(lv_bar_1, 100);
        lv_bar_bind_value(lv_bar_1, &pin_storage_percent);
        lv_obj_set_style_bg_color(lv_bar_1, lv_color_hex(0x404045), 0);
        lv_obj_set_style_bg_opa(lv_bar_1, 255, 0);
        lv_obj_set_style_radius(lv_bar_1, 3, 0);
        lv_obj_set_style_bg_color(lv_bar_1, lv_color_hex(0xFFCC00), LV_PART_INDICATOR);
        lv_obj_set_style_radius(lv_bar_1, 3, LV_PART_INDICATOR);

        lv_obj_t * card_6 = card_create(row_3);
        lv_obj_set_flex_flow(card_6, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_main_place(card_6, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_cross_place(card_6, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(card_6, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_hor(card_6, 14, 0);
        lv_obj_set_style_pad_ver(card_6, 8, 0);
        lv_obj_set_style_pad_row(card_6, 3, 0);
        lv_obj_set_width(card_6, 121);
        lv_obj_set_height(card_6, 95);
        lv_obj_set_style_bg_color(card_6, lv_color_hex(0x787878), 0);
        lv_obj_set_style_bg_opa(card_6, 10, 0);
        lv_obj_set_style_radius(card_6, 10, 0);
        lv_obj_t * label_11 = label_create(card_6);
        lv_label_set_text(label_11, "Mode");
        lv_obj_set_style_text_font(label_11, font_inter_medium_11, 0);
        lv_obj_set_style_text_letter_space(label_11, 1, 0);
        lv_obj_set_style_text_color(label_11, lv_color_hex(0x757575), 0);

        lv_obj_t * label_12 = label_create(card_6);
        lv_label_set_text(label_12, "Active");
        lv_label_bind_text(label_12, &power_mode_text, NULL);
        lv_obj_set_style_text_font(label_12, font_inter_bold_14, 0);
        lv_obj_bind_style(label_12, &style_state_good, 0, &power_state, 0);
        lv_obj_bind_style(label_12, &style_state_warn, 0, &power_state, 1);
        lv_obj_bind_style(label_12, &style_state_off, 0, &power_state, 2);

        the_root = lv_obj_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

