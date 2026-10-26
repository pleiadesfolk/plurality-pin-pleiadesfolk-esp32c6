/**
 * @file profile_picture_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "profile_picture_gen.h"
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

lv_obj_t * profile_picture_create(lv_obj_t * parent)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if PLURALITY_PIN_CHECK_COMPILE_TARGET(PLURALITY_PIN_TARGET_ALL)
    if (plurality_pin_check_target(PLURALITY_PIN_TARGET_ALL)) {
        lv_obj_t * container_0 = container_create(parent);
        lv_obj_set_name_static(container_0, "profile_picture_#");
        lv_obj_set_width(container_0, 456);
        lv_obj_set_height(container_0, 280);

        lv_obj_t * image_0 = image_create(container_0);
        lv_obj_set_align(image_0, LV_ALIGN_CENTER);
        lv_obj_set_x(image_0, 175);
        lv_obj_set_y(image_0, 0);
        lv_obj_set_width(image_0, 350);
        lv_obj_set_height(image_0, 350);
        lv_image_set_src(image_0, image_img_02c5506b);
        lv_obj_set_style_radius(image_0, 500, 0);

        the_root = container_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

