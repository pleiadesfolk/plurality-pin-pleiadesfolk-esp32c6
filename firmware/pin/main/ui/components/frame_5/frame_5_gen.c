/**
 * @file frame_5_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "frame_5_gen.h"
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

lv_obj_t * frame_5_create(lv_obj_t * parent)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if PLURALITY_PIN_CHECK_COMPILE_TARGET(PLURALITY_PIN_TARGET_ALL)
    if (plurality_pin_check_target(PLURALITY_PIN_TARGET_ALL)) {
        lv_obj_t * container_0 = container_create(parent);
        lv_obj_set_name_static(container_0, "frame_5_#");
        lv_obj_set_flex_flow(container_0, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_main_place(container_0, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_cross_place(container_0, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(container_0, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(container_0, 0, 0);
        lv_obj_set_style_pad_row(container_0, -28, 0);
        lv_obj_set_width(container_0, 420);
        lv_obj_set_height(container_0, 240);

        lv_obj_t * container_1 = container_create(container_0);
        lv_obj_set_flex_flow(container_1, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_flex_main_place(container_1, LV_FLEX_ALIGN_SPACE_BETWEEN, 0);
        lv_obj_set_style_flex_cross_place(container_1, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(container_1, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_hor(container_1, 0, 0);
        lv_obj_set_style_pad_ver(container_1, 2, 0);
        lv_obj_set_style_pad_column(container_1, 36, 0);
        lv_obj_set_width(container_1, 396);
        lv_obj_set_height(container_1, LV_SIZE_CONTENT);
        lv_obj_t * label_0 = label_create(container_1);
        lv_obj_set_width(label_0, 180);
        lv_obj_set_height(label_0, 43);
        lv_label_set_text(label_0, "Tuesday");
        lv_obj_set_style_text_font(label_0, font_ibm_plex_mono_regular_26, 0);
        lv_obj_set_style_text_letter_space(label_0, -1, 0);
        lv_obj_set_style_text_color(label_0, lv_color_hex(0x00B42D), 0);
        lv_label_set_long_mode(label_0, LV_LABEL_LONG_MODE_CLIP);

        lv_obj_t * label_1 = label_create(container_1);
        lv_obj_set_width(label_1, 180);
        lv_obj_set_height(label_1, 43);
        lv_label_set_text(label_1, "11/09/26");
        lv_obj_set_style_text_font(label_1, font_ibm_plex_mono_regular_26, 0);
        lv_obj_set_style_text_letter_space(label_1, -1, 0);
        lv_obj_set_style_text_color(label_1, lv_color_hex(0x00B42D), 0);
        lv_obj_set_style_text_align(label_1, LV_TEXT_ALIGN_RIGHT, 0);
        lv_label_set_long_mode(label_1, LV_LABEL_LONG_MODE_CLIP);

        lv_obj_t * label_2 = label_create(container_0);
        lv_obj_set_width(label_2, lv_pct(100));
        lv_obj_set_height(label_2, 208);
        lv_label_set_text(label_2, "12:34");
        lv_obj_set_style_text_font(label_2, font_ibm_plex_mono_semibold_150, 0);
        lv_obj_set_style_text_letter_space(label_2, -8, 0);
        lv_obj_set_style_text_color(label_2, lv_color_hex(0x00B42D), 0);
        lv_obj_set_style_text_align(label_2, LV_TEXT_ALIGN_CENTER, 0);
        lv_label_set_long_mode(label_2, LV_LABEL_LONG_MODE_CLIP);

        the_root = container_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

