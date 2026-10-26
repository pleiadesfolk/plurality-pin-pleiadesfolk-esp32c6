/**
 * @file bluetooth_card_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "bluetooth_card_gen.h"
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

lv_obj_t * bluetooth_card_create(lv_obj_t * parent)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if PLURALITY_PIN_CHECK_COMPILE_TARGET(PLURALITY_PIN_TARGET_ALL)
    if (plurality_pin_check_target(PLURALITY_PIN_TARGET_ALL)) {
        lv_obj_t * card_0 = card_create(parent);
        lv_obj_set_name_static(card_0, "bluetooth_card_#");
        lv_obj_set_flex_flow(card_0, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_flex_main_place(card_0, LV_FLEX_ALIGN_SPACE_BETWEEN, 0);
        lv_obj_set_style_flex_cross_place(card_0, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(card_0, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(card_0, 8, 0);
        lv_obj_set_style_pad_column(card_0, 0, 0);
        lv_obj_set_width(card_0, 50);
        lv_obj_set_height(card_0, 80);
        lv_obj_set_style_bg_color(card_0, lv_color_hex(0x787878), 0);
        lv_obj_set_style_bg_opa(card_0, 10, 0);
        lv_obj_set_style_radius(card_0, 12, 0);

        lv_obj_t * container_0 = container_create(card_0);
        lv_obj_set_flex_flow(container_0, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_flex_cross_place(container_0, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(container_0, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(container_0, 0, 0);
        lv_obj_set_style_pad_column(container_0, 6, 0);
        lv_obj_set_width(container_0, 14);
        lv_obj_set_height(container_0, 17);
        lv_obj_t * container_1 = container_create(container_0);
        lv_obj_set_flex_flow(container_1, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_main_place(container_1, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_cross_place(container_1, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(container_1, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(container_1, 0, 0);
        lv_obj_set_style_pad_row(container_1, 0, 0);
        lv_obj_set_width(container_1, 14);
        lv_obj_set_height(container_1, 23);
        lv_obj_t * image_0 = image_create(container_1);
        lv_obj_set_width(image_0, 20);
        lv_obj_set_height(image_0, 19);
        lv_image_set_src(image_0, image_vec_12_212);
        lv_obj_set_flag(image_0, LV_OBJ_FLAG_SCROLLABLE, false);

        lv_obj_t * card_1 = card_create(card_0);
        lv_obj_set_width(card_1, 6);
        lv_obj_set_height(card_1, 6);
        lv_obj_set_style_bg_color(card_1, lv_color_hex(0x59D173), 0);
        lv_obj_set_style_radius(card_1, 32767, 0);

        the_root = card_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

