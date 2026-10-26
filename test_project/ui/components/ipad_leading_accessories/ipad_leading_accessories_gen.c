/**
 * @file ipad_leading_accessories_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "ipad_leading_accessories_gen.h"
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

lv_obj_t * ipad_leading_accessories_create(lv_obj_t * parent)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if PLURALITY_PIN_CHECK_COMPILE_TARGET(PLURALITY_PIN_TARGET_ALL)
    if (plurality_pin_check_target(PLURALITY_PIN_TARGET_ALL)) {
        lv_obj_t * row_0 = row_create(parent, 0, 0, 0, 0, 8, 0, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_name_static(row_0, "ipad_leading_accessories_#");
        lv_obj_set_width(row_0, 132);
        lv_obj_set_height(row_0, LV_SIZE_CONTENT);

        lv_obj_t * row_1 = row_create(row_0, 0, 0, 0, 0, 2, 0, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_width(row_1, LV_SIZE_CONTENT);
        lv_obj_set_height(row_1, LV_SIZE_CONTENT);
        lv_obj_t * label_0 = label_create(row_1);
        lv_label_set_text(label_0, "9:41");
        lv_obj_set_style_text_color(label_0, lv_color_hex(0x000000), 0);

        lv_obj_t * label_1 = label_create(row_1);
        lv_label_set_text(label_1, "AM");
        lv_obj_set_style_text_color(label_1, lv_color_hex(0x000000), 0);

        lv_obj_t * label_2 = label_create(row_0);
        lv_label_set_text(label_2, "Wed Apr 1");
        lv_obj_set_style_text_color(label_2, lv_color_hex(0x000000), 0);

        the_root = row_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

