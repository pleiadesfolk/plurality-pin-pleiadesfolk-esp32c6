/**
 * @file tf_storage_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "tf_storage_gen.h"
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

lv_obj_t * tf_storage_create(lv_obj_t * parent)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if PLURALITY_PIN_CHECK_COMPILE_TARGET(PLURALITY_PIN_TARGET_ALL)
    if (plurality_pin_check_target(PLURALITY_PIN_TARGET_ALL)) {
        lv_obj_t * card_0 = card_create(parent);
        lv_obj_set_name_static(card_0, "tf_storage_#");
        lv_obj_set_flex_flow(card_0, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_pad_hor(card_0, 12, 0);
        lv_obj_set_style_pad_ver(card_0, 10, 0);
        lv_obj_set_style_pad_row(card_0, 10, 0);
        lv_obj_set_width(card_0, 283);
        lv_obj_set_height(card_0, 95);
        lv_obj_set_style_bg_color(card_0, lv_color_hex(0x787880), 0);
        lv_obj_set_style_bg_opa(card_0, 7, 0);
        lv_obj_set_style_radius(card_0, 10, 0);

        lv_obj_t * container_0 = container_create(card_0);
        lv_obj_set_flex_flow(container_0, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_flex_main_place(container_0, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_pad_all(container_0, 0, 0);
        lv_obj_set_style_pad_row(container_0, 4, 0);
        lv_obj_set_width(container_0, lv_pct(100));
        lv_obj_set_height(container_0, 75);
        lv_obj_t * label_0 = label_create(container_0);
        lv_label_set_text(label_0, "Card storage");
        lv_obj_set_style_text_font(label_0, font_inter_medium_11, 0);
        lv_obj_set_style_text_color(label_0, lv_color_hex(0x757575), 0);

        lv_obj_t * card_1 = card_create(container_0);
        lv_obj_set_width(card_1, lv_pct(100));
        lv_obj_set_height(card_1, 6);
        lv_obj_set_style_bg_color(card_1, lv_color_hex(0x404045), 0);
        lv_obj_set_style_radius(card_1, 3, 0);
        lv_obj_t * card_2 = card_create(card_1);
        lv_obj_set_x(card_2, 0);
        lv_obj_set_y(card_2, 0);
        lv_obj_set_width(card_2, 74);
        lv_obj_set_height(card_2, 6);
        lv_obj_set_style_bg_color(card_2, lv_color_hex(0x668FFF), 0);
        lv_obj_set_style_radius(card_2, 3, 0);

        lv_obj_t * label_1 = label_create(container_0);
        lv_label_set_text(label_1, "19.8 / 32 GB");
        lv_obj_set_style_text_font(label_1, font_inter_semi_bold_14, 0);
        lv_obj_set_style_text_color(label_1, lv_color_hex(0xF3F3F3), 0);

        the_root = card_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

