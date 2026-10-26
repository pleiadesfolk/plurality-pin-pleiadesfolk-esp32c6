/**
 * @file front_history_card_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "front_history_card_gen.h"
#include "../../plurality_pin.h"

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

lv_obj_t * front_history_card_create(lv_obj_t * parent)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if PLURALITY_PIN_CHECK_COMPILE_TARGET(PLURALITY_PIN_TARGET_ALL)
    if (plurality_pin_check_target(PLURALITY_PIN_TARGET_ALL)) {
        lv_obj_t * card_0 = card_create(parent);
        lv_obj_set_name_static(card_0, "front_history_card_#");
        lv_obj_set_flex_flow(card_0, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_pad_top(card_0, 12, 0);
        lv_obj_set_style_pad_bottom(card_0, 10, 0);
        lv_obj_set_style_pad_hor(card_0, 12, 0);
        lv_obj_set_style_pad_row(card_0, 8, 0);
        lv_obj_set_width(card_0, 416);
        lv_obj_set_height(card_0, 205);
        lv_obj_set_style_bg_color(card_0, lv_color_hex(0xF8FAFC), 0);
        lv_obj_set_style_border_color(card_0, lv_color_hex(0xE2E8F0), 0);
        lv_obj_set_style_border_width(card_0, 1, 0);
        lv_obj_set_style_radius(card_0, 15, 0);

        lv_obj_t * container_0 = container_create(card_0);
        lv_obj_set_flex_flow(container_0, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_flex_main_place(container_0, LV_FLEX_ALIGN_SPACE_BETWEEN, 0);
        lv_obj_set_style_flex_cross_place(container_0, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(container_0, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(container_0, 0, 0);
        lv_obj_set_style_pad_column(container_0, 0, 0);
        lv_obj_set_width(container_0, lv_pct(100));
        lv_obj_set_height(container_0, LV_SIZE_CONTENT);
        lv_obj_t * label_0 = label_create(container_0);
        lv_label_set_text(label_0, "Front history");
        lv_obj_set_style_text_font(label_0, font_inter_bold_14, 0);
        lv_obj_set_style_text_color(label_0, lv_color_hex(0x0F172A), 0);

        lv_obj_t * container_1 = container_create(card_0);
        lv_obj_set_flex_flow(container_1, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_pad_all(container_1, 0, 0);
        lv_obj_set_style_pad_row(container_1, 4, 0);
        lv_obj_set_width(container_1, lv_pct(100));
        lv_obj_set_height(container_1, 0);
        lv_obj_set_flex_grow(container_1, 1);
        lv_obj_t * container_2 = container_create(container_1);
        lv_obj_set_flex_flow(container_2, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_flex_cross_place(container_2, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(container_2, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(container_2, 0, 0);
        lv_obj_set_style_pad_column(container_2, 0, 0);
        lv_obj_set_width(container_2, lv_pct(100));
        lv_obj_set_height(container_2, 28);
        lv_obj_t * container_3 = container_create(container_2);
        lv_obj_set_flex_flow(container_3, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_pad_all(container_3, 0, 0);
        lv_obj_set_style_pad_row(container_3, 0, 0);
        lv_obj_set_width(container_3, 72);
        lv_obj_set_height(container_3, 28);

        lv_obj_t * container_4 = container_create(container_2);
        lv_obj_set_flex_flow(container_4, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_main_place(container_4, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_cross_place(container_4, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(container_4, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(container_4, 0, 0);
        lv_obj_set_style_pad_row(container_4, 0, 0);
        lv_obj_set_width(container_4, 64);
        lv_obj_set_height(container_4, 28);
        lv_obj_t * label_1 = label_create(container_4);
        lv_obj_set_width(label_1, lv_pct(100));
        lv_label_set_text(label_1, "Mon\n12:00pm");
        lv_obj_set_style_text_font(label_1, font_inter_semi_bold_8, 0);
        lv_obj_set_style_text_line_space(label_1, 1, 0);
        lv_obj_set_style_text_color(label_1, lv_color_hex(0x64748B), 0);
        lv_obj_set_style_text_align(label_1, LV_TEXT_ALIGN_CENTER, 0);

        lv_obj_t * container_5 = container_create(container_2);
        lv_obj_set_flex_flow(container_5, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_main_place(container_5, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_cross_place(container_5, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(container_5, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(container_5, 0, 0);
        lv_obj_set_style_pad_row(container_5, 0, 0);
        lv_obj_set_width(container_5, 64);
        lv_obj_set_height(container_5, 28);
        lv_obj_t * label_2 = label_create(container_5);
        lv_obj_set_width(label_2, lv_pct(100));
        lv_label_set_text(label_2, "Tue\n12:00pm");
        lv_obj_set_style_text_font(label_2, font_inter_semi_bold_8, 0);
        lv_obj_set_style_text_line_space(label_2, 1, 0);
        lv_obj_set_style_text_color(label_2, lv_color_hex(0x64748B), 0);
        lv_obj_set_style_text_align(label_2, LV_TEXT_ALIGN_CENTER, 0);

        lv_obj_t * container_6 = container_create(container_2);
        lv_obj_set_flex_flow(container_6, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_main_place(container_6, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_cross_place(container_6, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(container_6, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(container_6, 0, 0);
        lv_obj_set_style_pad_row(container_6, 0, 0);
        lv_obj_set_width(container_6, 64);
        lv_obj_set_height(container_6, 28);
        lv_obj_t * label_3 = label_create(container_6);
        lv_obj_set_width(label_3, lv_pct(100));
        lv_label_set_text(label_3, "Wed\n12:00pm");
        lv_obj_set_style_text_font(label_3, font_inter_semi_bold_8, 0);
        lv_obj_set_style_text_line_space(label_3, 1, 0);
        lv_obj_set_style_text_color(label_3, lv_color_hex(0x64748B), 0);
        lv_obj_set_style_text_align(label_3, LV_TEXT_ALIGN_CENTER, 0);

        lv_obj_t * container_7 = container_create(container_2);
        lv_obj_set_flex_flow(container_7, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_main_place(container_7, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_cross_place(container_7, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(container_7, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(container_7, 0, 0);
        lv_obj_set_style_pad_row(container_7, 0, 0);
        lv_obj_set_width(container_7, 64);
        lv_obj_set_height(container_7, 28);
        lv_obj_t * label_4 = label_create(container_7);
        lv_obj_set_width(label_4, lv_pct(100));
        lv_label_set_text(label_4, "Thu\n12:00pm");
        lv_obj_set_style_text_font(label_4, font_inter_semi_bold_8, 0);
        lv_obj_set_style_text_line_space(label_4, 1, 0);
        lv_obj_set_style_text_color(label_4, lv_color_hex(0x64748B), 0);
        lv_obj_set_style_text_align(label_4, LV_TEXT_ALIGN_CENTER, 0);

        lv_obj_t * container_8 = container_create(container_2);
        lv_obj_set_flex_flow(container_8, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_main_place(container_8, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_cross_place(container_8, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(container_8, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(container_8, 0, 0);
        lv_obj_set_style_pad_row(container_8, 0, 0);
        lv_obj_set_width(container_8, 64);
        lv_obj_set_height(container_8, 28);
        lv_obj_t * label_5 = label_create(container_8);
        lv_obj_set_width(label_5, lv_pct(100));
        lv_label_set_text(label_5, "Fri\n12:00pm");
        lv_obj_set_style_text_font(label_5, font_inter_semi_bold_8, 0);
        lv_obj_set_style_text_line_space(label_5, 1, 0);
        lv_obj_set_style_text_color(label_5, lv_color_hex(0x64748B), 0);
        lv_obj_set_style_text_align(label_5, LV_TEXT_ALIGN_CENTER, 0);

        lv_obj_t * container_9 = container_create(container_1);
        lv_obj_set_flex_flow(container_9, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_pad_all(container_9, 0, 0);
        lv_obj_set_style_pad_row(container_9, 0, 0);
        lv_obj_set_width(container_9, lv_pct(100));
        lv_obj_set_height(container_9, 0);
        lv_obj_set_flex_grow(container_9, 1);
        lv_obj_t * container_10 = container_create(container_9);
        lv_obj_set_flex_flow(container_10, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_flex_cross_place(container_10, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(container_10, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(container_10, 0, 0);
        lv_obj_set_style_pad_column(container_10, 0, 0);
        lv_obj_set_width(container_10, lv_pct(100));
        lv_obj_set_height(container_10, 24);
        lv_obj_t * container_11 = container_create(container_10);
        lv_obj_set_flex_flow(container_11, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_main_place(container_11, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(container_11, 0, 0);
        lv_obj_set_style_pad_row(container_11, 0, 0);
        lv_obj_set_width(container_11, 72);
        lv_obj_set_height(container_11, lv_pct(100));
        lv_obj_t * label_6 = label_create(container_11);
        lv_label_set_text(label_6, "Riley");
        lv_obj_set_style_text_font(label_6, font_inter_semi_bold_11, 0);
        lv_obj_set_style_text_color(label_6, lv_color_hex(0x334155), 0);

        lv_obj_t * container_12 = container_create(container_10);
        lv_obj_set_flex_flow(container_12, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_flex_cross_place(container_12, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(container_12, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(container_12, 0, 0);
        lv_obj_set_style_pad_column(container_12, 0, 0);
        lv_obj_set_width(container_12, 320);
        lv_obj_set_height(container_12, lv_pct(100));
        lv_obj_t * container_13 = container_create(container_12);
        lv_obj_set_flex_flow(container_13, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_main_place(container_13, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_cross_place(container_13, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(container_13, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(container_13, 0, 0);
        lv_obj_set_style_pad_row(container_13, 0, 0);
        lv_obj_set_width(container_13, 64);
        lv_obj_set_height(container_13, lv_pct(100));

        lv_obj_t * container_14 = container_create(container_12);
        lv_obj_set_flex_flow(container_14, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_main_place(container_14, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_cross_place(container_14, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(container_14, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(container_14, 0, 0);
        lv_obj_set_style_pad_row(container_14, 0, 0);
        lv_obj_set_width(container_14, 64);
        lv_obj_set_height(container_14, lv_pct(100));

        lv_obj_t * container_15 = container_create(container_12);
        lv_obj_set_flex_flow(container_15, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_main_place(container_15, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_cross_place(container_15, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(container_15, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(container_15, 0, 0);
        lv_obj_set_style_pad_row(container_15, 0, 0);
        lv_obj_set_width(container_15, 64);
        lv_obj_set_height(container_15, lv_pct(100));

        lv_obj_t * container_16 = container_create(container_12);
        lv_obj_set_flex_flow(container_16, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_main_place(container_16, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_cross_place(container_16, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(container_16, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(container_16, 0, 0);
        lv_obj_set_style_pad_row(container_16, 0, 0);
        lv_obj_set_width(container_16, 64);
        lv_obj_set_height(container_16, lv_pct(100));

        lv_obj_t * container_17 = container_create(container_12);
        lv_obj_set_flex_flow(container_17, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_main_place(container_17, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_cross_place(container_17, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(container_17, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(container_17, 0, 0);
        lv_obj_set_style_pad_row(container_17, 0, 0);
        lv_obj_set_width(container_17, 64);
        lv_obj_set_height(container_17, lv_pct(100));

        lv_obj_t * card_1 = card_create(container_12);
        lv_obj_set_flag(card_1, LV_OBJ_FLAG_IGNORE_LAYOUT, true);
        lv_obj_set_x(card_1, 0);
        lv_obj_set_y(card_1, 8);
        lv_obj_set_width(card_1, 116);
        lv_obj_set_height(card_1, 8);
        lv_obj_set_style_bg_color(card_1, lv_color_hex(0x3B82F6), 0);
        lv_obj_set_style_radius(card_1, 4, 0);

        lv_obj_t * container_18 = container_create(container_9);
        lv_obj_set_flex_flow(container_18, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_flex_cross_place(container_18, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(container_18, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(container_18, 0, 0);
        lv_obj_set_style_pad_column(container_18, 0, 0);
        lv_obj_set_width(container_18, lv_pct(100));
        lv_obj_set_height(container_18, 24);
        lv_obj_t * container_19 = container_create(container_18);
        lv_obj_set_flex_flow(container_19, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_main_place(container_19, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(container_19, 0, 0);
        lv_obj_set_style_pad_row(container_19, 0, 0);
        lv_obj_set_width(container_19, 72);
        lv_obj_set_height(container_19, lv_pct(100));
        lv_obj_t * label_7 = label_create(container_19);
        lv_label_set_text(label_7, "Ryn");
        lv_obj_set_style_text_font(label_7, font_inter_semi_bold_11, 0);
        lv_obj_set_style_text_color(label_7, lv_color_hex(0x334155), 0);

        lv_obj_t * container_20 = container_create(container_18);
        lv_obj_set_flex_flow(container_20, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_flex_cross_place(container_20, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(container_20, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(container_20, 0, 0);
        lv_obj_set_style_pad_column(container_20, 0, 0);
        lv_obj_set_width(container_20, 320);
        lv_obj_set_height(container_20, lv_pct(100));
        lv_obj_t * container_21 = container_create(container_20);
        lv_obj_set_flex_flow(container_21, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_main_place(container_21, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_cross_place(container_21, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(container_21, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(container_21, 0, 0);
        lv_obj_set_style_pad_row(container_21, 0, 0);
        lv_obj_set_width(container_21, 64);
        lv_obj_set_height(container_21, lv_pct(100));

        lv_obj_t * container_22 = container_create(container_20);
        lv_obj_set_flex_flow(container_22, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_main_place(container_22, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_cross_place(container_22, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(container_22, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(container_22, 0, 0);
        lv_obj_set_style_pad_row(container_22, 0, 0);
        lv_obj_set_width(container_22, 64);
        lv_obj_set_height(container_22, lv_pct(100));

        lv_obj_t * container_23 = container_create(container_20);
        lv_obj_set_flex_flow(container_23, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_main_place(container_23, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_cross_place(container_23, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(container_23, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(container_23, 0, 0);
        lv_obj_set_style_pad_row(container_23, 0, 0);
        lv_obj_set_width(container_23, 64);
        lv_obj_set_height(container_23, lv_pct(100));

        lv_obj_t * container_24 = container_create(container_20);
        lv_obj_set_flex_flow(container_24, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_main_place(container_24, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_cross_place(container_24, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(container_24, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(container_24, 0, 0);
        lv_obj_set_style_pad_row(container_24, 0, 0);
        lv_obj_set_width(container_24, 64);
        lv_obj_set_height(container_24, lv_pct(100));

        lv_obj_t * container_25 = container_create(container_20);
        lv_obj_set_flex_flow(container_25, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_main_place(container_25, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_cross_place(container_25, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(container_25, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(container_25, 0, 0);
        lv_obj_set_style_pad_row(container_25, 0, 0);
        lv_obj_set_width(container_25, 64);
        lv_obj_set_height(container_25, lv_pct(100));

        lv_obj_t * card_2 = card_create(container_20);
        lv_obj_set_flag(card_2, LV_OBJ_FLAG_IGNORE_LAYOUT, true);
        lv_obj_set_x(card_2, 26);
        lv_obj_set_y(card_2, 8);
        lv_obj_set_width(card_2, 134);
        lv_obj_set_height(card_2, 8);
        lv_obj_set_style_bg_color(card_2, lv_color_hex(0x8B5CF6), 0);
        lv_obj_set_style_radius(card_2, 4, 0);

        lv_obj_t * container_26 = container_create(container_9);
        lv_obj_set_flex_flow(container_26, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_flex_cross_place(container_26, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(container_26, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(container_26, 0, 0);
        lv_obj_set_style_pad_column(container_26, 0, 0);
        lv_obj_set_width(container_26, lv_pct(100));
        lv_obj_set_height(container_26, 24);
        lv_obj_t * container_27 = container_create(container_26);
        lv_obj_set_flex_flow(container_27, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_main_place(container_27, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(container_27, 0, 0);
        lv_obj_set_style_pad_row(container_27, 0, 0);
        lv_obj_set_width(container_27, 72);
        lv_obj_set_height(container_27, lv_pct(100));
        lv_obj_t * label_8 = label_create(container_27);
        lv_label_set_text(label_8, "Trinity");
        lv_obj_set_style_text_font(label_8, font_inter_semi_bold_11, 0);
        lv_obj_set_style_text_color(label_8, lv_color_hex(0x334155), 0);

        lv_obj_t * container_28 = container_create(container_26);
        lv_obj_set_flex_flow(container_28, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_flex_cross_place(container_28, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(container_28, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(container_28, 0, 0);
        lv_obj_set_style_pad_column(container_28, 0, 0);
        lv_obj_set_width(container_28, 320);
        lv_obj_set_height(container_28, lv_pct(100));
        lv_obj_t * container_29 = container_create(container_28);
        lv_obj_set_flex_flow(container_29, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_main_place(container_29, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_cross_place(container_29, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(container_29, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(container_29, 0, 0);
        lv_obj_set_style_pad_row(container_29, 0, 0);
        lv_obj_set_width(container_29, 64);
        lv_obj_set_height(container_29, lv_pct(100));

        lv_obj_t * container_30 = container_create(container_28);
        lv_obj_set_flex_flow(container_30, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_main_place(container_30, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_cross_place(container_30, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(container_30, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(container_30, 0, 0);
        lv_obj_set_style_pad_row(container_30, 0, 0);
        lv_obj_set_width(container_30, 64);
        lv_obj_set_height(container_30, lv_pct(100));

        lv_obj_t * container_31 = container_create(container_28);
        lv_obj_set_flex_flow(container_31, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_main_place(container_31, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_cross_place(container_31, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(container_31, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(container_31, 0, 0);
        lv_obj_set_style_pad_row(container_31, 0, 0);
        lv_obj_set_width(container_31, 64);
        lv_obj_set_height(container_31, lv_pct(100));

        lv_obj_t * container_32 = container_create(container_28);
        lv_obj_set_flex_flow(container_32, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_main_place(container_32, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_cross_place(container_32, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(container_32, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(container_32, 0, 0);
        lv_obj_set_style_pad_row(container_32, 0, 0);
        lv_obj_set_width(container_32, 64);
        lv_obj_set_height(container_32, lv_pct(100));

        lv_obj_t * container_33 = container_create(container_28);
        lv_obj_set_flex_flow(container_33, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_main_place(container_33, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_cross_place(container_33, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(container_33, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(container_33, 0, 0);
        lv_obj_set_style_pad_row(container_33, 0, 0);
        lv_obj_set_width(container_33, 64);
        lv_obj_set_height(container_33, lv_pct(100));

        lv_obj_t * card_3 = card_create(container_28);
        lv_obj_set_flag(card_3, LV_OBJ_FLAG_IGNORE_LAYOUT, true);
        lv_obj_set_x(card_3, 70);
        lv_obj_set_y(card_3, 8);
        lv_obj_set_width(card_3, 128);
        lv_obj_set_height(card_3, 8);
        lv_obj_set_style_bg_color(card_3, lv_color_hex(0xEC4899), 0);
        lv_obj_set_style_radius(card_3, 4, 0);

        lv_obj_t * container_34 = container_create(container_9);
        lv_obj_set_flex_flow(container_34, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_flex_cross_place(container_34, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(container_34, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(container_34, 0, 0);
        lv_obj_set_style_pad_column(container_34, 0, 0);
        lv_obj_set_width(container_34, lv_pct(100));
        lv_obj_set_height(container_34, 24);
        lv_obj_t * container_35 = container_create(container_34);
        lv_obj_set_flex_flow(container_35, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_main_place(container_35, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(container_35, 0, 0);
        lv_obj_set_style_pad_row(container_35, 0, 0);
        lv_obj_set_width(container_35, 72);
        lv_obj_set_height(container_35, lv_pct(100));
        lv_obj_t * label_9 = label_create(container_35);
        lv_label_set_text(label_9, "Kimberly");
        lv_obj_set_style_text_font(label_9, font_inter_semi_bold_11, 0);
        lv_obj_set_style_text_color(label_9, lv_color_hex(0x334155), 0);

        lv_obj_t * container_36 = container_create(container_34);
        lv_obj_set_flex_flow(container_36, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_flex_cross_place(container_36, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(container_36, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(container_36, 0, 0);
        lv_obj_set_style_pad_column(container_36, 0, 0);
        lv_obj_set_width(container_36, 320);
        lv_obj_set_height(container_36, lv_pct(100));
        lv_obj_t * container_37 = container_create(container_36);
        lv_obj_set_flex_flow(container_37, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_main_place(container_37, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_cross_place(container_37, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(container_37, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(container_37, 0, 0);
        lv_obj_set_style_pad_row(container_37, 0, 0);
        lv_obj_set_width(container_37, 64);
        lv_obj_set_height(container_37, lv_pct(100));

        lv_obj_t * container_38 = container_create(container_36);
        lv_obj_set_flex_flow(container_38, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_main_place(container_38, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_cross_place(container_38, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(container_38, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(container_38, 0, 0);
        lv_obj_set_style_pad_row(container_38, 0, 0);
        lv_obj_set_width(container_38, 64);
        lv_obj_set_height(container_38, lv_pct(100));

        lv_obj_t * container_39 = container_create(container_36);
        lv_obj_set_flex_flow(container_39, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_main_place(container_39, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_cross_place(container_39, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(container_39, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(container_39, 0, 0);
        lv_obj_set_style_pad_row(container_39, 0, 0);
        lv_obj_set_width(container_39, 64);
        lv_obj_set_height(container_39, lv_pct(100));

        lv_obj_t * container_40 = container_create(container_36);
        lv_obj_set_flex_flow(container_40, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_main_place(container_40, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_cross_place(container_40, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(container_40, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(container_40, 0, 0);
        lv_obj_set_style_pad_row(container_40, 0, 0);
        lv_obj_set_width(container_40, 64);
        lv_obj_set_height(container_40, lv_pct(100));

        lv_obj_t * container_41 = container_create(container_36);
        lv_obj_set_flex_flow(container_41, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_main_place(container_41, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_cross_place(container_41, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(container_41, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(container_41, 0, 0);
        lv_obj_set_style_pad_row(container_41, 0, 0);
        lv_obj_set_width(container_41, 64);
        lv_obj_set_height(container_41, lv_pct(100));

        lv_obj_t * card_4 = card_create(container_36);
        lv_obj_set_flag(card_4, LV_OBJ_FLAG_IGNORE_LAYOUT, true);
        lv_obj_set_x(card_4, 116);
        lv_obj_set_y(card_4, 8);
        lv_obj_set_width(card_4, 142);
        lv_obj_set_height(card_4, 8);
        lv_obj_set_style_bg_color(card_4, lv_color_hex(0xF59E0B), 0);
        lv_obj_set_style_radius(card_4, 4, 0);

        lv_obj_t * container_42 = container_create(container_9);
        lv_obj_set_flex_flow(container_42, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_flex_cross_place(container_42, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(container_42, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(container_42, 0, 0);
        lv_obj_set_style_pad_column(container_42, 0, 0);
        lv_obj_set_width(container_42, lv_pct(100));
        lv_obj_set_height(container_42, 24);
        lv_obj_t * container_43 = container_create(container_42);
        lv_obj_set_flex_flow(container_43, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_main_place(container_43, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(container_43, 0, 0);
        lv_obj_set_style_pad_row(container_43, 0, 0);
        lv_obj_set_width(container_43, 72);
        lv_obj_set_height(container_43, lv_pct(100));
        lv_obj_t * label_10 = label_create(container_43);
        lv_label_set_text(label_10, "Lyra");
        lv_obj_set_style_text_font(label_10, font_inter_semi_bold_11, 0);
        lv_obj_set_style_text_color(label_10, lv_color_hex(0x334155), 0);

        lv_obj_t * container_44 = container_create(container_42);
        lv_obj_set_flex_flow(container_44, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_flex_cross_place(container_44, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(container_44, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(container_44, 0, 0);
        lv_obj_set_style_pad_column(container_44, 0, 0);
        lv_obj_set_width(container_44, 320);
        lv_obj_set_height(container_44, lv_pct(100));
        lv_obj_t * container_45 = container_create(container_44);
        lv_obj_set_flex_flow(container_45, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_main_place(container_45, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_cross_place(container_45, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(container_45, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(container_45, 0, 0);
        lv_obj_set_style_pad_row(container_45, 0, 0);
        lv_obj_set_width(container_45, 64);
        lv_obj_set_height(container_45, lv_pct(100));

        lv_obj_t * container_46 = container_create(container_44);
        lv_obj_set_flex_flow(container_46, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_main_place(container_46, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_cross_place(container_46, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(container_46, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(container_46, 0, 0);
        lv_obj_set_style_pad_row(container_46, 0, 0);
        lv_obj_set_width(container_46, 64);
        lv_obj_set_height(container_46, lv_pct(100));

        lv_obj_t * container_47 = container_create(container_44);
        lv_obj_set_flex_flow(container_47, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_main_place(container_47, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_cross_place(container_47, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(container_47, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(container_47, 0, 0);
        lv_obj_set_style_pad_row(container_47, 0, 0);
        lv_obj_set_width(container_47, 64);
        lv_obj_set_height(container_47, lv_pct(100));

        lv_obj_t * container_48 = container_create(container_44);
        lv_obj_set_flex_flow(container_48, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_main_place(container_48, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_cross_place(container_48, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(container_48, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(container_48, 0, 0);
        lv_obj_set_style_pad_row(container_48, 0, 0);
        lv_obj_set_width(container_48, 64);
        lv_obj_set_height(container_48, lv_pct(100));

        lv_obj_t * container_49 = container_create(container_44);
        lv_obj_set_flex_flow(container_49, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_main_place(container_49, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_cross_place(container_49, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(container_49, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(container_49, 0, 0);
        lv_obj_set_style_pad_row(container_49, 0, 0);
        lv_obj_set_width(container_49, 64);
        lv_obj_set_height(container_49, lv_pct(100));

        lv_obj_t * card_5 = card_create(container_44);
        lv_obj_set_flag(card_5, LV_OBJ_FLAG_IGNORE_LAYOUT, true);
        lv_obj_set_x(card_5, 166);
        lv_obj_set_y(card_5, 8);
        lv_obj_set_width(card_5, 122);
        lv_obj_set_height(card_5, 8);
        lv_obj_set_style_bg_color(card_5, lv_color_hex(0x10B981), 0);
        lv_obj_set_style_radius(card_5, 4, 0);

        the_root = card_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

