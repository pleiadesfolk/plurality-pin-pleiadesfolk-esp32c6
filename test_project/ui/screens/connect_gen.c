/**
 * @file connect_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "connect_gen.h"
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

lv_obj_t * connect_create(void)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if PLURALITY_PIN_CHECK_COMPILE_TARGET(PLURALITY_PIN_TARGET_ALL)
    if (plurality_pin_check_target(PLURALITY_PIN_TARGET_ALL)) {
        lv_obj_t * lv_obj_0 = lv_obj_create(NULL);
        lv_obj_set_name_static(lv_obj_0, "connect_#");
        lv_obj_set_style_bg_color(lv_obj_0, lv_color_hex(0x333333), 0);
        lv_obj_set_flag(lv_obj_0, LV_OBJ_FLAG_SCROLLABLE, false);
        lv_obj_set_style_pad_all(lv_obj_0, 0, 0);

        lv_obj_add_style(lv_obj_0, &style_screen_base_global, 0);
        lv_obj_t * row_0 = row_create(lv_obj_0, 0, 0, 0, 0, 22, 0, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_align(row_0, LV_ALIGN_CENTER);
        lv_obj_set_x(row_0, 0);
        lv_obj_set_y(row_0, 0);
        lv_obj_set_width(row_0, 416);
        lv_obj_set_height(row_0, 250);
        lv_obj_t * qrcode_b_0 = qrcode_b_create(row_0);
        lv_obj_set_width(qrcode_b_0, 170);
        lv_obj_set_height(qrcode_b_0, 170);

        lv_obj_t * scan_for_web_dashboard_access_ensure_that_you_are_connected_to_the_pin_0 = scan_for_web_dashboard_access_ensure_that_you_are_connected_to_the_pin_create(row_0);
        lv_obj_set_width(scan_for_web_dashboard_access_ensure_that_you_are_connected_to_the_pin_0, 224);
        lv_obj_set_height(scan_for_web_dashboard_access_ensure_that_you_are_connected_to_the_pin_0, 250);

        the_root = lv_obj_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

