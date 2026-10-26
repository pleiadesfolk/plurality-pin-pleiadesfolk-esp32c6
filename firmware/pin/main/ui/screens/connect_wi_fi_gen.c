/**
 * @file connect_wi_fi_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "connect_wi_fi_gen.h"
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

lv_obj_t * connect_wi_fi_create(void)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if PLURALITY_PIN_CHECK_COMPILE_TARGET(PLURALITY_PIN_TARGET_ALL)
    if (plurality_pin_check_target(PLURALITY_PIN_TARGET_ALL)) {
        lv_obj_t * lv_obj_0 = lv_obj_create(NULL);
        lv_obj_set_name_static(lv_obj_0, "connect_wi_fi_#");
        lv_obj_set_style_bg_color(lv_obj_0, lv_color_hex(0x333333), 0);
        lv_obj_set_flag(lv_obj_0, LV_OBJ_FLAG_SCROLLABLE, false);
        lv_obj_set_style_pad_all(lv_obj_0, 0, 0);

        lv_obj_add_style(lv_obj_0, &style_screen_base_global, 0);
        lv_obj_t * row_0 = row_create(lv_obj_0, 0, 0, 0, 0, 22, 0, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_align(row_0, LV_ALIGN_CENTER);
        lv_obj_set_x(row_0, 0);
        lv_obj_set_y(row_0, 0);
        lv_obj_set_width(row_0, 416);
        lv_obj_set_height(row_0, 250);
        lv_obj_t * qrcode_b_0 = qrcode_b_create(row_0);
        lv_obj_set_width(qrcode_b_0, 170);
        lv_obj_set_height(qrcode_b_0, 170);

        lv_obj_t * container_0 = container_create(row_0);
        lv_obj_set_width(container_0, 224);
        lv_obj_set_height(container_0, 250);
        lv_obj_t * label_0 = label_create(container_0);
        lv_obj_set_align(label_0, LV_ALIGN_LEFT_MID);
        lv_obj_set_x(label_0, 0);
        lv_obj_set_width(label_0, 224);
        lv_obj_set_height(label_0, LV_SIZE_CONTENT);
        lv_label_set_text(label_0, "Scan to connect to the pin");
        lv_obj_set_style_text_font(label_0, font_ibm_plex_mono_regular_36, 0);
        lv_obj_set_style_text_letter_space(label_0, 0, 0);
        lv_obj_set_style_text_line_space(label_0, -10, 0);
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

