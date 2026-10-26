/**
 * @file qrcode_b_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "qrcode_b_gen.h"
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

lv_obj_t * qrcode_b_create(lv_obj_t * parent)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if PLURALITY_PIN_CHECK_COMPILE_TARGET(PLURALITY_PIN_TARGET_ALL)
    if (plurality_pin_check_target(PLURALITY_PIN_TARGET_ALL)) {
        lv_obj_t * container_0 = container_create(parent);
        lv_obj_set_name_static(container_0, "qrcode_b_#");
        lv_obj_set_width(container_0, 140);
        lv_obj_set_height(container_0, 140);

        lv_obj_t * container_1 = container_create(container_0);
        lv_obj_set_x(container_1, 0);
        lv_obj_set_y(container_1, 0);
        lv_obj_set_width(container_1, 140);
        lv_obj_set_height(container_1, 140);
        lv_obj_t * container_2 = container_create(container_1);
        lv_obj_set_x(container_2, 0);
        lv_obj_set_y(container_2, 0);
        lv_obj_set_width(container_2, 140);
        lv_obj_set_height(container_2, 140);
        lv_obj_t * image_0 = image_create(container_2);
        lv_obj_set_x(image_0, 0);
        lv_obj_set_y(image_0, 0);
        lv_obj_set_width(image_0, 140);
        lv_obj_set_height(image_0, 140);
        lv_image_set_src(image_0, image_vec_6_2604);

        lv_obj_t * image_1 = image_create(container_1);
        lv_obj_set_x(image_1, 0);
        lv_obj_set_y(image_1, 0);
        lv_obj_set_width(image_1, 140);
        lv_obj_set_height(image_1, 140);
        lv_image_set_src(image_1, image_vec_6_2605);

        lv_obj_t * container_3 = container_create(container_0);
        lv_obj_set_x(container_3, 9);
        lv_obj_set_y(container_3, 9);
        lv_obj_set_width(container_3, 122);
        lv_obj_set_height(container_3, 122);
        lv_obj_t * container_4 = container_create(container_3);
        lv_obj_set_x(container_4, 0);
        lv_obj_set_y(container_4, 0);
        lv_obj_set_width(container_4, 122);
        lv_obj_set_height(container_4, 122);
        lv_obj_t * image_2 = image_create(container_4);
        lv_obj_set_x(image_2, 50);
        lv_obj_set_y(image_2, 0);
        lv_obj_set_width(image_2, 4);
        lv_obj_set_height(image_2, 4);
        lv_image_set_src(image_2, image_vec_6_2608);

        lv_obj_t * image_3 = image_create(container_4);
        lv_obj_set_x(image_3, 55);
        lv_obj_set_y(image_3, 0);
        lv_obj_set_width(image_3, 4);
        lv_obj_set_height(image_3, 4);
        lv_image_set_src(image_3, image_vec_6_2609);

        lv_obj_t * image_4 = image_create(container_4);
        lv_obj_set_x(image_4, 80);
        lv_obj_set_y(image_4, 0);
        lv_obj_set_width(image_4, 4);
        lv_obj_set_height(image_4, 4);
        lv_image_set_src(image_4, image_vec_6_2610);

        lv_obj_t * image_5 = image_create(container_4);
        lv_obj_set_x(image_5, 84);
        lv_obj_set_y(image_5, 0);
        lv_obj_set_width(image_5, 4);
        lv_obj_set_height(image_5, 4);
        lv_image_set_src(image_5, image_vec_6_2611);

        lv_obj_t * image_6 = image_create(container_4);
        lv_obj_set_x(image_6, 42);
        lv_obj_set_y(image_6, 4);
        lv_obj_set_width(image_6, 4);
        lv_obj_set_height(image_6, 4);
        lv_image_set_src(image_6, image_vec_6_2612);

        lv_obj_t * image_7 = image_create(container_4);
        lv_obj_set_x(image_7, 46);
        lv_obj_set_y(image_7, 4);
        lv_obj_set_width(image_7, 4);
        lv_obj_set_height(image_7, 4);
        lv_image_set_src(image_7, image_vec_6_2613);

        lv_obj_t * image_8 = image_create(container_4);
        lv_obj_set_x(image_8, 67);
        lv_obj_set_y(image_8, 4);
        lv_obj_set_width(image_8, 4);
        lv_obj_set_height(image_8, 4);
        lv_image_set_src(image_8, image_vec_6_2614);

        lv_obj_t * image_9 = image_create(container_4);
        lv_obj_set_x(image_9, 76);
        lv_obj_set_y(image_9, 4);
        lv_obj_set_width(image_9, 4);
        lv_obj_set_height(image_9, 4);
        lv_image_set_src(image_9, image_vec_6_2615);

        lv_obj_t * image_10 = image_create(container_4);
        lv_obj_set_x(image_10, 80);
        lv_obj_set_y(image_10, 4);
        lv_obj_set_width(image_10, 4);
        lv_obj_set_height(image_10, 4);
        lv_image_set_src(image_10, image_vec_6_2616);

        lv_obj_t * image_11 = image_create(container_4);
        lv_obj_set_x(image_11, 34);
        lv_obj_set_y(image_11, 8);
        lv_obj_set_width(image_11, 4);
        lv_obj_set_height(image_11, 4);
        lv_image_set_src(image_11, image_vec_6_2617);

        lv_obj_t * image_12 = image_create(container_4);
        lv_obj_set_x(image_12, 38);
        lv_obj_set_y(image_12, 8);
        lv_obj_set_width(image_12, 4);
        lv_obj_set_height(image_12, 4);
        lv_image_set_src(image_12, image_vec_6_2618);

        lv_obj_t * image_13 = image_create(container_4);
        lv_obj_set_x(image_13, 46);
        lv_obj_set_y(image_13, 8);
        lv_obj_set_width(image_13, 4);
        lv_obj_set_height(image_13, 4);
        lv_image_set_src(image_13, image_vec_6_2619);

        lv_obj_t * image_14 = image_create(container_4);
        lv_obj_set_x(image_14, 50);
        lv_obj_set_y(image_14, 8);
        lv_obj_set_width(image_14, 4);
        lv_obj_set_height(image_14, 4);
        lv_image_set_src(image_14, image_vec_6_2620);

        lv_obj_t * image_15 = image_create(container_4);
        lv_obj_set_x(image_15, 55);
        lv_obj_set_y(image_15, 8);
        lv_obj_set_width(image_15, 4);
        lv_obj_set_height(image_15, 4);
        lv_image_set_src(image_15, image_vec_6_2621);

        lv_obj_t * image_16 = image_create(container_4);
        lv_obj_set_x(image_16, 67);
        lv_obj_set_y(image_16, 8);
        lv_obj_set_width(image_16, 4);
        lv_obj_set_height(image_16, 4);
        lv_image_set_src(image_16, image_vec_6_2622);

        lv_obj_t * image_17 = image_create(container_4);
        lv_obj_set_x(image_17, 71);
        lv_obj_set_y(image_17, 8);
        lv_obj_set_width(image_17, 4);
        lv_obj_set_height(image_17, 4);
        lv_image_set_src(image_17, image_vec_6_2623);

        lv_obj_t * image_18 = image_create(container_4);
        lv_obj_set_x(image_18, 76);
        lv_obj_set_y(image_18, 8);
        lv_obj_set_width(image_18, 4);
        lv_obj_set_height(image_18, 4);
        lv_image_set_src(image_18, image_vec_6_2624);

        lv_obj_t * image_19 = image_create(container_4);
        lv_obj_set_x(image_19, 38);
        lv_obj_set_y(image_19, 13);
        lv_obj_set_width(image_19, 4);
        lv_obj_set_height(image_19, 4);
        lv_image_set_src(image_19, image_vec_6_2625);

        lv_obj_t * image_20 = image_create(container_4);
        lv_obj_set_x(image_20, 42);
        lv_obj_set_y(image_20, 13);
        lv_obj_set_width(image_20, 4);
        lv_obj_set_height(image_20, 4);
        lv_image_set_src(image_20, image_vec_6_2626);

        lv_obj_t * image_21 = image_create(container_4);
        lv_obj_set_x(image_21, 50);
        lv_obj_set_y(image_21, 13);
        lv_obj_set_width(image_21, 4);
        lv_obj_set_height(image_21, 4);
        lv_image_set_src(image_21, image_vec_6_2627);

        lv_obj_t * image_22 = image_create(container_4);
        lv_obj_set_x(image_22, 55);
        lv_obj_set_y(image_22, 13);
        lv_obj_set_width(image_22, 4);
        lv_obj_set_height(image_22, 4);
        lv_image_set_src(image_22, image_vec_6_2628);

        lv_obj_t * image_23 = image_create(container_4);
        lv_obj_set_x(image_23, 67);
        lv_obj_set_y(image_23, 13);
        lv_obj_set_width(image_23, 4);
        lv_obj_set_height(image_23, 4);
        lv_image_set_src(image_23, image_vec_6_2629);

        lv_obj_t * image_24 = image_create(container_4);
        lv_obj_set_x(image_24, 76);
        lv_obj_set_y(image_24, 13);
        lv_obj_set_width(image_24, 4);
        lv_obj_set_height(image_24, 4);
        lv_image_set_src(image_24, image_vec_6_2630);

        lv_obj_t * image_25 = image_create(container_4);
        lv_obj_set_x(image_25, 34);
        lv_obj_set_y(image_25, 17);
        lv_obj_set_width(image_25, 4);
        lv_obj_set_height(image_25, 4);
        lv_image_set_src(image_25, image_vec_6_2631);

        lv_obj_t * image_26 = image_create(container_4);
        lv_obj_set_x(image_26, 38);
        lv_obj_set_y(image_26, 17);
        lv_obj_set_width(image_26, 4);
        lv_obj_set_height(image_26, 4);
        lv_image_set_src(image_26, image_vec_6_2632);

        lv_obj_t * image_27 = image_create(container_4);
        lv_obj_set_x(image_27, 42);
        lv_obj_set_y(image_27, 17);
        lv_obj_set_width(image_27, 4);
        lv_obj_set_height(image_27, 4);
        lv_image_set_src(image_27, image_vec_6_2633);

        lv_obj_t * image_28 = image_create(container_4);
        lv_obj_set_x(image_28, 46);
        lv_obj_set_y(image_28, 17);
        lv_obj_set_width(image_28, 4);
        lv_obj_set_height(image_28, 4);
        lv_image_set_src(image_28, image_vec_6_2634);

        lv_obj_t * image_29 = image_create(container_4);
        lv_obj_set_x(image_29, 59);
        lv_obj_set_y(image_29, 17);
        lv_obj_set_width(image_29, 4);
        lv_obj_set_height(image_29, 4);
        lv_image_set_src(image_29, image_vec_6_2635);

        lv_obj_t * image_30 = image_create(container_4);
        lv_obj_set_x(image_30, 63);
        lv_obj_set_y(image_30, 17);
        lv_obj_set_width(image_30, 4);
        lv_obj_set_height(image_30, 4);
        lv_image_set_src(image_30, image_vec_6_2636);

        lv_obj_t * image_31 = image_create(container_4);
        lv_obj_set_x(image_31, 71);
        lv_obj_set_y(image_31, 17);
        lv_obj_set_width(image_31, 4);
        lv_obj_set_height(image_31, 4);
        lv_image_set_src(image_31, image_vec_6_2637);

        lv_obj_t * image_32 = image_create(container_4);
        lv_obj_set_x(image_32, 76);
        lv_obj_set_y(image_32, 17);
        lv_obj_set_width(image_32, 4);
        lv_obj_set_height(image_32, 4);
        lv_image_set_src(image_32, image_vec_6_2638);

        lv_obj_t * image_33 = image_create(container_4);
        lv_obj_set_x(image_33, 34);
        lv_obj_set_y(image_33, 21);
        lv_obj_set_width(image_33, 4);
        lv_obj_set_height(image_33, 4);
        lv_image_set_src(image_33, image_vec_6_2639);

        lv_obj_t * image_34 = image_create(container_4);
        lv_obj_set_x(image_34, 42);
        lv_obj_set_y(image_34, 21);
        lv_obj_set_width(image_34, 4);
        lv_obj_set_height(image_34, 4);
        lv_image_set_src(image_34, image_vec_6_2640);

        lv_obj_t * image_35 = image_create(container_4);
        lv_obj_set_x(image_35, 50);
        lv_obj_set_y(image_35, 21);
        lv_obj_set_width(image_35, 4);
        lv_obj_set_height(image_35, 4);
        lv_image_set_src(image_35, image_vec_6_2641);

        lv_obj_t * image_36 = image_create(container_4);
        lv_obj_set_x(image_36, 59);
        lv_obj_set_y(image_36, 21);
        lv_obj_set_width(image_36, 4);
        lv_obj_set_height(image_36, 4);
        lv_image_set_src(image_36, image_vec_6_2642);

        lv_obj_t * image_37 = image_create(container_4);
        lv_obj_set_x(image_37, 63);
        lv_obj_set_y(image_37, 21);
        lv_obj_set_width(image_37, 4);
        lv_obj_set_height(image_37, 4);
        lv_image_set_src(image_37, image_vec_6_2643);

        lv_obj_t * image_38 = image_create(container_4);
        lv_obj_set_x(image_38, 71);
        lv_obj_set_y(image_38, 21);
        lv_obj_set_width(image_38, 4);
        lv_obj_set_height(image_38, 4);
        lv_image_set_src(image_38, image_vec_6_2644);

        lv_obj_t * image_39 = image_create(container_4);
        lv_obj_set_x(image_39, 80);
        lv_obj_set_y(image_39, 21);
        lv_obj_set_width(image_39, 4);
        lv_obj_set_height(image_39, 4);
        lv_image_set_src(image_39, image_vec_6_2645);

        lv_obj_t * image_40 = image_create(container_4);
        lv_obj_set_x(image_40, 84);
        lv_obj_set_y(image_40, 21);
        lv_obj_set_width(image_40, 4);
        lv_obj_set_height(image_40, 4);
        lv_image_set_src(image_40, image_vec_6_2646);

        lv_obj_t * image_41 = image_create(container_4);
        lv_obj_set_x(image_41, 34);
        lv_obj_set_y(image_41, 25);
        lv_obj_set_width(image_41, 4);
        lv_obj_set_height(image_41, 4);
        lv_image_set_src(image_41, image_vec_6_2647);

        lv_obj_t * image_42 = image_create(container_4);
        lv_obj_set_x(image_42, 42);
        lv_obj_set_y(image_42, 25);
        lv_obj_set_width(image_42, 4);
        lv_obj_set_height(image_42, 4);
        lv_image_set_src(image_42, image_vec_6_2648);

        lv_obj_t * image_43 = image_create(container_4);
        lv_obj_set_x(image_43, 50);
        lv_obj_set_y(image_43, 25);
        lv_obj_set_width(image_43, 4);
        lv_obj_set_height(image_43, 4);
        lv_image_set_src(image_43, image_vec_6_2649);

        lv_obj_t * image_44 = image_create(container_4);
        lv_obj_set_x(image_44, 59);
        lv_obj_set_y(image_44, 25);
        lv_obj_set_width(image_44, 4);
        lv_obj_set_height(image_44, 4);
        lv_image_set_src(image_44, image_vec_6_2650);

        lv_obj_t * image_45 = image_create(container_4);
        lv_obj_set_x(image_45, 67);
        lv_obj_set_y(image_45, 25);
        lv_obj_set_width(image_45, 4);
        lv_obj_set_height(image_45, 4);
        lv_image_set_src(image_45, image_vec_6_2651);

        lv_obj_t * image_46 = image_create(container_4);
        lv_obj_set_x(image_46, 76);
        lv_obj_set_y(image_46, 25);
        lv_obj_set_width(image_46, 4);
        lv_obj_set_height(image_46, 4);
        lv_image_set_src(image_46, image_vec_6_2652);

        lv_obj_t * image_47 = image_create(container_4);
        lv_obj_set_x(image_47, 84);
        lv_obj_set_y(image_47, 25);
        lv_obj_set_width(image_47, 4);
        lv_obj_set_height(image_47, 4);
        lv_image_set_src(image_47, image_vec_6_2653);

        lv_obj_t * image_48 = image_create(container_4);
        lv_obj_set_x(image_48, 42);
        lv_obj_set_y(image_48, 29);
        lv_obj_set_width(image_48, 4);
        lv_obj_set_height(image_48, 4);
        lv_image_set_src(image_48, image_vec_6_2654);

        lv_obj_t * image_49 = image_create(container_4);
        lv_obj_set_x(image_49, 55);
        lv_obj_set_y(image_49, 29);
        lv_obj_set_width(image_49, 4);
        lv_obj_set_height(image_49, 4);
        lv_image_set_src(image_49, image_vec_6_2655);

        lv_obj_t * image_50 = image_create(container_4);
        lv_obj_set_x(image_50, 63);
        lv_obj_set_y(image_50, 29);
        lv_obj_set_width(image_50, 4);
        lv_obj_set_height(image_50, 4);
        lv_image_set_src(image_50, image_vec_6_2656);

        lv_obj_t * image_51 = image_create(container_4);
        lv_obj_set_x(image_51, 67);
        lv_obj_set_y(image_51, 29);
        lv_obj_set_width(image_51, 4);
        lv_obj_set_height(image_51, 4);
        lv_image_set_src(image_51, image_vec_6_2657);

        lv_obj_t * image_52 = image_create(container_4);
        lv_obj_set_x(image_52, 80);
        lv_obj_set_y(image_52, 29);
        lv_obj_set_width(image_52, 4);
        lv_obj_set_height(image_52, 4);
        lv_image_set_src(image_52, image_vec_6_2658);

        lv_obj_t * image_53 = image_create(container_4);
        lv_obj_set_x(image_53, 84);
        lv_obj_set_y(image_53, 29);
        lv_obj_set_width(image_53, 4);
        lv_obj_set_height(image_53, 4);
        lv_image_set_src(image_53, image_vec_6_2659);

        lv_obj_t * image_54 = image_create(container_4);
        lv_obj_set_x(image_54, 4);
        lv_obj_set_y(image_54, 34);
        lv_obj_set_width(image_54, 4);
        lv_obj_set_height(image_54, 4);
        lv_image_set_src(image_54, image_vec_6_2660);

        lv_obj_t * image_55 = image_create(container_4);
        lv_obj_set_x(image_55, 17);
        lv_obj_set_y(image_55, 34);
        lv_obj_set_width(image_55, 4);
        lv_obj_set_height(image_55, 4);
        lv_image_set_src(image_55, image_vec_6_2661);

        lv_obj_t * image_56 = image_create(container_4);
        lv_obj_set_x(image_56, 25);
        lv_obj_set_y(image_56, 34);
        lv_obj_set_width(image_56, 4);
        lv_obj_set_height(image_56, 4);
        lv_image_set_src(image_56, image_vec_6_2662);

        lv_obj_t * image_57 = image_create(container_4);
        lv_obj_set_x(image_57, 34);
        lv_obj_set_y(image_57, 34);
        lv_obj_set_width(image_57, 4);
        lv_obj_set_height(image_57, 4);
        lv_image_set_src(image_57, image_vec_6_2663);

        lv_obj_t * image_58 = image_create(container_4);
        lv_obj_set_x(image_58, 38);
        lv_obj_set_y(image_58, 34);
        lv_obj_set_width(image_58, 4);
        lv_obj_set_height(image_58, 4);
        lv_image_set_src(image_58, image_vec_6_2664);

        lv_obj_t * image_59 = image_create(container_4);
        lv_obj_set_x(image_59, 50);
        lv_obj_set_y(image_59, 34);
        lv_obj_set_width(image_59, 4);
        lv_obj_set_height(image_59, 4);
        lv_image_set_src(image_59, image_vec_6_2665);

        lv_obj_t * image_60 = image_create(container_4);
        lv_obj_set_x(image_60, 55);
        lv_obj_set_y(image_60, 34);
        lv_obj_set_width(image_60, 4);
        lv_obj_set_height(image_60, 4);
        lv_image_set_src(image_60, image_vec_6_2666);

        lv_obj_t * image_61 = image_create(container_4);
        lv_obj_set_x(image_61, 63);
        lv_obj_set_y(image_61, 34);
        lv_obj_set_width(image_61, 4);
        lv_obj_set_height(image_61, 4);
        lv_image_set_src(image_61, image_vec_6_2667);

        lv_obj_t * image_62 = image_create(container_4);
        lv_obj_set_x(image_62, 80);
        lv_obj_set_y(image_62, 34);
        lv_obj_set_width(image_62, 4);
        lv_obj_set_height(image_62, 4);
        lv_image_set_src(image_62, image_vec_6_2668);

        lv_obj_t * image_63 = image_create(container_4);
        lv_obj_set_x(image_63, 84);
        lv_obj_set_y(image_63, 34);
        lv_obj_set_width(image_63, 4);
        lv_obj_set_height(image_63, 4);
        lv_image_set_src(image_63, image_vec_6_2669);

        lv_obj_t * image_64 = image_create(container_4);
        lv_obj_set_x(image_64, 88);
        lv_obj_set_y(image_64, 34);
        lv_obj_set_width(image_64, 4);
        lv_obj_set_height(image_64, 4);
        lv_image_set_src(image_64, image_vec_6_2670);

        lv_obj_t * image_65 = image_create(container_4);
        lv_obj_set_x(image_65, 97);
        lv_obj_set_y(image_65, 34);
        lv_obj_set_width(image_65, 4);
        lv_obj_set_height(image_65, 4);
        lv_image_set_src(image_65, image_vec_6_2671);

        lv_obj_t * image_66 = image_create(container_4);
        lv_obj_set_x(image_66, 101);
        lv_obj_set_y(image_66, 34);
        lv_obj_set_width(image_66, 4);
        lv_obj_set_height(image_66, 4);
        lv_image_set_src(image_66, image_vec_6_2672);

        lv_obj_t * image_67 = image_create(container_4);
        lv_obj_set_x(image_67, 109);
        lv_obj_set_y(image_67, 34);
        lv_obj_set_width(image_67, 4);
        lv_obj_set_height(image_67, 4);
        lv_image_set_src(image_67, image_vec_6_2673);

        lv_obj_t * image_68 = image_create(container_4);
        lv_obj_set_x(image_68, 0);
        lv_obj_set_y(image_68, 38);
        lv_obj_set_width(image_68, 4);
        lv_obj_set_height(image_68, 4);
        lv_image_set_src(image_68, image_vec_6_2674);

        lv_obj_t * image_69 = image_create(container_4);
        lv_obj_set_x(image_69, 4);
        lv_obj_set_y(image_69, 38);
        lv_obj_set_width(image_69, 4);
        lv_obj_set_height(image_69, 4);
        lv_image_set_src(image_69, image_vec_6_2675);

        lv_obj_t * image_70 = image_create(container_4);
        lv_obj_set_x(image_70, 8);
        lv_obj_set_y(image_70, 38);
        lv_obj_set_width(image_70, 4);
        lv_obj_set_height(image_70, 4);
        lv_image_set_src(image_70, image_vec_6_2676);

        lv_obj_t * image_71 = image_create(container_4);
        lv_obj_set_x(image_71, 13);
        lv_obj_set_y(image_71, 38);
        lv_obj_set_width(image_71, 4);
        lv_obj_set_height(image_71, 4);
        lv_image_set_src(image_71, image_vec_6_2677);

        lv_obj_t * image_72 = image_create(container_4);
        lv_obj_set_x(image_72, 34);
        lv_obj_set_y(image_72, 38);
        lv_obj_set_width(image_72, 4);
        lv_obj_set_height(image_72, 4);
        lv_image_set_src(image_72, image_vec_6_2678);

        lv_obj_t * image_73 = image_create(container_4);
        lv_obj_set_x(image_73, 42);
        lv_obj_set_y(image_73, 38);
        lv_obj_set_width(image_73, 4);
        lv_obj_set_height(image_73, 4);
        lv_image_set_src(image_73, image_vec_6_2679);

        lv_obj_t * image_74 = image_create(container_4);
        lv_obj_set_x(image_74, 46);
        lv_obj_set_y(image_74, 38);
        lv_obj_set_width(image_74, 4);
        lv_obj_set_height(image_74, 4);
        lv_image_set_src(image_74, image_vec_6_2680);

        lv_obj_t * image_75 = image_create(container_4);
        lv_obj_set_x(image_75, 59);
        lv_obj_set_y(image_75, 38);
        lv_obj_set_width(image_75, 4);
        lv_obj_set_height(image_75, 4);
        lv_image_set_src(image_75, image_vec_6_2681);

        lv_obj_t * image_76 = image_create(container_4);
        lv_obj_set_x(image_76, 67);
        lv_obj_set_y(image_76, 38);
        lv_obj_set_width(image_76, 4);
        lv_obj_set_height(image_76, 4);
        lv_image_set_src(image_76, image_vec_6_2682);

        lv_obj_t * image_77 = image_create(container_4);
        lv_obj_set_x(image_77, 76);
        lv_obj_set_y(image_77, 38);
        lv_obj_set_width(image_77, 4);
        lv_obj_set_height(image_77, 4);
        lv_image_set_src(image_77, image_vec_6_2683);

        lv_obj_t * image_78 = image_create(container_4);
        lv_obj_set_x(image_78, 80);
        lv_obj_set_y(image_78, 38);
        lv_obj_set_width(image_78, 4);
        lv_obj_set_height(image_78, 4);
        lv_image_set_src(image_78, image_vec_6_2684);

        lv_obj_t * image_79 = image_create(container_4);
        lv_obj_set_x(image_79, 92);
        lv_obj_set_y(image_79, 38);
        lv_obj_set_width(image_79, 4);
        lv_obj_set_height(image_79, 4);
        lv_image_set_src(image_79, image_vec_6_2685);

        lv_obj_t * image_80 = image_create(container_4);
        lv_obj_set_x(image_80, 97);
        lv_obj_set_y(image_80, 38);
        lv_obj_set_width(image_80, 4);
        lv_obj_set_height(image_80, 4);
        lv_image_set_src(image_80, image_vec_6_2686);

        lv_obj_t * image_81 = image_create(container_4);
        lv_obj_set_x(image_81, 101);
        lv_obj_set_y(image_81, 38);
        lv_obj_set_width(image_81, 4);
        lv_obj_set_height(image_81, 4);
        lv_image_set_src(image_81, image_vec_6_2687);

        lv_obj_t * image_82 = image_create(container_4);
        lv_obj_set_x(image_82, 109);
        lv_obj_set_y(image_82, 38);
        lv_obj_set_width(image_82, 4);
        lv_obj_set_height(image_82, 4);
        lv_image_set_src(image_82, image_vec_6_2688);

        lv_obj_t * image_83 = image_create(container_4);
        lv_obj_set_x(image_83, 118);
        lv_obj_set_y(image_83, 38);
        lv_obj_set_width(image_83, 4);
        lv_obj_set_height(image_83, 4);
        lv_image_set_src(image_83, image_vec_6_2689);

        lv_obj_t * image_84 = image_create(container_4);
        lv_obj_set_x(image_84, 0);
        lv_obj_set_y(image_84, 42);
        lv_obj_set_width(image_84, 4);
        lv_obj_set_height(image_84, 4);
        lv_image_set_src(image_84, image_vec_6_2690);

        lv_obj_t * image_85 = image_create(container_4);
        lv_obj_set_x(image_85, 8);
        lv_obj_set_y(image_85, 42);
        lv_obj_set_width(image_85, 4);
        lv_obj_set_height(image_85, 4);
        lv_image_set_src(image_85, image_vec_6_2691);

        lv_obj_t * image_86 = image_create(container_4);
        lv_obj_set_x(image_86, 25);
        lv_obj_set_y(image_86, 42);
        lv_obj_set_width(image_86, 4);
        lv_obj_set_height(image_86, 4);
        lv_image_set_src(image_86, image_vec_6_2692);

        lv_obj_t * image_87 = image_create(container_4);
        lv_obj_set_x(image_87, 29);
        lv_obj_set_y(image_87, 42);
        lv_obj_set_width(image_87, 4);
        lv_obj_set_height(image_87, 4);
        lv_image_set_src(image_87, image_vec_6_2693);

        lv_obj_t * image_88 = image_create(container_4);
        lv_obj_set_x(image_88, 38);
        lv_obj_set_y(image_88, 42);
        lv_obj_set_width(image_88, 4);
        lv_obj_set_height(image_88, 4);
        lv_image_set_src(image_88, image_vec_6_2694);

        lv_obj_t * image_89 = image_create(container_4);
        lv_obj_set_x(image_89, 50);
        lv_obj_set_y(image_89, 42);
        lv_obj_set_width(image_89, 4);
        lv_obj_set_height(image_89, 4);
        lv_image_set_src(image_89, image_vec_6_2695);

        lv_obj_t * image_90 = image_create(container_4);
        lv_obj_set_x(image_90, 59);
        lv_obj_set_y(image_90, 42);
        lv_obj_set_width(image_90, 4);
        lv_obj_set_height(image_90, 4);
        lv_image_set_src(image_90, image_vec_6_2696);

        lv_obj_t * image_91 = image_create(container_4);
        lv_obj_set_x(image_91, 76);
        lv_obj_set_y(image_91, 42);
        lv_obj_set_width(image_91, 4);
        lv_obj_set_height(image_91, 4);
        lv_image_set_src(image_91, image_vec_6_2697);

        lv_obj_t * image_92 = image_create(container_4);
        lv_obj_set_x(image_92, 80);
        lv_obj_set_y(image_92, 42);
        lv_obj_set_width(image_92, 4);
        lv_obj_set_height(image_92, 4);
        lv_image_set_src(image_92, image_vec_6_2698);

        lv_obj_t * image_93 = image_create(container_4);
        lv_obj_set_x(image_93, 92);
        lv_obj_set_y(image_93, 42);
        lv_obj_set_width(image_93, 4);
        lv_obj_set_height(image_93, 4);
        lv_image_set_src(image_93, image_vec_6_2699);

        lv_obj_t * image_94 = image_create(container_4);
        lv_obj_set_x(image_94, 101);
        lv_obj_set_y(image_94, 42);
        lv_obj_set_width(image_94, 4);
        lv_obj_set_height(image_94, 4);
        lv_image_set_src(image_94, image_vec_6_2700);

        lv_obj_t * image_95 = image_create(container_4);
        lv_obj_set_x(image_95, 109);
        lv_obj_set_y(image_95, 42);
        lv_obj_set_width(image_95, 4);
        lv_obj_set_height(image_95, 4);
        lv_image_set_src(image_95, image_vec_6_2701);

        lv_obj_t * image_96 = image_create(container_4);
        lv_obj_set_x(image_96, 118);
        lv_obj_set_y(image_96, 42);
        lv_obj_set_width(image_96, 4);
        lv_obj_set_height(image_96, 4);
        lv_image_set_src(image_96, image_vec_6_2702);

        lv_obj_t * image_97 = image_create(container_4);
        lv_obj_set_x(image_97, 0);
        lv_obj_set_y(image_97, 46);
        lv_obj_set_width(image_97, 4);
        lv_obj_set_height(image_97, 4);
        lv_image_set_src(image_97, image_vec_6_2703);

        lv_obj_t * image_98 = image_create(container_4);
        lv_obj_set_x(image_98, 8);
        lv_obj_set_y(image_98, 46);
        lv_obj_set_width(image_98, 4);
        lv_obj_set_height(image_98, 4);
        lv_image_set_src(image_98, image_vec_6_2704);

        lv_obj_t * image_99 = image_create(container_4);
        lv_obj_set_x(image_99, 29);
        lv_obj_set_y(image_99, 46);
        lv_obj_set_width(image_99, 4);
        lv_obj_set_height(image_99, 4);
        lv_image_set_src(image_99, image_vec_6_2705);

        lv_obj_t * image_100 = image_create(container_4);
        lv_obj_set_x(image_100, 34);
        lv_obj_set_y(image_100, 46);
        lv_obj_set_width(image_100, 4);
        lv_obj_set_height(image_100, 4);
        lv_image_set_src(image_100, image_vec_6_2706);

        lv_obj_t * image_101 = image_create(container_4);
        lv_obj_set_x(image_101, 42);
        lv_obj_set_y(image_101, 46);
        lv_obj_set_width(image_101, 4);
        lv_obj_set_height(image_101, 4);
        lv_image_set_src(image_101, image_vec_6_2707);

        lv_obj_t * image_102 = image_create(container_4);
        lv_obj_set_x(image_102, 71);
        lv_obj_set_y(image_102, 46);
        lv_obj_set_width(image_102, 4);
        lv_obj_set_height(image_102, 4);
        lv_image_set_src(image_102, image_vec_6_2708);

        lv_obj_t * image_103 = image_create(container_4);
        lv_obj_set_x(image_103, 80);
        lv_obj_set_y(image_103, 46);
        lv_obj_set_width(image_103, 4);
        lv_obj_set_height(image_103, 4);
        lv_image_set_src(image_103, image_vec_6_2709);

        lv_obj_t * image_104 = image_create(container_4);
        lv_obj_set_x(image_104, 84);
        lv_obj_set_y(image_104, 46);
        lv_obj_set_width(image_104, 4);
        lv_obj_set_height(image_104, 4);
        lv_image_set_src(image_104, image_vec_6_2710);

        lv_obj_t * image_105 = image_create(container_4);
        lv_obj_set_x(image_105, 88);
        lv_obj_set_y(image_105, 46);
        lv_obj_set_width(image_105, 4);
        lv_obj_set_height(image_105, 4);
        lv_image_set_src(image_105, image_vec_6_2711);

        lv_obj_t * image_106 = image_create(container_4);
        lv_obj_set_x(image_106, 97);
        lv_obj_set_y(image_106, 46);
        lv_obj_set_width(image_106, 4);
        lv_obj_set_height(image_106, 4);
        lv_image_set_src(image_106, image_vec_6_2712);

        lv_obj_t * image_107 = image_create(container_4);
        lv_obj_set_x(image_107, 105);
        lv_obj_set_y(image_107, 46);
        lv_obj_set_width(image_107, 4);
        lv_obj_set_height(image_107, 4);
        lv_image_set_src(image_107, image_vec_6_2713);

        lv_obj_t * image_108 = image_create(container_4);
        lv_obj_set_x(image_108, 0);
        lv_obj_set_y(image_108, 50);
        lv_obj_set_width(image_108, 4);
        lv_obj_set_height(image_108, 4);
        lv_image_set_src(image_108, image_vec_6_2714);

        lv_obj_t * image_109 = image_create(container_4);
        lv_obj_set_x(image_109, 8);
        lv_obj_set_y(image_109, 50);
        lv_obj_set_width(image_109, 4);
        lv_obj_set_height(image_109, 4);
        lv_image_set_src(image_109, image_vec_6_2715);

        lv_obj_t * image_110 = image_create(container_4);
        lv_obj_set_x(image_110, 13);
        lv_obj_set_y(image_110, 50);
        lv_obj_set_width(image_110, 4);
        lv_obj_set_height(image_110, 4);
        lv_image_set_src(image_110, image_vec_6_2716);

        lv_obj_t * image_111 = image_create(container_4);
        lv_obj_set_x(image_111, 17);
        lv_obj_set_y(image_111, 50);
        lv_obj_set_width(image_111, 4);
        lv_obj_set_height(image_111, 4);
        lv_image_set_src(image_111, image_vec_6_2717);

        lv_obj_t * image_112 = image_create(container_4);
        lv_obj_set_x(image_112, 25);
        lv_obj_set_y(image_112, 50);
        lv_obj_set_width(image_112, 4);
        lv_obj_set_height(image_112, 4);
        lv_image_set_src(image_112, image_vec_6_2718);

        lv_obj_t * image_113 = image_create(container_4);
        lv_obj_set_x(image_113, 38);
        lv_obj_set_y(image_113, 50);
        lv_obj_set_width(image_113, 4);
        lv_obj_set_height(image_113, 4);
        lv_image_set_src(image_113, image_vec_6_2719);

        lv_obj_t * image_114 = image_create(container_4);
        lv_obj_set_x(image_114, 42);
        lv_obj_set_y(image_114, 50);
        lv_obj_set_width(image_114, 4);
        lv_obj_set_height(image_114, 4);
        lv_image_set_src(image_114, image_vec_6_2720);

        lv_obj_t * image_115 = image_create(container_4);
        lv_obj_set_x(image_115, 46);
        lv_obj_set_y(image_115, 50);
        lv_obj_set_width(image_115, 4);
        lv_obj_set_height(image_115, 4);
        lv_image_set_src(image_115, image_vec_6_2721);

        lv_obj_t * image_116 = image_create(container_4);
        lv_obj_set_x(image_116, 55);
        lv_obj_set_y(image_116, 50);
        lv_obj_set_width(image_116, 4);
        lv_obj_set_height(image_116, 4);
        lv_image_set_src(image_116, image_vec_6_2722);

        lv_obj_t * image_117 = image_create(container_4);
        lv_obj_set_x(image_117, 59);
        lv_obj_set_y(image_117, 50);
        lv_obj_set_width(image_117, 4);
        lv_obj_set_height(image_117, 4);
        lv_image_set_src(image_117, image_vec_6_2723);

        lv_obj_t * image_118 = image_create(container_4);
        lv_obj_set_x(image_118, 67);
        lv_obj_set_y(image_118, 50);
        lv_obj_set_width(image_118, 4);
        lv_obj_set_height(image_118, 4);
        lv_image_set_src(image_118, image_vec_6_2724);

        lv_obj_t * image_119 = image_create(container_4);
        lv_obj_set_x(image_119, 71);
        lv_obj_set_y(image_119, 50);
        lv_obj_set_width(image_119, 4);
        lv_obj_set_height(image_119, 4);
        lv_image_set_src(image_119, image_vec_6_2725);

        lv_obj_t * image_120 = image_create(container_4);
        lv_obj_set_x(image_120, 84);
        lv_obj_set_y(image_120, 50);
        lv_obj_set_width(image_120, 4);
        lv_obj_set_height(image_120, 4);
        lv_image_set_src(image_120, image_vec_6_2726);

        lv_obj_t * image_121 = image_create(container_4);
        lv_obj_set_x(image_121, 88);
        lv_obj_set_y(image_121, 50);
        lv_obj_set_width(image_121, 4);
        lv_obj_set_height(image_121, 4);
        lv_image_set_src(image_121, image_vec_6_2727);

        lv_obj_t * image_122 = image_create(container_4);
        lv_obj_set_x(image_122, 101);
        lv_obj_set_y(image_122, 50);
        lv_obj_set_width(image_122, 4);
        lv_obj_set_height(image_122, 4);
        lv_image_set_src(image_122, image_vec_6_2728);

        lv_obj_t * image_123 = image_create(container_4);
        lv_obj_set_x(image_123, 105);
        lv_obj_set_y(image_123, 50);
        lv_obj_set_width(image_123, 4);
        lv_obj_set_height(image_123, 4);
        lv_image_set_src(image_123, image_vec_6_2729);

        lv_obj_t * image_124 = image_create(container_4);
        lv_obj_set_x(image_124, 0);
        lv_obj_set_y(image_124, 55);
        lv_obj_set_width(image_124, 4);
        lv_obj_set_height(image_124, 4);
        lv_image_set_src(image_124, image_vec_6_2730);

        lv_obj_t * image_125 = image_create(container_4);
        lv_obj_set_x(image_125, 8);
        lv_obj_set_y(image_125, 55);
        lv_obj_set_width(image_125, 4);
        lv_obj_set_height(image_125, 4);
        lv_image_set_src(image_125, image_vec_6_2731);

        lv_obj_t * image_126 = image_create(container_4);
        lv_obj_set_x(image_126, 13);
        lv_obj_set_y(image_126, 55);
        lv_obj_set_width(image_126, 4);
        lv_obj_set_height(image_126, 4);
        lv_image_set_src(image_126, image_vec_6_2732);

        lv_obj_t * image_127 = image_create(container_4);
        lv_obj_set_x(image_127, 17);
        lv_obj_set_y(image_127, 55);
        lv_obj_set_width(image_127, 4);
        lv_obj_set_height(image_127, 4);
        lv_image_set_src(image_127, image_vec_6_2733);

        lv_obj_t * image_128 = image_create(container_4);
        lv_obj_set_x(image_128, 21);
        lv_obj_set_y(image_128, 55);
        lv_obj_set_width(image_128, 4);
        lv_obj_set_height(image_128, 4);
        lv_image_set_src(image_128, image_vec_6_2734);

        lv_obj_t * image_129 = image_create(container_4);
        lv_obj_set_x(image_129, 34);
        lv_obj_set_y(image_129, 55);
        lv_obj_set_width(image_129, 4);
        lv_obj_set_height(image_129, 4);
        lv_image_set_src(image_129, image_vec_6_2735);

        lv_obj_t * image_130 = image_create(container_4);
        lv_obj_set_x(image_130, 38);
        lv_obj_set_y(image_130, 55);
        lv_obj_set_width(image_130, 4);
        lv_obj_set_height(image_130, 4);
        lv_image_set_src(image_130, image_vec_6_2736);

        lv_obj_t * image_131 = image_create(container_4);
        lv_obj_set_x(image_131, 67);
        lv_obj_set_y(image_131, 55);
        lv_obj_set_width(image_131, 4);
        lv_obj_set_height(image_131, 4);
        lv_image_set_src(image_131, image_vec_6_2737);

        lv_obj_t * image_132 = image_create(container_4);
        lv_obj_set_x(image_132, 76);
        lv_obj_set_y(image_132, 55);
        lv_obj_set_width(image_132, 4);
        lv_obj_set_height(image_132, 4);
        lv_image_set_src(image_132, image_vec_6_2738);

        lv_obj_t * image_133 = image_create(container_4);
        lv_obj_set_x(image_133, 97);
        lv_obj_set_y(image_133, 55);
        lv_obj_set_width(image_133, 4);
        lv_obj_set_height(image_133, 4);
        lv_image_set_src(image_133, image_vec_6_2739);

        lv_obj_t * image_134 = image_create(container_4);
        lv_obj_set_x(image_134, 101);
        lv_obj_set_y(image_134, 55);
        lv_obj_set_width(image_134, 4);
        lv_obj_set_height(image_134, 4);
        lv_image_set_src(image_134, image_vec_6_2740);

        lv_obj_t * image_135 = image_create(container_4);
        lv_obj_set_x(image_135, 109);
        lv_obj_set_y(image_135, 55);
        lv_obj_set_width(image_135, 4);
        lv_obj_set_height(image_135, 4);
        lv_image_set_src(image_135, image_vec_6_2741);

        lv_obj_t * image_136 = image_create(container_4);
        lv_obj_set_x(image_136, 118);
        lv_obj_set_y(image_136, 55);
        lv_obj_set_width(image_136, 4);
        lv_obj_set_height(image_136, 4);
        lv_image_set_src(image_136, image_vec_6_2742);

        lv_obj_t * image_137 = image_create(container_4);
        lv_obj_set_x(image_137, 4);
        lv_obj_set_y(image_137, 59);
        lv_obj_set_width(image_137, 4);
        lv_obj_set_height(image_137, 4);
        lv_image_set_src(image_137, image_vec_6_2743);

        lv_obj_t * image_138 = image_create(container_4);
        lv_obj_set_x(image_138, 13);
        lv_obj_set_y(image_138, 59);
        lv_obj_set_width(image_138, 4);
        lv_obj_set_height(image_138, 4);
        lv_image_set_src(image_138, image_vec_6_2744);

        lv_obj_t * image_139 = image_create(container_4);
        lv_obj_set_x(image_139, 25);
        lv_obj_set_y(image_139, 59);
        lv_obj_set_width(image_139, 4);
        lv_obj_set_height(image_139, 4);
        lv_image_set_src(image_139, image_vec_6_2745);

        lv_obj_t * image_140 = image_create(container_4);
        lv_obj_set_x(image_140, 29);
        lv_obj_set_y(image_140, 59);
        lv_obj_set_width(image_140, 4);
        lv_obj_set_height(image_140, 4);
        lv_image_set_src(image_140, image_vec_6_2746);

        lv_obj_t * image_141 = image_create(container_4);
        lv_obj_set_x(image_141, 34);
        lv_obj_set_y(image_141, 59);
        lv_obj_set_width(image_141, 4);
        lv_obj_set_height(image_141, 4);
        lv_image_set_src(image_141, image_vec_6_2747);

        lv_obj_t * image_142 = image_create(container_4);
        lv_obj_set_x(image_142, 50);
        lv_obj_set_y(image_142, 59);
        lv_obj_set_width(image_142, 4);
        lv_obj_set_height(image_142, 4);
        lv_image_set_src(image_142, image_vec_6_2748);

        lv_obj_t * image_143 = image_create(container_4);
        lv_obj_set_x(image_143, 59);
        lv_obj_set_y(image_143, 59);
        lv_obj_set_width(image_143, 4);
        lv_obj_set_height(image_143, 4);
        lv_image_set_src(image_143, image_vec_6_2749);

        lv_obj_t * image_144 = image_create(container_4);
        lv_obj_set_x(image_144, 63);
        lv_obj_set_y(image_144, 59);
        lv_obj_set_width(image_144, 4);
        lv_obj_set_height(image_144, 4);
        lv_image_set_src(image_144, image_vec_6_2750);

        lv_obj_t * image_145 = image_create(container_4);
        lv_obj_set_x(image_145, 71);
        lv_obj_set_y(image_145, 59);
        lv_obj_set_width(image_145, 4);
        lv_obj_set_height(image_145, 4);
        lv_image_set_src(image_145, image_vec_6_2751);

        lv_obj_t * image_146 = image_create(container_4);
        lv_obj_set_x(image_146, 92);
        lv_obj_set_y(image_146, 59);
        lv_obj_set_width(image_146, 4);
        lv_obj_set_height(image_146, 4);
        lv_image_set_src(image_146, image_vec_6_2752);

        lv_obj_t * image_147 = image_create(container_4);
        lv_obj_set_x(image_147, 97);
        lv_obj_set_y(image_147, 59);
        lv_obj_set_width(image_147, 4);
        lv_obj_set_height(image_147, 4);
        lv_image_set_src(image_147, image_vec_6_2753);

        lv_obj_t * image_148 = image_create(container_4);
        lv_obj_set_x(image_148, 118);
        lv_obj_set_y(image_148, 59);
        lv_obj_set_width(image_148, 4);
        lv_obj_set_height(image_148, 4);
        lv_image_set_src(image_148, image_vec_6_2754);

        lv_obj_t * image_149 = image_create(container_4);
        lv_obj_set_x(image_149, 0);
        lv_obj_set_y(image_149, 63);
        lv_obj_set_width(image_149, 4);
        lv_obj_set_height(image_149, 4);
        lv_image_set_src(image_149, image_vec_6_2755);

        lv_obj_t * image_150 = image_create(container_4);
        lv_obj_set_x(image_150, 4);
        lv_obj_set_y(image_150, 63);
        lv_obj_set_width(image_150, 4);
        lv_obj_set_height(image_150, 4);
        lv_image_set_src(image_150, image_vec_6_2756);

        lv_obj_t * image_151 = image_create(container_4);
        lv_obj_set_x(image_151, 8);
        lv_obj_set_y(image_151, 63);
        lv_obj_set_width(image_151, 4);
        lv_obj_set_height(image_151, 4);
        lv_image_set_src(image_151, image_vec_6_2757);

        lv_obj_t * image_152 = image_create(container_4);
        lv_obj_set_x(image_152, 13);
        lv_obj_set_y(image_152, 63);
        lv_obj_set_width(image_152, 4);
        lv_obj_set_height(image_152, 4);
        lv_image_set_src(image_152, image_vec_6_2758);

        lv_obj_t * image_153 = image_create(container_4);
        lv_obj_set_x(image_153, 17);
        lv_obj_set_y(image_153, 63);
        lv_obj_set_width(image_153, 4);
        lv_obj_set_height(image_153, 4);
        lv_image_set_src(image_153, image_vec_6_2759);

        lv_obj_t * image_154 = image_create(container_4);
        lv_obj_set_x(image_154, 21);
        lv_obj_set_y(image_154, 63);
        lv_obj_set_width(image_154, 4);
        lv_obj_set_height(image_154, 4);
        lv_image_set_src(image_154, image_vec_6_2760);

        lv_obj_t * image_155 = image_create(container_4);
        lv_obj_set_x(image_155, 34);
        lv_obj_set_y(image_155, 63);
        lv_obj_set_width(image_155, 4);
        lv_obj_set_height(image_155, 4);
        lv_image_set_src(image_155, image_vec_6_2761);

        lv_obj_t * image_156 = image_create(container_4);
        lv_obj_set_x(image_156, 38);
        lv_obj_set_y(image_156, 63);
        lv_obj_set_width(image_156, 4);
        lv_obj_set_height(image_156, 4);
        lv_image_set_src(image_156, image_vec_6_2762);

        lv_obj_t * image_157 = image_create(container_4);
        lv_obj_set_x(image_157, 42);
        lv_obj_set_y(image_157, 63);
        lv_obj_set_width(image_157, 4);
        lv_obj_set_height(image_157, 4);
        lv_image_set_src(image_157, image_vec_6_2763);

        lv_obj_t * image_158 = image_create(container_4);
        lv_obj_set_x(image_158, 50);
        lv_obj_set_y(image_158, 63);
        lv_obj_set_width(image_158, 4);
        lv_obj_set_height(image_158, 4);
        lv_image_set_src(image_158, image_vec_6_2764);

        lv_obj_t * image_159 = image_create(container_4);
        lv_obj_set_x(image_159, 55);
        lv_obj_set_y(image_159, 63);
        lv_obj_set_width(image_159, 4);
        lv_obj_set_height(image_159, 4);
        lv_image_set_src(image_159, image_vec_6_2765);

        lv_obj_t * image_160 = image_create(container_4);
        lv_obj_set_x(image_160, 67);
        lv_obj_set_y(image_160, 63);
        lv_obj_set_width(image_160, 4);
        lv_obj_set_height(image_160, 4);
        lv_image_set_src(image_160, image_vec_6_2766);

        lv_obj_t * image_161 = image_create(container_4);
        lv_obj_set_x(image_161, 71);
        lv_obj_set_y(image_161, 63);
        lv_obj_set_width(image_161, 4);
        lv_obj_set_height(image_161, 4);
        lv_image_set_src(image_161, image_vec_6_2767);

        lv_obj_t * image_162 = image_create(container_4);
        lv_obj_set_x(image_162, 76);
        lv_obj_set_y(image_162, 63);
        lv_obj_set_width(image_162, 4);
        lv_obj_set_height(image_162, 4);
        lv_image_set_src(image_162, image_vec_6_2768);

        lv_obj_t * image_163 = image_create(container_4);
        lv_obj_set_x(image_163, 80);
        lv_obj_set_y(image_163, 63);
        lv_obj_set_width(image_163, 4);
        lv_obj_set_height(image_163, 4);
        lv_image_set_src(image_163, image_vec_6_2769);

        lv_obj_t * image_164 = image_create(container_4);
        lv_obj_set_x(image_164, 84);
        lv_obj_set_y(image_164, 63);
        lv_obj_set_width(image_164, 4);
        lv_obj_set_height(image_164, 4);
        lv_image_set_src(image_164, image_vec_6_2770);

        lv_obj_t * image_165 = image_create(container_4);
        lv_obj_set_x(image_165, 88);
        lv_obj_set_y(image_165, 63);
        lv_obj_set_width(image_165, 4);
        lv_obj_set_height(image_165, 4);
        lv_image_set_src(image_165, image_vec_6_2771);

        lv_obj_t * image_166 = image_create(container_4);
        lv_obj_set_x(image_166, 92);
        lv_obj_set_y(image_166, 63);
        lv_obj_set_width(image_166, 4);
        lv_obj_set_height(image_166, 4);
        lv_image_set_src(image_166, image_vec_6_2772);

        lv_obj_t * image_167 = image_create(container_4);
        lv_obj_set_x(image_167, 105);
        lv_obj_set_y(image_167, 63);
        lv_obj_set_width(image_167, 4);
        lv_obj_set_height(image_167, 4);
        lv_image_set_src(image_167, image_vec_6_2773);

        lv_obj_t * image_168 = image_create(container_4);
        lv_obj_set_x(image_168, 113);
        lv_obj_set_y(image_168, 63);
        lv_obj_set_width(image_168, 4);
        lv_obj_set_height(image_168, 4);
        lv_image_set_src(image_168, image_vec_6_2774);

        lv_obj_t * image_169 = image_create(container_4);
        lv_obj_set_x(image_169, 118);
        lv_obj_set_y(image_169, 63);
        lv_obj_set_width(image_169, 4);
        lv_obj_set_height(image_169, 4);
        lv_image_set_src(image_169, image_vec_6_2775);

        lv_obj_t * image_170 = image_create(container_4);
        lv_obj_set_x(image_170, 0);
        lv_obj_set_y(image_170, 67);
        lv_obj_set_width(image_170, 4);
        lv_obj_set_height(image_170, 4);
        lv_image_set_src(image_170, image_vec_6_2776);

        lv_obj_t * image_171 = image_create(container_4);
        lv_obj_set_x(image_171, 4);
        lv_obj_set_y(image_171, 67);
        lv_obj_set_width(image_171, 4);
        lv_obj_set_height(image_171, 4);
        lv_image_set_src(image_171, image_vec_6_2777);

        lv_obj_t * image_172 = image_create(container_4);
        lv_obj_set_x(image_172, 8);
        lv_obj_set_y(image_172, 67);
        lv_obj_set_width(image_172, 4);
        lv_obj_set_height(image_172, 4);
        lv_image_set_src(image_172, image_vec_6_2778);

        lv_obj_t * image_173 = image_create(container_4);
        lv_obj_set_x(image_173, 21);
        lv_obj_set_y(image_173, 67);
        lv_obj_set_width(image_173, 4);
        lv_obj_set_height(image_173, 4);
        lv_image_set_src(image_173, image_vec_6_2779);

        lv_obj_t * image_174 = image_create(container_4);
        lv_obj_set_x(image_174, 25);
        lv_obj_set_y(image_174, 67);
        lv_obj_set_width(image_174, 4);
        lv_obj_set_height(image_174, 4);
        lv_image_set_src(image_174, image_vec_6_2780);

        lv_obj_t * image_175 = image_create(container_4);
        lv_obj_set_x(image_175, 29);
        lv_obj_set_y(image_175, 67);
        lv_obj_set_width(image_175, 4);
        lv_obj_set_height(image_175, 4);
        lv_image_set_src(image_175, image_vec_6_2781);

        lv_obj_t * image_176 = image_create(container_4);
        lv_obj_set_x(image_176, 34);
        lv_obj_set_y(image_176, 67);
        lv_obj_set_width(image_176, 4);
        lv_obj_set_height(image_176, 4);
        lv_image_set_src(image_176, image_vec_6_2782);

        lv_obj_t * image_177 = image_create(container_4);
        lv_obj_set_x(image_177, 38);
        lv_obj_set_y(image_177, 67);
        lv_obj_set_width(image_177, 4);
        lv_obj_set_height(image_177, 4);
        lv_image_set_src(image_177, image_vec_6_2783);

        lv_obj_t * image_178 = image_create(container_4);
        lv_obj_set_x(image_178, 42);
        lv_obj_set_y(image_178, 67);
        lv_obj_set_width(image_178, 4);
        lv_obj_set_height(image_178, 4);
        lv_image_set_src(image_178, image_vec_6_2784);

        lv_obj_t * image_179 = image_create(container_4);
        lv_obj_set_x(image_179, 46);
        lv_obj_set_y(image_179, 67);
        lv_obj_set_width(image_179, 4);
        lv_obj_set_height(image_179, 4);
        lv_image_set_src(image_179, image_vec_6_2785);

        lv_obj_t * image_180 = image_create(container_4);
        lv_obj_set_x(image_180, 50);
        lv_obj_set_y(image_180, 67);
        lv_obj_set_width(image_180, 4);
        lv_obj_set_height(image_180, 4);
        lv_image_set_src(image_180, image_vec_6_2786);

        lv_obj_t * image_181 = image_create(container_4);
        lv_obj_set_x(image_181, 55);
        lv_obj_set_y(image_181, 67);
        lv_obj_set_width(image_181, 4);
        lv_obj_set_height(image_181, 4);
        lv_image_set_src(image_181, image_vec_6_2787);

        lv_obj_t * image_182 = image_create(container_4);
        lv_obj_set_x(image_182, 59);
        lv_obj_set_y(image_182, 67);
        lv_obj_set_width(image_182, 4);
        lv_obj_set_height(image_182, 4);
        lv_image_set_src(image_182, image_vec_6_2788);

        lv_obj_t * image_183 = image_create(container_4);
        lv_obj_set_x(image_183, 63);
        lv_obj_set_y(image_183, 67);
        lv_obj_set_width(image_183, 4);
        lv_obj_set_height(image_183, 4);
        lv_image_set_src(image_183, image_vec_6_2789);

        lv_obj_t * image_184 = image_create(container_4);
        lv_obj_set_x(image_184, 76);
        lv_obj_set_y(image_184, 67);
        lv_obj_set_width(image_184, 4);
        lv_obj_set_height(image_184, 4);
        lv_image_set_src(image_184, image_vec_6_2790);

        lv_obj_t * image_185 = image_create(container_4);
        lv_obj_set_x(image_185, 80);
        lv_obj_set_y(image_185, 67);
        lv_obj_set_width(image_185, 4);
        lv_obj_set_height(image_185, 4);
        lv_image_set_src(image_185, image_vec_6_2791);

        lv_obj_t * image_186 = image_create(container_4);
        lv_obj_set_x(image_186, 97);
        lv_obj_set_y(image_186, 67);
        lv_obj_set_width(image_186, 4);
        lv_obj_set_height(image_186, 4);
        lv_image_set_src(image_186, image_vec_6_2792);

        lv_obj_t * image_187 = image_create(container_4);
        lv_obj_set_x(image_187, 105);
        lv_obj_set_y(image_187, 67);
        lv_obj_set_width(image_187, 4);
        lv_obj_set_height(image_187, 4);
        lv_image_set_src(image_187, image_vec_6_2793);

        lv_obj_t * image_188 = image_create(container_4);
        lv_obj_set_x(image_188, 113);
        lv_obj_set_y(image_188, 67);
        lv_obj_set_width(image_188, 4);
        lv_obj_set_height(image_188, 4);
        lv_image_set_src(image_188, image_vec_6_2794);

        lv_obj_t * image_189 = image_create(container_4);
        lv_obj_set_x(image_189, 0);
        lv_obj_set_y(image_189, 71);
        lv_obj_set_width(image_189, 4);
        lv_obj_set_height(image_189, 4);
        lv_image_set_src(image_189, image_vec_6_2795);

        lv_obj_t * image_190 = image_create(container_4);
        lv_obj_set_x(image_190, 13);
        lv_obj_set_y(image_190, 71);
        lv_obj_set_width(image_190, 4);
        lv_obj_set_height(image_190, 4);
        lv_image_set_src(image_190, image_vec_6_2796);

        lv_obj_t * image_191 = image_create(container_4);
        lv_obj_set_x(image_191, 17);
        lv_obj_set_y(image_191, 71);
        lv_obj_set_width(image_191, 4);
        lv_obj_set_height(image_191, 4);
        lv_image_set_src(image_191, image_vec_6_2797);

        lv_obj_t * image_192 = image_create(container_4);
        lv_obj_set_x(image_192, 46);
        lv_obj_set_y(image_192, 71);
        lv_obj_set_width(image_192, 4);
        lv_obj_set_height(image_192, 4);
        lv_image_set_src(image_192, image_vec_6_2798);

        lv_obj_t * image_193 = image_create(container_4);
        lv_obj_set_x(image_193, 50);
        lv_obj_set_y(image_193, 71);
        lv_obj_set_width(image_193, 4);
        lv_obj_set_height(image_193, 4);
        lv_image_set_src(image_193, image_vec_6_2799);

        lv_obj_t * image_194 = image_create(container_4);
        lv_obj_set_x(image_194, 55);
        lv_obj_set_y(image_194, 71);
        lv_obj_set_width(image_194, 4);
        lv_obj_set_height(image_194, 4);
        lv_image_set_src(image_194, image_vec_6_2800);

        lv_obj_t * image_195 = image_create(container_4);
        lv_obj_set_x(image_195, 67);
        lv_obj_set_y(image_195, 71);
        lv_obj_set_width(image_195, 4);
        lv_obj_set_height(image_195, 4);
        lv_image_set_src(image_195, image_vec_6_2801);

        lv_obj_t * image_196 = image_create(container_4);
        lv_obj_set_x(image_196, 80);
        lv_obj_set_y(image_196, 71);
        lv_obj_set_width(image_196, 4);
        lv_obj_set_height(image_196, 4);
        lv_image_set_src(image_196, image_vec_6_2802);

        lv_obj_t * image_197 = image_create(container_4);
        lv_obj_set_x(image_197, 84);
        lv_obj_set_y(image_197, 71);
        lv_obj_set_width(image_197, 4);
        lv_obj_set_height(image_197, 4);
        lv_image_set_src(image_197, image_vec_6_2803);

        lv_obj_t * image_198 = image_create(container_4);
        lv_obj_set_x(image_198, 97);
        lv_obj_set_y(image_198, 71);
        lv_obj_set_width(image_198, 4);
        lv_obj_set_height(image_198, 4);
        lv_image_set_src(image_198, image_vec_6_2804);

        lv_obj_t * image_199 = image_create(container_4);
        lv_obj_set_x(image_199, 101);
        lv_obj_set_y(image_199, 71);
        lv_obj_set_width(image_199, 4);
        lv_obj_set_height(image_199, 4);
        lv_image_set_src(image_199, image_vec_6_2805);

        lv_obj_t * image_200 = image_create(container_4);
        lv_obj_set_x(image_200, 105);
        lv_obj_set_y(image_200, 71);
        lv_obj_set_width(image_200, 4);
        lv_obj_set_height(image_200, 4);
        lv_image_set_src(image_200, image_vec_6_2806);

        lv_obj_t * image_201 = image_create(container_4);
        lv_obj_set_x(image_201, 109);
        lv_obj_set_y(image_201, 71);
        lv_obj_set_width(image_201, 4);
        lv_obj_set_height(image_201, 4);
        lv_image_set_src(image_201, image_vec_6_2807);

        lv_obj_t * image_202 = image_create(container_4);
        lv_obj_set_x(image_202, 113);
        lv_obj_set_y(image_202, 71);
        lv_obj_set_width(image_202, 4);
        lv_obj_set_height(image_202, 4);
        lv_image_set_src(image_202, image_vec_6_2808);

        lv_obj_t * image_203 = image_create(container_4);
        lv_obj_set_x(image_203, 118);
        lv_obj_set_y(image_203, 71);
        lv_obj_set_width(image_203, 4);
        lv_obj_set_height(image_203, 4);
        lv_image_set_src(image_203, image_vec_6_2809);

        lv_obj_t * image_204 = image_create(container_4);
        lv_obj_set_x(image_204, 13);
        lv_obj_set_y(image_204, 76);
        lv_obj_set_width(image_204, 4);
        lv_obj_set_height(image_204, 4);
        lv_image_set_src(image_204, image_vec_6_2810);

        lv_obj_t * image_205 = image_create(container_4);
        lv_obj_set_x(image_205, 17);
        lv_obj_set_y(image_205, 76);
        lv_obj_set_width(image_205, 4);
        lv_obj_set_height(image_205, 4);
        lv_image_set_src(image_205, image_vec_6_2811);

        lv_obj_t * image_206 = image_create(container_4);
        lv_obj_set_x(image_206, 21);
        lv_obj_set_y(image_206, 76);
        lv_obj_set_width(image_206, 4);
        lv_obj_set_height(image_206, 4);
        lv_image_set_src(image_206, image_vec_6_2812);

        lv_obj_t * image_207 = image_create(container_4);
        lv_obj_set_x(image_207, 25);
        lv_obj_set_y(image_207, 76);
        lv_obj_set_width(image_207, 4);
        lv_obj_set_height(image_207, 4);
        lv_image_set_src(image_207, image_vec_6_2813);

        lv_obj_t * image_208 = image_create(container_4);
        lv_obj_set_x(image_208, 42);
        lv_obj_set_y(image_208, 76);
        lv_obj_set_width(image_208, 4);
        lv_obj_set_height(image_208, 4);
        lv_image_set_src(image_208, image_vec_6_2814);

        lv_obj_t * image_209 = image_create(container_4);
        lv_obj_set_x(image_209, 50);
        lv_obj_set_y(image_209, 76);
        lv_obj_set_width(image_209, 4);
        lv_obj_set_height(image_209, 4);
        lv_image_set_src(image_209, image_vec_6_2815);

        lv_obj_t * image_210 = image_create(container_4);
        lv_obj_set_x(image_210, 59);
        lv_obj_set_y(image_210, 76);
        lv_obj_set_width(image_210, 4);
        lv_obj_set_height(image_210, 4);
        lv_image_set_src(image_210, image_vec_6_2816);

        lv_obj_t * image_211 = image_create(container_4);
        lv_obj_set_x(image_211, 67);
        lv_obj_set_y(image_211, 76);
        lv_obj_set_width(image_211, 4);
        lv_obj_set_height(image_211, 4);
        lv_image_set_src(image_211, image_vec_6_2817);

        lv_obj_t * image_212 = image_create(container_4);
        lv_obj_set_x(image_212, 76);
        lv_obj_set_y(image_212, 76);
        lv_obj_set_width(image_212, 4);
        lv_obj_set_height(image_212, 4);
        lv_image_set_src(image_212, image_vec_6_2818);

        lv_obj_t * image_213 = image_create(container_4);
        lv_obj_set_x(image_213, 84);
        lv_obj_set_y(image_213, 76);
        lv_obj_set_width(image_213, 4);
        lv_obj_set_height(image_213, 4);
        lv_image_set_src(image_213, image_vec_6_2819);

        lv_obj_t * image_214 = image_create(container_4);
        lv_obj_set_x(image_214, 92);
        lv_obj_set_y(image_214, 76);
        lv_obj_set_width(image_214, 4);
        lv_obj_set_height(image_214, 4);
        lv_image_set_src(image_214, image_vec_6_2820);

        lv_obj_t * image_215 = image_create(container_4);
        lv_obj_set_x(image_215, 105);
        lv_obj_set_y(image_215, 76);
        lv_obj_set_width(image_215, 4);
        lv_obj_set_height(image_215, 4);
        lv_image_set_src(image_215, image_vec_6_2821);

        lv_obj_t * image_216 = image_create(container_4);
        lv_obj_set_x(image_216, 118);
        lv_obj_set_y(image_216, 76);
        lv_obj_set_width(image_216, 4);
        lv_obj_set_height(image_216, 4);
        lv_image_set_src(image_216, image_vec_6_2822);

        lv_obj_t * image_217 = image_create(container_4);
        lv_obj_set_x(image_217, 29);
        lv_obj_set_y(image_217, 80);
        lv_obj_set_width(image_217, 4);
        lv_obj_set_height(image_217, 4);
        lv_image_set_src(image_217, image_vec_6_2823);

        lv_obj_t * image_218 = image_create(container_4);
        lv_obj_set_x(image_218, 34);
        lv_obj_set_y(image_218, 80);
        lv_obj_set_width(image_218, 4);
        lv_obj_set_height(image_218, 4);
        lv_image_set_src(image_218, image_vec_6_2824);

        lv_obj_t * image_219 = image_create(container_4);
        lv_obj_set_x(image_219, 50);
        lv_obj_set_y(image_219, 80);
        lv_obj_set_width(image_219, 4);
        lv_obj_set_height(image_219, 4);
        lv_image_set_src(image_219, image_vec_6_2825);

        lv_obj_t * image_220 = image_create(container_4);
        lv_obj_set_x(image_220, 55);
        lv_obj_set_y(image_220, 80);
        lv_obj_set_width(image_220, 4);
        lv_obj_set_height(image_220, 4);
        lv_image_set_src(image_220, image_vec_6_2826);

        lv_obj_t * image_221 = image_create(container_4);
        lv_obj_set_x(image_221, 71);
        lv_obj_set_y(image_221, 80);
        lv_obj_set_width(image_221, 4);
        lv_obj_set_height(image_221, 4);
        lv_image_set_src(image_221, image_vec_6_2827);

        lv_obj_t * image_222 = image_create(container_4);
        lv_obj_set_x(image_222, 76);
        lv_obj_set_y(image_222, 80);
        lv_obj_set_width(image_222, 4);
        lv_obj_set_height(image_222, 4);
        lv_image_set_src(image_222, image_vec_6_2828);

        lv_obj_t * image_223 = image_create(container_4);
        lv_obj_set_x(image_223, 88);
        lv_obj_set_y(image_223, 80);
        lv_obj_set_width(image_223, 4);
        lv_obj_set_height(image_223, 4);
        lv_image_set_src(image_223, image_vec_6_2829);

        lv_obj_t * image_224 = image_create(container_4);
        lv_obj_set_x(image_224, 92);
        lv_obj_set_y(image_224, 80);
        lv_obj_set_width(image_224, 4);
        lv_obj_set_height(image_224, 4);
        lv_image_set_src(image_224, image_vec_6_2830);

        lv_obj_t * image_225 = image_create(container_4);
        lv_obj_set_x(image_225, 97);
        lv_obj_set_y(image_225, 80);
        lv_obj_set_width(image_225, 4);
        lv_obj_set_height(image_225, 4);
        lv_image_set_src(image_225, image_vec_6_2831);

        lv_obj_t * image_226 = image_create(container_4);
        lv_obj_set_x(image_226, 105);
        lv_obj_set_y(image_226, 80);
        lv_obj_set_width(image_226, 4);
        lv_obj_set_height(image_226, 4);
        lv_image_set_src(image_226, image_vec_6_2832);

        lv_obj_t * image_227 = image_create(container_4);
        lv_obj_set_x(image_227, 0);
        lv_obj_set_y(image_227, 84);
        lv_obj_set_width(image_227, 4);
        lv_obj_set_height(image_227, 4);
        lv_image_set_src(image_227, image_vec_6_2833);

        lv_obj_t * image_228 = image_create(container_4);
        lv_obj_set_x(image_228, 4);
        lv_obj_set_y(image_228, 84);
        lv_obj_set_width(image_228, 4);
        lv_obj_set_height(image_228, 4);
        lv_image_set_src(image_228, image_vec_6_2834);

        lv_obj_t * image_229 = image_create(container_4);
        lv_obj_set_x(image_229, 13);
        lv_obj_set_y(image_229, 84);
        lv_obj_set_width(image_229, 4);
        lv_obj_set_height(image_229, 4);
        lv_image_set_src(image_229, image_vec_6_2835);

        lv_obj_t * image_230 = image_create(container_4);
        lv_obj_set_x(image_230, 17);
        lv_obj_set_y(image_230, 84);
        lv_obj_set_width(image_230, 4);
        lv_obj_set_height(image_230, 4);
        lv_image_set_src(image_230, image_vec_6_2836);

        lv_obj_t * image_231 = image_create(container_4);
        lv_obj_set_x(image_231, 25);
        lv_obj_set_y(image_231, 84);
        lv_obj_set_width(image_231, 4);
        lv_obj_set_height(image_231, 4);
        lv_image_set_src(image_231, image_vec_6_2837);

        lv_obj_t * image_232 = image_create(container_4);
        lv_obj_set_x(image_232, 34);
        lv_obj_set_y(image_232, 84);
        lv_obj_set_width(image_232, 4);
        lv_obj_set_height(image_232, 4);
        lv_image_set_src(image_232, image_vec_6_2838);

        lv_obj_t * image_233 = image_create(container_4);
        lv_obj_set_x(image_233, 38);
        lv_obj_set_y(image_233, 84);
        lv_obj_set_width(image_233, 4);
        lv_obj_set_height(image_233, 4);
        lv_image_set_src(image_233, image_vec_6_2839);

        lv_obj_t * image_234 = image_create(container_4);
        lv_obj_set_x(image_234, 42);
        lv_obj_set_y(image_234, 84);
        lv_obj_set_width(image_234, 4);
        lv_obj_set_height(image_234, 4);
        lv_image_set_src(image_234, image_vec_6_2840);

        lv_obj_t * image_235 = image_create(container_4);
        lv_obj_set_x(image_235, 63);
        lv_obj_set_y(image_235, 84);
        lv_obj_set_width(image_235, 4);
        lv_obj_set_height(image_235, 4);
        lv_image_set_src(image_235, image_vec_6_2841);

        lv_obj_t * image_236 = image_create(container_4);
        lv_obj_set_x(image_236, 71);
        lv_obj_set_y(image_236, 84);
        lv_obj_set_width(image_236, 4);
        lv_obj_set_height(image_236, 4);
        lv_image_set_src(image_236, image_vec_6_2842);

        lv_obj_t * image_237 = image_create(container_4);
        lv_obj_set_x(image_237, 80);
        lv_obj_set_y(image_237, 84);
        lv_obj_set_width(image_237, 4);
        lv_obj_set_height(image_237, 4);
        lv_image_set_src(image_237, image_vec_6_2843);

        lv_obj_t * image_238 = image_create(container_4);
        lv_obj_set_x(image_238, 84);
        lv_obj_set_y(image_238, 84);
        lv_obj_set_width(image_238, 4);
        lv_obj_set_height(image_238, 4);
        lv_image_set_src(image_238, image_vec_6_2844);

        lv_obj_t * image_239 = image_create(container_4);
        lv_obj_set_x(image_239, 88);
        lv_obj_set_y(image_239, 84);
        lv_obj_set_width(image_239, 4);
        lv_obj_set_height(image_239, 4);
        lv_image_set_src(image_239, image_vec_6_2845);

        lv_obj_t * image_240 = image_create(container_4);
        lv_obj_set_x(image_240, 92);
        lv_obj_set_y(image_240, 84);
        lv_obj_set_width(image_240, 4);
        lv_obj_set_height(image_240, 4);
        lv_image_set_src(image_240, image_vec_6_2846);

        lv_obj_t * image_241 = image_create(container_4);
        lv_obj_set_x(image_241, 97);
        lv_obj_set_y(image_241, 84);
        lv_obj_set_width(image_241, 4);
        lv_obj_set_height(image_241, 4);
        lv_image_set_src(image_241, image_vec_6_2847);

        lv_obj_t * image_242 = image_create(container_4);
        lv_obj_set_x(image_242, 101);
        lv_obj_set_y(image_242, 84);
        lv_obj_set_width(image_242, 4);
        lv_obj_set_height(image_242, 4);
        lv_image_set_src(image_242, image_vec_6_2848);

        lv_obj_t * image_243 = image_create(container_4);
        lv_obj_set_x(image_243, 105);
        lv_obj_set_y(image_243, 84);
        lv_obj_set_width(image_243, 4);
        lv_obj_set_height(image_243, 4);
        lv_image_set_src(image_243, image_vec_6_2849);

        lv_obj_t * image_244 = image_create(container_4);
        lv_obj_set_x(image_244, 113);
        lv_obj_set_y(image_244, 84);
        lv_obj_set_width(image_244, 4);
        lv_obj_set_height(image_244, 4);
        lv_image_set_src(image_244, image_vec_6_2850);

        lv_obj_t * image_245 = image_create(container_4);
        lv_obj_set_x(image_245, 34);
        lv_obj_set_y(image_245, 88);
        lv_obj_set_width(image_245, 4);
        lv_obj_set_height(image_245, 4);
        lv_image_set_src(image_245, image_vec_6_2851);

        lv_obj_t * image_246 = image_create(container_4);
        lv_obj_set_x(image_246, 38);
        lv_obj_set_y(image_246, 88);
        lv_obj_set_width(image_246, 4);
        lv_obj_set_height(image_246, 4);
        lv_image_set_src(image_246, image_vec_6_2852);

        lv_obj_t * image_247 = image_create(container_4);
        lv_obj_set_x(image_247, 50);
        lv_obj_set_y(image_247, 88);
        lv_obj_set_width(image_247, 4);
        lv_obj_set_height(image_247, 4);
        lv_image_set_src(image_247, image_vec_6_2853);

        lv_obj_t * image_248 = image_create(container_4);
        lv_obj_set_x(image_248, 55);
        lv_obj_set_y(image_248, 88);
        lv_obj_set_width(image_248, 4);
        lv_obj_set_height(image_248, 4);
        lv_image_set_src(image_248, image_vec_6_2854);

        lv_obj_t * image_249 = image_create(container_4);
        lv_obj_set_x(image_249, 63);
        lv_obj_set_y(image_249, 88);
        lv_obj_set_width(image_249, 4);
        lv_obj_set_height(image_249, 4);
        lv_image_set_src(image_249, image_vec_6_2855);

        lv_obj_t * image_250 = image_create(container_4);
        lv_obj_set_x(image_250, 67);
        lv_obj_set_y(image_250, 88);
        lv_obj_set_width(image_250, 4);
        lv_obj_set_height(image_250, 4);
        lv_image_set_src(image_250, image_vec_6_2856);

        lv_obj_t * image_251 = image_create(container_4);
        lv_obj_set_x(image_251, 71);
        lv_obj_set_y(image_251, 88);
        lv_obj_set_width(image_251, 4);
        lv_obj_set_height(image_251, 4);
        lv_image_set_src(image_251, image_vec_6_2857);

        lv_obj_t * image_252 = image_create(container_4);
        lv_obj_set_x(image_252, 76);
        lv_obj_set_y(image_252, 88);
        lv_obj_set_width(image_252, 4);
        lv_obj_set_height(image_252, 4);
        lv_image_set_src(image_252, image_vec_6_2858);

        lv_obj_t * image_253 = image_create(container_4);
        lv_obj_set_x(image_253, 80);
        lv_obj_set_y(image_253, 88);
        lv_obj_set_width(image_253, 4);
        lv_obj_set_height(image_253, 4);
        lv_image_set_src(image_253, image_vec_6_2859);

        lv_obj_t * image_254 = image_create(container_4);
        lv_obj_set_x(image_254, 84);
        lv_obj_set_y(image_254, 88);
        lv_obj_set_width(image_254, 4);
        lv_obj_set_height(image_254, 4);
        lv_image_set_src(image_254, image_vec_6_2860);

        lv_obj_t * image_255 = image_create(container_4);
        lv_obj_set_x(image_255, 101);
        lv_obj_set_y(image_255, 88);
        lv_obj_set_width(image_255, 4);
        lv_obj_set_height(image_255, 4);
        lv_image_set_src(image_255, image_vec_6_2861);

        lv_obj_t * image_256 = image_create(container_4);
        lv_obj_set_x(image_256, 109);
        lv_obj_set_y(image_256, 88);
        lv_obj_set_width(image_256, 4);
        lv_obj_set_height(image_256, 4);
        lv_image_set_src(image_256, image_vec_6_2862);

        lv_obj_t * image_257 = image_create(container_4);
        lv_obj_set_x(image_257, 118);
        lv_obj_set_y(image_257, 88);
        lv_obj_set_width(image_257, 4);
        lv_obj_set_height(image_257, 4);
        lv_image_set_src(image_257, image_vec_6_2863);

        lv_obj_t * image_258 = image_create(container_4);
        lv_obj_set_x(image_258, 42);
        lv_obj_set_y(image_258, 92);
        lv_obj_set_width(image_258, 4);
        lv_obj_set_height(image_258, 4);
        lv_image_set_src(image_258, image_vec_6_2864);

        lv_obj_t * image_259 = image_create(container_4);
        lv_obj_set_x(image_259, 50);
        lv_obj_set_y(image_259, 92);
        lv_obj_set_width(image_259, 4);
        lv_obj_set_height(image_259, 4);
        lv_image_set_src(image_259, image_vec_6_2865);

        lv_obj_t * image_260 = image_create(container_4);
        lv_obj_set_x(image_260, 59);
        lv_obj_set_y(image_260, 92);
        lv_obj_set_width(image_260, 4);
        lv_obj_set_height(image_260, 4);
        lv_image_set_src(image_260, image_vec_6_2866);

        lv_obj_t * image_261 = image_create(container_4);
        lv_obj_set_x(image_261, 63);
        lv_obj_set_y(image_261, 92);
        lv_obj_set_width(image_261, 4);
        lv_obj_set_height(image_261, 4);
        lv_image_set_src(image_261, image_vec_6_2867);

        lv_obj_t * image_262 = image_create(container_4);
        lv_obj_set_x(image_262, 76);
        lv_obj_set_y(image_262, 92);
        lv_obj_set_width(image_262, 4);
        lv_obj_set_height(image_262, 4);
        lv_image_set_src(image_262, image_vec_6_2868);

        lv_obj_t * image_263 = image_create(container_4);
        lv_obj_set_x(image_263, 80);
        lv_obj_set_y(image_263, 92);
        lv_obj_set_width(image_263, 4);
        lv_obj_set_height(image_263, 4);
        lv_image_set_src(image_263, image_vec_6_2869);

        lv_obj_t * image_264 = image_create(container_4);
        lv_obj_set_x(image_264, 84);
        lv_obj_set_y(image_264, 92);
        lv_obj_set_width(image_264, 4);
        lv_obj_set_height(image_264, 4);
        lv_image_set_src(image_264, image_vec_6_2870);

        lv_obj_t * image_265 = image_create(container_4);
        lv_obj_set_x(image_265, 92);
        lv_obj_set_y(image_265, 92);
        lv_obj_set_width(image_265, 4);
        lv_obj_set_height(image_265, 4);
        lv_image_set_src(image_265, image_vec_6_2871);

        lv_obj_t * image_266 = image_create(container_4);
        lv_obj_set_x(image_266, 101);
        lv_obj_set_y(image_266, 92);
        lv_obj_set_width(image_266, 4);
        lv_obj_set_height(image_266, 4);
        lv_image_set_src(image_266, image_vec_6_2872);

        lv_obj_t * image_267 = image_create(container_4);
        lv_obj_set_x(image_267, 109);
        lv_obj_set_y(image_267, 92);
        lv_obj_set_width(image_267, 4);
        lv_obj_set_height(image_267, 4);
        lv_image_set_src(image_267, image_vec_6_2873);

        lv_obj_t * image_268 = image_create(container_4);
        lv_obj_set_x(image_268, 118);
        lv_obj_set_y(image_268, 92);
        lv_obj_set_width(image_268, 4);
        lv_obj_set_height(image_268, 4);
        lv_image_set_src(image_268, image_vec_6_2874);

        lv_obj_t * image_269 = image_create(container_4);
        lv_obj_set_x(image_269, 42);
        lv_obj_set_y(image_269, 97);
        lv_obj_set_width(image_269, 4);
        lv_obj_set_height(image_269, 4);
        lv_image_set_src(image_269, image_vec_6_2875);

        lv_obj_t * image_270 = image_create(container_4);
        lv_obj_set_x(image_270, 46);
        lv_obj_set_y(image_270, 97);
        lv_obj_set_width(image_270, 4);
        lv_obj_set_height(image_270, 4);
        lv_image_set_src(image_270, image_vec_6_2876);

        lv_obj_t * image_271 = image_create(container_4);
        lv_obj_set_x(image_271, 67);
        lv_obj_set_y(image_271, 97);
        lv_obj_set_width(image_271, 4);
        lv_obj_set_height(image_271, 4);
        lv_image_set_src(image_271, image_vec_6_2877);

        lv_obj_t * image_272 = image_create(container_4);
        lv_obj_set_x(image_272, 80);
        lv_obj_set_y(image_272, 97);
        lv_obj_set_width(image_272, 4);
        lv_obj_set_height(image_272, 4);
        lv_image_set_src(image_272, image_vec_6_2878);

        lv_obj_t * image_273 = image_create(container_4);
        lv_obj_set_x(image_273, 84);
        lv_obj_set_y(image_273, 97);
        lv_obj_set_width(image_273, 4);
        lv_obj_set_height(image_273, 4);
        lv_image_set_src(image_273, image_vec_6_2879);

        lv_obj_t * image_274 = image_create(container_4);
        lv_obj_set_x(image_274, 101);
        lv_obj_set_y(image_274, 97);
        lv_obj_set_width(image_274, 4);
        lv_obj_set_height(image_274, 4);
        lv_image_set_src(image_274, image_vec_6_2880);

        lv_obj_t * image_275 = image_create(container_4);
        lv_obj_set_x(image_275, 105);
        lv_obj_set_y(image_275, 97);
        lv_obj_set_width(image_275, 4);
        lv_obj_set_height(image_275, 4);
        lv_image_set_src(image_275, image_vec_6_2881);

        lv_obj_t * image_276 = image_create(container_4);
        lv_obj_set_x(image_276, 34);
        lv_obj_set_y(image_276, 101);
        lv_obj_set_width(image_276, 4);
        lv_obj_set_height(image_276, 4);
        lv_image_set_src(image_276, image_vec_6_2882);

        lv_obj_t * image_277 = image_create(container_4);
        lv_obj_set_x(image_277, 38);
        lv_obj_set_y(image_277, 101);
        lv_obj_set_width(image_277, 4);
        lv_obj_set_height(image_277, 4);
        lv_image_set_src(image_277, image_vec_6_2883);

        lv_obj_t * image_278 = image_create(container_4);
        lv_obj_set_x(image_278, 46);
        lv_obj_set_y(image_278, 101);
        lv_obj_set_width(image_278, 4);
        lv_obj_set_height(image_278, 4);
        lv_image_set_src(image_278, image_vec_6_2884);

        lv_obj_t * image_279 = image_create(container_4);
        lv_obj_set_x(image_279, 50);
        lv_obj_set_y(image_279, 101);
        lv_obj_set_width(image_279, 4);
        lv_obj_set_height(image_279, 4);
        lv_image_set_src(image_279, image_vec_6_2885);

        lv_obj_t * image_280 = image_create(container_4);
        lv_obj_set_x(image_280, 59);
        lv_obj_set_y(image_280, 101);
        lv_obj_set_width(image_280, 4);
        lv_obj_set_height(image_280, 4);
        lv_image_set_src(image_280, image_vec_6_2886);

        lv_obj_t * image_281 = image_create(container_4);
        lv_obj_set_x(image_281, 67);
        lv_obj_set_y(image_281, 101);
        lv_obj_set_width(image_281, 4);
        lv_obj_set_height(image_281, 4);
        lv_image_set_src(image_281, image_vec_6_2887);

        lv_obj_t * image_282 = image_create(container_4);
        lv_obj_set_x(image_282, 80);
        lv_obj_set_y(image_282, 101);
        lv_obj_set_width(image_282, 4);
        lv_obj_set_height(image_282, 4);
        lv_image_set_src(image_282, image_vec_6_2888);

        lv_obj_t * image_283 = image_create(container_4);
        lv_obj_set_x(image_283, 84);
        lv_obj_set_y(image_283, 101);
        lv_obj_set_width(image_283, 4);
        lv_obj_set_height(image_283, 4);
        lv_image_set_src(image_283, image_vec_6_2889);

        lv_obj_t * image_284 = image_create(container_4);
        lv_obj_set_x(image_284, 88);
        lv_obj_set_y(image_284, 101);
        lv_obj_set_width(image_284, 4);
        lv_obj_set_height(image_284, 4);
        lv_image_set_src(image_284, image_vec_6_2890);

        lv_obj_t * image_285 = image_create(container_4);
        lv_obj_set_x(image_285, 92);
        lv_obj_set_y(image_285, 101);
        lv_obj_set_width(image_285, 4);
        lv_obj_set_height(image_285, 4);
        lv_image_set_src(image_285, image_vec_6_2891);

        lv_obj_t * image_286 = image_create(container_4);
        lv_obj_set_x(image_286, 97);
        lv_obj_set_y(image_286, 101);
        lv_obj_set_width(image_286, 4);
        lv_obj_set_height(image_286, 4);
        lv_image_set_src(image_286, image_vec_6_2892);

        lv_obj_t * image_287 = image_create(container_4);
        lv_obj_set_x(image_287, 101);
        lv_obj_set_y(image_287, 101);
        lv_obj_set_width(image_287, 4);
        lv_obj_set_height(image_287, 4);
        lv_image_set_src(image_287, image_vec_6_2893);

        lv_obj_t * image_288 = image_create(container_4);
        lv_obj_set_x(image_288, 105);
        lv_obj_set_y(image_288, 101);
        lv_obj_set_width(image_288, 4);
        lv_obj_set_height(image_288, 4);
        lv_image_set_src(image_288, image_vec_6_2894);

        lv_obj_t * image_289 = image_create(container_4);
        lv_obj_set_x(image_289, 109);
        lv_obj_set_y(image_289, 101);
        lv_obj_set_width(image_289, 4);
        lv_obj_set_height(image_289, 4);
        lv_image_set_src(image_289, image_vec_6_2895);

        lv_obj_t * image_290 = image_create(container_4);
        lv_obj_set_x(image_290, 113);
        lv_obj_set_y(image_290, 101);
        lv_obj_set_width(image_290, 4);
        lv_obj_set_height(image_290, 4);
        lv_image_set_src(image_290, image_vec_6_2896);

        lv_obj_t * image_291 = image_create(container_4);
        lv_obj_set_x(image_291, 38);
        lv_obj_set_y(image_291, 105);
        lv_obj_set_width(image_291, 4);
        lv_obj_set_height(image_291, 4);
        lv_image_set_src(image_291, image_vec_6_2897);

        lv_obj_t * image_292 = image_create(container_4);
        lv_obj_set_x(image_292, 42);
        lv_obj_set_y(image_292, 105);
        lv_obj_set_width(image_292, 4);
        lv_obj_set_height(image_292, 4);
        lv_image_set_src(image_292, image_vec_6_2898);

        lv_obj_t * image_293 = image_create(container_4);
        lv_obj_set_x(image_293, 50);
        lv_obj_set_y(image_293, 105);
        lv_obj_set_width(image_293, 4);
        lv_obj_set_height(image_293, 4);
        lv_image_set_src(image_293, image_vec_6_2899);

        lv_obj_t * image_294 = image_create(container_4);
        lv_obj_set_x(image_294, 59);
        lv_obj_set_y(image_294, 105);
        lv_obj_set_width(image_294, 4);
        lv_obj_set_height(image_294, 4);
        lv_image_set_src(image_294, image_vec_6_2900);

        lv_obj_t * image_295 = image_create(container_4);
        lv_obj_set_x(image_295, 76);
        lv_obj_set_y(image_295, 105);
        lv_obj_set_width(image_295, 4);
        lv_obj_set_height(image_295, 4);
        lv_image_set_src(image_295, image_vec_6_2901);

        lv_obj_t * image_296 = image_create(container_4);
        lv_obj_set_x(image_296, 88);
        lv_obj_set_y(image_296, 105);
        lv_obj_set_width(image_296, 4);
        lv_obj_set_height(image_296, 4);
        lv_image_set_src(image_296, image_vec_6_2902);

        lv_obj_t * image_297 = image_create(container_4);
        lv_obj_set_x(image_297, 101);
        lv_obj_set_y(image_297, 105);
        lv_obj_set_width(image_297, 4);
        lv_obj_set_height(image_297, 4);
        lv_image_set_src(image_297, image_vec_6_2903);

        lv_obj_t * image_298 = image_create(container_4);
        lv_obj_set_x(image_298, 109);
        lv_obj_set_y(image_298, 105);
        lv_obj_set_width(image_298, 4);
        lv_obj_set_height(image_298, 4);
        lv_image_set_src(image_298, image_vec_6_2904);

        lv_obj_t * image_299 = image_create(container_4);
        lv_obj_set_x(image_299, 113);
        lv_obj_set_y(image_299, 105);
        lv_obj_set_width(image_299, 4);
        lv_obj_set_height(image_299, 4);
        lv_image_set_src(image_299, image_vec_6_2905);

        lv_obj_t * image_300 = image_create(container_4);
        lv_obj_set_x(image_300, 46);
        lv_obj_set_y(image_300, 109);
        lv_obj_set_width(image_300, 4);
        lv_obj_set_height(image_300, 4);
        lv_image_set_src(image_300, image_vec_6_2906);

        lv_obj_t * image_301 = image_create(container_4);
        lv_obj_set_x(image_301, 50);
        lv_obj_set_y(image_301, 109);
        lv_obj_set_width(image_301, 4);
        lv_obj_set_height(image_301, 4);
        lv_image_set_src(image_301, image_vec_6_2907);

        lv_obj_t * image_302 = image_create(container_4);
        lv_obj_set_x(image_302, 59);
        lv_obj_set_y(image_302, 109);
        lv_obj_set_width(image_302, 4);
        lv_obj_set_height(image_302, 4);
        lv_image_set_src(image_302, image_vec_6_2908);

        lv_obj_t * image_303 = image_create(container_4);
        lv_obj_set_x(image_303, 63);
        lv_obj_set_y(image_303, 109);
        lv_obj_set_width(image_303, 4);
        lv_obj_set_height(image_303, 4);
        lv_image_set_src(image_303, image_vec_6_2909);

        lv_obj_t * image_304 = image_create(container_4);
        lv_obj_set_x(image_304, 71);
        lv_obj_set_y(image_304, 109);
        lv_obj_set_width(image_304, 4);
        lv_obj_set_height(image_304, 4);
        lv_image_set_src(image_304, image_vec_6_2910);

        lv_obj_t * image_305 = image_create(container_4);
        lv_obj_set_x(image_305, 109);
        lv_obj_set_y(image_305, 109);
        lv_obj_set_width(image_305, 4);
        lv_obj_set_height(image_305, 4);
        lv_image_set_src(image_305, image_vec_6_2911);

        lv_obj_t * image_306 = image_create(container_4);
        lv_obj_set_x(image_306, 113);
        lv_obj_set_y(image_306, 109);
        lv_obj_set_width(image_306, 4);
        lv_obj_set_height(image_306, 4);
        lv_image_set_src(image_306, image_vec_6_2912);

        lv_obj_t * image_307 = image_create(container_4);
        lv_obj_set_x(image_307, 118);
        lv_obj_set_y(image_307, 109);
        lv_obj_set_width(image_307, 4);
        lv_obj_set_height(image_307, 4);
        lv_image_set_src(image_307, image_vec_6_2913);

        lv_obj_t * image_308 = image_create(container_4);
        lv_obj_set_x(image_308, 34);
        lv_obj_set_y(image_308, 113);
        lv_obj_set_width(image_308, 4);
        lv_obj_set_height(image_308, 4);
        lv_image_set_src(image_308, image_vec_6_2914);

        lv_obj_t * image_309 = image_create(container_4);
        lv_obj_set_x(image_309, 42);
        lv_obj_set_y(image_309, 113);
        lv_obj_set_width(image_309, 4);
        lv_obj_set_height(image_309, 4);
        lv_image_set_src(image_309, image_vec_6_2915);

        lv_obj_t * image_310 = image_create(container_4);
        lv_obj_set_x(image_310, 46);
        lv_obj_set_y(image_310, 113);
        lv_obj_set_width(image_310, 4);
        lv_obj_set_height(image_310, 4);
        lv_image_set_src(image_310, image_vec_6_2916);

        lv_obj_t * image_311 = image_create(container_4);
        lv_obj_set_x(image_311, 50);
        lv_obj_set_y(image_311, 113);
        lv_obj_set_width(image_311, 4);
        lv_obj_set_height(image_311, 4);
        lv_image_set_src(image_311, image_vec_6_2917);

        lv_obj_t * image_312 = image_create(container_4);
        lv_obj_set_x(image_312, 59);
        lv_obj_set_y(image_312, 113);
        lv_obj_set_width(image_312, 4);
        lv_obj_set_height(image_312, 4);
        lv_image_set_src(image_312, image_vec_6_2918);

        lv_obj_t * image_313 = image_create(container_4);
        lv_obj_set_x(image_313, 63);
        lv_obj_set_y(image_313, 113);
        lv_obj_set_width(image_313, 4);
        lv_obj_set_height(image_313, 4);
        lv_image_set_src(image_313, image_vec_6_2919);

        lv_obj_t * image_314 = image_create(container_4);
        lv_obj_set_x(image_314, 67);
        lv_obj_set_y(image_314, 113);
        lv_obj_set_width(image_314, 4);
        lv_obj_set_height(image_314, 4);
        lv_image_set_src(image_314, image_vec_6_2920);

        lv_obj_t * image_315 = image_create(container_4);
        lv_obj_set_x(image_315, 71);
        lv_obj_set_y(image_315, 113);
        lv_obj_set_width(image_315, 4);
        lv_obj_set_height(image_315, 4);
        lv_image_set_src(image_315, image_vec_6_2921);

        lv_obj_t * image_316 = image_create(container_4);
        lv_obj_set_x(image_316, 76);
        lv_obj_set_y(image_316, 113);
        lv_obj_set_width(image_316, 4);
        lv_obj_set_height(image_316, 4);
        lv_image_set_src(image_316, image_vec_6_2922);

        lv_obj_t * image_317 = image_create(container_4);
        lv_obj_set_x(image_317, 97);
        lv_obj_set_y(image_317, 113);
        lv_obj_set_width(image_317, 4);
        lv_obj_set_height(image_317, 4);
        lv_image_set_src(image_317, image_vec_6_2923);

        lv_obj_t * image_318 = image_create(container_4);
        lv_obj_set_x(image_318, 101);
        lv_obj_set_y(image_318, 113);
        lv_obj_set_width(image_318, 4);
        lv_obj_set_height(image_318, 4);
        lv_image_set_src(image_318, image_vec_6_2924);

        lv_obj_t * image_319 = image_create(container_4);
        lv_obj_set_x(image_319, 105);
        lv_obj_set_y(image_319, 113);
        lv_obj_set_width(image_319, 4);
        lv_obj_set_height(image_319, 4);
        lv_image_set_src(image_319, image_vec_6_2925);

        lv_obj_t * image_320 = image_create(container_4);
        lv_obj_set_x(image_320, 113);
        lv_obj_set_y(image_320, 113);
        lv_obj_set_width(image_320, 4);
        lv_obj_set_height(image_320, 4);
        lv_image_set_src(image_320, image_vec_6_2926);

        lv_obj_t * image_321 = image_create(container_4);
        lv_obj_set_x(image_321, 118);
        lv_obj_set_y(image_321, 113);
        lv_obj_set_width(image_321, 4);
        lv_obj_set_height(image_321, 4);
        lv_image_set_src(image_321, image_vec_6_2927);

        lv_obj_t * image_322 = image_create(container_4);
        lv_obj_set_x(image_322, 38);
        lv_obj_set_y(image_322, 118);
        lv_obj_set_width(image_322, 4);
        lv_obj_set_height(image_322, 4);
        lv_image_set_src(image_322, image_vec_6_2928);

        lv_obj_t * image_323 = image_create(container_4);
        lv_obj_set_x(image_323, 46);
        lv_obj_set_y(image_323, 118);
        lv_obj_set_width(image_323, 4);
        lv_obj_set_height(image_323, 4);
        lv_image_set_src(image_323, image_vec_6_2929);

        lv_obj_t * image_324 = image_create(container_4);
        lv_obj_set_x(image_324, 50);
        lv_obj_set_y(image_324, 118);
        lv_obj_set_width(image_324, 4);
        lv_obj_set_height(image_324, 4);
        lv_image_set_src(image_324, image_vec_6_2930);

        lv_obj_t * image_325 = image_create(container_4);
        lv_obj_set_x(image_325, 55);
        lv_obj_set_y(image_325, 118);
        lv_obj_set_width(image_325, 4);
        lv_obj_set_height(image_325, 4);
        lv_image_set_src(image_325, image_vec_6_2931);

        lv_obj_t * image_326 = image_create(container_4);
        lv_obj_set_x(image_326, 59);
        lv_obj_set_y(image_326, 118);
        lv_obj_set_width(image_326, 4);
        lv_obj_set_height(image_326, 4);
        lv_image_set_src(image_326, image_vec_6_2932);

        lv_obj_t * image_327 = image_create(container_4);
        lv_obj_set_x(image_327, 67);
        lv_obj_set_y(image_327, 118);
        lv_obj_set_width(image_327, 4);
        lv_obj_set_height(image_327, 4);
        lv_image_set_src(image_327, image_vec_6_2933);

        lv_obj_t * image_328 = image_create(container_4);
        lv_obj_set_x(image_328, 71);
        lv_obj_set_y(image_328, 118);
        lv_obj_set_width(image_328, 4);
        lv_obj_set_height(image_328, 4);
        lv_image_set_src(image_328, image_vec_6_2934);

        lv_obj_t * image_329 = image_create(container_4);
        lv_obj_set_x(image_329, 92);
        lv_obj_set_y(image_329, 118);
        lv_obj_set_width(image_329, 4);
        lv_obj_set_height(image_329, 4);
        lv_image_set_src(image_329, image_vec_6_2935);

        lv_obj_t * image_330 = image_create(container_4);
        lv_obj_set_x(image_330, 97);
        lv_obj_set_y(image_330, 118);
        lv_obj_set_width(image_330, 4);
        lv_obj_set_height(image_330, 4);
        lv_image_set_src(image_330, image_vec_6_2936);

        lv_obj_t * image_331 = image_create(container_4);
        lv_obj_set_x(image_331, 101);
        lv_obj_set_y(image_331, 118);
        lv_obj_set_width(image_331, 4);
        lv_obj_set_height(image_331, 4);
        lv_image_set_src(image_331, image_vec_6_2937);

        lv_obj_t * image_332 = image_create(container_4);
        lv_obj_set_x(image_332, 105);
        lv_obj_set_y(image_332, 118);
        lv_obj_set_width(image_332, 4);
        lv_obj_set_height(image_332, 4);
        lv_image_set_src(image_332, image_vec_6_2938);

        lv_obj_t * image_333 = image_create(container_4);
        lv_obj_set_x(image_333, 113);
        lv_obj_set_y(image_333, 118);
        lv_obj_set_width(image_333, 4);
        lv_obj_set_height(image_333, 4);
        lv_image_set_src(image_333, image_vec_6_2939);

        lv_obj_t * image_334 = image_create(container_3);
        lv_obj_set_x(image_334, -9);
        lv_obj_set_y(image_334, -9);
        lv_obj_set_width(image_334, 140);
        lv_obj_set_height(image_334, 140);
        lv_image_set_src(image_334, image_vec_6_2940);

        lv_obj_t * container_5 = container_create(container_0);
        lv_obj_set_x(container_5, 9);
        lv_obj_set_y(container_5, 9);
        lv_obj_set_width(container_5, 29);
        lv_obj_set_height(container_5, 29);
        lv_obj_t * container_6 = container_create(container_5);
        lv_obj_set_x(container_6, 0);
        lv_obj_set_y(container_6, 0);
        lv_obj_set_width(container_6, 29);
        lv_obj_set_height(container_6, 29);
        lv_obj_t * image_335 = image_create(container_6);
        lv_obj_set_x(image_335, 0);
        lv_obj_set_y(image_335, 0);
        lv_obj_set_width(image_335, 29);
        lv_obj_set_height(image_335, 29);
        lv_image_set_src(image_335, image_vec_6_2943);

        lv_obj_t * image_336 = image_create(container_5);
        lv_obj_set_x(image_336, 0);
        lv_obj_set_y(image_336, 0);
        lv_obj_set_width(image_336, 29);
        lv_obj_set_height(image_336, 29);
        lv_image_set_src(image_336, image_vec_6_2944);

        lv_obj_t * container_7 = container_create(container_0);
        lv_obj_set_x(container_7, 18);
        lv_obj_set_y(container_7, 18);
        lv_obj_set_width(container_7, 13);
        lv_obj_set_height(container_7, 13);
        lv_obj_t * container_8 = container_create(container_7);
        lv_obj_set_x(container_8, 0);
        lv_obj_set_y(container_8, 0);
        lv_obj_set_width(container_8, 13);
        lv_obj_set_height(container_8, 13);
        lv_obj_t * image_337 = image_create(container_8);
        lv_obj_set_x(image_337, 0);
        lv_obj_set_y(image_337, 0);
        lv_obj_set_width(image_337, 13);
        lv_obj_set_height(image_337, 13);
        lv_image_set_src(image_337, image_vec_6_2947);

        lv_obj_t * image_338 = image_create(container_7);
        lv_obj_set_x(image_338, 0);
        lv_obj_set_y(image_338, 0);
        lv_obj_set_width(image_338, 13);
        lv_obj_set_height(image_338, 13);
        lv_image_set_src(image_338, image_vec_6_2948);

        lv_obj_t * container_9 = container_create(container_0);
        lv_obj_set_x(container_9, 101);
        lv_obj_set_y(container_9, 9);
        lv_obj_set_width(container_9, 29);
        lv_obj_set_height(container_9, 29);
        lv_obj_t * container_10 = container_create(container_9);
        lv_obj_set_x(container_10, 0);
        lv_obj_set_y(container_10, 0);
        lv_obj_set_width(container_10, 29);
        lv_obj_set_height(container_10, 29);
        lv_obj_t * image_339 = image_create(container_10);
        lv_obj_set_x(image_339, 29);
        lv_obj_set_y(image_339, 0);
        lv_obj_set_width(image_339, 29);
        lv_obj_set_height(image_339, 29);
        lv_image_set_src(image_339, image_vec_6_2951);
        lv_obj_set_style_transform_rotation(image_339, 900, 0);
        lv_obj_set_style_transform_pivot_x(image_339, 15, 0);
        lv_obj_set_style_transform_pivot_y(image_339, 15, 0);

        lv_obj_t * image_340 = image_create(container_9);
        lv_obj_set_x(image_340, 0);
        lv_obj_set_y(image_340, 0);
        lv_obj_set_width(image_340, 29);
        lv_obj_set_height(image_340, 29);
        lv_image_set_src(image_340, image_vec_6_2952);

        lv_obj_t * container_11 = container_create(container_0);
        lv_obj_set_x(container_11, 110);
        lv_obj_set_y(container_11, 18);
        lv_obj_set_width(container_11, 13);
        lv_obj_set_height(container_11, 13);
        lv_obj_t * container_12 = container_create(container_11);
        lv_obj_set_x(container_12, 0);
        lv_obj_set_y(container_12, 0);
        lv_obj_set_width(container_12, 13);
        lv_obj_set_height(container_12, 13);
        lv_obj_t * image_341 = image_create(container_12);
        lv_obj_set_x(image_341, 13);
        lv_obj_set_y(image_341, 0);
        lv_obj_set_width(image_341, 13);
        lv_obj_set_height(image_341, 13);
        lv_image_set_src(image_341, image_vec_6_2955);
        lv_obj_set_style_transform_rotation(image_341, 900, 0);
        lv_obj_set_style_transform_pivot_x(image_341, 7, 0);
        lv_obj_set_style_transform_pivot_y(image_341, 7, 0);

        lv_obj_t * image_342 = image_create(container_11);
        lv_obj_set_x(image_342, 0);
        lv_obj_set_y(image_342, 0);
        lv_obj_set_width(image_342, 13);
        lv_obj_set_height(image_342, 13);
        lv_image_set_src(image_342, image_vec_6_2956);

        lv_obj_t * container_13 = container_create(container_0);
        lv_obj_set_x(container_13, 9);
        lv_obj_set_y(container_13, 101);
        lv_obj_set_width(container_13, 29);
        lv_obj_set_height(container_13, 29);
        lv_obj_t * container_14 = container_create(container_13);
        lv_obj_set_x(container_14, 0);
        lv_obj_set_y(container_14, 0);
        lv_obj_set_width(container_14, 29);
        lv_obj_set_height(container_14, 29);
        lv_obj_t * image_343 = image_create(container_14);
        lv_obj_set_x(image_343, 0);
        lv_obj_set_y(image_343, 29);
        lv_obj_set_width(image_343, 29);
        lv_obj_set_height(image_343, 29);
        lv_image_set_src(image_343, image_vec_6_2959);
        lv_obj_set_style_transform_rotation(image_343, -900, 0);
        lv_obj_set_style_transform_pivot_x(image_343, 15, 0);
        lv_obj_set_style_transform_pivot_y(image_343, 15, 0);

        lv_obj_t * image_344 = image_create(container_13);
        lv_obj_set_x(image_344, 0);
        lv_obj_set_y(image_344, 0);
        lv_obj_set_width(image_344, 29);
        lv_obj_set_height(image_344, 29);
        lv_image_set_src(image_344, image_vec_6_2960);

        lv_obj_t * container_15 = container_create(container_0);
        lv_obj_set_x(container_15, 18);
        lv_obj_set_y(container_15, 110);
        lv_obj_set_width(container_15, 13);
        lv_obj_set_height(container_15, 13);
        lv_obj_t * container_16 = container_create(container_15);
        lv_obj_set_x(container_16, 0);
        lv_obj_set_y(container_16, 0);
        lv_obj_set_width(container_16, 13);
        lv_obj_set_height(container_16, 13);
        lv_obj_t * image_345 = image_create(container_16);
        lv_obj_set_x(image_345, 0);
        lv_obj_set_y(image_345, 13);
        lv_obj_set_width(image_345, 13);
        lv_obj_set_height(image_345, 13);
        lv_image_set_src(image_345, image_vec_6_2963);
        lv_obj_set_style_transform_rotation(image_345, -900, 0);
        lv_obj_set_style_transform_pivot_x(image_345, 7, 0);
        lv_obj_set_style_transform_pivot_y(image_345, 7, 0);

        lv_obj_t * image_346 = image_create(container_15);
        lv_obj_set_x(image_346, 0);
        lv_obj_set_y(image_346, 0);
        lv_obj_set_width(image_346, 13);
        lv_obj_set_height(image_346, 13);
        lv_image_set_src(image_346, image_vec_6_2964);

        the_root = container_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

