/**
 * @file wi_fi_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "wi_fi_gen.h"
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

lv_obj_t * wi_fi_create(lv_obj_t * parent)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if PLURALITY_PIN_CHECK_COMPILE_TARGET(PLURALITY_PIN_TARGET_ALL)
    if (plurality_pin_check_target(PLURALITY_PIN_TARGET_ALL)) {
        lv_obj_t * card_0 = card_create(parent);
        lv_obj_set_name_static(card_0, "wi_fi_#");
        lv_obj_set_flex_flow(card_0, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_main_place(card_0, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_cross_place(card_0, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(card_0, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_hor(card_0, 12, 0);
        lv_obj_set_style_pad_ver(card_0, 8, 0);
        lv_obj_set_style_pad_row(card_0, 2, 0);
        lv_obj_set_width(card_0, 149);
        lv_obj_set_height(card_0, lv_pct(100));
        lv_obj_set_style_bg_color(card_0, lv_color_hex(0x787878), 0);
        lv_obj_set_style_bg_opa(card_0, 10, 0);
        lv_obj_set_style_radius(card_0, 10, 0);

        lv_obj_t * container_0 = container_create(card_0);
        lv_obj_set_flex_flow(container_0, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_main_place(container_0, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(container_0, 0, 0);
        lv_obj_set_style_pad_row(container_0, 3, 0);
        lv_obj_set_width(container_0, lv_pct(100));
        lv_obj_set_height(container_0, 0);
        lv_obj_set_flex_grow(container_0, 1);
        lv_obj_t * container_1 = container_create(container_0);
        lv_obj_set_flex_flow(container_1, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_main_place(container_1, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(container_1, 0, 0);
        lv_obj_set_style_pad_row(container_1, 0, 0);
        lv_obj_set_width(container_1, 25);
        lv_obj_set_height(container_1, 25);
        lv_obj_t * image_0 = image_create(container_1);
        lv_obj_set_width(image_0, 25);
        lv_obj_set_height(image_0, 25);
        lv_image_set_src(image_0, image_vec_23_372);
        lv_obj_set_flag(image_0, LV_OBJ_FLAG_SCROLLABLE, false);

        lv_obj_t * container_2 = container_create(container_0);
        lv_obj_set_flex_flow(container_2, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_flex_main_place(container_2, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_cross_place(container_2, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(container_2, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(container_2, 0, 0);
        lv_obj_set_style_pad_column(container_2, 10, 0);
        lv_obj_set_width(container_2, 125);
        lv_obj_set_height(container_2, 15);
        lv_obj_t * label_0 = label_create(container_2);
        lv_obj_set_width(label_0, 0);
        lv_obj_set_height(label_0, lv_pct(100));
        lv_obj_set_flex_grow(label_0, 1);
        lv_label_set_text(label_0, "Wi-Fi");
        lv_obj_set_style_text_font(label_0, font_inter_semi_bold_14, 0);
        lv_obj_set_style_text_color(label_0, lv_color_hex(0x757575), 0);
        lv_label_set_long_mode(label_0, LV_LABEL_LONG_MODE_CLIP);

        lv_obj_t * label_1 = label_create(container_2);
        lv_obj_set_height(label_1, lv_pct(100));
        lv_label_set_text(label_1, "Connected");
        lv_obj_set_style_text_font(label_1, font_inter_semi_bold_14, 0);
        lv_obj_set_style_text_color(label_1, lv_color_hex(0x34C759), 0);
        lv_obj_set_style_text_align(label_1, LV_TEXT_ALIGN_RIGHT, 0);
        lv_label_set_long_mode(label_1, LV_LABEL_LONG_MODE_DOTS);

        lv_obj_t * label_2 = label_create(container_0);
        lv_obj_set_height(label_2, 15);
        lv_label_set_text(label_2, "wifi network name");
        lv_obj_set_style_text_font(label_2, font_inter_semi_bold_14, 0);
        lv_obj_set_style_text_color(label_2, lv_color_hex(0xF3F3F3), 0);
        lv_label_set_long_mode(label_2, LV_LABEL_LONG_MODE_DOTS);

        the_root = card_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

