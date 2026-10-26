/**
 * @file ellipse_2_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "ellipse_2_gen.h"
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

lv_obj_t * ellipse_2_create(lv_obj_t * parent)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if PLURALITY_PIN_CHECK_COMPILE_TARGET(PLURALITY_PIN_TARGET_ALL)
    if (plurality_pin_check_target(PLURALITY_PIN_TARGET_ALL)) {
        lv_obj_t * container_0 = container_create(parent);
        lv_obj_set_name_static(container_0, "ellipse_2_#");
        lv_obj_set_width(container_0, 600);
        lv_obj_set_height(container_0, 600);

        lv_obj_t * card_0 = card_create(container_0);
        lv_obj_set_x(card_0, -68);
        lv_obj_set_y(card_0, 562);
        lv_obj_set_width(card_0, 737);
        lv_obj_set_height(card_0, 737);
        lv_obj_set_style_bg_color(card_0, lv_color_hex(0x1E1E1E), 0);
        lv_obj_set_style_transform_rotation(card_0, -900, 0);
        lv_obj_set_style_transform_pivot_x(card_0, 369, 0);
        lv_obj_set_style_transform_pivot_y(card_0, 369, 0);
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

