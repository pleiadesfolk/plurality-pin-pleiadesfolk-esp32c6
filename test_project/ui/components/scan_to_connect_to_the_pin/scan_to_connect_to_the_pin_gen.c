/**
 * @file scan_to_connect_to_the_pin_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "scan_to_connect_to_the_pin_gen.h"
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

lv_obj_t * scan_to_connect_to_the_pin_create(lv_obj_t * parent)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if PLURALITY_PIN_CHECK_COMPILE_TARGET(PLURALITY_PIN_TARGET_ALL)
    if (plurality_pin_check_target(PLURALITY_PIN_TARGET_ALL)) {
        lv_obj_t * container_0 = container_create(parent);
        lv_obj_set_name_static(container_0, "scan_to_connect_to_the_pin_#");
        lv_obj_set_width(container_0, 224);
        lv_obj_set_height(container_0, 250);

        lv_obj_t * label_0 = label_create(container_0);
        lv_obj_set_x(label_0, 0);
        lv_obj_set_y(label_0, 0);
        lv_obj_set_width(label_0, 224);
        lv_obj_set_height(label_0, 250);
        lv_label_set_text(label_0, "Scan to connect to the pin");
        lv_obj_set_style_text_font(label_0, font_ibm_plex_mono_regular_36, 0);
        lv_obj_set_style_text_letter_space(label_0, 0, 0);
        lv_obj_set_style_text_color(label_0, lv_color_hex(0xFFFFFF), 0);
        lv_label_set_long_mode(label_0, LV_LABEL_LONG_MODE_CLIP);

        the_root = container_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

