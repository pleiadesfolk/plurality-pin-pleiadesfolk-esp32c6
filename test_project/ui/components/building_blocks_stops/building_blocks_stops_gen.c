/**
 * @file building_blocks_stops_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "building_blocks_stops_gen.h"
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

lv_obj_t * building_blocks_stops_create(lv_obj_t * parent)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if PLURALITY_PIN_CHECK_COMPILE_TARGET(PLURALITY_PIN_TARGET_ALL)
    if (plurality_pin_check_target(PLURALITY_PIN_TARGET_ALL)) {
        lv_obj_t * row_0 = row_create(parent, 4, 4, 0, 0, 34, 0, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_name_static(row_0, "building_blocks_stops_#");
        lv_obj_set_width(row_0, 354);
        lv_obj_set_height(row_0, LV_SIZE_CONTENT);

        building_blocks_track_stop_create(row_0, false, false, true);

        building_blocks_track_stop_create(row_0, false, false, true);

        building_blocks_track_stop_create(row_0, false, false, true);

        building_blocks_track_stop_create(row_0, false, false, true);

        building_blocks_track_stop_create(row_0, false, false, true);

        building_blocks_track_stop_create(row_0, false, false, true);

        building_blocks_track_stop_create(row_0, false, false, true);

        building_blocks_track_stop_create(row_0, false, false, true);

        building_blocks_track_stop_create(row_0, false, false, true);

        building_blocks_track_stop_create(row_0, false, false, true);

        building_blocks_track_stop_create(row_0, false, false, true);

        the_root = row_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

