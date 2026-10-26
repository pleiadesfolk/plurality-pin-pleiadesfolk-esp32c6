/**
 * @file image_mode_with_text_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "image_mode_with_text_gen.h"
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

lv_obj_t * image_mode_with_text_create(void)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if PLURALITY_PIN_CHECK_COMPILE_TARGET(PLURALITY_PIN_TARGET_ALL)
    if (plurality_pin_check_target(PLURALITY_PIN_TARGET_ALL)) {
        lv_obj_t * lv_obj_0 = lv_obj_create(NULL);
        lv_obj_set_name_static(lv_obj_0, "image_mode_with_text_#");
        lv_obj_set_style_bg_color(lv_obj_0, lv_color_hex(0x333333), 0);
        lv_obj_set_flag(lv_obj_0, LV_OBJ_FLAG_SCROLLABLE, false);
        lv_obj_set_style_pad_all(lv_obj_0, 0, 0);

        lv_obj_add_style(lv_obj_0, &style_screen_base_global, 0);
        lv_obj_t * container_0 = container_create(lv_obj_0);
        lv_obj_set_x(container_0, 0);
        lv_obj_set_y(container_0, 0);
        lv_obj_set_width(container_0, 456);
        lv_obj_set_height(container_0, 280);
        lv_obj_t * panel_0 = panel_create(container_0);
        lv_obj_set_x(panel_0, 0);
        lv_obj_set_y(panel_0, 0);
        lv_obj_set_width(panel_0, 456);
        lv_obj_set_height(panel_0, 280);
        lv_obj_set_style_bg_color(panel_0, lv_color_hex(0x0088FF), 0);

        lv_obj_t * column_0 = column_create(lv_obj_0, 0, 0, 0, 0, 10, 0, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_align(column_0, LV_ALIGN_CENTER);
        lv_obj_set_x(column_0, -109);
        lv_obj_set_y(column_0, 0);
        lv_obj_set_width(column_0, 202);
        lv_obj_set_height(column_0, 256);
        lv_obj_t * label_0 = label_create(column_0);
        lv_obj_set_width(label_0, lv_pct(100));
        lv_obj_set_height(label_0, LV_SIZE_CONTENT);
        lv_label_set_text(label_0, "Meredith\nEllis");
        lv_obj_set_style_text_font(label_0, font_playwrite_us_trad_regular_40, 0);
        lv_obj_set_style_text_line_space(label_0, -18, 0);
        lv_obj_set_style_text_color(label_0, lv_color_hex(0xFFFFFF), 0);
        lv_obj_set_style_text_align(label_0, LV_TEXT_ALIGN_CENTER, 0);
        lv_label_set_long_mode(label_0, LV_LABEL_LONG_MODE_CLIP);

        lv_obj_t * container_1 = container_create(lv_obj_0);
        lv_obj_set_align(container_1, LV_ALIGN_CENTER);
        lv_obj_set_x(container_1, 0);
        lv_obj_set_y(container_1, 0);
        lv_obj_set_width(container_1, 456);
        lv_obj_set_height(container_1, 280);
        lv_obj_t * image_0 = image_create(container_1);
        lv_obj_set_align(image_0, LV_ALIGN_CENTER);
        lv_obj_set_x(image_0, 175);
        lv_obj_set_y(image_0, 0);
        lv_obj_set_width(image_0, 350);
        lv_obj_set_height(image_0, 350);
        lv_image_set_src(image_0, image_img_02c5506b);
        lv_obj_set_style_radius(image_0, 500, 0);

        the_root = lv_obj_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

