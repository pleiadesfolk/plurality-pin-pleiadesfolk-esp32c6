/**
 * @file mode_light_context_content_area_state_idle_type_tick_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "mode_light_context_content_area_state_idle_type_tick_gen.h"
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

lv_obj_t * mode_light_context_content_area_state_idle_type_tick_create(lv_obj_t * parent)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if PLURALITY_PIN_CHECK_COMPILE_TARGET(PLURALITY_PIN_TARGET_ALL)
    if (plurality_pin_check_target(PLURALITY_PIN_TARGET_ALL)) {
        lv_obj_t * panel_0 = panel_create(parent);
        lv_obj_set_name_static(panel_0, "mode_light_context_content_area_state_idle_type_tick_#");
        lv_obj_set_width(panel_0, 20);
        lv_obj_set_height(panel_0, 20);
        lv_obj_set_style_bg_color(panel_0, lv_color_hex(0x000000), 0);
        lv_obj_set_style_bg_opa(panel_0, 184, 0);
        lv_obj_set_style_opa(panel_0, 64, 0);

        the_root = panel_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

