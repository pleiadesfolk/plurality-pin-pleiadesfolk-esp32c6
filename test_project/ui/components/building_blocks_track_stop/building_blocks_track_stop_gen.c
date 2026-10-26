/**
 * @file building_blocks_track_stop_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "building_blocks_track_stop_gen.h"
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

lv_obj_t * building_blocks_track_stop_create(lv_obj_t * parent, bool show_stops, bool show_icon, bool show_value_indicator)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if PLURALITY_PIN_CHECK_COMPILE_TARGET(PLURALITY_PIN_TARGET_ALL)
    if (plurality_pin_check_target(PLURALITY_PIN_TARGET_ALL)) {
        lv_obj_t * container_0 = container_create(parent);
        lv_obj_set_name_static(container_0, "building_blocks_track_stop_#");
        lv_obj_set_width(container_0, 4);
        lv_obj_set_height(container_0, 4);

        lv_obj_t * card_0 = card_create(container_0);
        lv_obj_set_x(card_0, 0);
        lv_obj_set_y(card_0, 0);
        lv_obj_set_width(card_0, 4);
        lv_obj_set_height(card_0, 4);
        lv_obj_set_style_bg_color(card_0, lv_color_hex(0x6750A4), 0);
        lv_obj_set_style_radius(card_0, 32767, 0);

        the_root = container_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

