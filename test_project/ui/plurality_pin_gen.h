/**
 * @file plurality_pin_gen.h
 */

#ifndef LVGL_PRO_PLURALITY_PIN_GEN_H
#define LVGL_PRO_PLURALITY_PIN_GEN_H

#ifndef UI_SUBJECT_STRING_LENGTH
#define UI_SUBJECT_STRING_LENGTH 256
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
    #include "lvgl.h"
    #include "lvgl_private.h"
#else
    #include "lvgl/lvgl.h"
    #include "lvgl/lvgl_private.h"
#endif

#if defined(LV_USE_XML) && LV_USE_XML
    #include "lv_xml/lv_xml.h"
#endif



/* Prototypes for target functions, needed by responsive const definitions */

void plurality_pin_set_target(uint32_t target);
uint32_t plurality_pin_get_target(void);
bool plurality_pin_check_target(uint32_t target);

/*********************
 *      DEFINES
 *********************/

#define PLURALITY_PIN_TARGET_UNDEFINED  (0 << 1)
#define PLURALITY_PIN_TARGET_TARGET1    (1 << 1)
#define PLURALITY_PIN_TARGET_ALL        0x0FFFFFFF

/* By default compile for all targets, allowing to switch to any targets at runtime */
#ifndef PLURALITY_PIN_COMPILE_TARGET
#define PLURALITY_PIN_COMPILE_TARGET PLURALITY_PIN_TARGET_ALL
#endif

#define PLURALITY_PIN_CHECK_COMPILE_TARGET(target) (PLURALITY_PIN_COMPILE_TARGET & (target) ? 1 : 0)

#define CONST_BASELIB_ACCENT_GLOBAL lv_color_hex(0x70609C)
#define CONST_BASELIB_UNIT_SM_GLOBAL 4


#ifndef LV_XML_EVAL_STRING_BUF_SIZE
    #define LV_XML_EVAL_STRING_BUF_SIZE 256
#endif

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL VARIABLES
 **********************/

/*-------------------
 * Permanent screens
 *------------------*/

/*----------------
 * Global styles
 *----------------*/

extern lv_style_t style_screen_base_global;

/*----------------
 * Fonts
 *----------------*/

/* Targets: any */
extern lv_font_t * font_ibm_plex_mono_regular_26;
extern lv_font_t * font_ibm_plex_mono_semibold_150;
extern lv_font_t * font_inter_medium_24_460227966308594;
extern lv_font_t * font_roboto_semibold_22;
extern lv_font_t * font_inter_semi_bold_12;
extern lv_font_t * font_inter_bold_28;
extern lv_font_t * font_inter_semi_bold_16;
extern lv_font_t * font_inter_semi_bold_14;
extern lv_font_t * font_inter_medium_11;
extern lv_font_t * font_inter_bold_14;
extern lv_font_t * font_inter_bold_20;
extern lv_font_t * font_inter_bold_23;
extern lv_font_t * font_inter_semi_bold_13;
extern lv_font_t * font_playwrite_us_trad_regular_40;
extern lv_font_t * font_playwrite_us_trad_regular_52;
extern lv_font_t * font_inter_semi_bold_8;
extern lv_font_t * font_inter_semi_bold_11;
extern lv_font_t * font_roboto_medium_14;
extern lv_font_t * font_ibm_plex_mono_regular_36;
extern lv_font_t * font_roboto_medium_16;
extern lv_font_t * font_ibm_plex_mono_medium_14;
extern lv_font_t * font_ibm_plex_mono_regular_29;
extern lv_font_t * font_inter_medium_24_manual;
extern lv_font_t * font_inter_semi_bold_22_manual;


/*----------------
 * Images
 *----------------*/

