/**
 * @file crash_screen_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "crash_screen_gen.h"
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

lv_obj_t * crash_screen_create(void)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if PLURALITY_PIN_CHECK_COMPILE_TARGET(PLURALITY_PIN_TARGET_ALL)
    if (plurality_pin_check_target(PLURALITY_PIN_TARGET_ALL)) {
        lv_obj_t * lv_obj_0 = lv_obj_create(NULL);
        lv_obj_set_name_static(lv_obj_0, "crash_screen_#");
        lv_obj_set_style_bg_color(lv_obj_0, lv_color_hex(0x333333), 0);
        lv_obj_set_flag(lv_obj_0, LV_OBJ_FLAG_SCROLLABLE, false);
        lv_obj_set_style_pad_all(lv_obj_0, 0, 0);

        lv_obj_add_style(lv_obj_0, &style_screen_base_global, 0);
        lv_obj_t * container_0 = container_create(lv_obj_0);
        lv_obj_set_x(container_0, 199);
        lv_obj_set_y(container_0, 119);
        lv_obj_set_width(container_0, 43);
        lv_obj_set_height(container_0, 43);
        lv_obj_t * image_0 = image_create(container_0);
        lv_obj_set_x(image_0, 0);
        lv_obj_set_y(image_0, 0);
        lv_obj_set_width(image_0, 43);
        lv_obj_set_height(image_0, 43);
        lv_image_set_src(image_0, image_vec_49_900);

        lv_obj_t * image_1 = image_create(container_0);
        lv_obj_set_x(image_1, 0);
        lv_obj_set_y(image_1, 0);
        lv_obj_set_width(image_1, 43);
        lv_obj_set_height(image_1, 43);
        lv_image_set_src(image_1, image_vec_49_901);

        lv_obj_t * container_1 = container_create(lv_obj_0);
        lv_obj_set_x(container_1, 155);
        lv_obj_set_y(container_1, 94);
        lv_obj_set_width(container_1, 146);
        lv_obj_set_height(container_1, 92);
        lv_obj_t * image_2 = image_create(container_1);
        lv_obj_set_x(image_2, 0);
        lv_obj_set_y(image_2, 0);
        lv_obj_set_width(image_2, 130);
        lv_obj_set_height(image_2, 92);
        lv_image_set_src(image_2, image_vec_49_913);

        lv_obj_t * image_3 = image_create(container_1);
        lv_obj_set_x(image_3, 136);
        lv_obj_set_y(image_3, 22);
        lv_obj_set_width(image_3, 10);
        lv_obj_set_height(image_3, 48);
        lv_image_set_src(image_3, image_vec_49_914);

        lv_obj_t * image_4 = image_create(lv_obj_0);
        lv_obj_set_x(image_4, 202);
        lv_obj_set_y(image_4, 111);
        lv_obj_set_width(image_4, 36);
        lv_obj_set_height(image_4, 58);
        lv_image_set_src(image_4, image_vec_49_912);
        lv_obj_set_flag(image_4, LV_OBJ_FLAG_SCROLLABLE, false);

        lv_obj_t * container_2 = container_create(lv_obj_0);
        lv_obj_set_x(container_2, 175);
        lv_obj_set_y(container_2, 114);
        lv_obj_set_width(container_2, 25);
        lv_obj_set_height(container_2, 52);
        lv_obj_t * card_0 = card_create(container_2);
        lv_obj_set_x(card_0, 0);
        lv_obj_set_y(card_0, 0);
        lv_obj_set_width(card_0, 25);
        lv_obj_set_height(card_0, 52);
        lv_obj_set_style_bg_color(card_0, lv_color_hex(0xFF0000), 0);
        lv_obj_set_style_radius(card_0, 50, 0);

        the_root = lv_obj_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

