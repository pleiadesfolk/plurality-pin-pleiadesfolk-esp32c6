/**
 * @file watch_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "watch_gen.h"
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

lv_obj_t * watch_create(void)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if PLURALITY_PIN_CHECK_COMPILE_TARGET(PLURALITY_PIN_TARGET_ALL)
    if (plurality_pin_check_target(PLURALITY_PIN_TARGET_ALL)) {
        lv_obj_t * lv_obj_0 = lv_obj_create(NULL);
        lv_obj_set_name_static(lv_obj_0, "watch_#");
        lv_obj_set_style_bg_color(lv_obj_0, lv_color_hex(0x333333), 0);
        lv_obj_set_flag(lv_obj_0, LV_OBJ_FLAG_SCROLLABLE, false);
        lv_obj_set_style_pad_all(lv_obj_0, 0, 0);

        lv_obj_add_style(lv_obj_0, &style_screen_base_global, 0);
        lv_obj_t * column_0 = column_create(lv_obj_0, 0, 0, 0, 0, -28, 0, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_align(column_0, LV_ALIGN_CENTER);
        lv_obj_set_x(column_0, 0);
        lv_obj_set_y(column_0, 0);
        lv_obj_set_width(column_0, 420);
        lv_obj_set_height(column_0, 240);
        lv_obj_t * row_0 = row_create(column_0, 0, 0, 2, -5, 36, 0, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_width(row_0, 396);
        lv_obj_set_height(row_0, LV_SIZE_CONTENT);
        lv_obj_t * label_0 = label_create(row_0);
        lv_obj_set_width(label_0, 180);
        lv_obj_set_height(label_0, 40);
        lv_label_set_text(label_0, "Tuesday");
        lv_obj_set_style_text_font(label_0, font_ibm_plex_mono_regular_26, 0);
        lv_obj_set_style_text_letter_space(label_0, -1, 0);
        lv_obj_set_style_text_color(label_0, lv_color_hex(0x00B42D), 0);
        lv_label_set_long_mode(label_0, LV_LABEL_LONG_MODE_CLIP);

        lv_obj_t * label_1 = label_create(row_0);
        lv_obj_set_width(label_1, 180);
        lv_obj_set_height(label_1, 40);
        lv_label_set_text(label_1, "11/09/26");
        lv_obj_set_style_text_font(label_1, font_ibm_plex_mono_regular_26, 0);
        lv_obj_set_style_text_letter_space(label_1, -1, 0);
        lv_obj_set_style_text_color(label_1, lv_color_hex(0x00B42D), 0);
        lv_obj_set_style_text_align(label_1, LV_TEXT_ALIGN_RIGHT, 0);
        lv_label_set_long_mode(label_1, LV_LABEL_LONG_MODE_CLIP);

        lv_obj_t * label_2 = label_create(column_0);
        lv_obj_set_width(label_2, 420);
        lv_obj_set_height(label_2, 178);
        lv_label_set_text(label_2, "12:34");
        lv_obj_set_style_text_font(label_2, font_ibm_plex_mono_semibold_150, 0);
        lv_obj_set_style_text_color(label_2, lv_color_hex(0x00B42D), 0);
        lv_obj_set_style_text_letter_space(label_2, -8, 0);
        lv_obj_set_style_text_align(label_2, LV_TEXT_ALIGN_CENTER, 0);
        lv_label_set_long_mode(label_2, LV_LABEL_LONG_MODE_CLIP);

        the_root = lv_obj_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

