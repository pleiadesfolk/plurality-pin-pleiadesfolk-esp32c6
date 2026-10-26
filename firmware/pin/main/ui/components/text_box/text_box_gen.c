/**
 * @file text_box_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "text_box_gen.h"
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

lv_obj_t * text_box_create(lv_obj_t * parent)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if PLURALITY_PIN_CHECK_COMPILE_TARGET(PLURALITY_PIN_TARGET_ALL)
    if (plurality_pin_check_target(PLURALITY_PIN_TARGET_ALL)) {
        lv_obj_t * container_0 = container_create(parent);
        lv_obj_set_name_static(container_0, "text_box_#");
        lv_obj_set_flex_flow(container_0, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_main_place(container_0, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_cross_place(container_0, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(container_0, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(container_0, 0, 0);
        lv_obj_set_style_pad_row(container_0, 10, 0);
        lv_obj_set_width(container_0, 202);
        lv_obj_set_height(container_0, 256);

        lv_obj_t * label_0 = label_create(container_0);
        lv_obj_set_width(label_0, lv_pct(100));
        lv_obj_set_height(label_0, 0);
        lv_obj_set_flex_grow(label_0, 1);
        lv_label_set_text(label_0, "Meredith\nEllis");
        lv_obj_set_style_text_font(label_0, font_playwrite_us_trad_regular_40, 0);
        lv_obj_set_style_text_line_space(label_0, 18, 0);
        lv_obj_set_style_text_color(label_0, lv_color_hex(0xFFFFFF), 0);
        lv_obj_set_style_text_align(label_0, LV_TEXT_ALIGN_CENTER, 0);
        lv_label_set_long_mode(label_0, LV_LABEL_LONG_MODE_CLIP);

        the_root = container_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

