/**
 * @file building_blocks_inactive_track_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "building_blocks_inactive_track_gen.h"
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

lv_obj_t * building_blocks_inactive_track_create(lv_obj_t * parent)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if PLURALITY_PIN_CHECK_COMPILE_TARGET(PLURALITY_PIN_TARGET_ALL)
    if (plurality_pin_check_target(PLURALITY_PIN_TARGET_ALL)) {
        lv_obj_t * row_0 = row_create(parent, 0, 0, 0, 0, 0, 0, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_name_static(row_0, "building_blocks_inactive_track_#");
        lv_obj_set_width(row_0, 354);
        lv_obj_set_height(row_0, 16);

        lv_obj_t * card_0 = card_create(row_0);
        lv_obj_set_width(card_0, 0);
        lv_obj_set_height(card_0, lv_pct(100));
        lv_obj_set_flex_grow(card_0, 1);
        lv_obj_set_style_bg_color(card_0, lv_color_hex(0x5A5A5A), 0);
        lv_obj_set_style_radius(card_0, 2, 0);

        lv_obj_t * building_blocks_track_stop_0 = building_blocks_track_stop_create(row_0, false, false, true);
        lv_obj_set_flag(building_blocks_track_stop_0, LV_OBJ_FLAG_IGNORE_LAYOUT, true);
        lv_obj_set_align(building_blocks_track_stop_0, LV_ALIGN_RIGHT_MID);
        lv_obj_set_x(building_blocks_track_stop_0, -4);
        lv_obj_set_y(building_blocks_track_stop_0, 0);

        the_root = row_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

