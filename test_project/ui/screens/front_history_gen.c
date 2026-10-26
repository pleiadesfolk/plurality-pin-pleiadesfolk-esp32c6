/**
 * @file front_history_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "front_history_gen.h"
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

lv_obj_t * front_history_create(void)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if PLURALITY_PIN_CHECK_COMPILE_TARGET(PLURALITY_PIN_TARGET_ALL)
    if (plurality_pin_check_target(PLURALITY_PIN_TARGET_ALL)) {
        lv_obj_t * lv_obj_0 = lv_obj_create(NULL);
        lv_obj_set_name_static(lv_obj_0, "front_history_#");
        lv_obj_set_style_bg_color(lv_obj_0, lv_color_hex(0x333333), 0);
        lv_obj_set_flag(lv_obj_0, LV_OBJ_FLAG_SCROLLABLE, false);
        lv_obj_set_style_pad_all(lv_obj_0, 0, 0);

        lv_obj_add_style(lv_obj_0, &style_screen_base_global, 0);
        lv_obj_t * card_0 = card_create(lv_obj_0);
        lv_obj_set_flex_flow(card_0, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_pad_top(card_0, 12, 0);
        lv_obj_set_style_pad_bottom(card_0, 10, 0);
        lv_obj_set_style_pad_hor(card_0, 12, 0);
        lv_obj_set_style_pad_row(card_0, 8, 0);
        lv_obj_set_align(card_0, LV_ALIGN_CENTER);
        lv_obj_set_x(card_0, 0);
        lv_obj_set_y(card_0, -23);
        lv_obj_set_width(card_0, 416);
        lv_obj_set_height(card_0, 205);
        lv_obj_set_style_bg_color(card_0, lv_color_hex(0xF8FAFC), 0);
        lv_obj_set_style_border_color(card_0, lv_color_hex(0xE2E8F0), 0);
        lv_obj_set_style_border_width(card_0, 1, 0);
        lv_obj_set_style_radius(card_0, 15, 0);
        lv_obj_t * row_0 = row_create(card_0, 0, 0, 0, 0, 0, 0, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_width(row_0, lv_pct(100));
        lv_obj_set_height(row_0, LV_SIZE_CONTENT);
        lv_obj_t * label_0 = label_create(row_0);
        lv_label_set_text(label_0, "Front history");
        lv_obj_set_style_text_font(label_0, font_inter_bold_14, 0);
        lv_obj_set_style_text_color(label_0, lv_color_hex(0x0F172A), 0);

        lv_obj_t * column_0 = column_create(card_0, 0, 0, 0, 0, 4, 1, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
        lv_obj_set_width(column_0, lv_pct(100));
        lv_obj_set_height(column_0, 0);
        lv_obj_t * row_1 = row_create(column_0, 0, 0, 0, 0, 0, 0, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_width(row_1, lv_pct(100));
        lv_obj_set_height(row_1, 28);
        lv_obj_t * column_1 = column_create(row_1, 0, 0, 0, 0, 0, 0, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
        lv_obj_set_width(column_1, 72);
        lv_obj_set_height(column_1, 28);

        lv_obj_t * column_2 = column_create(row_1, 0, 0, 0, 0, 0, 0, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_width(column_2, 64);
        lv_obj_set_height(column_2, 28);
        lv_obj_t * label_1 = label_create(column_2);
        lv_obj_set_width(label_1, lv_pct(100));
        lv_label_set_text(label_1, "Mon\n12:00pm");
        lv_obj_set_style_text_font(label_1, font_inter_semi_bold_8, 0);
        lv_obj_set_style_text_line_space(label_1, 1, 0);
        lv_obj_set_style_text_color(label_1, lv_color_hex(0x64748B), 0);
        lv_obj_set_style_text_align(label_1, LV_TEXT_ALIGN_CENTER, 0);

        lv_obj_t * column_3 = column_create(row_1, 0, 0, 0, 0, 0, 0, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_width(column_3, 64);
        lv_obj_set_height(column_3, 28);
        lv_obj_t * label_2 = label_create(column_3);
        lv_obj_set_width(label_2, lv_pct(100));
        lv_label_set_text(label_2, "Tue\n12:00pm");
        lv_obj_set_style_text_font(label_2, font_inter_semi_bold_8, 0);
        lv_obj_set_style_text_line_space(label_2, 1, 0);
        lv_obj_set_style_text_color(label_2, lv_color_hex(0x64748B), 0);
        lv_obj_set_style_text_align(label_2, LV_TEXT_ALIGN_CENTER, 0);

        lv_obj_t * column_4 = column_create(row_1, 0, 0, 0, 0, 0, 0, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_width(column_4, 64);
        lv_obj_set_height(column_4, 28);
        lv_obj_t * label_3 = label_create(column_4);
        lv_obj_set_width(label_3, lv_pct(100));
        lv_label_set_text(label_3, "Wed\n12:00pm");
        lv_obj_set_style_text_font(label_3, font_inter_semi_bold_8, 0);
        lv_obj_set_style_text_line_space(label_3, 1, 0);
        lv_obj_set_style_text_color(label_3, lv_color_hex(0x64748B), 0);
        lv_obj_set_style_text_align(label_3, LV_TEXT_ALIGN_CENTER, 0);

        lv_obj_t * column_5 = column_create(row_1, 0, 0, 0, 0, 0, 0, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_width(column_5, 64);
        lv_obj_set_height(column_5, 28);
        lv_obj_t * label_4 = label_create(column_5);
        lv_obj_set_width(label_4, lv_pct(100));
        lv_label_set_text(label_4, "Thu\n12:00pm");
        lv_obj_set_style_text_font(label_4, font_inter_semi_bold_8, 0);
        lv_obj_set_style_text_line_space(label_4, 1, 0);
        lv_obj_set_style_text_color(label_4, lv_color_hex(0x64748B), 0);
        lv_obj_set_style_text_align(label_4, LV_TEXT_ALIGN_CENTER, 0);

        lv_obj_t * column_6 = column_create(row_1, 0, 0, 0, 0, 0, 0, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_width(column_6, 64);
        lv_obj_set_height(column_6, 28);
        lv_obj_t * label_5 = label_create(column_6);
        lv_obj_set_width(label_5, lv_pct(100));
        lv_label_set_text(label_5, "Fri\n12:00pm");
        lv_obj_set_style_text_font(label_5, font_inter_semi_bold_8, 0);
        lv_obj_set_style_text_line_space(label_5, 1, 0);
        lv_obj_set_style_text_color(label_5, lv_color_hex(0x64748B), 0);
        lv_obj_set_style_text_align(label_5, LV_TEXT_ALIGN_CENTER, 0);

        lv_obj_t * column_7 = column_create(column_0, 0, 0, 0, 0, 0, 1, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
        lv_obj_set_width(column_7, lv_pct(100));
        lv_obj_set_height(column_7, 0);
        lv_obj_t * row_2 = row_create(column_7, 0, 0, 0, 0, 0, 0, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_width(row_2, lv_pct(100));
        lv_obj_set_height(row_2, 24);
        lv_obj_t * column_8 = column_create(row_2, 0, 0, 0, 0, 0, 0, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
        lv_obj_set_width(column_8, 72);
        lv_obj_set_height(column_8, lv_pct(100));
        lv_obj_t * label_6 = label_create(column_8);
        lv_label_set_text(label_6, "Riley");
        lv_obj_set_style_text_font(label_6, font_inter_semi_bold_11, 0);
        lv_obj_set_style_text_color(label_6, lv_color_hex(0x334155), 0);

        lv_obj_t * row_3 = row_create(row_2, 0, 0, 0, 0, 0, 0, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_width(row_3, 320);
        lv_obj_set_height(row_3, lv_pct(100));
        lv_obj_t * column_9 = column_create(row_3, 0, 0, 0, 0, 0, 0, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_width(column_9, 64);
        lv_obj_set_height(column_9, lv_pct(100));

        lv_obj_t * column_10 = column_create(row_3, 0, 0, 0, 0, 0, 0, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_width(column_10, 64);
        lv_obj_set_height(column_10, lv_pct(100));

        lv_obj_t * column_11 = column_create(row_3, 0, 0, 0, 0, 0, 0, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_width(column_11, 64);
        lv_obj_set_height(column_11, lv_pct(100));

        lv_obj_t * column_12 = column_create(row_3, 0, 0, 0, 0, 0, 0, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_width(column_12, 64);
        lv_obj_set_height(column_12, lv_pct(100));

        lv_obj_t * column_13 = column_create(row_3, 0, 0, 0, 0, 0, 0, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_width(column_13, 64);
        lv_obj_set_height(column_13, lv_pct(100));

        lv_obj_t * card_1 = card_create(row_3);
        lv_obj_set_flag(card_1, LV_OBJ_FLAG_IGNORE_LAYOUT, true);
        lv_obj_set_x(card_1, 0);
        lv_obj_set_y(card_1, 8);
        lv_obj_set_width(card_1, 116);
        lv_obj_set_height(card_1, 8);
        lv_obj_set_style_bg_color(card_1, lv_color_hex(0x3B82F6), 0);
        lv_obj_set_style_radius(card_1, 4, 0);

        lv_obj_t * row_4 = row_create(column_7, 0, 0, 0, 0, 0, 0, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_width(row_4, lv_pct(100));
        lv_obj_set_height(row_4, 24);
        lv_obj_t * column_14 = column_create(row_4, 0, 0, 0, 0, 0, 0, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
        lv_obj_set_width(column_14, 72);
        lv_obj_set_height(column_14, lv_pct(100));
        lv_obj_t * label_7 = label_create(column_14);
        lv_label_set_text(label_7, "Ryn");
        lv_obj_set_style_text_font(label_7, font_inter_semi_bold_11, 0);
        lv_obj_set_style_text_color(label_7, lv_color_hex(0x334155), 0);

        lv_obj_t * row_5 = row_create(row_4, 0, 0, 0, 0, 0, 0, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_width(row_5, 320);
        lv_obj_set_height(row_5, lv_pct(100));
        lv_obj_t * column_15 = column_create(row_5, 0, 0, 0, 0, 0, 0, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_width(column_15, 64);
        lv_obj_set_height(column_15, lv_pct(100));

        lv_obj_t * column_16 = column_create(row_5, 0, 0, 0, 0, 0, 0, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_width(column_16, 64);
        lv_obj_set_height(column_16, lv_pct(100));

        lv_obj_t * column_17 = column_create(row_5, 0, 0, 0, 0, 0, 0, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_width(column_17, 64);
        lv_obj_set_height(column_17, lv_pct(100));

        lv_obj_t * column_18 = column_create(row_5, 0, 0, 0, 0, 0, 0, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_width(column_18, 64);
        lv_obj_set_height(column_18, lv_pct(100));

        lv_obj_t * column_19 = column_create(row_5, 0, 0, 0, 0, 0, 0, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_width(column_19, 64);
        lv_obj_set_height(column_19, lv_pct(100));

        lv_obj_t * card_2 = card_create(row_5);
        lv_obj_set_flag(card_2, LV_OBJ_FLAG_IGNORE_LAYOUT, true);
        lv_obj_set_x(card_2, 26);
        lv_obj_set_y(card_2, 8);
        lv_obj_set_width(card_2, 134);
        lv_obj_set_height(card_2, 8);
        lv_obj_set_style_bg_color(card_2, lv_color_hex(0x8B5CF6), 0);
        lv_obj_set_style_radius(card_2, 4, 0);

        lv_obj_t * row_6 = row_create(column_7, 0, 0, 0, 0, 0, 0, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_width(row_6, lv_pct(100));
        lv_obj_set_height(row_6, 24);
        lv_obj_t * column_20 = column_create(row_6, 0, 0, 0, 0, 0, 0, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
        lv_obj_set_width(column_20, 72);
        lv_obj_set_height(column_20, lv_pct(100));
        lv_obj_t * label_8 = label_create(column_20);
        lv_label_set_text(label_8, "Trinity");
        lv_obj_set_style_text_font(label_8, font_inter_semi_bold_11, 0);
        lv_obj_set_style_text_color(label_8, lv_color_hex(0x334155), 0);

        lv_obj_t * row_7 = row_create(row_6, 0, 0, 0, 0, 0, 0, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_width(row_7, 320);
        lv_obj_set_height(row_7, lv_pct(100));
        lv_obj_t * column_21 = column_create(row_7, 0, 0, 0, 0, 0, 0, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_width(column_21, 64);
        lv_obj_set_height(column_21, lv_pct(100));

        lv_obj_t * column_22 = column_create(row_7, 0, 0, 0, 0, 0, 0, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_width(column_22, 64);
        lv_obj_set_height(column_22, lv_pct(100));

        lv_obj_t * column_23 = column_create(row_7, 0, 0, 0, 0, 0, 0, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_width(column_23, 64);
        lv_obj_set_height(column_23, lv_pct(100));

        lv_obj_t * column_24 = column_create(row_7, 0, 0, 0, 0, 0, 0, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_width(column_24, 64);
        lv_obj_set_height(column_24, lv_pct(100));

        lv_obj_t * column_25 = column_create(row_7, 0, 0, 0, 0, 0, 0, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_width(column_25, 64);
        lv_obj_set_height(column_25, lv_pct(100));

        lv_obj_t * card_3 = card_create(row_7);
        lv_obj_set_flag(card_3, LV_OBJ_FLAG_IGNORE_LAYOUT, true);
        lv_obj_set_x(card_3, 70);
        lv_obj_set_y(card_3, 8);
        lv_obj_set_width(card_3, 128);
        lv_obj_set_height(card_3, 8);
        lv_obj_set_style_bg_color(card_3, lv_color_hex(0xEC4899), 0);
        lv_obj_set_style_radius(card_3, 4, 0);

        lv_obj_t * row_8 = row_create(column_7, 0, 0, 0, 0, 0, 0, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_width(row_8, lv_pct(100));
        lv_obj_set_height(row_8, 24);
        lv_obj_t * column_26 = column_create(row_8, 0, 0, 0, 0, 0, 0, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
        lv_obj_set_width(column_26, 72);
        lv_obj_set_height(column_26, lv_pct(100));
        lv_obj_t * label_9 = label_create(column_26);
        lv_label_set_text(label_9, "Kimberly");
        lv_obj_set_style_text_font(label_9, font_inter_semi_bold_11, 0);
        lv_obj_set_style_text_color(label_9, lv_color_hex(0x334155), 0);

        lv_obj_t * row_9 = row_create(row_8, 0, 0, 0, 0, 0, 0, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_width(row_9, 320);
        lv_obj_set_height(row_9, lv_pct(100));
        lv_obj_t * column_27 = column_create(row_9, 0, 0, 0, 0, 0, 0, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_width(column_27, 64);
        lv_obj_set_height(column_27, lv_pct(100));

        lv_obj_t * column_28 = column_create(row_9, 0, 0, 0, 0, 0, 0, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_width(column_28, 64);
        lv_obj_set_height(column_28, lv_pct(100));

        lv_obj_t * column_29 = column_create(row_9, 0, 0, 0, 0, 0, 0, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_width(column_29, 64);
        lv_obj_set_height(column_29, lv_pct(100));

        lv_obj_t * column_30 = column_create(row_9, 0, 0, 0, 0, 0, 0, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_width(column_30, 64);
        lv_obj_set_height(column_30, lv_pct(100));

        lv_obj_t * column_31 = column_create(row_9, 0, 0, 0, 0, 0, 0, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_width(column_31, 64);
        lv_obj_set_height(column_31, lv_pct(100));

        lv_obj_t * card_4 = card_create(row_9);
        lv_obj_set_flag(card_4, LV_OBJ_FLAG_IGNORE_LAYOUT, true);
        lv_obj_set_x(card_4, 116);
        lv_obj_set_y(card_4, 8);
        lv_obj_set_width(card_4, 142);
        lv_obj_set_height(card_4, 8);
        lv_obj_set_style_bg_color(card_4, lv_color_hex(0xF59E0B), 0);
        lv_obj_set_style_radius(card_4, 4, 0);

        lv_obj_t * row_10 = row_create(column_7, 0, 0, 0, 0, 0, 0, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_width(row_10, lv_pct(100));
        lv_obj_set_height(row_10, 24);
        lv_obj_t * column_32 = column_create(row_10, 0, 0, 0, 0, 0, 0, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
        lv_obj_set_width(column_32, 72);
        lv_obj_set_height(column_32, lv_pct(100));
        lv_obj_t * label_10 = label_create(column_32);
        lv_label_set_text(label_10, "Lyra");
        lv_obj_set_style_text_font(label_10, font_inter_semi_bold_11, 0);
        lv_obj_set_style_text_color(label_10, lv_color_hex(0x334155), 0);

        lv_obj_t * row_11 = row_create(row_10, 0, 0, 0, 0, 0, 0, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_width(row_11, 320);
        lv_obj_set_height(row_11, lv_pct(100));
        lv_obj_t * column_33 = column_create(row_11, 0, 0, 0, 0, 0, 0, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_width(column_33, 64);
        lv_obj_set_height(column_33, lv_pct(100));

        lv_obj_t * column_34 = column_create(row_11, 0, 0, 0, 0, 0, 0, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_width(column_34, 64);
        lv_obj_set_height(column_34, lv_pct(100));

        lv_obj_t * column_35 = column_create(row_11, 0, 0, 0, 0, 0, 0, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_width(column_35, 64);
        lv_obj_set_height(column_35, lv_pct(100));

        lv_obj_t * column_36 = column_create(row_11, 0, 0, 0, 0, 0, 0, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_width(column_36, 64);
        lv_obj_set_height(column_36, lv_pct(100));

        lv_obj_t * column_37 = column_create(row_11, 0, 0, 0, 0, 0, 0, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_width(column_37, 64);
        lv_obj_set_height(column_37, lv_pct(100));

        lv_obj_t * card_5 = card_create(row_11);
        lv_obj_set_flag(card_5, LV_OBJ_FLAG_IGNORE_LAYOUT, true);
        lv_obj_set_x(card_5, 166);
        lv_obj_set_y(card_5, 8);
        lv_obj_set_width(card_5, 122);
        lv_obj_set_height(card_5, 8);
        lv_obj_set_style_bg_color(card_5, lv_color_hex(0x10B981), 0);
        lv_obj_set_style_radius(card_5, 4, 0);

        lv_obj_t * segments_2_density_0_0 = segments_2_density_0_create(lv_obj_0);
        lv_obj_set_align(segments_2_density_0_0, LV_ALIGN_TOP_MID);
        lv_obj_set_x(segments_2_density_0_0, 0);
        lv_obj_set_y(segments_2_density_0_0, 219);
        lv_obj_set_height(segments_2_density_0_0, 47);

        the_root = lv_obj_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