/* Targets: any */
extern const void * image_img_02c5506b;
extern const void * image_img_45c6bb3a;
extern const void * image_vec_37_864;
extern const void * image_vec_6_2604;
extern const void * image_vec_6_2605;
extern const void * image_vec_6_2608;
extern const void * image_vec_6_2609;
extern const void * image_vec_6_2610;
extern const void * image_vec_6_2611;
extern const void * image_vec_6_2612;
extern const void * image_vec_6_2613;
extern const void * image_vec_6_2614;
extern const void * image_vec_6_2615;
extern const void * image_vec_6_2616;
extern const void * image_vec_6_2617;
extern const void * image_vec_6_2618;
extern const void * image_vec_6_2619;
extern const void * image_vec_6_2620;
extern const void * image_vec_6_2621;
extern const void * image_vec_6_2622;
extern const void * image_vec_6_2623;
extern const void * image_vec_6_2624;
extern const void * image_vec_6_2625;
extern const void * image_vec_6_2626;
extern const void * image_vec_6_2627;
extern const void * image_vec_6_2628;
extern const void * image_vec_6_2629;
extern const void * image_vec_6_2630;
extern const void * image_vec_6_2631;
extern const void * image_vec_6_2632;
extern const void * image_vec_6_2633;
extern const void * image_vec_6_2634;
extern const void * image_vec_6_2635;
extern const void * image_vec_6_2636;
extern const void * image_vec_6_2637;
extern const void * image_vec_6_2638;
extern const void * image_vec_6_2639;
extern const void * image_vec_6_2640;
extern const void * image_vec_6_2641;
extern const void * image_vec_6_2642;
extern const void * image_vec_6_2643;
extern const void * image_vec_6_2644;
extern const void * image_vec_6_2645;
extern const void * image_vec_6_2646;
extern const void * image_vec_6_2647;
extern const void * image_vec_6_2648;
extern const void * image_vec_6_2649;
extern const void * image_vec_6_2650;
extern const void * image_vec_6_2651;
extern const void * image_vec_6_2652;
extern const void * image_vec_6_2653;
extern const void * image_vec_6_2654;
extern const void * image_vec_6_2655;
extern const void * image_vec_6_2656;
extern const void * image_vec_6_2657;
extern const void * image_vec_6_2658;
extern const void * image_vec_6_2659;
extern const void * image_vec_6_2660;
extern const void * image_vec_6_2661;
extern const void * image_vec_6_2662;
extern const void * image_vec_6_2663;
extern const void * image_vec_6_2664;
extern const void * image_vec_6_2665;
extern const void * image_vec_6_2666;
extern const void * image_vec_6_2667;
extern const void * image_vec_6_2668;
extern const void * image_vec_6_2669;
extern const void * image_vec_6_2670;
extern const void * image_vec_6_2671;
extern const void * image_vec_6_2672;
extern const void * image_vec_6_2673;
extern const void * image_vec_6_2674;
extern const void * image_vec_6_2675;
extern const void * image_vec_6_2676;
extern const void * image_vec_6_2677;
extern const void * image_vec_6_2678;
extern const void * image_vec_6_2679;
extern const void * image_vec_6_2680;
extern const void * image_vec_6_2681;
extern const void * image_vec_6_2682;
extern const void * image_vec_6_2683;
extern const void * image_vec_6_2684;
extern const void * image_vec_6_2685;
extern const void * image_vec_6_2686;
extern const void * image_vec_6_2687;
extern const void * image_vec_6_2688;
extern const void * image_vec_6_2689;
extern const void * image_vec_6_2690;
extern const void * image_vec_6_2691;
extern const void * image_vec_6_2692;
extern const void * image_vec_6_2693;
extern const void * image_vec_6_2694;
extern const void * image_vec_6_2695;
extern const void * image_vec_6_2696;
extern const void * image_vec_6_2697;
extern const void * image_vec_6_2698;
extern const void * image_vec_6_2699;
extern const void * image_vec_6_2700;
extern const void * image_vec_6_2701;
extern const void * image_vec_6_2702;
extern const void * image_vec_6_2703;
extern const void * image_vec_6_2704;
extern const void * image_vec_6_2705;
extern const void * image_vec_6_2706;
extern const void * image_vec_6_2707;
extern const void * image_vec_6_2708;
extern const void * image_vec_6_2709;
extern const void * image_vec_6_2710;
extern const void * image_vec_6_2711;
extern const void * image_vec_6_2712;
extern const void * image_vec_6_2713;
extern const void * image_vec_6_2714;
extern const void * image_vec_6_2715;
extern const void * image_vec_6_2716;
extern const void * image_vec_6_2717;
extern const void * image_vec_6_2718;
extern const void * image_vec_6_2719;
extern const void * image_vec_6_2720;
extern const void * image_vec_6_2721;
extern const void * image_vec_6_2722;
extern const void * image_vec_6_2723;
extern const void * image_vec_6_2724;
extern const void * image_vec_6_2725;
extern const void * image_vec_6_2726;
extern const void * image_vec_6_2727;
extern const void * image_vec_6_2728;
extern const void * image_vec_6_2729;
extern const void * image_vec_6_2730;
extern const void * image_vec_6_2731;
extern const void * image_vec_6_2732;
extern const void * image_vec_6_2733;
extern const void * image_vec_6_2734;
extern const void * image_vec_6_2735;
extern const void * image_vec_6_2736;
extern const void * image_vec_6_2737;
extern const void * image_vec_6_2738;
extern const void * image_vec_6_2739;
extern const void * image_vec_6_2740;
extern const void * image_vec_6_2741;
extern const void * image_vec_6_2742;
extern const void * image_vec_6_2743;
extern const void * image_vec_6_2744;
extern const void * image_vec_6_2745;
extern const void * image_vec_6_2746;
extern const void * image_vec_6_2747;
extern const void * image_vec_6_2748;
extern const void * image_vec_6_2749;
extern const void * image_vec_6_2750;
extern const void * image_vec_6_2751;
extern const void * image_vec_6_2752;
extern const void * image_vec_6_2753;
extern const void * image_vec_6_2754;
extern const void * image_vec_6_2755;
extern const void * image_vec_6_2756;
extern const void * image_vec_6_2757;
extern const void * image_vec_6_2758;
extern const void * image_vec_6_2759;
extern const void * image_vec_6_2760;
extern const void * image_vec_6_2761;
extern const void * image_vec_6_2762;
extern const void * image_vec_6_2763;
extern const void * image_vec_6_2764;
extern const void * image_vec_6_2765;
extern const void * image_vec_6_2766;
extern const void * image_vec_6_2767;
extern const void * image_vec_6_2768;
extern const void * image_vec_6_2769;
extern const void * image_vec_6_2770;
extern const void * image_vec_6_2771;
extern const void * image_vec_6_2772;
extern const void * image_vec_6_2773;
extern const void * image_vec_6_2774;
extern const void * image_vec_6_2775;
extern const void * image_vec_6_2776;
extern const void * image_vec_6_2777;
extern const void * image_vec_6_2778;
extern const void * image_vec_6_2779;
extern const void * image_vec_6_2780;
extern const void * image_vec_6_2781;
extern const void * image_vec_6_2782;
extern const void * image_vec_6_2783;
extern const void * image_vec_6_2784;
extern const void * image_vec_6_2785;
extern const void * image_vec_6_2786;
extern const void * image_vec_6_2787;
extern const void * image_vec_6_2788;
extern const void * image_vec_6_2789;
extern const void * image_vec_6_2790;
extern const void * image_vec_6_2791;
extern const void * image_vec_6_2792;
extern const void * image_vec_6_2793;
extern const void * image_vec_6_2794;
extern const void * image_vec_6_2795;
extern const void * image_vec_6_2796;
extern const void * image_vec_6_2797;
extern const void * image_vec_6_2798;
extern const void * image_vec_6_2799;
extern const void * image_vec_6_2800;
extern const void * image_vec_6_2801;
extern const void * image_vec_6_2802;
extern const void * image_vec_6_2803;
extern const void * image_vec_6_2804;
extern const void * image_vec_6_2805;
extern const void * image_vec_6_2806;
extern const void * image_vec_6_2807;
extern const void * image_vec_6_2808;
extern const void * image_vec_6_2809;
extern const void * image_vec_6_2810;
extern const void * image_vec_6_2811;
extern const void * image_vec_6_2812;
extern const void * image_vec_6_2813;
extern const void * image_vec_6_2814;
extern const void * image_vec_6_2815;
extern const void * image_vec_6_2816;
extern const void * image_vec_6_2817;
extern const void * image_vec_6_2818;
extern const void * image_vec_6_2819;
extern const void * image_vec_6_2820;
extern const void * image_vec_6_2821;
extern const void * image_vec_6_2822;
extern const void * image_vec_6_2823;
extern const void * image_vec_6_2824;
extern const void * image_vec_6_2825;
extern const void * image_vec_6_2826;
extern const void * image_vec_6_2827;
extern const void * image_vec_6_2828;
extern const void * image_vec_6_2829;
extern const void * image_vec_6_2830;
extern const void * image_vec_6_2831;
extern const void * image_vec_6_2832;
extern const void * image_vec_6_2833;
extern const void * image_vec_6_2834;
extern const void * image_vec_6_2835;
extern const void * image_vec_6_2836;
extern const void * image_vec_6_2837;
extern const void * image_vec_6_2838;
extern const void * image_vec_6_2839;
extern const void * image_vec_6_2840;
extern const void * image_vec_6_2841;
extern const void * image_vec_6_2842;
extern const void * image_vec_6_2843;
extern const void * image_vec_6_2844;
extern const void * image_vec_6_2845;
extern const void * image_vec_6_2846;
extern const void * image_vec_6_2847;
extern const void * image_vec_6_2848;
extern const void * image_vec_6_2849;
extern const void * image_vec_6_2850;
extern const void * image_vec_6_2851;
extern const void * image_vec_6_2852;
extern const void * image_vec_6_2853;
extern const void * image_vec_6_2854;
extern const void * image_vec_6_2855;
extern const void * image_vec_6_2856;
extern const void * image_vec_6_2857;
extern const void * image_vec_6_2858;
extern const void * image_vec_6_2859;
extern const void * image_vec_6_2860;
extern const void * image_vec_6_2861;
extern const void * image_vec_6_2862;
extern const void * image_vec_6_2863;
extern const void * image_vec_6_2864;
extern const void * image_vec_6_2865;
extern const void * image_vec_6_2866;
extern const void * image_vec_6_2867;
extern const void * image_vec_6_2868;
extern const void * image_vec_6_2869;
extern const void * image_vec_6_2870;
extern const void * image_vec_6_2871;
extern const void * image_vec_6_2872;
extern const void * image_vec_6_2873;
extern const void * image_vec_6_2874;
extern const void * image_vec_6_2875;
extern const void * image_vec_6_2876;
extern const void * image_vec_6_2877;
extern const void * image_vec_6_2878;
extern const void * image_vec_6_2879;
extern const void * image_vec_6_2880;
extern const void * image_vec_6_2881;
extern const void * image_vec_6_2882;
extern const void * image_vec_6_2883;
extern const void * image_vec_6_2884;
extern const void * image_vec_6_2885;
extern const void * image_vec_6_2886;
extern const void * image_vec_6_2887;
extern const void * image_vec_6_2888;
extern const void * image_vec_6_2889;
extern const void * image_vec_6_2890;
extern const void * image_vec_6_2891;
extern const void * image_vec_6_2892;
extern const void * image_vec_6_2893;
extern const void * image_vec_6_2894;
extern const void * image_vec_6_2895;
extern const void * image_vec_6_2896;
extern const void * image_vec_6_2897;
extern const void * image_vec_6_2898;
extern const void * image_vec_6_2899;
extern const void * image_vec_6_2900;
extern const void * image_vec_6_2901;
extern const void * image_vec_6_2902;
extern const void * image_vec_6_2903;
extern const void * image_vec_6_2904;
extern const void * image_vec_6_2905;
extern const void * image_vec_6_2906;
extern const void * image_vec_6_2907;
extern const void * image_vec_6_2908;
extern const void * image_vec_6_2909;
extern const void * image_vec_6_2910;
extern const void * image_vec_6_2911;
extern const void * image_vec_6_2912;
extern const void * image_vec_6_2913;
extern const void * image_vec_6_2914;
extern const void * image_vec_6_2915;
extern const void * image_vec_6_2916;
extern const void * image_vec_6_2917;
extern const void * image_vec_6_2918;
extern const void * image_vec_6_2919;
extern const void * image_vec_6_2920;
extern const void * image_vec_6_2921;
extern const void * image_vec_6_2922;
extern const void * image_vec_6_2923;
extern const void * image_vec_6_2924;
extern const void * image_vec_6_2925;
extern const void * image_vec_6_2926;
extern const void * image_vec_6_2927;
extern const void * image_vec_6_2928;
extern const void * image_vec_6_2929;
extern const void * image_vec_6_2930;
extern const void * image_vec_6_2931;
extern const void * image_vec_6_2932;
extern const void * image_vec_6_2933;
extern const void * image_vec_6_2934;
extern const void * image_vec_6_2935;
extern const void * image_vec_6_2936;
extern const void * image_vec_6_2937;
extern const void * image_vec_6_2938;
extern const void * image_vec_6_2939;
extern const void * image_vec_6_2940;
extern const void * image_vec_6_2943;
extern const void * image_vec_6_2944;
extern const void * image_vec_6_2947;
extern const void * image_vec_6_2948;
extern const void * image_vec_6_2951;
extern const void * image_vec_6_2952;
extern const void * image_vec_6_2955;
extern const void * image_vec_6_2956;
extern const void * image_vec_6_2959;
extern const void * image_vec_6_2960;
extern const void * image_vec_6_2963;
extern const void * image_vec_6_2964;
extern const void * image_vec_25_1105;
extern const void * image_vec_34_869;
extern const void * image_vec_34_872;
extern const void * image_vec_23_372;
extern const void * image_vec_42_877;
extern const void * image_vec_12_212;
extern const void * image_vec_42_862;
extern const void * image_vec_7_1590;
extern const void * image_vec_7_1412;
extern const void * image_vec_1_241;
extern const void * image_vec_7_1491;
extern const void * image_vec_7_1493;
extern const void * image_vec_1_790;
extern const void * image_vec_1_882;
extern const void * image_vec_25_1004;
extern const void * image_vec_7_1415;
extern const void * image_vec_42_2416;
extern const void * image_vec_42_2418;
extern const void * image_vec_23_214;

