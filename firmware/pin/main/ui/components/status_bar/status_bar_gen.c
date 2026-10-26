/**
 * @file status_bar_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "status_bar_gen.h"
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

lv_obj_t * status_bar_create(lv_obj_t * parent)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if PLURALITY_PIN_CHECK_COMPILE_TARGET(PLURALITY_PIN_TARGET_ALL)
    if (plurality_pin_check_target(PLURALITY_PIN_TARGET_ALL)) {
        lv_obj_t * row_0 = row_create(parent, 0, 0, 15, 16, 56, 0, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_name_static(row_0, "status_bar_#");
        lv_obj_set_width(row_0, lv_pct(100));
        lv_obj_set_height(row_0, 31);

        lv_obj_t * row_1 = row_create(row_0, 0, 0, 0, 0, 9, 0, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_width(row_1, 153);
        lv_obj_set_height(row_1, 25);
        lv_obj_t * image_0 = image_create(row_1);
        lv_obj_set_width(image_0, 24);
        lv_obj_set_height(image_0, 17);
        lv_image_set_src(image_0, image_vec_42_2416);
        lv_obj_set_flag(image_0, LV_OBJ_FLAG_SCROLLABLE, false);

        lv_obj_t * label_0 = label_create(row_1);
        lv_label_set_text(label_0, "100%");
        lv_obj_set_style_text_font(label_0, font_inter_medium_24_manual, 0);
        lv_obj_set_style_text_color(label_0, lv_color_hex(0xF2F2F7), 0);
        lv_obj_set_style_text_align(label_0, LV_TEXT_ALIGN_RIGHT, 0);

        lv_obj_t * image_1 = image_create(row_1);
        lv_obj_set_width(image_1, 48);
        lv_obj_set_height(image_1, 23);
        lv_image_set_src(image_1, image_vec_42_2418);

        lv_obj_t * row_2 = row_create(row_0, 0, 0, 0, 0, 14, 0, LV_FLEX_ALIGN_END, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_width(row_2, 231);
        lv_obj_set_height(row_2, 28);
        lv_obj_t * row_3 = row_create(row_2, 0, 0, 0, 0, 3, 0, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_width(row_3, LV_SIZE_CONTENT);
        lv_obj_set_height(row_3, LV_SIZE_CONTENT);
        lv_obj_t * label_1 = label_create(row_3);
        lv_label_set_text(label_1, "9:41");
        lv_obj_set_style_text_font(label_1, font_inter_medium_24_manual, 0);
        lv_obj_set_style_text_color(label_1, lv_color_hex(0xE5E5EA), 0);

        lv_obj_t * label_2 = label_create(row_3);
        lv_label_set_text(label_2, "AM");
        lv_obj_set_style_text_font(label_2, font_inter_medium_24_manual, 0);
        lv_obj_set_style_text_color(label_2, lv_color_hex(0xE5E5EA), 0);

        lv_obj_t * label_3 = label_create(row_2);
        lv_label_set_text(label_3, "Wed Apr 1");
        lv_obj_set_style_text_font(label_3, font_inter_medium_24_manual, 0);
        lv_obj_set_style_text_color(label_3, lv_color_hex(0xF2F2F7), 0);

        the_root = row_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

