/**
 * @file boot_screen_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "boot_screen_gen.h"
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

lv_obj_t * boot_screen_create(void)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if PLURALITY_PIN_CHECK_COMPILE_TARGET(PLURALITY_PIN_TARGET_ALL)
    if (plurality_pin_check_target(PLURALITY_PIN_TARGET_ALL)) {
        lv_obj_t * lv_obj_0 = lv_obj_create(NULL);
        lv_obj_set_name_static(lv_obj_0, "boot_screen_#");
        lv_obj_set_style_bg_color(lv_obj_0, lv_color_hex(0x333333), 0);
        lv_obj_set_flag(lv_obj_0, LV_OBJ_FLAG_SCROLLABLE, false);
        lv_obj_set_style_pad_all(lv_obj_0, 0, 0);

        lv_obj_add_style(lv_obj_0, &style_screen_base_global, 0);
        lv_obj_t * container_0 = container_create(lv_obj_0);
        lv_obj_set_align(container_0, LV_ALIGN_CENTER);
        lv_obj_set_x(container_0, 1);
        lv_obj_set_y(container_0, 0);
        lv_obj_set_width(container_0, 377);
        lv_obj_set_height(container_0, 243);
        lv_obj_t * image_0 = image_create(container_0);
        lv_obj_set_x(image_0, 296);
        lv_obj_set_y(image_0, 128);
        lv_obj_set_width(image_0, 40);
        lv_obj_set_height(image_0, 40);
        lv_image_set_src(image_0, image_vec_46_963);

        lv_obj_t * image_1 = image_create(container_0);
        lv_obj_set_x(image_1, 125);
        lv_obj_set_y(image_1, 139);
        lv_obj_set_width(image_1, 28);
        lv_obj_set_height(image_1, 27);
        lv_image_set_src(image_1, image_vec_46_964);

        lv_obj_t * image_2 = image_create(container_0);
        lv_obj_set_x(image_2, 153);
        lv_obj_set_y(image_2, 131);
        lv_obj_set_width(image_2, 11);
        lv_obj_set_height(image_2, 11);
        lv_image_set_src(image_2, image_vec_46_965);

        lv_obj_t * image_3 = image_create(container_0);
        lv_obj_set_x(image_3, 162);
        lv_obj_set_y(image_3, 118);
        lv_obj_set_width(image_3, 10);
        lv_obj_set_height(image_3, 10);
        lv_image_set_src(image_3, image_vec_46_966);

        lv_obj_t * image_4 = image_create(container_0);
        lv_obj_set_x(image_4, 168);
        lv_obj_set_y(image_4, 134);
        lv_obj_set_width(image_4, 12);
        lv_obj_set_height(image_4, 12);
        lv_image_set_src(image_4, image_vec_46_967);

        lv_obj_t * image_5 = image_create(container_0);
        lv_obj_set_x(image_5, 206);
        lv_obj_set_y(image_5, 184);
        lv_obj_set_width(image_5, 23);
        lv_obj_set_height(image_5, 23);
        lv_image_set_src(image_5, image_vec_46_968);

        lv_obj_t * image_6 = image_create(container_0);
        lv_obj_set_x(image_6, 241);
        lv_obj_set_y(image_6, 57);
        lv_obj_set_width(image_6, 23);
        lv_obj_set_height(image_6, 23);
        lv_image_set_src(image_6, image_vec_46_969);

        lv_obj_t * image_7 = image_create(container_0);
        lv_obj_set_x(image_7, 259);
        lv_obj_set_y(image_7, 76);
        lv_obj_set_width(image_7, 12);
        lv_obj_set_height(image_7, 12);
        lv_image_set_src(image_7, image_vec_46_970);

        lv_obj_t * image_8 = image_create(container_0);
        lv_obj_set_x(image_8, 214);
        lv_obj_set_y(image_8, 125);
        lv_obj_set_width(image_8, 12);
        lv_obj_set_height(image_8, 12);
        lv_image_set_src(image_8, image_vec_46_971);

        lv_obj_t * image_9 = image_create(container_0);
        lv_obj_set_x(image_9, 221);
        lv_obj_set_y(image_9, 113);
        lv_obj_set_width(image_9, 12);
        lv_obj_set_height(image_9, 12);
        lv_image_set_src(image_9, image_vec_46_972);

        lv_obj_t * image_10 = image_create(container_0);
        lv_obj_set_x(image_10, 203);
        lv_obj_set_y(image_10, 97);
        lv_obj_set_width(image_10, 12);
        lv_obj_set_height(image_10, 12);
        lv_image_set_src(image_10, image_vec_46_973);

        lv_obj_t * image_11 = image_create(container_0);
        lv_obj_set_x(image_11, 293);
        lv_obj_set_y(image_11, 96);
        lv_obj_set_width(image_11, 12);
        lv_obj_set_height(image_11, 12);
        lv_image_set_src(image_11, image_vec_46_974);

        lv_obj_t * image_12 = image_create(container_0);
        lv_obj_set_x(image_12, 312);
        lv_obj_set_y(image_12, 86);
        lv_obj_set_width(image_12, 19);
        lv_obj_set_height(image_12, 19);
        lv_image_set_src(image_12, image_vec_46_975);

        lv_obj_t * image_13 = image_create(container_0);
        lv_obj_set_x(image_13, 287);
        lv_obj_set_y(image_13, 33);
        lv_obj_set_width(image_13, 18);
        lv_obj_set_height(image_13, 18);
        lv_image_set_src(image_13, image_vec_46_976);

        lv_obj_t * image_14 = image_create(container_0);
        lv_obj_set_x(image_14, 241);
        lv_obj_set_y(image_14, 8);
        lv_obj_set_width(image_14, 12);
        lv_obj_set_height(image_14, 12);
        lv_image_set_src(image_14, image_vec_46_977);

        lv_obj_t * image_15 = image_create(container_0);
        lv_obj_set_x(image_15, 232);
        lv_obj_set_y(image_15, 18);
        lv_obj_set_width(image_15, 10);
        lv_obj_set_height(image_15, 10);
        lv_image_set_src(image_15, image_vec_46_978);

        lv_obj_t * image_16 = image_create(container_0);
        lv_obj_set_x(image_16, 167);
        lv_obj_set_y(image_16, 18);
        lv_obj_set_width(image_16, 12);
        lv_obj_set_height(image_16, 12);
        lv_image_set_src(image_16, image_vec_46_979);

        lv_obj_t * image_17 = image_create(container_0);
        lv_obj_set_x(image_17, 141);
        lv_obj_set_y(image_17, 0);
        lv_obj_set_width(image_17, 12);
        lv_obj_set_height(image_17, 12);
        lv_image_set_src(image_17, image_vec_46_980);

        lv_obj_t * image_18 = image_create(container_0);
        lv_obj_set_x(image_18, 132);
        lv_obj_set_y(image_18, 87);
        lv_obj_set_width(image_18, 12);
        lv_obj_set_height(image_18, 12);
        lv_image_set_src(image_18, image_vec_46_981);

        lv_obj_t * image_19 = image_create(container_0);
        lv_obj_set_x(image_19, 136);
        lv_obj_set_y(image_19, 199);
        lv_obj_set_width(image_19, 12);
        lv_obj_set_height(image_19, 12);
        lv_image_set_src(image_19, image_vec_46_982);

        lv_obj_t * image_20 = image_create(container_0);
        lv_obj_set_x(image_20, 142);
        lv_obj_set_y(image_20, 231);
        lv_obj_set_width(image_20, 12);
        lv_obj_set_height(image_20, 12);
        lv_image_set_src(image_20, image_vec_46_983);

        lv_obj_t * image_21 = image_create(container_0);
        lv_obj_set_x(image_21, 30);
        lv_obj_set_y(image_21, 213);
        lv_obj_set_width(image_21, 12);
        lv_obj_set_height(image_21, 12);
        lv_image_set_src(image_21, image_vec_46_984);

        lv_obj_t * image_22 = image_create(container_0);
        lv_obj_set_x(image_22, 13);
        lv_obj_set_y(image_22, 205);
        lv_obj_set_width(image_22, 12);
        lv_obj_set_height(image_22, 12);
        lv_image_set_src(image_22, image_vec_46_985);

        lv_obj_t * image_23 = image_create(container_0);
        lv_obj_set_x(image_23, 83);
        lv_obj_set_y(image_23, 79);
        lv_obj_set_width(image_23, 11);
        lv_obj_set_height(image_23, 11);
        lv_image_set_src(image_23, image_vec_46_986);

        lv_obj_t * image_24 = image_create(container_0);
        lv_obj_set_x(image_24, 64);
        lv_obj_set_y(image_24, 68);
        lv_obj_set_width(image_24, 12);
        lv_obj_set_height(image_24, 12);
        lv_image_set_src(image_24, image_vec_46_987);

        lv_obj_t * image_25 = image_create(container_0);
        lv_obj_set_x(image_25, 14);
        lv_obj_set_y(image_25, 52);
        lv_obj_set_width(image_25, 12);
        lv_obj_set_height(image_25, 12);
        lv_image_set_src(image_25, image_vec_46_988);

        lv_obj_t * image_26 = image_create(container_0);
        lv_obj_set_x(image_26, 5);
        lv_obj_set_y(image_26, 63);
        lv_obj_set_width(image_26, 12);
        lv_obj_set_height(image_26, 12);
        lv_image_set_src(image_26, image_vec_46_989);

        lv_obj_t * image_27 = image_create(container_0);
        lv_obj_set_x(image_27, 0);
        lv_obj_set_y(image_27, 96);
        lv_obj_set_width(image_27, 12);
        lv_obj_set_height(image_27, 12);
        lv_image_set_src(image_27, image_vec_46_990);

        lv_obj_t * image_28 = image_create(container_0);
        lv_obj_set_x(image_28, 14);
        lv_obj_set_y(image_28, 153);
        lv_obj_set_width(image_28, 23);
        lv_obj_set_height(image_28, 23);
        lv_image_set_src(image_28, image_vec_46_991);

        lv_obj_t * image_29 = image_create(container_0);
        lv_obj_set_x(image_29, 9);
        lv_obj_set_y(image_29, 126);
        lv_obj_set_width(image_29, 20);
        lv_obj_set_height(image_29, 20);
        lv_image_set_src(image_29, image_vec_46_992);

        lv_obj_t * image_30 = image_create(container_0);
        lv_obj_set_x(image_30, 244);
        lv_obj_set_y(image_30, 164);
        lv_obj_set_width(image_30, 11);
        lv_obj_set_height(image_30, 11);
        lv_image_set_src(image_30, image_vec_46_993);

        lv_obj_t * image_31 = image_create(container_0);
        lv_obj_set_x(image_31, 273);
        lv_obj_set_y(image_31, 167);
        lv_obj_set_width(image_31, 10);
        lv_obj_set_height(image_31, 11);
        lv_image_set_src(image_31, image_vec_46_994);

        lv_obj_t * image_32 = image_create(container_0);
        lv_obj_set_x(image_32, 159);
        lv_obj_set_y(image_32, 174);
        lv_obj_set_width(image_32, 11);
        lv_obj_set_height(image_32, 12);
        lv_image_set_src(image_32, image_vec_46_995);

        lv_obj_t * image_33 = image_create(container_0);
        lv_obj_set_x(image_33, 366);
        lv_obj_set_y(image_33, 9);
        lv_obj_set_width(image_33, 11);
        lv_obj_set_height(image_33, 12);
        lv_image_set_src(image_33, image_vec_46_996);

        lv_obj_t * image_34 = image_create(container_0);
        lv_obj_set_x(image_34, 340);
        lv_obj_set_y(image_34, 56);
        lv_obj_set_width(image_34, 11);
        lv_obj_set_height(image_34, 12);
        lv_image_set_src(image_34, image_vec_46_997);

        lv_obj_t * image_35 = image_create(container_0);
        lv_obj_set_x(image_35, 346);
        lv_obj_set_y(image_35, 135);
        lv_obj_set_width(image_35, 11);
        lv_obj_set_height(image_35, 12);
        lv_image_set_src(image_35, image_vec_46_998);

        the_root = lv_obj_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