/*----------------
 * Subjects
 *----------------*/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/*----------------
 * Event Callbacks
 *----------------*/

/**
 * Initialize the component library
 */

void plurality_pin_init_gen(const char * asset_path);

/**********************
 *      MACROS
 **********************/

/**********************
 *   POST INCLUDES
 **********************/

/*Include all the widgets, components and screens of this library*/
#include "components/account_circle/account_circle_gen.h"
#include "components/background/background_gen.h"
#include "components/base/card/card_gen.h"
#include "components/base/column/column_gen.h"
#include "components/base/container/container_gen.h"
#include "components/base/image/image_gen.h"
#include "components/base/label/label_gen.h"
#include "components/base/panel/panel_gen.h"
#include "components/base/row/row_gen.h"
#include "components/battery_card/battery_card_gen.h"
#include "components/battery/battery_gen.h"
#include "components/bluetooth_card/bluetooth_card_gen.h"
#include "components/brightness_card/brightness_card_gen.h"
#include "components/building_blocks_active_track/building_blocks_active_track_gen.h"
#include "components/building_blocks_handle/building_blocks_handle_gen.h"
#include "components/building_blocks_inactive_track/building_blocks_inactive_track_gen.h"
#include "components/building_blocks_stops/building_blocks_stops_gen.h"
#include "components/building_blocks_track_stop/building_blocks_track_stop_gen.h"
#include "components/check/check_gen.h"
#include "components/configuration_label_only_state_enabled_selected_false/configuration_label_only_state_enabled_selected_false_gen.h"
#include "components/configuration_label_only_state_enabled_selected_true/configuration_label_only_state_enabled_selected_true_gen.h"
#include "components/connect_b/connect_b_gen.h"
#include "components/derived/tile_2/tile_2_gen.h"
#include "components/derived/tile/tile_gen.h"
#include "components/edit_b/edit_b_gen.h"
#include "components/edit/edit_gen.h"
#include "components/ellipse_2/ellipse_2_gen.h"
#include "components/front_history_card/front_history_card_gen.h"
#include "components/image_b/image_b_gen.h"
#include "components/ipad_leading_accessories/ipad_leading_accessories_gen.h"
#include "components/ipad_trailing_accessories/ipad_trailing_accessories_gen.h"
#include "components/link/link_gen.h"
#include "components/mode_light_active_true_context_content_area_state_idle_b/mode_light_active_true_context_content_area_state_idle_b_gen.h"
#include "components/mode_light_active_true_context_content_area_state_idle/mode_light_active_true_context_content_area_state_idle_gen.h"
#include "components/mode_light_active_true/mode_light_active_true_gen.h"
#include "components/mode_light_context_content_area_state_idle_type_tick/mode_light_context_content_area_state_idle_type_tick_gen.h"
#include "components/orientation_horizontal_size_xsmall_state_enabled_value_50/orientation_horizontal_size_xsmall_state_enabled_value_50_gen.h"
#include "components/power_mode/power_mode_gen.h"
#include "components/profile_picture/profile_picture_gen.h"
#include "components/qrcode_b/qrcode_b_gen.h"
#include "components/scan_for_web_dashboard_access_ensure_that_you_are_connected_to_the_pin/scan_for_web_dashboard_access_ensure_that_you_are_connected_to_the_pin_gen.h"
#include "components/scan_to_connect_to_the_pin/scan_to_connect_to_the_pin_gen.h"
#include "components/segments_2_density_0/segments_2_density_0_gen.h"
#include "components/settings_b/settings_b_gen.h"
#include "components/settings_c/settings_c_gen.h"
#include "components/settings_d/settings_d_gen.h"
#include "components/settings_e/settings_e_gen.h"
#include "components/stars_filled/stars_filled_gen.h"
#include "components/stars/stars_gen.h"
#include "components/status_b/status_b_gen.h"
#include "components/status_bar/status_bar_gen.h"
#include "components/status_c/status_c_gen.h"
#include "components/text_box_b/text_box_b_gen.h"
#include "components/text_box/text_box_gen.h"
#include "components/tf_storage/tf_storage_gen.h"
#include "components/type_round_size_medium_state_enabled_selected_false/type_round_size_medium_state_enabled_selected_false_gen.h"
#include "components/type_round_size_medium_state_enabled_selected_true/type_round_size_medium_state_enabled_selected_true_gen.h"
#include "components/type_round_size_small_state_enabled_selected_false/type_round_size_small_state_enabled_selected_false_gen.h"
#include "components/type_round_size_small_state_enabled_selected_true/type_round_size_small_state_enabled_selected_true_gen.h"
#include "components/wi_fi/wi_fi_gen.h"
#include "components/wifi_card/wifi_card_gen.h"
#include "screens/connect_gen.h"
#include "screens/connect_wi_fi_gen.h"
#include "screens/front_history_gen.h"
#include "screens/image_mode_full_gen.h"
#include "screens/image_mode_with_text_gen.h"
#include "screens/namecard_mode_gen.h"
#include "screens/pull_down_menu_connected_gen.h"
#include "screens/pull_down_menu_initial_gen.h"
#include "screens/settings_gen.h"
#include "screens/status_gen.h"
#include "screens/watch_gen.h"

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LVGL_PRO_PLURALITY_PIN_GEN_H*/