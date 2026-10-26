/**
 * @file orientation_horizontal_size_xsmall_state_enabled_value_50_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "orientation_horizontal_size_xsmall_state_enabled_value_50_gen.h"
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

lv_obj_t * orientation_horizontal_size_xsmall_state_enabled_value_50_create(lv_obj_t * parent)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if PLURALITY_PIN_CHECK_COMPILE_TARGET(PLURALITY_PIN_TARGET_ALL)
    if (plurality_pin_check_target(PLURALITY_PIN_TARGET_ALL)) {
        lv_obj_t * lv_slider_0 = lv_slider_create(parent);
        lv_obj_set_name_static(lv_slider_0, "orientation_horizontal_size_xsmall_state_enabled_value_50_#");
        lv_obj_set_width(lv_slider_0, 398);
        lv_obj_set_height(lv_slider_0, 6);
        lv_slider_set_min_value(lv_slider_0, 10);
        lv_slider_set_max_value(lv_slider_0, 100);
        lv_slider_bind_value(lv_slider_0, &brightness_percent);
        lv_obj_set_style_bg_color(lv_slider_0, lv_color_hex(0x5A5A5A), 0);
        lv_obj_set_style_bg_opa(lv_slider_0, 255, 0);
        lv_obj_set_style_radius(lv_slider_0, 3, 0);
        lv_obj_set_style_bg_color(lv_slider_0, lv_color_hex(0xFFCC00), LV_PART_INDICATOR);
        lv_obj_set_style_bg_opa(lv_slider_0, 255, LV_PART_INDICATOR);
        lv_obj_set_style_radius(lv_slider_0, 3, LV_PART_INDICATOR);
        lv_obj_set_style_bg_color(lv_slider_0, lv_color_hex(0xFFFFFF), LV_PART_KNOB);
        lv_obj_set_style_bg_opa(lv_slider_0, 255, LV_PART_KNOB);
        lv_obj_set_style_radius(lv_slider_0, 6, LV_PART_KNOB);
        lv_obj_set_style_pad_left(lv_slider_0, 3, LV_PART_KNOB);
        lv_obj_set_style_pad_right(lv_slider_0, 3, LV_PART_KNOB);
        lv_obj_set_style_pad_top(lv_slider_0, 4, LV_PART_KNOB);
        lv_obj_set_style_pad_bottom(lv_slider_0, 4, LV_PART_KNOB);

        the_root = lv_slider_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

