/**
 * @file settings_c_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "settings_c_gen.h"
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

lv_obj_t * settings_c_create(lv_obj_t * parent)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if PLURALITY_PIN_CHECK_COMPILE_TARGET(PLURALITY_PIN_TARGET_ALL)
    if (plurality_pin_check_target(PLURALITY_PIN_TARGET_ALL)) {
        lv_obj_t * row_0 = row_create(parent, 0, 0, 0, 0, 0, 0, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
        lv_obj_set_name_static(row_0, "settings_c_#");
        lv_obj_set_width(row_0, 44);
        lv_obj_set_height(row_0, LV_SIZE_CONTENT);

        lv_obj_t * type_round_size_small_state_enabled_selected_false_0 = type_round_size_small_state_enabled_selected_false_create(row_0);
        lv_obj_set_width(type_round_size_small_state_enabled_selected_false_0, 143);
        lv_obj_set_height(type_round_size_small_state_enabled_selected_false_0, 44);

        the_root = row_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

