/**
 * @file pull_down_menu_initial_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "pull_down_menu_initial_gen.h"
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

lv_obj_t * pull_down_menu_initial_create(void)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if PLURALITY_PIN_CHECK_COMPILE_TARGET(PLURALITY_PIN_TARGET_ALL)
    if (plurality_pin_check_target(PLURALITY_PIN_TARGET_ALL)) {
        lv_obj_t * lv_obj_0 = lv_obj_create(NULL);
        lv_obj_set_name_static(lv_obj_0, "pull_down_menu_initial_#");
        lv_obj_set_style_bg_color(lv_obj_0, lv_color_hex(0x8E8E8E), 0);
        lv_obj_set_flag(lv_obj_0, LV_OBJ_FLAG_SCROLLABLE, false);
        lv_obj_set_style_pad_all(lv_obj_0, 0, 0);

        lv_obj_add_style(lv_obj_0, &style_screen_base_global, 0);
        lv_obj_t * container_0 = container_create(lv_obj_0);
        lv_obj_set_align(container_0, LV_ALIGN_TOP_MID);
        lv_obj_set_x(container_0, 0);
        lv_obj_set_y(container_0, -238);
        lv_obj_set_width(container_0, 600);
        lv_obj_set_height(container_0, 600);
        lv_obj_t * card_0 = card_create(container_0);
        lv_obj_set_x(card_0, -68);
        lv_obj_set_y(card_0, 562);
        lv_obj_set_width(card_0, 737);
        lv_obj_set_height(card_0, 737);
        lv_obj_set_style_bg_color(card_0, lv_color_hex(0x1E1E1E), 0);
        lv_obj_set_style_transform_rotation(card_0, -900, 0);
        lv_obj_set_style_transform_pivot_x(card_0, 369, 0);
        lv_obj_set_style_transform_pivot_y(card_0, 369, 0);
        lv_obj_set_style_radius(card_0, 32767, 0);

        lv_obj_t * column_0 = column_create(lv_obj_0, 0, 0, 0, 0, 27, 0, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
        lv_obj_set_align(column_0, LV_ALIGN_CENTER);
        lv_obj_set_x(column_0, 0);
        lv_obj_set_y(column_0, -17);
        lv_obj_set_width(column_0, 440);
        lv_obj_set_height(column_0, 228);
        status_bar_create(column_0);

        lv_obj_t * column_1 = column_create(column_0, 0, 0, 0, 0, 10, 0, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
        lv_obj_set_width(column_1, lv_pct(100));
        lv_obj_set_height(column_1, 170);
        lv_obj_t * row_0 = row_create(column_1, 0, 0, 0, 0, 0, 0, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_width(row_0, lv_pct(100));
        lv_obj_set_height(row_0, 50);
        lv_obj_t * tile_0 = tile_create(row_0, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, false);
        lv_obj_set_style_pad_column(tile_0, 0, 0);
        lv_obj_set_width(tile_0, 0);
        lv_obj_set_height(tile_0, lv_pct(100));
        lv_obj_set_flex_grow(tile_0, 1);
        lv_obj_t * row_1 = row_create(tile_0, 24, 24, 16, 16, 8, 1, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_width(row_1, 0);
        lv_obj_set_height(row_1, lv_pct(100));
        account_circle_create(row_1);

        lv_obj_t * label_0 = label_create(row_1);
        lv_label_set_text(label_0, "Status");
        lv_obj_set_style_text_font(label_0, font_inter_semi_bold_22_manual, 0);
        lv_obj_set_style_text_color(label_0, lv_color_hex(0xFFFFFF), 0);

        lv_obj_t * row_2 = row_create(column_1, 0, 0, 0, 0, 0, 0, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_width(row_2, 440);
        lv_obj_set_height(row_2, 50);
        lv_obj_t * tile_1 = tile_create(row_2, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, false);
        lv_obj_set_style_pad_column(tile_1, 0, 0);
        lv_obj_set_width(tile_1, 0);
        lv_obj_set_height(tile_1, lv_pct(100));
        lv_obj_set_flex_grow(tile_1, 1);
        lv_obj_t * row_3 = row_create(tile_1, 24, 24, 16, 16, 8, 1, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_width(row_3, 0);
        lv_obj_set_height(row_3, lv_pct(100));
        settings_e_create(row_3);

        lv_obj_t * label_1 = label_create(row_3);
        lv_label_set_text(label_1, "Settings");
        lv_obj_set_style_text_font(label_1, font_inter_semi_bold_22_manual, 0);
        lv_obj_set_style_text_color(label_1, lv_color_hex(0xFFFFFF), 0);

        lv_obj_t * row_4 = row_create(column_1, 0, 0, 0, 0, 0, 0, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_width(row_4, lv_pct(100));
        lv_obj_set_height(row_4, 50);
        lv_obj_t * tile_2_0 = tile_2_create(row_4, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, false);
        lv_obj_set_style_pad_column(tile_2_0, 0, 0);
        lv_obj_set_width(tile_2_0, 0);
        lv_obj_set_height(tile_2_0, lv_pct(100));
        lv_obj_set_flex_grow(tile_2_0, 1);
        lv_obj_t * row_5 = row_create(tile_2_0, 24, 24, 16, 16, 8, 1, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_width(row_5, 0);
        lv_obj_set_height(row_5, lv_pct(100));
        link_create(row_5);

        lv_obj_t * label_2 = label_create(row_5);
        lv_label_set_text(label_2, "Connect to pin");
        lv_obj_set_style_text_font(label_2, font_inter_semi_bold_22_manual, 0);
        lv_obj_set_style_text_color(label_2, lv_color_hex(0x000000), 0);

        the_root = lv_obj_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

