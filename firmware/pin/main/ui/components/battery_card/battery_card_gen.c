/**
 * @file battery_card_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "battery_card_gen.h"
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

lv_obj_t * battery_card_create(lv_obj_t * parent)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if PLURALITY_PIN_CHECK_COMPILE_TARGET(PLURALITY_PIN_TARGET_ALL)
    if (plurality_pin_check_target(PLURALITY_PIN_TARGET_ALL)) {
        lv_obj_t * card_0 = card_create(parent);
        lv_obj_set_name_static(card_0, "battery_card_#");
        lv_obj_set_flex_flow(card_0, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_flex_cross_place(card_0, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(card_0, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(card_0, 12, 0);
        lv_obj_set_style_pad_column(card_0, 12, 0);
        lv_obj_set_width(card_0, 195);
        lv_obj_set_height(card_0, 80);
        lv_obj_set_style_bg_color(card_0, lv_color_hex(0x787878), 0);
        lv_obj_set_style_bg_opa(card_0, 10, 0);
        lv_obj_set_style_radius(card_0, 10, 0);

        lv_obj_t * card_1 = card_create(card_0);
        lv_obj_set_flex_flow(card_1, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_main_place(card_1, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_cross_place(card_1, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(card_1, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(card_1, 0, 0);
        lv_obj_set_style_pad_row(card_1, 0, 0);
        lv_obj_set_width(card_1, 50);
        lv_obj_set_height(card_1, 50);
        lv_obj_set_style_bg_color(card_1, lv_color_hex(0xFFFFFF), 0);
        lv_obj_set_style_bg_opa(card_1, 2, 0);
        lv_obj_set_style_border_color(card_1, lv_color_hex(0xFFFFFF), 0);
        lv_obj_set_style_border_opa(card_1, 6, 0);
        lv_obj_set_style_border_width(card_1, 1, 0);
        lv_obj_set_style_radius(card_1, 10, 0);
        lv_obj_t * image_0 = image_create(card_1);
        lv_obj_set_width(image_0, 22);
        lv_obj_set_height(image_0, 22);
        lv_image_set_src(image_0, image_vec_42_862);
        lv_obj_set_flag(image_0, LV_OBJ_FLAG_SCROLLABLE, false);

        lv_obj_t * container_0 = container_create(card_0);
        lv_obj_set_flex_flow(container_0, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_pad_all(container_0, 0, 0);
        lv_obj_set_style_pad_row(container_0, 2, 0);
        lv_obj_set_width(container_0, 0);
        lv_obj_set_height(container_0, LV_SIZE_CONTENT);
        lv_obj_set_flex_grow(container_0, 1);
        lv_obj_t * label_0 = label_create(container_0);
        lv_label_set_text(label_0, "Battery");
        lv_obj_set_style_text_font(label_0, font_inter_semi_bold_12, 0);
        lv_obj_set_style_text_color(label_0, lv_color_hex(0xFFFFFF), 0);
        lv_obj_set_style_text_opa(label_0, 126, 0);

        lv_obj_t * container_1 = container_create(container_0);
        lv_obj_set_flex_flow(container_1, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_pad_all(container_1, 0, 0);
        lv_obj_set_style_pad_column(container_1, 8, 0);
        lv_obj_set_width(container_1, lv_pct(100));
        lv_obj_set_height(container_1, LV_SIZE_CONTENT);
        lv_obj_t * label_1 = label_create(container_1);
        lv_label_set_text(label_1, "82");
        lv_obj_set_style_text_font(label_1, font_inter_bold_23, 0);
        lv_obj_set_style_text_color(label_1, lv_color_hex(0xFFFFFF), 0);

        lv_obj_t * label_2 = label_create(container_1);
        lv_label_set_text(label_2, "%");
        lv_obj_set_style_text_font(label_2, font_inter_semi_bold_16, 0);
        lv_obj_set_style_text_color(label_2, lv_color_hex(0xFFFFFF), 0);
        lv_obj_set_style_text_opa(label_2, 126, 0);

        the_root = card_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

