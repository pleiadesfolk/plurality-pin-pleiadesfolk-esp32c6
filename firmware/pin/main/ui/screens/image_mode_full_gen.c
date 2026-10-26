/**
 * @file image_mode_full_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "image_mode_full_gen.h"
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

lv_obj_t * image_mode_full_create(void)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if PLURALITY_PIN_CHECK_COMPILE_TARGET(PLURALITY_PIN_TARGET_ALL)
    if (plurality_pin_check_target(PLURALITY_PIN_TARGET_ALL)) {
        lv_obj_t * lv_obj_0 = lv_obj_create(NULL);
        lv_obj_set_name_static(lv_obj_0, "image_mode_full_#");
        lv_obj_set_style_bg_color(lv_obj_0, lv_color_hex(0xFFFFFF), 0);
        lv_obj_set_flag(lv_obj_0, LV_OBJ_FLAG_SCROLLABLE, false);
        lv_obj_set_style_pad_all(lv_obj_0, 0, 0);

        lv_obj_add_style(lv_obj_0, &style_screen_base_global, 0);
        lv_obj_t * container_0 = container_create(lv_obj_0);
        lv_obj_set_x(container_0, 0);
        lv_obj_set_y(container_0, 0);
        lv_obj_set_width(container_0, 456);
        lv_obj_set_height(container_0, 280);
        lv_obj_t * panel_0 = panel_create(container_0);
        lv_obj_set_x(panel_0, 0);
        lv_obj_set_y(panel_0, 280);
        lv_obj_set_width(panel_0, 280);
        lv_obj_set_height(panel_0, 456);
        lv_obj_set_style_bg_color(panel_0, lv_color_hex(0xFFFFFF), 0);
        lv_obj_set_style_bg_opa(panel_0, 0, 0);
        lv_obj_set_style_transform_rotation(panel_0, -900, 0);
        lv_obj_set_style_transform_pivot_x(panel_0, 140, 0);
        lv_obj_set_style_transform_pivot_y(panel_0, 228, 0);

        lv_obj_t * image_0 = image_create(container_0);
        lv_obj_set_align(image_0, LV_ALIGN_CENTER);
        lv_obj_set_x(image_0, 0);
        lv_obj_set_y(image_0, 0);
        lv_obj_set_width(image_0, 280);
        lv_obj_set_height(image_0, 280);
        lv_image_set_src(image_0, image_img_45c6bb3a);

        the_root = lv_obj_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

