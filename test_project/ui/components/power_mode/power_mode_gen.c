/**
 * @file power_mode_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "power_mode_gen.h"
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

lv_obj_t * power_mode_create(lv_obj_t * parent)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if PLURALITY_PIN_CHECK_COMPILE_TARGET(PLURALITY_PIN_TARGET_ALL)
    if (plurality_pin_check_target(PLURALITY_PIN_TARGET_ALL)) {
        lv_obj_t * card_0 = card_create(parent);
        lv_obj_set_name_static(card_0, "power_mode_#");
        lv_obj_set_flex_flow(card_0, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_main_place(card_0, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_cross_place(card_0, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(card_0, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_hor(card_0, 14, 0);
        lv_obj_set_style_pad_ver(card_0, 8, 0);
        lv_obj_set_style_pad_row(card_0, 3, 0);
        lv_obj_set_width(card_0, 121);
        lv_obj_set_height(card_0, 95);
        lv_obj_set_style_bg_color(card_0, lv_color_hex(0x787878), 0);
        lv_obj_set_style_bg_opa(card_0, 10, 0);
        lv_obj_set_style_radius(card_0, 10, 0);

        lv_obj_t * label_0 = label_create(card_0);
        lv_label_set_text(label_0, "Mode");
        lv_obj_set_style_text_font(label_0, font_inter_medium_11, 0);
        lv_obj_set_style_text_color(label_0, lv_color_hex(0x757575), 0);

        lv_obj_t * label_1 = label_create(card_0);
        lv_label_set_text(label_1, "Active");
        lv_obj_set_style_text_font(label_1, font_inter_bold_14, 0);
        lv_obj_set_style_text_color(label_1, lv_color_hex(0x59D173), 0);

        the_root = card_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

