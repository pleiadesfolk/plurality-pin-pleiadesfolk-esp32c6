/**
 * @file brightness_card_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "brightness_card_gen.h"
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

lv_obj_t * brightness_card_create(lv_obj_t * parent)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if PLURALITY_PIN_CHECK_COMPILE_TARGET(PLURALITY_PIN_TARGET_ALL)
    if (plurality_pin_check_target(PLURALITY_PIN_TARGET_ALL)) {
        lv_obj_t * card_0 = card_create(parent);
        lv_obj_set_name_static(card_0, "brightness_card_#");
        lv_obj_set_flex_flow(card_0, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_pad_all(card_0, 8, 0);
        lv_obj_set_style_pad_row(card_0, 6, 0);
        lv_obj_set_width(card_0, 414);
        lv_obj_set_height(card_0, lv_pct(100));
        lv_obj_set_style_bg_color(card_0, lv_color_hex(0x787878), 0);
        lv_obj_set_style_bg_opa(card_0, 10, 0);
        lv_obj_set_style_radius(card_0, 12, 0);

        lv_obj_t * container_0 = container_create(card_0);
        lv_obj_set_flex_flow(container_0, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_flex_main_place(container_0, LV_FLEX_ALIGN_SPACE_BETWEEN, 0);
        lv_obj_set_style_flex_cross_place(container_0, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(container_0, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(container_0, 0, 0);
        lv_obj_set_style_pad_column(container_0, 0, 0);
        lv_obj_set_width(container_0, lv_pct(100));
        lv_obj_set_height(container_0, 36);
        lv_obj_t * container_1 = container_create(container_0);
        lv_obj_set_flex_flow(container_1, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_flex_cross_place(container_1, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(container_1, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(container_1, 0, 0);
        lv_obj_set_style_pad_column(container_1, 6, 0);
        lv_obj_set_width(container_1, LV_SIZE_CONTENT);
        lv_obj_set_height(container_1, LV_SIZE_CONTENT);
        lv_obj_t * container_2 = container_create(container_1);
        lv_obj_set_flex_flow(container_2, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_main_place(container_2, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_cross_place(container_2, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(container_2, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(container_2, 0, 0);
        lv_obj_set_style_pad_row(container_2, 0, 0);
        lv_obj_set_width(container_2, 14);
        lv_obj_set_height(container_2, 14);
        lv_obj_t * image_0 = image_create(container_2);
        lv_obj_set_width(image_0, 14);
        lv_obj_set_height(image_0, 14);
        lv_image_set_src(image_0, image_vec_7_1590);
        lv_obj_set_flag(image_0, LV_OBJ_FLAG_SCROLLABLE, false);

        lv_obj_t * label_0 = label_create(container_1);
        lv_label_set_text(label_0, "Brightness");
        lv_obj_set_style_text_font(label_0, font_inter_semi_bold_13, 0);
        lv_obj_set_style_text_color(label_0, lv_color_hex(0xFFFFFF), 0);

        lv_obj_t * label_1 = label_create(container_0);
        lv_label_set_text(label_1, "50%");
        lv_obj_set_style_text_font(label_1, font_inter_semi_bold_13, 0);
        lv_obj_set_style_text_color(label_1, lv_color_hex(0xFFFFFF), 0);

        lv_obj_t * container_3 = container_create(card_0);
        lv_obj_set_width(container_3, lv_pct(100));
        lv_obj_set_height(container_3, 22);
        lv_obj_t * container_4 = container_create(container_3);
        lv_obj_set_x(container_4, 0);
        lv_obj_set_y(container_4, 8);
        lv_obj_set_width(container_4, 398);
        lv_obj_set_height(container_4, 6);
        lv_obj_t * container_5 = container_create(container_4);
        lv_obj_set_flex_flow(container_5, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_flex_main_place(container_5, LV_FLEX_ALIGN_SPACE_BETWEEN, 0);
        lv_obj_set_style_pad_top(container_5, 2, 0);
        lv_obj_set_style_pad_bottom(container_5, 0, 0);
        lv_obj_set_style_pad_hor(container_5, 2, 0);
        lv_obj_set_style_pad_column(container_5, 0, 0);
        lv_obj_set_x(container_5, -3);
        lv_obj_set_y(container_5, 7);
        lv_obj_set_width(container_5, 404);
        lv_obj_set_height(container_5, 6);
        lv_obj_t * mode_light_context_content_area_state_idle_type_tick_0 = mode_light_context_content_area_state_idle_type_tick_create(container_5);
        lv_obj_set_width(mode_light_context_content_area_state_idle_type_tick_0, 2);
        lv_obj_set_height(mode_light_context_content_area_state_idle_type_tick_0, 2);

        lv_obj_t * mode_light_context_content_area_state_idle_type_tick_1 = mode_light_context_content_area_state_idle_type_tick_create(container_5);
        lv_obj_set_width(mode_light_context_content_area_state_idle_type_tick_1, 2);
        lv_obj_set_height(mode_light_context_content_area_state_idle_type_tick_1, 2);

        lv_obj_t * mode_light_context_content_area_state_idle_type_tick_2 = mode_light_context_content_area_state_idle_type_tick_create(container_5);
        lv_obj_set_width(mode_light_context_content_area_state_idle_type_tick_2, 2);
        lv_obj_set_height(mode_light_context_content_area_state_idle_type_tick_2, 2);

        lv_obj_t * mode_light_context_content_area_state_idle_type_tick_3 = mode_light_context_content_area_state_idle_type_tick_create(container_5);
        lv_obj_set_width(mode_light_context_content_area_state_idle_type_tick_3, 2);
        lv_obj_set_height(mode_light_context_content_area_state_idle_type_tick_3, 2);

        lv_obj_t * mode_light_context_content_area_state_idle_type_tick_4 = mode_light_context_content_area_state_idle_type_tick_create(container_5);
        lv_obj_set_width(mode_light_context_content_area_state_idle_type_tick_4, 2);
        lv_obj_set_height(mode_light_context_content_area_state_idle_type_tick_4, 2);

        lv_obj_t * container_6 = container_create(container_4);
        lv_obj_set_flex_flow(container_6, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_main_place(container_6, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_cross_place(container_6, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(container_6, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(container_6, 1, 0);
        lv_obj_set_style_pad_row(container_6, 0, 0);
        lv_obj_set_x(container_6, -3);
        lv_obj_set_y(container_6, 6);
        lv_obj_set_width(container_6, 404);
        lv_obj_set_height(container_6, 6);
        lv_obj_t * mode_light_active_true_context_content_area_state_idle_0 = mode_light_active_true_context_content_area_state_idle_create(container_6);
        lv_obj_set_width(mode_light_active_true_context_content_area_state_idle_0, lv_pct(100));
        lv_obj_set_height(mode_light_active_true_context_content_area_state_idle_0, 0);
        lv_obj_set_flex_grow(mode_light_active_true_context_content_area_state_idle_0, 1);

        lv_obj_t * container_7 = container_create(container_3);
        lv_obj_set_x(container_7, 199);
        lv_obj_set_y(container_7, 8);
        lv_obj_set_width(container_7, 199);
        lv_obj_set_height(container_7, 6);
        lv_obj_set_style_transform_rotation(container_7, 1800, 0);
        lv_obj_set_style_transform_pivot_x(container_7, 100, 0);
        lv_obj_set_style_transform_pivot_y(container_7, 3, 0);
        lv_obj_t * container_8 = container_create(container_7);
        lv_obj_set_flex_flow(container_8, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_main_place(container_8, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_cross_place(container_8, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(container_8, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_left(container_8, 0, 0);
        lv_obj_set_style_pad_right(container_8, 1, 0);
        lv_obj_set_style_pad_ver(container_8, 1, 0);
        lv_obj_set_style_pad_row(container_8, 0, 0);
        lv_obj_set_x(container_8, -1);
        lv_obj_set_y(container_8, 6);
        lv_obj_set_width(container_8, 203);
        lv_obj_set_height(container_8, 6);
        lv_obj_t * mode_light_active_true_context_content_area_state_idle_b_0 = mode_light_active_true_context_content_area_state_idle_b_create(container_8);
        lv_obj_set_width(mode_light_active_true_context_content_area_state_idle_b_0, lv_pct(100));
        lv_obj_set_height(mode_light_active_true_context_content_area_state_idle_b_0, 0);
        lv_obj_set_flex_grow(mode_light_active_true_context_content_area_state_idle_b_0, 1);

        lv_obj_t * container_9 = container_create(container_7);
        lv_obj_set_flex_flow(container_9, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_flex_cross_place(container_9, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(container_9, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_left(container_9, 0, 0);
        lv_obj_set_style_pad_right(container_9, 1, 0);
        lv_obj_set_style_pad_ver(container_9, 1, 0);
        lv_obj_set_style_pad_column(container_9, 0, 0);
        lv_obj_set_x(container_9, -1);
        lv_obj_set_y(container_9, 6);
        lv_obj_set_width(container_9, 203);
        lv_obj_set_height(container_9, 6);
        lv_obj_t * mode_light_active_true_0 = mode_light_active_true_create(container_9);
        lv_obj_set_width(mode_light_active_true_0, 2);
        lv_obj_set_height(mode_light_active_true_0, 4);

        lv_obj_t * container_10 = container_create(container_3);
        lv_obj_set_flex_flow(container_10, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_main_place(container_10, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_cross_place(container_10, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(container_10, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(container_10, 0, 0);
        lv_obj_set_style_pad_row(container_10, 0, 0);
        lv_obj_set_align(container_10, LV_ALIGN_LEFT_MID);
        lv_obj_set_x(container_10, 197);
        lv_obj_set_y(container_10, 0);
        lv_obj_set_width(container_10, 1);
        lv_obj_set_height(container_10, 20);
        lv_obj_t * card_1 = card_create(container_10);
        lv_obj_set_width(card_1, 20);
        lv_obj_set_height(card_1, 16);
        lv_obj_set_style_bg_color(card_1, lv_color_hex(0xFFFFFF), 0);
        lv_obj_set_style_radius(card_1, 100, 0);
        lv_obj_set_style_shadow_width(card_1, 6, 0);
        lv_obj_set_style_shadow_offset_y(card_1, 1, 0);
        lv_obj_set_style_shadow_color(card_1, lv_color_hex(0x000000), 0);
        lv_obj_set_style_shadow_opa(card_1, 31, 0);

        the_root = card_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

