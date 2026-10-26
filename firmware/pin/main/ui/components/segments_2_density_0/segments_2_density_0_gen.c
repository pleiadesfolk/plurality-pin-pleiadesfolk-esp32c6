/**
 * @file segments_2_density_0_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "segments_2_density_0_gen.h"
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

lv_obj_t * segments_2_density_0_create(lv_obj_t * parent)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if PLURALITY_PIN_CHECK_COMPILE_TARGET(PLURALITY_PIN_TARGET_ALL)
    if (plurality_pin_check_target(PLURALITY_PIN_TARGET_ALL)) {
        lv_obj_t * row_0 = row_create(parent, 0, 0, 0, 0, -1, 0, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_name_static(row_0, "segments_2_density_0_#");
        lv_obj_set_width(row_0, 207);
        lv_obj_set_height(row_0, 48);

        lv_obj_t * configuration_label_only_state_enabled_selected_true_0 = configuration_label_only_state_enabled_selected_true_create(row_0);
        lv_obj_set_width(configuration_label_only_state_enabled_selected_true_0, 0);
        lv_obj_set_flex_grow(configuration_label_only_state_enabled_selected_true_0, 1);

        lv_obj_t * configuration_label_only_state_enabled_selected_false_0 = configuration_label_only_state_enabled_selected_false_create(row_0);
        lv_obj_set_width(configuration_label_only_state_enabled_selected_false_0, 0);
        lv_obj_set_flex_grow(configuration_label_only_state_enabled_selected_false_0, 1);

        the_root = row_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

