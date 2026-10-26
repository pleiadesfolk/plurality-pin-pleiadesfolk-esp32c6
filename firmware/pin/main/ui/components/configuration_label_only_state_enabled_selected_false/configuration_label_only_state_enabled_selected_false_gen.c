/**
 * @file configuration_label_only_state_enabled_selected_false_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "configuration_label_only_state_enabled_selected_false_gen.h"
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

lv_obj_t * configuration_label_only_state_enabled_selected_false_create(lv_obj_t * parent)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if PLURALITY_PIN_CHECK_COMPILE_TARGET(PLURALITY_PIN_TARGET_ALL)
    if (plurality_pin_check_target(PLURALITY_PIN_TARGET_ALL)) {
        lv_obj_t * container_0 = container_create(parent);
        lv_obj_set_name_static(container_0, "configuration_label_only_state_enabled_selected_false_#");
        lv_obj_set_flex_flow(container_0, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_flex_main_place(container_0, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_cross_place(container_0, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(container_0, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_hor(container_0, 0, 0);
        lv_obj_set_style_pad_ver(container_0, 4, 0);
        lv_obj_set_style_pad_column(container_0, 0, 0);
        lv_obj_set_width(container_0, 108);
        lv_obj_set_height(container_0, 48);

        lv_obj_t * container_1 = container_create(container_0);
        lv_obj_set_flex_flow(container_1, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_main_place(container_1, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_cross_place(container_1, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(container_1, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(container_1, 0, 0);
        lv_obj_set_style_pad_row(container_1, 10, 0);
        lv_obj_set_width(container_1, 0);
        lv_obj_set_height(container_1, lv_pct(100));
        lv_obj_set_flex_grow(container_1, 1);
        lv_obj_set_style_border_color(container_1, lv_color_hex(0x79747E), 0);
        lv_obj_set_style_border_width(container_1, 1, 0);
        lv_obj_set_style_clip_corner(container_1, true, 0);
        lv_obj_t * row_0 = row_create(container_1, 12, 12, 10, 10, 8, 1, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_width(row_0, lv_pct(100));
        lv_obj_set_height(row_0, 0);
        lv_obj_t * label_0 = label_create(row_0);
        lv_label_set_text(label_0, "Label");
        lv_obj_set_style_text_font(label_0, font_roboto_medium_14, 0);
        lv_obj_set_style_text_letter_space(label_0, 0, 0);
        lv_obj_set_style_text_color(label_0, lv_color_hex(0x1D1B20), 0);
        lv_obj_set_style_text_align(label_0, LV_TEXT_ALIGN_CENTER, 0);

        the_root = container_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

