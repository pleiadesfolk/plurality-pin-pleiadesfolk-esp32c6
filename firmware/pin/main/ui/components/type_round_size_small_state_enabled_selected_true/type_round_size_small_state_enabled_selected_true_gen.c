/**
 * @file type_round_size_small_state_enabled_selected_true_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "type_round_size_small_state_enabled_selected_true_gen.h"
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

lv_obj_t * type_round_size_small_state_enabled_selected_true_create(lv_obj_t * parent)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if PLURALITY_PIN_CHECK_COMPILE_TARGET(PLURALITY_PIN_TARGET_ALL)
    if (plurality_pin_check_target(PLURALITY_PIN_TARGET_ALL)) {
        lv_obj_t * container_0 = container_create(parent);
        lv_obj_set_name_static(container_0, "type_round_size_small_state_enabled_selected_true_#");
        lv_obj_set_flex_flow(container_0, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_flex_main_place(container_0, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_cross_place(container_0, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(container_0, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(container_0, 0, 0);
        lv_obj_set_style_pad_column(container_0, 0, 0);
        lv_obj_set_width(container_0, LV_SIZE_CONTENT);
        lv_obj_set_height(container_0, 48);

        lv_obj_t * card_0 = card_create(container_0);
        lv_obj_set_flex_flow(card_0, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_main_place(card_0, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_cross_place(card_0, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(card_0, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(card_0, 0, 0);
        lv_obj_set_style_pad_row(card_0, 0, 0);
        lv_obj_set_width(card_0, LV_SIZE_CONTENT);
        lv_obj_set_height(card_0, LV_SIZE_CONTENT);
        lv_obj_set_style_bg_color(card_0, lv_color_hex(0x6750A4), 0);
        lv_obj_set_style_radius(card_0, 12, 0);
        lv_obj_t * row_0 = row_create(card_0, 16, 16, 10, 10, 8, 0, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_width(row_0, LV_SIZE_CONTENT);
        lv_obj_set_height(row_0, LV_SIZE_CONTENT);
        lv_obj_t * stars_filled_0 = stars_filled_create(row_0);
        lv_obj_set_width(stars_filled_0, 20);
        lv_obj_set_height(stars_filled_0, 20);

        lv_obj_t * label_0 = label_create(row_0);
        lv_label_set_text(label_0, "Label");
        lv_obj_set_style_text_font(label_0, font_roboto_medium_14, 0);
        lv_obj_set_style_text_letter_space(label_0, 0, 0);
        lv_obj_set_style_text_color(label_0, lv_color_hex(0xFFFFFF), 0);

        the_root = container_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

