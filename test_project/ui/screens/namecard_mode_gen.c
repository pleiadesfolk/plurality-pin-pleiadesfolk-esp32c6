/**
 * @file namecard_mode_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "namecard_mode_gen.h"
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

lv_obj_t * namecard_mode_create(void)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if PLURALITY_PIN_CHECK_COMPILE_TARGET(PLURALITY_PIN_TARGET_ALL)
    if (plurality_pin_check_target(PLURALITY_PIN_TARGET_ALL)) {
        lv_obj_t * lv_obj_0 = lv_obj_create(NULL);
        lv_obj_set_name_static(lv_obj_0, "namecard_mode_#");
        lv_obj_set_style_bg_color(lv_obj_0, lv_color_hex(0x333333), 0);
        lv_obj_set_flag(lv_obj_0, LV_OBJ_FLAG_SCROLLABLE, false);
        lv_obj_set_style_pad_all(lv_obj_0, 0, 0);

        lv_obj_add_style(lv_obj_0, &style_screen_base_global, 0);
        lv_obj_t * panel_0 = panel_create(lv_obj_0);
        lv_obj_set_x(panel_0, 0);
        lv_obj_set_y(panel_0, 0);
        lv_obj_set_width(panel_0, 456);
        lv_obj_set_height(panel_0, 280);
        lv_obj_set_style_bg_color(panel_0, lv_color_hex(0x1F3B5C), 0);
        lv_obj_set_style_bg_grad_color(panel_0, lv_color_hex(0x468DC3), 0);
        lv_obj_set_style_bg_grad_dir(panel_0, LV_GRAD_DIR_HOR, 0);

        lv_obj_t * container_0 = container_create(lv_obj_0);
        lv_obj_set_x(container_0, 20);
        lv_obj_set_y(container_0, 11);
        lv_obj_set_width(container_0, 416);
        lv_obj_set_height(container_0, 260);
        lv_obj_t * label_0 = label_create(container_0);
        lv_obj_set_align(label_0, LV_ALIGN_LEFT_MID);
        lv_obj_set_x(label_0, 0);
        lv_obj_set_y(label_0, -10);
        lv_obj_set_width(label_0, 416);
        lv_obj_set_height(label_0, LV_SIZE_CONTENT);
        lv_label_set_text(label_0, "Helvetica Ellis of the Pleiadesfolk");
        lv_obj_set_style_text_font(label_0, font_playwrite_us_trad_regular_52, 0);
        lv_obj_set_style_text_line_space(label_0, -30, 0);
        lv_obj_set_style_text_color(label_0, lv_color_hex(0xFFFFFF), 0);
        lv_obj_set_style_text_align(label_0, LV_TEXT_ALIGN_LEFT, 0);
        lv_label_set_long_mode(label_0, LV_LABEL_LONG_MODE_WRAP);

        the_root = lv_obj_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

