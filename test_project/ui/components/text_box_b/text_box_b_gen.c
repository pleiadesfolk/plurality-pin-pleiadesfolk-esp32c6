/**
 * @file text_box_b_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "text_box_b_gen.h"
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

lv_obj_t * text_box_b_create(lv_obj_t * parent)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if PLURALITY_PIN_CHECK_COMPILE_TARGET(PLURALITY_PIN_TARGET_ALL)
    if (plurality_pin_check_target(PLURALITY_PIN_TARGET_ALL)) {
        lv_obj_t * container_0 = container_create(parent);
        lv_obj_set_name_static(container_0, "text_box_b_#");
        lv_obj_set_width(container_0, 416);
        lv_obj_set_height(container_0, 260);

        lv_obj_t * label_0 = label_create(container_0);
        lv_obj_set_align(label_0, LV_ALIGN_CENTER);
        lv_obj_set_x(label_0, 0);
        lv_obj_set_y(label_0, 0);
        lv_obj_set_width(label_0, 416);
        lv_obj_set_height(label_0, 260);
        lv_label_set_text(label_0, "Helvetica Ellis\nof the Pleiadesfolk");
        lv_obj_set_style_text_font(label_0, font_playwrite_us_trad_regular_52, 0);
        lv_obj_set_style_text_line_space(label_0, 9, 0);
        lv_obj_set_style_text_color(label_0, lv_color_hex(0xFFFFFF), 0);
        lv_label_set_long_mode(label_0, LV_LABEL_LONG_MODE_CLIP);

        lv_obj_t * panel_0 = panel_create(container_0);
        lv_obj_set_x(panel_0, -18);
        lv_obj_set_y(panel_0, -42);
        lv_obj_set_width(panel_0, 479);
        lv_obj_set_height(panel_0, 316);
        lv_obj_set_style_bg_color(panel_0, lv_color_hex(0xFFFFFF), 0);
        lv_obj_set_style_bg_grad_color(panel_0, lv_color_hex(0x468DC3), 0);
        lv_obj_set_style_bg_grad_dir(panel_0, LV_GRAD_DIR_HOR, 0);

        the_root = container_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

