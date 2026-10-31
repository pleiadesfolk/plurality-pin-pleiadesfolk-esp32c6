/**
 * @file settings_g_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "settings_g_gen.h"
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

lv_obj_t * settings_g_create(lv_obj_t * parent)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if PLURALITY_PIN_CHECK_COMPILE_TARGET(PLURALITY_PIN_TARGET_ALL)
    if (plurality_pin_check_target(PLURALITY_PIN_TARGET_ALL)) {
        lv_obj_t * container_0 = container_create(parent);
        lv_obj_set_name_static(container_0, "settings_g_#");
        lv_obj_set_flex_flow(container_0, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_flex_main_place(container_0, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_cross_place(container_0, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(container_0, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(container_0, 0, 0);
        lv_obj_set_style_pad_column(container_0, 0, 0);
        lv_obj_set_width(container_0, lv_pct(100));
        lv_obj_set_height(container_0, 50);

        lv_obj_t * card_0 = card_create(container_0);
        lv_obj_set_flex_flow(card_0, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_flex_main_place(card_0, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_cross_place(card_0, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(card_0, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(card_0, 0, 0);
        lv_obj_set_style_pad_column(card_0, 0, 0);
        lv_obj_set_width(card_0, 0);
        lv_obj_set_height(card_0, lv_pct(100));
        lv_obj_set_flex_grow(card_0, 1);
        lv_obj_set_style_bg_color(card_0, lv_color_hex(0x0088FF), 0);
        lv_obj_set_style_radius(card_0, 100, 0);
        lv_obj_t * container_1 = container_create(card_0);
        lv_obj_set_flex_flow(container_1, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_flex_main_place(container_1, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_cross_place(container_1, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_track_place(container_1, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_hor(container_1, 24, 0);
        lv_obj_set_style_pad_ver(container_1, 16, 0);
        lv_obj_set_style_pad_column(container_1, 8, 0);
        lv_obj_set_width(container_1, 0);
        lv_obj_set_height(container_1, lv_pct(100));
        lv_obj_set_flex_grow(container_1, 1);
        settings_e_create(container_1);

        lv_obj_t * label_0 = label_create(container_1);
        lv_label_set_text(label_0, "Settings");
        lv_obj_set_style_text_font(label_0, font_roboto_semibold_22, 0);
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

