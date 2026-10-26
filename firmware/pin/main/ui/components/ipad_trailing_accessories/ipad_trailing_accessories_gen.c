/**
 * @file ipad_trailing_accessories_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "ipad_trailing_accessories_gen.h"
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

lv_obj_t * ipad_trailing_accessories_create(lv_obj_t * parent)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if PLURALITY_PIN_CHECK_COMPILE_TARGET(PLURALITY_PIN_TARGET_ALL)
    if (plurality_pin_check_target(PLURALITY_PIN_TARGET_ALL)) {
        lv_obj_t * row_0 = row_create(parent, 0, 0, 0, 0, 5, 0, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_name_static(row_0, "ipad_trailing_accessories_#");
        lv_obj_set_width(row_0, LV_SIZE_CONTENT);
        lv_obj_set_height(row_0, LV_SIZE_CONTENT);

        lv_obj_t * image_0 = image_create(row_0);
        lv_obj_set_width(image_0, 14);
        lv_obj_set_height(image_0, 10);
        lv_image_set_src(image_0, image_vec_7_1491);
        lv_obj_set_flag(image_0, LV_OBJ_FLAG_SCROLLABLE, false);

        lv_obj_t * label_0 = label_create(row_0);
        lv_label_set_text(label_0, "100%");
        lv_obj_set_style_text_color(label_0, lv_color_hex(0x000000), 0);
        lv_obj_set_style_text_align(label_0, LV_TEXT_ALIGN_RIGHT, 0);

        lv_obj_t * image_1 = image_create(row_0);
        lv_obj_set_width(image_1, 27);
        lv_obj_set_height(image_1, 13);
        lv_image_set_src(image_1, image_vec_7_1493);

        the_root = row_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

