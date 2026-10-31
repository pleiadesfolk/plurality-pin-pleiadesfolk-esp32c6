/* Copied by tools/sync_ui.py with two changes:
 *  - fonts are pre-rendered bitmaps (ui/fonts) instead of TTF files
 *  - images come from the assets partition (assets_image(N))
 *    instead of built-in C arrays */

/**
 * @file plurality_pin_gen.c
 */

/*********************
 *      INCLUDES
 *********************/

#include "plurality_pin_gen.h"
#include "assets.h"

extern const lv_font_t bitmap_ibmplexmono_medium_14;
extern const lv_font_t bitmap_ibmplexmono_regular_26;
extern const lv_font_t bitmap_ibmplexmono_regular_29;
extern const lv_font_t bitmap_ibmplexmono_regular_36;
extern const lv_font_t bitmap_ibmplexmono_semibold_150;
extern const lv_font_t bitmap_inter_bold_14;
extern const lv_font_t bitmap_inter_bold_20;
extern const lv_font_t bitmap_inter_bold_23;
extern const lv_font_t bitmap_inter_bold_28;
extern const lv_font_t bitmap_inter_medium_11;
extern const lv_font_t bitmap_inter_medium_16;
extern const lv_font_t bitmap_inter_medium_24;
extern const lv_font_t bitmap_inter_semibold_11;
extern const lv_font_t bitmap_inter_semibold_12;
extern const lv_font_t bitmap_inter_semibold_13;
extern const lv_font_t bitmap_inter_semibold_14;
extern const lv_font_t bitmap_inter_semibold_16;
extern const lv_font_t bitmap_inter_semibold_22;
extern const lv_font_t bitmap_inter_semibold_8;
extern const lv_font_t bitmap_playwriteustrad_regular_40;
extern const lv_font_t bitmap_playwriteustrad_regular_52;
extern const lv_font_t bitmap_roboto_medium_14;
extern const lv_font_t bitmap_roboto_semibold_22;

#if defined(LV_USE_XML) && LV_USE_XML
#endif /* LV_USE_XML */

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

static void check_font(lv_font_t ** font, const char * name);

/**********************
 *  STATIC VARIABLES
 **********************/

static uint32_t plurality_pin_target = PLURALITY_PIN_TARGET_ALL;

/*----------------
 * Translations
 *----------------*/

/**********************
 *  GLOBAL VARIABLES
 **********************/

/*--------------------
 *  Permanent screens
 *-------------------*/

/*----------------
 * Fonts
 *----------------*/

lv_font_t * font_ibm_plex_mono_regular_26;
lv_font_t * font_ibm_plex_mono_semibold_150;
lv_font_t * font_inter_medium_24_460227966308594;
lv_font_t * font_roboto_semibold_22;
lv_font_t * font_inter_semi_bold_12;
lv_font_t * font_inter_bold_28;
lv_font_t * font_inter_semi_bold_16;
lv_font_t * font_inter_semi_bold_14;
lv_font_t * font_inter_medium_11;
lv_font_t * font_inter_bold_14;
lv_font_t * font_inter_bold_20;
lv_font_t * font_inter_bold_23;
lv_font_t * font_inter_semi_bold_13;
lv_font_t * font_playwrite_us_trad_regular_40;
lv_font_t * font_playwrite_us_trad_regular_52;
lv_font_t * font_inter_semi_bold_8;
lv_font_t * font_inter_semi_bold_11;
lv_font_t * font_roboto_medium_14;
lv_font_t * font_ibm_plex_mono_regular_36;
lv_font_t * font_roboto_medium_16;
lv_font_t * font_ibm_plex_mono_medium_14;
lv_font_t * font_ibm_plex_mono_regular_29;
lv_font_t * font_inter_medium_24_manual;
lv_font_t * font_inter_semi_bold_22_manual;

/*----------------
 * Images
 *----------------*/

/* Targets: any */
const void * image_img_02c5506b = NULL;
extern const void * image_img_02c5506b_data;
const void * image_img_45c6bb3a = NULL;
extern const void * image_img_45c6bb3a_data;
const void * image_vec_37_864 = NULL;
extern const void * image_vec_37_864_data;
const void * image_vec_6_2604 = NULL;
extern const void * image_vec_6_2604_data;
const void * image_vec_6_2605 = NULL;
extern const void * image_vec_6_2605_data;
const void * image_vec_6_2608 = NULL;
extern const void * image_vec_6_2608_data;
const void * image_vec_6_2609 = NULL;
extern const void * image_vec_6_2609_data;
const void * image_vec_6_2610 = NULL;
extern const void * image_vec_6_2610_data;
const void * image_vec_6_2611 = NULL;
extern const void * image_vec_6_2611_data;
const void * image_vec_6_2612 = NULL;
extern const void * image_vec_6_2612_data;
const void * image_vec_6_2613 = NULL;
extern const void * image_vec_6_2613_data;
const void * image_vec_6_2614 = NULL;
extern const void * image_vec_6_2614_data;
const void * image_vec_6_2615 = NULL;
extern const void * image_vec_6_2615_data;
const void * image_vec_6_2616 = NULL;
extern const void * image_vec_6_2616_data;
const void * image_vec_6_2617 = NULL;
extern const void * image_vec_6_2617_data;
const void * image_vec_6_2618 = NULL;
extern const void * image_vec_6_2618_data;
const void * image_vec_6_2619 = NULL;
extern const void * image_vec_6_2619_data;
const void * image_vec_6_2620 = NULL;
extern const void * image_vec_6_2620_data;
const void * image_vec_6_2621 = NULL;
extern const void * image_vec_6_2621_data;
const void * image_vec_6_2622 = NULL;
extern const void * image_vec_6_2622_data;
const void * image_vec_6_2623 = NULL;
extern const void * image_vec_6_2623_data;
const void * image_vec_6_2624 = NULL;
extern const void * image_vec_6_2624_data;
const void * image_vec_6_2625 = NULL;
extern const void * image_vec_6_2625_data;
const void * image_vec_6_2626 = NULL;
extern const void * image_vec_6_2626_data;
const void * image_vec_6_2627 = NULL;
extern const void * image_vec_6_2627_data;
const void * image_vec_6_2628 = NULL;
extern const void * image_vec_6_2628_data;
const void * image_vec_6_2629 = NULL;
extern const void * image_vec_6_2629_data;
const void * image_vec_6_2630 = NULL;
extern const void * image_vec_6_2630_data;
const void * image_vec_6_2631 = NULL;
extern const void * image_vec_6_2631_data;
const void * image_vec_6_2632 = NULL;
extern const void * image_vec_6_2632_data;
const void * image_vec_6_2633 = NULL;
extern const void * image_vec_6_2633_data;
const void * image_vec_6_2634 = NULL;
extern const void * image_vec_6_2634_data;
const void * image_vec_6_2635 = NULL;
extern const void * image_vec_6_2635_data;
const void * image_vec_6_2636 = NULL;
extern const void * image_vec_6_2636_data;
const void * image_vec_6_2637 = NULL;
extern const void * image_vec_6_2637_data;
const void * image_vec_6_2638 = NULL;
extern const void * image_vec_6_2638_data;
const void * image_vec_6_2639 = NULL;
extern const void * image_vec_6_2639_data;
const void * image_vec_6_2640 = NULL;
extern const void * image_vec_6_2640_data;
const void * image_vec_6_2641 = NULL;
extern const void * image_vec_6_2641_data;
const void * image_vec_6_2642 = NULL;
extern const void * image_vec_6_2642_data;
const void * image_vec_6_2643 = NULL;
extern const void * image_vec_6_2643_data;
const void * image_vec_6_2644 = NULL;
extern const void * image_vec_6_2644_data;
const void * image_vec_6_2645 = NULL;
extern const void * image_vec_6_2645_data;
const void * image_vec_6_2646 = NULL;
extern const void * image_vec_6_2646_data;
const void * image_vec_6_2647 = NULL;
extern const void * image_vec_6_2647_data;
const void * image_vec_6_2648 = NULL;
extern const void * image_vec_6_2648_data;
const void * image_vec_6_2649 = NULL;
extern const void * image_vec_6_2649_data;
const void * image_vec_6_2650 = NULL;
extern const void * image_vec_6_2650_data;
const void * image_vec_6_2651 = NULL;
extern const void * image_vec_6_2651_data;
const void * image_vec_6_2652 = NULL;
extern const void * image_vec_6_2652_data;
const void * image_vec_6_2653 = NULL;
extern const void * image_vec_6_2653_data;
const void * image_vec_6_2654 = NULL;
extern const void * image_vec_6_2654_data;
const void * image_vec_6_2655 = NULL;
extern const void * image_vec_6_2655_data;
const void * image_vec_6_2656 = NULL;
extern const void * image_vec_6_2656_data;
const void * image_vec_6_2657 = NULL;
extern const void * image_vec_6_2657_data;
const void * image_vec_6_2658 = NULL;
extern const void * image_vec_6_2658_data;
const void * image_vec_6_2659 = NULL;
extern const void * image_vec_6_2659_data;
const void * image_vec_6_2660 = NULL;
extern const void * image_vec_6_2660_data;
const void * image_vec_6_2661 = NULL;
extern const void * image_vec_6_2661_data;
const void * image_vec_6_2662 = NULL;
extern const void * image_vec_6_2662_data;
const void * image_vec_6_2663 = NULL;
extern const void * image_vec_6_2663_data;
const void * image_vec_6_2664 = NULL;
extern const void * image_vec_6_2664_data;
const void * image_vec_6_2665 = NULL;
extern const void * image_vec_6_2665_data;
const void * image_vec_6_2666 = NULL;
extern const void * image_vec_6_2666_data;
const void * image_vec_6_2667 = NULL;
extern const void * image_vec_6_2667_data;
const void * image_vec_6_2668 = NULL;
extern const void * image_vec_6_2668_data;
const void * image_vec_6_2669 = NULL;
extern const void * image_vec_6_2669_data;
const void * image_vec_6_2670 = NULL;
extern const void * image_vec_6_2670_data;
const void * image_vec_6_2671 = NULL;
extern const void * image_vec_6_2671_data;
const void * image_vec_6_2672 = NULL;
extern const void * image_vec_6_2672_data;
const void * image_vec_6_2673 = NULL;
extern const void * image_vec_6_2673_data;
const void * image_vec_6_2674 = NULL;
extern const void * image_vec_6_2674_data;
const void * image_vec_6_2675 = NULL;
extern const void * image_vec_6_2675_data;
const void * image_vec_6_2676 = NULL;
extern const void * image_vec_6_2676_data;
const void * image_vec_6_2677 = NULL;
extern const void * image_vec_6_2677_data;
const void * image_vec_6_2678 = NULL;
extern const void * image_vec_6_2678_data;
const void * image_vec_6_2679 = NULL;
extern const void * image_vec_6_2679_data;
const void * image_vec_6_2680 = NULL;
extern const void * image_vec_6_2680_data;
const void * image_vec_6_2681 = NULL;
extern const void * image_vec_6_2681_data;
const void * image_vec_6_2682 = NULL;
extern const void * image_vec_6_2682_data;
const void * image_vec_6_2683 = NULL;
extern const void * image_vec_6_2683_data;
const void * image_vec_6_2684 = NULL;
extern const void * image_vec_6_2684_data;
const void * image_vec_6_2685 = NULL;
extern const void * image_vec_6_2685_data;
const void * image_vec_6_2686 = NULL;
extern const void * image_vec_6_2686_data;
const void * image_vec_6_2687 = NULL;
extern const void * image_vec_6_2687_data;
const void * image_vec_6_2688 = NULL;
extern const void * image_vec_6_2688_data;
const void * image_vec_6_2689 = NULL;
extern const void * image_vec_6_2689_data;
const void * image_vec_6_2690 = NULL;
extern const void * image_vec_6_2690_data;
const void * image_vec_6_2691 = NULL;
extern const void * image_vec_6_2691_data;
const void * image_vec_6_2692 = NULL;
extern const void * image_vec_6_2692_data;
const void * image_vec_6_2693 = NULL;
extern const void * image_vec_6_2693_data;
const void * image_vec_6_2694 = NULL;
extern const void * image_vec_6_2694_data;
const void * image_vec_6_2695 = NULL;
extern const void * image_vec_6_2695_data;
const void * image_vec_6_2696 = NULL;
extern const void * image_vec_6_2696_data;
const void * image_vec_6_2697 = NULL;
extern const void * image_vec_6_2697_data;
const void * image_vec_6_2698 = NULL;
extern const void * image_vec_6_2698_data;
const void * image_vec_6_2699 = NULL;
extern const void * image_vec_6_2699_data;
const void * image_vec_6_2700 = NULL;
extern const void * image_vec_6_2700_data;
const void * image_vec_6_2701 = NULL;
extern const void * image_vec_6_2701_data;
const void * image_vec_6_2702 = NULL;
extern const void * image_vec_6_2702_data;
const void * image_vec_6_2703 = NULL;
extern const void * image_vec_6_2703_data;
const void * image_vec_6_2704 = NULL;
extern const void * image_vec_6_2704_data;
const void * image_vec_6_2705 = NULL;
extern const void * image_vec_6_2705_data;
const void * image_vec_6_2706 = NULL;
extern const void * image_vec_6_2706_data;
const void * image_vec_6_2707 = NULL;
extern const void * image_vec_6_2707_data;
const void * image_vec_6_2708 = NULL;
extern const void * image_vec_6_2708_data;
const void * image_vec_6_2709 = NULL;
extern const void * image_vec_6_2709_data;
const void * image_vec_6_2710 = NULL;
extern const void * image_vec_6_2710_data;
const void * image_vec_6_2711 = NULL;
extern const void * image_vec_6_2711_data;
const void * image_vec_6_2712 = NULL;
extern const void * image_vec_6_2712_data;
const void * image_vec_6_2713 = NULL;
extern const void * image_vec_6_2713_data;
const void * image_vec_6_2714 = NULL;
extern const void * image_vec_6_2714_data;
const void * image_vec_6_2715 = NULL;
extern const void * image_vec_6_2715_data;
const void * image_vec_6_2716 = NULL;
extern const void * image_vec_6_2716_data;
const void * image_vec_6_2717 = NULL;
extern const void * image_vec_6_2717_data;
const void * image_vec_6_2718 = NULL;
extern const void * image_vec_6_2718_data;
const void * image_vec_6_2719 = NULL;
extern const void * image_vec_6_2719_data;
const void * image_vec_6_2720 = NULL;
extern const void * image_vec_6_2720_data;
const void * image_vec_6_2721 = NULL;
extern const void * image_vec_6_2721_data;
const void * image_vec_6_2722 = NULL;
extern const void * image_vec_6_2722_data;
const void * image_vec_6_2723 = NULL;
extern const void * image_vec_6_2723_data;
const void * image_vec_6_2724 = NULL;
extern const void * image_vec_6_2724_data;
const void * image_vec_6_2725 = NULL;
extern const void * image_vec_6_2725_data;
const void * image_vec_6_2726 = NULL;
extern const void * image_vec_6_2726_data;
const void * image_vec_6_2727 = NULL;
extern const void * image_vec_6_2727_data;
const void * image_vec_6_2728 = NULL;
extern const void * image_vec_6_2728_data;
const void * image_vec_6_2729 = NULL;
extern const void * image_vec_6_2729_data;
const void * image_vec_6_2730 = NULL;
extern const void * image_vec_6_2730_data;
const void * image_vec_6_2731 = NULL;
extern const void * image_vec_6_2731_data;
const void * image_vec_6_2732 = NULL;
extern const void * image_vec_6_2732_data;
const void * image_vec_6_2733 = NULL;
extern const void * image_vec_6_2733_data;
const void * image_vec_6_2734 = NULL;
extern const void * image_vec_6_2734_data;
const void * image_vec_6_2735 = NULL;
extern const void * image_vec_6_2735_data;
const void * image_vec_6_2736 = NULL;
extern const void * image_vec_6_2736_data;
const void * image_vec_6_2737 = NULL;
extern const void * image_vec_6_2737_data;
const void * image_vec_6_2738 = NULL;
extern const void * image_vec_6_2738_data;
const void * image_vec_6_2739 = NULL;
extern const void * image_vec_6_2739_data;
const void * image_vec_6_2740 = NULL;
extern const void * image_vec_6_2740_data;
const void * image_vec_6_2741 = NULL;
extern const void * image_vec_6_2741_data;
const void * image_vec_6_2742 = NULL;
extern const void * image_vec_6_2742_data;
const void * image_vec_6_2743 = NULL;
extern const void * image_vec_6_2743_data;
const void * image_vec_6_2744 = NULL;
extern const void * image_vec_6_2744_data;
const void * image_vec_6_2745 = NULL;
extern const void * image_vec_6_2745_data;
const void * image_vec_6_2746 = NULL;
extern const void * image_vec_6_2746_data;
const void * image_vec_6_2747 = NULL;
extern const void * image_vec_6_2747_data;
const void * image_vec_6_2748 = NULL;
extern const void * image_vec_6_2748_data;
const void * image_vec_6_2749 = NULL;
extern const void * image_vec_6_2749_data;
const void * image_vec_6_2750 = NULL;
extern const void * image_vec_6_2750_data;
const void * image_vec_6_2751 = NULL;
extern const void * image_vec_6_2751_data;
const void * image_vec_6_2752 = NULL;
extern const void * image_vec_6_2752_data;
const void * image_vec_6_2753 = NULL;
extern const void * image_vec_6_2753_data;
const void * image_vec_6_2754 = NULL;
extern const void * image_vec_6_2754_data;
const void * image_vec_6_2755 = NULL;
extern const void * image_vec_6_2755_data;
const void * image_vec_6_2756 = NULL;
extern const void * image_vec_6_2756_data;
const void * image_vec_6_2757 = NULL;
extern const void * image_vec_6_2757_data;
const void * image_vec_6_2758 = NULL;
extern const void * image_vec_6_2758_data;
const void * image_vec_6_2759 = NULL;
extern const void * image_vec_6_2759_data;
const void * image_vec_6_2760 = NULL;
extern const void * image_vec_6_2760_data;
const void * image_vec_6_2761 = NULL;
extern const void * image_vec_6_2761_data;
const void * image_vec_6_2762 = NULL;
extern const void * image_vec_6_2762_data;
const void * image_vec_6_2763 = NULL;
extern const void * image_vec_6_2763_data;
const void * image_vec_6_2764 = NULL;
extern const void * image_vec_6_2764_data;
const void * image_vec_6_2765 = NULL;
extern const void * image_vec_6_2765_data;
const void * image_vec_6_2766 = NULL;
extern const void * image_vec_6_2766_data;
const void * image_vec_6_2767 = NULL;
extern const void * image_vec_6_2767_data;
const void * image_vec_6_2768 = NULL;
extern const void * image_vec_6_2768_data;
const void * image_vec_6_2769 = NULL;
extern const void * image_vec_6_2769_data;
const void * image_vec_6_2770 = NULL;
extern const void * image_vec_6_2770_data;
const void * image_vec_6_2771 = NULL;
extern const void * image_vec_6_2771_data;
const void * image_vec_6_2772 = NULL;
extern const void * image_vec_6_2772_data;
const void * image_vec_6_2773 = NULL;
extern const void * image_vec_6_2773_data;
const void * image_vec_6_2774 = NULL;
extern const void * image_vec_6_2774_data;
const void * image_vec_6_2775 = NULL;
extern const void * image_vec_6_2775_data;
const void * image_vec_6_2776 = NULL;
extern const void * image_vec_6_2776_data;
const void * image_vec_6_2777 = NULL;
extern const void * image_vec_6_2777_data;
const void * image_vec_6_2778 = NULL;
extern const void * image_vec_6_2778_data;
const void * image_vec_6_2779 = NULL;
extern const void * image_vec_6_2779_data;
const void * image_vec_6_2780 = NULL;
extern const void * image_vec_6_2780_data;
const void * image_vec_6_2781 = NULL;
extern const void * image_vec_6_2781_data;
const void * image_vec_6_2782 = NULL;
extern const void * image_vec_6_2782_data;
const void * image_vec_6_2783 = NULL;
extern const void * image_vec_6_2783_data;
const void * image_vec_6_2784 = NULL;
extern const void * image_vec_6_2784_data;
const void * image_vec_6_2785 = NULL;
extern const void * image_vec_6_2785_data;
const void * image_vec_6_2786 = NULL;
extern const void * image_vec_6_2786_data;
const void * image_vec_6_2787 = NULL;
extern const void * image_vec_6_2787_data;
const void * image_vec_6_2788 = NULL;
extern const void * image_vec_6_2788_data;
const void * image_vec_6_2789 = NULL;
extern const void * image_vec_6_2789_data;
const void * image_vec_6_2790 = NULL;
extern const void * image_vec_6_2790_data;
const void * image_vec_6_2791 = NULL;
extern const void * image_vec_6_2791_data;
const void * image_vec_6_2792 = NULL;
extern const void * image_vec_6_2792_data;
const void * image_vec_6_2793 = NULL;
extern const void * image_vec_6_2793_data;
const void * image_vec_6_2794 = NULL;
extern const void * image_vec_6_2794_data;
const void * image_vec_6_2795 = NULL;
extern const void * image_vec_6_2795_data;
const void * image_vec_6_2796 = NULL;
extern const void * image_vec_6_2796_data;
const void * image_vec_6_2797 = NULL;
extern const void * image_vec_6_2797_data;
const void * image_vec_6_2798 = NULL;
extern const void * image_vec_6_2798_data;
const void * image_vec_6_2799 = NULL;
extern const void * image_vec_6_2799_data;
const void * image_vec_6_2800 = NULL;
extern const void * image_vec_6_2800_data;
const void * image_vec_6_2801 = NULL;
extern const void * image_vec_6_2801_data;
const void * image_vec_6_2802 = NULL;
extern const void * image_vec_6_2802_data;
const void * image_vec_6_2803 = NULL;
extern const void * image_vec_6_2803_data;
const void * image_vec_6_2804 = NULL;
extern const void * image_vec_6_2804_data;
const void * image_vec_6_2805 = NULL;
extern const void * image_vec_6_2805_data;
const void * image_vec_6_2806 = NULL;
extern const void * image_vec_6_2806_data;
const void * image_vec_6_2807 = NULL;
extern const void * image_vec_6_2807_data;
const void * image_vec_6_2808 = NULL;
extern const void * image_vec_6_2808_data;
const void * image_vec_6_2809 = NULL;
extern const void * image_vec_6_2809_data;
const void * image_vec_6_2810 = NULL;
extern const void * image_vec_6_2810_data;
const void * image_vec_6_2811 = NULL;
extern const void * image_vec_6_2811_data;
const void * image_vec_6_2812 = NULL;
extern const void * image_vec_6_2812_data;
const void * image_vec_6_2813 = NULL;
extern const void * image_vec_6_2813_data;
const void * image_vec_6_2814 = NULL;
extern const void * image_vec_6_2814_data;
const void * image_vec_6_2815 = NULL;
extern const void * image_vec_6_2815_data;
const void * image_vec_6_2816 = NULL;
extern const void * image_vec_6_2816_data;
const void * image_vec_6_2817 = NULL;
extern const void * image_vec_6_2817_data;
const void * image_vec_6_2818 = NULL;
extern const void * image_vec_6_2818_data;
const void * image_vec_6_2819 = NULL;
extern const void * image_vec_6_2819_data;
const void * image_vec_6_2820 = NULL;
extern const void * image_vec_6_2820_data;
const void * image_vec_6_2821 = NULL;
extern const void * image_vec_6_2821_data;
const void * image_vec_6_2822 = NULL;
extern const void * image_vec_6_2822_data;
const void * image_vec_6_2823 = NULL;
extern const void * image_vec_6_2823_data;
const void * image_vec_6_2824 = NULL;
extern const void * image_vec_6_2824_data;
const void * image_vec_6_2825 = NULL;
extern const void * image_vec_6_2825_data;
const void * image_vec_6_2826 = NULL;
extern const void * image_vec_6_2826_data;
const void * image_vec_6_2827 = NULL;
extern const void * image_vec_6_2827_data;
const void * image_vec_6_2828 = NULL;
extern const void * image_vec_6_2828_data;
const void * image_vec_6_2829 = NULL;
extern const void * image_vec_6_2829_data;
const void * image_vec_6_2830 = NULL;
extern const void * image_vec_6_2830_data;
const void * image_vec_6_2831 = NULL;
extern const void * image_vec_6_2831_data;
const void * image_vec_6_2832 = NULL;
extern const void * image_vec_6_2832_data;
const void * image_vec_6_2833 = NULL;
extern const void * image_vec_6_2833_data;
const void * image_vec_6_2834 = NULL;
extern const void * image_vec_6_2834_data;
const void * image_vec_6_2835 = NULL;
extern const void * image_vec_6_2835_data;
const void * image_vec_6_2836 = NULL;
extern const void * image_vec_6_2836_data;
const void * image_vec_6_2837 = NULL;
extern const void * image_vec_6_2837_data;
const void * image_vec_6_2838 = NULL;
extern const void * image_vec_6_2838_data;
const void * image_vec_6_2839 = NULL;
extern const void * image_vec_6_2839_data;
const void * image_vec_6_2840 = NULL;
extern const void * image_vec_6_2840_data;
const void * image_vec_6_2841 = NULL;
extern const void * image_vec_6_2841_data;
const void * image_vec_6_2842 = NULL;
extern const void * image_vec_6_2842_data;
const void * image_vec_6_2843 = NULL;
extern const void * image_vec_6_2843_data;
const void * image_vec_6_2844 = NULL;
extern const void * image_vec_6_2844_data;
const void * image_vec_6_2845 = NULL;
extern const void * image_vec_6_2845_data;
const void * image_vec_6_2846 = NULL;
extern const void * image_vec_6_2846_data;
const void * image_vec_6_2847 = NULL;
extern const void * image_vec_6_2847_data;
const void * image_vec_6_2848 = NULL;
extern const void * image_vec_6_2848_data;
const void * image_vec_6_2849 = NULL;
extern const void * image_vec_6_2849_data;
const void * image_vec_6_2850 = NULL;
extern const void * image_vec_6_2850_data;
const void * image_vec_6_2851 = NULL;
extern const void * image_vec_6_2851_data;
const void * image_vec_6_2852 = NULL;
extern const void * image_vec_6_2852_data;
const void * image_vec_6_2853 = NULL;
extern const void * image_vec_6_2853_data;
const void * image_vec_6_2854 = NULL;
extern const void * image_vec_6_2854_data;
const void * image_vec_6_2855 = NULL;
extern const void * image_vec_6_2855_data;
const void * image_vec_6_2856 = NULL;
extern const void * image_vec_6_2856_data;
const void * image_vec_6_2857 = NULL;
extern const void * image_vec_6_2857_data;
const void * image_vec_6_2858 = NULL;
extern const void * image_vec_6_2858_data;
const void * image_vec_6_2859 = NULL;
extern const void * image_vec_6_2859_data;
const void * image_vec_6_2860 = NULL;
extern const void * image_vec_6_2860_data;
const void * image_vec_6_2861 = NULL;
extern const void * image_vec_6_2861_data;
const void * image_vec_6_2862 = NULL;
extern const void * image_vec_6_2862_data;
const void * image_vec_6_2863 = NULL;
extern const void * image_vec_6_2863_data;
const void * image_vec_6_2864 = NULL;
extern const void * image_vec_6_2864_data;
const void * image_vec_6_2865 = NULL;
extern const void * image_vec_6_2865_data;
const void * image_vec_6_2866 = NULL;
extern const void * image_vec_6_2866_data;
const void * image_vec_6_2867 = NULL;
extern const void * image_vec_6_2867_data;
const void * image_vec_6_2868 = NULL;
extern const void * image_vec_6_2868_data;
const void * image_vec_6_2869 = NULL;
extern const void * image_vec_6_2869_data;
const void * image_vec_6_2870 = NULL;
extern const void * image_vec_6_2870_data;
const void * image_vec_6_2871 = NULL;
extern const void * image_vec_6_2871_data;
const void * image_vec_6_2872 = NULL;
extern const void * image_vec_6_2872_data;
const void * image_vec_6_2873 = NULL;
extern const void * image_vec_6_2873_data;
const void * image_vec_6_2874 = NULL;
extern const void * image_vec_6_2874_data;
const void * image_vec_6_2875 = NULL;
extern const void * image_vec_6_2875_data;
const void * image_vec_6_2876 = NULL;
extern const void * image_vec_6_2876_data;
const void * image_vec_6_2877 = NULL;
extern const void * image_vec_6_2877_data;
const void * image_vec_6_2878 = NULL;
extern const void * image_vec_6_2878_data;
const void * image_vec_6_2879 = NULL;
extern const void * image_vec_6_2879_data;
const void * image_vec_6_2880 = NULL;
extern const void * image_vec_6_2880_data;
const void * image_vec_6_2881 = NULL;
extern const void * image_vec_6_2881_data;
const void * image_vec_6_2882 = NULL;
extern const void * image_vec_6_2882_data;
const void * image_vec_6_2883 = NULL;
extern const void * image_vec_6_2883_data;
const void * image_vec_6_2884 = NULL;
extern const void * image_vec_6_2884_data;
const void * image_vec_6_2885 = NULL;
extern const void * image_vec_6_2885_data;
const void * image_vec_6_2886 = NULL;
extern const void * image_vec_6_2886_data;
const void * image_vec_6_2887 = NULL;
extern const void * image_vec_6_2887_data;
const void * image_vec_6_2888 = NULL;
extern const void * image_vec_6_2888_data;
const void * image_vec_6_2889 = NULL;
extern const void * image_vec_6_2889_data;
const void * image_vec_6_2890 = NULL;
extern const void * image_vec_6_2890_data;
const void * image_vec_6_2891 = NULL;
extern const void * image_vec_6_2891_data;
const void * image_vec_6_2892 = NULL;
extern const void * image_vec_6_2892_data;
const void * image_vec_6_2893 = NULL;
extern const void * image_vec_6_2893_data;
const void * image_vec_6_2894 = NULL;
extern const void * image_vec_6_2894_data;
const void * image_vec_6_2895 = NULL;
extern const void * image_vec_6_2895_data;
const void * image_vec_6_2896 = NULL;
extern const void * image_vec_6_2896_data;
const void * image_vec_6_2897 = NULL;
extern const void * image_vec_6_2897_data;
const void * image_vec_6_2898 = NULL;
extern const void * image_vec_6_2898_data;
const void * image_vec_6_2899 = NULL;
extern const void * image_vec_6_2899_data;
const void * image_vec_6_2900 = NULL;
extern const void * image_vec_6_2900_data;
const void * image_vec_6_2901 = NULL;
extern const void * image_vec_6_2901_data;
const void * image_vec_6_2902 = NULL;
extern const void * image_vec_6_2902_data;
const void * image_vec_6_2903 = NULL;
extern const void * image_vec_6_2903_data;
const void * image_vec_6_2904 = NULL;
extern const void * image_vec_6_2904_data;
const void * image_vec_6_2905 = NULL;
extern const void * image_vec_6_2905_data;
const void * image_vec_6_2906 = NULL;
extern const void * image_vec_6_2906_data;
const void * image_vec_6_2907 = NULL;
extern const void * image_vec_6_2907_data;
const void * image_vec_6_2908 = NULL;
extern const void * image_vec_6_2908_data;
const void * image_vec_6_2909 = NULL;
extern const void * image_vec_6_2909_data;
const void * image_vec_6_2910 = NULL;
extern const void * image_vec_6_2910_data;
const void * image_vec_6_2911 = NULL;
extern const void * image_vec_6_2911_data;
const void * image_vec_6_2912 = NULL;
extern const void * image_vec_6_2912_data;
const void * image_vec_6_2913 = NULL;
extern const void * image_vec_6_2913_data;
const void * image_vec_6_2914 = NULL;
extern const void * image_vec_6_2914_data;
const void * image_vec_6_2915 = NULL;
extern const void * image_vec_6_2915_data;
const void * image_vec_6_2916 = NULL;
extern const void * image_vec_6_2916_data;
const void * image_vec_6_2917 = NULL;
extern const void * image_vec_6_2917_data;
const void * image_vec_6_2918 = NULL;
extern const void * image_vec_6_2918_data;
const void * image_vec_6_2919 = NULL;
extern const void * image_vec_6_2919_data;
const void * image_vec_6_2920 = NULL;
extern const void * image_vec_6_2920_data;
const void * image_vec_6_2921 = NULL;
extern const void * image_vec_6_2921_data;
const void * image_vec_6_2922 = NULL;
extern const void * image_vec_6_2922_data;
const void * image_vec_6_2923 = NULL;
extern const void * image_vec_6_2923_data;
const void * image_vec_6_2924 = NULL;
extern const void * image_vec_6_2924_data;
const void * image_vec_6_2925 = NULL;
extern const void * image_vec_6_2925_data;
const void * image_vec_6_2926 = NULL;
extern const void * image_vec_6_2926_data;
const void * image_vec_6_2927 = NULL;
extern const void * image_vec_6_2927_data;
const void * image_vec_6_2928 = NULL;
extern const void * image_vec_6_2928_data;
const void * image_vec_6_2929 = NULL;
extern const void * image_vec_6_2929_data;
const void * image_vec_6_2930 = NULL;
extern const void * image_vec_6_2930_data;
const void * image_vec_6_2931 = NULL;
extern const void * image_vec_6_2931_data;
const void * image_vec_6_2932 = NULL;
extern const void * image_vec_6_2932_data;
const void * image_vec_6_2933 = NULL;
extern const void * image_vec_6_2933_data;
const void * image_vec_6_2934 = NULL;
extern const void * image_vec_6_2934_data;
const void * image_vec_6_2935 = NULL;
extern const void * image_vec_6_2935_data;
const void * image_vec_6_2936 = NULL;
extern const void * image_vec_6_2936_data;
const void * image_vec_6_2937 = NULL;
extern const void * image_vec_6_2937_data;
const void * image_vec_6_2938 = NULL;
extern const void * image_vec_6_2938_data;
const void * image_vec_6_2939 = NULL;
extern const void * image_vec_6_2939_data;
const void * image_vec_6_2940 = NULL;
extern const void * image_vec_6_2940_data;
const void * image_vec_6_2943 = NULL;
extern const void * image_vec_6_2943_data;
const void * image_vec_6_2944 = NULL;
extern const void * image_vec_6_2944_data;
const void * image_vec_6_2947 = NULL;
extern const void * image_vec_6_2947_data;
const void * image_vec_6_2948 = NULL;
extern const void * image_vec_6_2948_data;
const void * image_vec_6_2951 = NULL;
extern const void * image_vec_6_2951_data;
const void * image_vec_6_2952 = NULL;
extern const void * image_vec_6_2952_data;
const void * image_vec_6_2955 = NULL;
extern const void * image_vec_6_2955_data;
const void * image_vec_6_2956 = NULL;
extern const void * image_vec_6_2956_data;
const void * image_vec_6_2959 = NULL;
extern const void * image_vec_6_2959_data;
const void * image_vec_6_2960 = NULL;
extern const void * image_vec_6_2960_data;
const void * image_vec_6_2963 = NULL;
extern const void * image_vec_6_2963_data;
const void * image_vec_6_2964 = NULL;
extern const void * image_vec_6_2964_data;
const void * image_vec_25_1105 = NULL;
extern const void * image_vec_25_1105_data;
const void * image_vec_7_1412 = NULL;
extern const void * image_vec_7_1412_data;
const void * image_vec_1_241 = NULL;
extern const void * image_vec_1_241_data;
const void * image_vec_7_1491 = NULL;
extern const void * image_vec_7_1491_data;
const void * image_vec_7_1493 = NULL;
extern const void * image_vec_7_1493_data;
const void * image_vec_1_790 = NULL;
extern const void * image_vec_1_790_data;
const void * image_vec_1_882 = NULL;
extern const void * image_vec_1_882_data;
const void * image_vec_25_1004 = NULL;
extern const void * image_vec_25_1004_data;
const void * image_vec_7_1415 = NULL;
extern const void * image_vec_7_1415_data;
const void * image_vec_23_214 = NULL;
extern const void * image_vec_23_214_data;
const void * image_vec_42_2416 = NULL;
extern const void * image_vec_42_2416_data;
const void * image_vec_42_2418 = NULL;
extern const void * image_vec_42_2418_data;
const void * image_vec_34_869 = NULL;
extern const void * image_vec_34_869_data;
const void * image_vec_34_872 = NULL;
extern const void * image_vec_34_872_data;
const void * image_vec_23_372 = NULL;
extern const void * image_vec_23_372_data;
const void * image_vec_42_877 = NULL;
extern const void * image_vec_42_877_data;
const void * image_vec_12_212 = NULL;
extern const void * image_vec_12_212_data;
const void * image_vec_42_862 = NULL;
extern const void * image_vec_42_862_data;
const void * image_vec_7_1590 = NULL;
extern const void * image_vec_7_1590_data;
const void * image_vec_46_963 = NULL;
extern const void * image_vec_46_963_data;
const void * image_vec_46_964 = NULL;
extern const void * image_vec_46_964_data;
const void * image_vec_46_965 = NULL;
extern const void * image_vec_46_965_data;
const void * image_vec_46_966 = NULL;
extern const void * image_vec_46_966_data;
const void * image_vec_46_967 = NULL;
extern const void * image_vec_46_967_data;
const void * image_vec_46_968 = NULL;
extern const void * image_vec_46_968_data;
const void * image_vec_46_969 = NULL;
extern const void * image_vec_46_969_data;
const void * image_vec_46_970 = NULL;
extern const void * image_vec_46_970_data;
const void * image_vec_46_971 = NULL;
extern const void * image_vec_46_971_data;
const void * image_vec_46_972 = NULL;
extern const void * image_vec_46_972_data;
const void * image_vec_46_973 = NULL;
extern const void * image_vec_46_973_data;
const void * image_vec_46_974 = NULL;
extern const void * image_vec_46_974_data;
const void * image_vec_46_975 = NULL;
extern const void * image_vec_46_975_data;
const void * image_vec_46_976 = NULL;
extern const void * image_vec_46_976_data;
const void * image_vec_46_977 = NULL;
extern const void * image_vec_46_977_data;
const void * image_vec_46_978 = NULL;
extern const void * image_vec_46_978_data;
const void * image_vec_46_979 = NULL;
extern const void * image_vec_46_979_data;
const void * image_vec_46_980 = NULL;
extern const void * image_vec_46_980_data;
const void * image_vec_46_981 = NULL;
extern const void * image_vec_46_981_data;
const void * image_vec_46_982 = NULL;
extern const void * image_vec_46_982_data;
const void * image_vec_46_983 = NULL;
extern const void * image_vec_46_983_data;
const void * image_vec_46_984 = NULL;
extern const void * image_vec_46_984_data;
const void * image_vec_46_985 = NULL;
extern const void * image_vec_46_985_data;
const void * image_vec_46_986 = NULL;
extern const void * image_vec_46_986_data;
const void * image_vec_46_987 = NULL;
extern const void * image_vec_46_987_data;
const void * image_vec_46_988 = NULL;
extern const void * image_vec_46_988_data;
const void * image_vec_46_989 = NULL;
extern const void * image_vec_46_989_data;
const void * image_vec_46_990 = NULL;
extern const void * image_vec_46_990_data;
const void * image_vec_46_991 = NULL;
extern const void * image_vec_46_991_data;
const void * image_vec_46_992 = NULL;
extern const void * image_vec_46_992_data;
const void * image_vec_46_993 = NULL;
extern const void * image_vec_46_993_data;
const void * image_vec_46_994 = NULL;
extern const void * image_vec_46_994_data;
const void * image_vec_46_995 = NULL;
extern const void * image_vec_46_995_data;
const void * image_vec_46_996 = NULL;
extern const void * image_vec_46_996_data;
const void * image_vec_46_997 = NULL;
extern const void * image_vec_46_997_data;
const void * image_vec_46_998 = NULL;
extern const void * image_vec_46_998_data;

/*----------------
 * Global styles
 *----------------*/

lv_style_t style_screen_base_global;
lv_style_t style_state_on;
lv_style_t style_state_good;
lv_style_t style_state_off;
lv_style_t style_state_warn;
lv_style_t style_dot_on;
lv_style_t style_dot_off;

/*----------------
 * Subjects
 *----------------*/

lv_subject_t brightness_percent;
lv_subject_t battery_percent;
lv_subject_t time_text;
lv_subject_t ampm_text;
lv_subject_t date_text;
lv_subject_t wifi_status;
lv_subject_t wifi_name;
lv_subject_t wifi_state;
lv_subject_t bluetooth_on;
lv_subject_t usb_power;
lv_subject_t power_state;
lv_subject_t power_mode_text;
lv_subject_t sd_text;
lv_subject_t sd_percent;
lv_subject_t pin_storage_text;
lv_subject_t pin_storage_percent;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void plurality_pin_init_gen(const char * asset_path)
{
    char buf[256];


    /*----------------
     * Fonts
     *----------------*/

    /* Targets: any */

    #if PLURALITY_PIN_CHECK_COMPILE_TARGET(PLURALITY_PIN_TARGET_ALL)
    if (plurality_pin_check_target(PLURALITY_PIN_TARGET_ALL)) {
        if (!font_ibm_plex_mono_regular_26) {
            /* font_ibm_plex_mono_regular_26 */
            /* create tiny ttf font "font_ibm_plex_mono_regular_26" from file */
            font_ibm_plex_mono_regular_26 = (lv_font_t *)&bitmap_ibmplexmono_regular_26;  /* IBMPlexMono-Regular.ttf at 26 px */
        }
        if (!font_ibm_plex_mono_semibold_150) {
            /* font_ibm_plex_mono_semibold_150 */
            /* create tiny ttf font "font_ibm_plex_mono_semibold_150" from file */
            font_ibm_plex_mono_semibold_150 = (lv_font_t *)&bitmap_ibmplexmono_semibold_150;  /* IBMPlexMono-SemiBold.ttf at 150 px */
        }
        if (!font_inter_medium_24_460227966308594) {
            /* font_inter_medium_24_460227966308594 */
            /* create tiny ttf font "font_inter_medium_24_460227966308594" from file */
            font_inter_medium_24_460227966308594 = (lv_font_t *)&bitmap_inter_medium_24;  /* Inter-Medium.ttf at 24 px */
        }
        if (!font_roboto_semibold_22) {
            /* font_roboto_semibold_22 */
            /* create tiny ttf font "font_roboto_semibold_22" from file */
            font_roboto_semibold_22 = (lv_font_t *)&bitmap_roboto_semibold_22;  /* Roboto-SemiBold.ttf at 22 px */
        }
        if (!font_inter_semi_bold_12) {
            /* font_inter_semi_bold_12 */
            /* create tiny ttf font "font_inter_semi_bold_12" from file */
            font_inter_semi_bold_12 = (lv_font_t *)&bitmap_inter_semibold_12;  /* Inter-SemiBold.ttf at 12 px */
        }
        if (!font_inter_bold_28) {
            /* font_inter_bold_28 */
            /* create tiny ttf font "font_inter_bold_28" from file */
            font_inter_bold_28 = (lv_font_t *)&bitmap_inter_bold_28;  /* Inter-Bold.ttf at 28 px */
        }
        if (!font_inter_semi_bold_16) {
            /* font_inter_semi_bold_16 */
            /* create tiny ttf font "font_inter_semi_bold_16" from file */
            font_inter_semi_bold_16 = (lv_font_t *)&bitmap_inter_semibold_16;  /* Inter-SemiBold.ttf at 16 px */
        }
        if (!font_inter_semi_bold_14) {
            /* font_inter_semi_bold_14 */
            /* create tiny ttf font "font_inter_semi_bold_14" from file */
            font_inter_semi_bold_14 = (lv_font_t *)&bitmap_inter_semibold_14;  /* Inter-SemiBold.ttf at 14 px */
        }
        if (!font_inter_medium_11) {
            /* font_inter_medium_11 */
            /* create tiny ttf font "font_inter_medium_11" from file */
            font_inter_medium_11 = (lv_font_t *)&bitmap_inter_medium_11;  /* Inter-Medium.ttf at 11 px */
        }
        if (!font_inter_bold_14) {
            /* font_inter_bold_14 */
            /* create tiny ttf font "font_inter_bold_14" from file */
            font_inter_bold_14 = (lv_font_t *)&bitmap_inter_bold_14;  /* Inter-Bold.ttf at 14 px */
        }
        if (!font_inter_bold_20) {
            /* font_inter_bold_20 */
            /* create tiny ttf font "font_inter_bold_20" from file */
            font_inter_bold_20 = (lv_font_t *)&bitmap_inter_bold_20;  /* Inter-Bold.ttf at 20 px */
        }
        if (!font_inter_bold_23) {
            /* font_inter_bold_23 */
            /* create tiny ttf font "font_inter_bold_23" from file */
            font_inter_bold_23 = (lv_font_t *)&bitmap_inter_bold_23;  /* Inter-Bold.ttf at 23 px */
        }
        if (!font_inter_semi_bold_13) {
            /* font_inter_semi_bold_13 */
            /* create tiny ttf font "font_inter_semi_bold_13" from file */
            font_inter_semi_bold_13 = (lv_font_t *)&bitmap_inter_semibold_13;  /* Inter-SemiBold.ttf at 13 px */
        }
        if (!font_playwrite_us_trad_regular_40) {
            /* font_playwrite_us_trad_regular_40 */
            /* create tiny ttf font "font_playwrite_us_trad_regular_40" from file */
            font_playwrite_us_trad_regular_40 = (lv_font_t *)&bitmap_playwriteustrad_regular_40;  /* PlaywriteUSTrad-Regular.ttf at 40 px */
        }
        if (!font_playwrite_us_trad_regular_52) {
            /* font_playwrite_us_trad_regular_52 */
            /* create tiny ttf font "font_playwrite_us_trad_regular_52" from file */
            font_playwrite_us_trad_regular_52 = (lv_font_t *)&bitmap_playwriteustrad_regular_52;  /* PlaywriteUSTrad-Regular.ttf at 52 px */
        }
        if (!font_inter_semi_bold_8) {
            /* font_inter_semi_bold_8 */
            /* create tiny ttf font "font_inter_semi_bold_8" from file */
            font_inter_semi_bold_8 = (lv_font_t *)&bitmap_inter_semibold_8;  /* Inter-SemiBold.ttf at 8 px */
        }
        if (!font_inter_semi_bold_11) {
            /* font_inter_semi_bold_11 */
            /* create tiny ttf font "font_inter_semi_bold_11" from file */
            font_inter_semi_bold_11 = (lv_font_t *)&bitmap_inter_semibold_11;  /* Inter-SemiBold.ttf at 11 px */
        }
        if (!font_roboto_medium_14) {
            /* font_roboto_medium_14 */
            /* create tiny ttf font "font_roboto_medium_14" from file */
            font_roboto_medium_14 = (lv_font_t *)&bitmap_roboto_medium_14;  /* Roboto-Medium.ttf at 14 px */
        }
        if (!font_ibm_plex_mono_regular_36) {
            /* font_ibm_plex_mono_regular_36 */
            /* create tiny ttf font "font_ibm_plex_mono_regular_36" from file */
            font_ibm_plex_mono_regular_36 = (lv_font_t *)&bitmap_ibmplexmono_regular_36;  /* IBMPlexMono-Regular.ttf at 36 px */
        }
        if (!font_roboto_medium_16) {
            /* font_roboto_medium_16 */
            /* create tiny ttf font "font_roboto_medium_16" from file */
            font_roboto_medium_16 = (lv_font_t *)&bitmap_inter_medium_16;  /* Inter-Medium.ttf at 16 px */
        }
        if (!font_ibm_plex_mono_medium_14) {
            /* font_ibm_plex_mono_medium_14 */
            /* create tiny ttf font "font_ibm_plex_mono_medium_14" from file */
            font_ibm_plex_mono_medium_14 = (lv_font_t *)&bitmap_ibmplexmono_medium_14;  /* IBMPlexMono-Medium.ttf at 14 px */
        }
        if (!font_ibm_plex_mono_regular_29) {
            /* font_ibm_plex_mono_regular_29 */
            /* create tiny ttf font "font_ibm_plex_mono_regular_29" from file */
            font_ibm_plex_mono_regular_29 = (lv_font_t *)&bitmap_ibmplexmono_regular_29;  /* IBMPlexMono-Regular.ttf at 29 px */
        }
        if (!font_inter_medium_24_manual) {
            /* font_inter_medium_24_manual */
            /* create tiny ttf font "font_inter_medium_24_manual" from file */
            font_inter_medium_24_manual = (lv_font_t *)&bitmap_inter_medium_24;  /* Inter-Medium.ttf at 24 px */
        }
        if (!font_inter_semi_bold_22_manual) {
            /* font_inter_semi_bold_22_manual */
            /* create tiny ttf font "font_inter_semi_bold_22_manual" from file */
            font_inter_semi_bold_22_manual = (lv_font_t *)&bitmap_inter_semibold_22;  /* Inter-SemiBold.ttf at 22 px */
        }
    }
    #endif

    /*----------------
     * Images
     *----------------*/

    /* Targets: any */
    #if PLURALITY_PIN_CHECK_COMPILE_TARGET(PLURALITY_PIN_TARGET_ALL)
    if (plurality_pin_check_target(PLURALITY_PIN_TARGET_ALL)) {
        /* image_img_02c5506b */
        if (!image_img_02c5506b) {
            image_img_02c5506b = assets_image(4);  /* img_02c5506b */
        }
        /* image_img_45c6bb3a */
        if (!image_img_45c6bb3a) {
            image_img_45c6bb3a = assets_image(5);  /* img_45c6bb3a */
        }
        /* image_vec_37_864 */
        if (!image_vec_37_864) {
            image_vec_37_864 = assets_image(20);  /* vec_37_864 */
        }
        /* image_vec_6_2604 */
        if (!image_vec_6_2604) {
            image_vec_6_2604 = assets_image(61);  /* vec_6_2604 */
        }
        /* image_vec_6_2605 */
        if (!image_vec_6_2605) {
            image_vec_6_2605 = assets_image(62);  /* vec_6_2605 */
        }
        /* image_vec_6_2608 */
        if (!image_vec_6_2608) {
            image_vec_6_2608 = assets_image(63);  /* vec_6_2608 */
        }
        /* image_vec_6_2609 */
        if (!image_vec_6_2609) {
            image_vec_6_2609 = assets_image(64);  /* vec_6_2609 */
        }
        /* image_vec_6_2610 */
        if (!image_vec_6_2610) {
            image_vec_6_2610 = assets_image(65);  /* vec_6_2610 */
        }
        /* image_vec_6_2611 */
        if (!image_vec_6_2611) {
            image_vec_6_2611 = assets_image(66);  /* vec_6_2611 */
        }
        /* image_vec_6_2612 */
        if (!image_vec_6_2612) {
            image_vec_6_2612 = assets_image(67);  /* vec_6_2612 */
        }
        /* image_vec_6_2613 */
        if (!image_vec_6_2613) {
            image_vec_6_2613 = assets_image(68);  /* vec_6_2613 */
        }
        /* image_vec_6_2614 */
        if (!image_vec_6_2614) {
            image_vec_6_2614 = assets_image(69);  /* vec_6_2614 */
        }
        /* image_vec_6_2615 */
        if (!image_vec_6_2615) {
            image_vec_6_2615 = assets_image(70);  /* vec_6_2615 */
        }
        /* image_vec_6_2616 */
        if (!image_vec_6_2616) {
            image_vec_6_2616 = assets_image(71);  /* vec_6_2616 */
        }
        /* image_vec_6_2617 */
        if (!image_vec_6_2617) {
            image_vec_6_2617 = assets_image(72);  /* vec_6_2617 */
        }
        /* image_vec_6_2618 */
        if (!image_vec_6_2618) {
            image_vec_6_2618 = assets_image(73);  /* vec_6_2618 */
        }
        /* image_vec_6_2619 */
        if (!image_vec_6_2619) {
            image_vec_6_2619 = assets_image(74);  /* vec_6_2619 */
        }
        /* image_vec_6_2620 */
        if (!image_vec_6_2620) {
            image_vec_6_2620 = assets_image(75);  /* vec_6_2620 */
        }
        /* image_vec_6_2621 */
        if (!image_vec_6_2621) {
            image_vec_6_2621 = assets_image(76);  /* vec_6_2621 */
        }
        /* image_vec_6_2622 */
        if (!image_vec_6_2622) {
            image_vec_6_2622 = assets_image(77);  /* vec_6_2622 */
        }
        /* image_vec_6_2623 */
        if (!image_vec_6_2623) {
            image_vec_6_2623 = assets_image(78);  /* vec_6_2623 */
        }
        /* image_vec_6_2624 */
        if (!image_vec_6_2624) {
            image_vec_6_2624 = assets_image(79);  /* vec_6_2624 */
        }
        /* image_vec_6_2625 */
        if (!image_vec_6_2625) {
            image_vec_6_2625 = assets_image(80);  /* vec_6_2625 */
        }
        /* image_vec_6_2626 */
        if (!image_vec_6_2626) {
            image_vec_6_2626 = assets_image(81);  /* vec_6_2626 */
        }
        /* image_vec_6_2627 */
        if (!image_vec_6_2627) {
            image_vec_6_2627 = assets_image(82);  /* vec_6_2627 */
        }
        /* image_vec_6_2628 */
        if (!image_vec_6_2628) {
            image_vec_6_2628 = assets_image(83);  /* vec_6_2628 */
        }
        /* image_vec_6_2629 */
        if (!image_vec_6_2629) {
            image_vec_6_2629 = assets_image(84);  /* vec_6_2629 */
        }
        /* image_vec_6_2630 */
        if (!image_vec_6_2630) {
            image_vec_6_2630 = assets_image(85);  /* vec_6_2630 */
        }
        /* image_vec_6_2631 */
        if (!image_vec_6_2631) {
            image_vec_6_2631 = assets_image(86);  /* vec_6_2631 */
        }
        /* image_vec_6_2632 */
        if (!image_vec_6_2632) {
            image_vec_6_2632 = assets_image(87);  /* vec_6_2632 */
        }
        /* image_vec_6_2633 */
        if (!image_vec_6_2633) {
            image_vec_6_2633 = assets_image(88);  /* vec_6_2633 */
        }
        /* image_vec_6_2634 */
        if (!image_vec_6_2634) {
            image_vec_6_2634 = assets_image(89);  /* vec_6_2634 */
        }
        /* image_vec_6_2635 */
        if (!image_vec_6_2635) {
            image_vec_6_2635 = assets_image(90);  /* vec_6_2635 */
        }
        /* image_vec_6_2636 */
        if (!image_vec_6_2636) {
            image_vec_6_2636 = assets_image(91);  /* vec_6_2636 */
        }
        /* image_vec_6_2637 */
        if (!image_vec_6_2637) {
            image_vec_6_2637 = assets_image(92);  /* vec_6_2637 */
        }
        /* image_vec_6_2638 */
        if (!image_vec_6_2638) {
            image_vec_6_2638 = assets_image(93);  /* vec_6_2638 */
        }
        /* image_vec_6_2639 */
        if (!image_vec_6_2639) {
            image_vec_6_2639 = assets_image(94);  /* vec_6_2639 */
        }
        /* image_vec_6_2640 */
        if (!image_vec_6_2640) {
            image_vec_6_2640 = assets_image(95);  /* vec_6_2640 */
        }
        /* image_vec_6_2641 */
        if (!image_vec_6_2641) {
            image_vec_6_2641 = assets_image(96);  /* vec_6_2641 */
        }
        /* image_vec_6_2642 */
        if (!image_vec_6_2642) {
            image_vec_6_2642 = assets_image(97);  /* vec_6_2642 */
        }
        /* image_vec_6_2643 */
        if (!image_vec_6_2643) {
            image_vec_6_2643 = assets_image(98);  /* vec_6_2643 */
        }
        /* image_vec_6_2644 */
        if (!image_vec_6_2644) {
            image_vec_6_2644 = assets_image(99);  /* vec_6_2644 */
        }
        /* image_vec_6_2645 */
        if (!image_vec_6_2645) {
            image_vec_6_2645 = assets_image(100);  /* vec_6_2645 */
        }
        /* image_vec_6_2646 */
        if (!image_vec_6_2646) {
            image_vec_6_2646 = assets_image(101);  /* vec_6_2646 */
        }
        /* image_vec_6_2647 */
        if (!image_vec_6_2647) {
            image_vec_6_2647 = assets_image(102);  /* vec_6_2647 */
        }
        /* image_vec_6_2648 */
        if (!image_vec_6_2648) {
            image_vec_6_2648 = assets_image(103);  /* vec_6_2648 */
        }
        /* image_vec_6_2649 */
        if (!image_vec_6_2649) {
            image_vec_6_2649 = assets_image(104);  /* vec_6_2649 */
        }
        /* image_vec_6_2650 */
        if (!image_vec_6_2650) {
            image_vec_6_2650 = assets_image(105);  /* vec_6_2650 */
        }
        /* image_vec_6_2651 */
        if (!image_vec_6_2651) {
            image_vec_6_2651 = assets_image(106);  /* vec_6_2651 */
        }
        /* image_vec_6_2652 */
        if (!image_vec_6_2652) {
            image_vec_6_2652 = assets_image(107);  /* vec_6_2652 */
        }
        /* image_vec_6_2653 */
        if (!image_vec_6_2653) {
            image_vec_6_2653 = assets_image(108);  /* vec_6_2653 */
        }
        /* image_vec_6_2654 */
        if (!image_vec_6_2654) {
            image_vec_6_2654 = assets_image(109);  /* vec_6_2654 */
        }
        /* image_vec_6_2655 */
        if (!image_vec_6_2655) {
            image_vec_6_2655 = assets_image(110);  /* vec_6_2655 */
        }
        /* image_vec_6_2656 */
        if (!image_vec_6_2656) {
            image_vec_6_2656 = assets_image(111);  /* vec_6_2656 */
        }
        /* image_vec_6_2657 */
        if (!image_vec_6_2657) {
            image_vec_6_2657 = assets_image(112);  /* vec_6_2657 */
        }
        /* image_vec_6_2658 */
        if (!image_vec_6_2658) {
            image_vec_6_2658 = assets_image(113);  /* vec_6_2658 */
        }
        /* image_vec_6_2659 */
        if (!image_vec_6_2659) {
            image_vec_6_2659 = assets_image(114);  /* vec_6_2659 */
        }
        /* image_vec_6_2660 */
        if (!image_vec_6_2660) {
            image_vec_6_2660 = assets_image(115);  /* vec_6_2660 */
        }
        /* image_vec_6_2661 */
        if (!image_vec_6_2661) {
            image_vec_6_2661 = assets_image(116);  /* vec_6_2661 */
        }
        /* image_vec_6_2662 */
        if (!image_vec_6_2662) {
            image_vec_6_2662 = assets_image(117);  /* vec_6_2662 */
        }
        /* image_vec_6_2663 */
        if (!image_vec_6_2663) {
            image_vec_6_2663 = assets_image(118);  /* vec_6_2663 */
        }
        /* image_vec_6_2664 */
        if (!image_vec_6_2664) {
            image_vec_6_2664 = assets_image(119);  /* vec_6_2664 */
        }
        /* image_vec_6_2665 */
        if (!image_vec_6_2665) {
            image_vec_6_2665 = assets_image(120);  /* vec_6_2665 */
        }
        /* image_vec_6_2666 */
        if (!image_vec_6_2666) {
            image_vec_6_2666 = assets_image(121);  /* vec_6_2666 */
        }
        /* image_vec_6_2667 */
        if (!image_vec_6_2667) {
            image_vec_6_2667 = assets_image(122);  /* vec_6_2667 */
        }
        /* image_vec_6_2668 */
        if (!image_vec_6_2668) {
            image_vec_6_2668 = assets_image(123);  /* vec_6_2668 */
        }
        /* image_vec_6_2669 */
        if (!image_vec_6_2669) {
            image_vec_6_2669 = assets_image(124);  /* vec_6_2669 */
        }
        /* image_vec_6_2670 */
        if (!image_vec_6_2670) {
            image_vec_6_2670 = assets_image(125);  /* vec_6_2670 */
        }
        /* image_vec_6_2671 */
        if (!image_vec_6_2671) {
            image_vec_6_2671 = assets_image(126);  /* vec_6_2671 */
        }
        /* image_vec_6_2672 */
        if (!image_vec_6_2672) {
            image_vec_6_2672 = assets_image(127);  /* vec_6_2672 */
        }
        /* image_vec_6_2673 */
        if (!image_vec_6_2673) {
            image_vec_6_2673 = assets_image(128);  /* vec_6_2673 */
        }
        /* image_vec_6_2674 */
        if (!image_vec_6_2674) {
            image_vec_6_2674 = assets_image(129);  /* vec_6_2674 */
        }
        /* image_vec_6_2675 */
        if (!image_vec_6_2675) {
            image_vec_6_2675 = assets_image(130);  /* vec_6_2675 */
        }
        /* image_vec_6_2676 */
        if (!image_vec_6_2676) {
            image_vec_6_2676 = assets_image(131);  /* vec_6_2676 */
        }
        /* image_vec_6_2677 */
        if (!image_vec_6_2677) {
            image_vec_6_2677 = assets_image(132);  /* vec_6_2677 */
        }
        /* image_vec_6_2678 */
        if (!image_vec_6_2678) {
            image_vec_6_2678 = assets_image(133);  /* vec_6_2678 */
        }
        /* image_vec_6_2679 */
        if (!image_vec_6_2679) {
            image_vec_6_2679 = assets_image(134);  /* vec_6_2679 */
        }
        /* image_vec_6_2680 */
        if (!image_vec_6_2680) {
            image_vec_6_2680 = assets_image(135);  /* vec_6_2680 */
        }
        /* image_vec_6_2681 */
        if (!image_vec_6_2681) {
            image_vec_6_2681 = assets_image(136);  /* vec_6_2681 */
        }
        /* image_vec_6_2682 */
        if (!image_vec_6_2682) {
            image_vec_6_2682 = assets_image(137);  /* vec_6_2682 */
        }
        /* image_vec_6_2683 */
        if (!image_vec_6_2683) {
            image_vec_6_2683 = assets_image(138);  /* vec_6_2683 */
        }
        /* image_vec_6_2684 */
        if (!image_vec_6_2684) {
            image_vec_6_2684 = assets_image(139);  /* vec_6_2684 */
        }
        /* image_vec_6_2685 */
        if (!image_vec_6_2685) {
            image_vec_6_2685 = assets_image(140);  /* vec_6_2685 */
        }
        /* image_vec_6_2686 */
        if (!image_vec_6_2686) {
            image_vec_6_2686 = assets_image(141);  /* vec_6_2686 */
        }
        /* image_vec_6_2687 */
        if (!image_vec_6_2687) {
            image_vec_6_2687 = assets_image(142);  /* vec_6_2687 */
        }
        /* image_vec_6_2688 */
        if (!image_vec_6_2688) {
            image_vec_6_2688 = assets_image(143);  /* vec_6_2688 */
        }
        /* image_vec_6_2689 */
        if (!image_vec_6_2689) {
            image_vec_6_2689 = assets_image(144);  /* vec_6_2689 */
        }
        /* image_vec_6_2690 */
        if (!image_vec_6_2690) {
            image_vec_6_2690 = assets_image(145);  /* vec_6_2690 */
        }
        /* image_vec_6_2691 */
        if (!image_vec_6_2691) {
            image_vec_6_2691 = assets_image(146);  /* vec_6_2691 */
        }
        /* image_vec_6_2692 */
        if (!image_vec_6_2692) {
            image_vec_6_2692 = assets_image(147);  /* vec_6_2692 */
        }
        /* image_vec_6_2693 */
        if (!image_vec_6_2693) {
            image_vec_6_2693 = assets_image(148);  /* vec_6_2693 */
        }
        /* image_vec_6_2694 */
        if (!image_vec_6_2694) {
            image_vec_6_2694 = assets_image(149);  /* vec_6_2694 */
        }
        /* image_vec_6_2695 */
        if (!image_vec_6_2695) {
            image_vec_6_2695 = assets_image(150);  /* vec_6_2695 */
        }
        /* image_vec_6_2696 */
        if (!image_vec_6_2696) {
            image_vec_6_2696 = assets_image(151);  /* vec_6_2696 */
        }
        /* image_vec_6_2697 */
        if (!image_vec_6_2697) {
            image_vec_6_2697 = assets_image(152);  /* vec_6_2697 */
        }
        /* image_vec_6_2698 */
        if (!image_vec_6_2698) {
            image_vec_6_2698 = assets_image(153);  /* vec_6_2698 */
        }
        /* image_vec_6_2699 */
        if (!image_vec_6_2699) {
            image_vec_6_2699 = assets_image(154);  /* vec_6_2699 */
        }
        /* image_vec_6_2700 */
        if (!image_vec_6_2700) {
            image_vec_6_2700 = assets_image(155);  /* vec_6_2700 */
        }
        /* image_vec_6_2701 */
        if (!image_vec_6_2701) {
            image_vec_6_2701 = assets_image(156);  /* vec_6_2701 */
        }
        /* image_vec_6_2702 */
        if (!image_vec_6_2702) {
            image_vec_6_2702 = assets_image(157);  /* vec_6_2702 */
        }
        /* image_vec_6_2703 */
        if (!image_vec_6_2703) {
            image_vec_6_2703 = assets_image(158);  /* vec_6_2703 */
        }
        /* image_vec_6_2704 */
        if (!image_vec_6_2704) {
            image_vec_6_2704 = assets_image(159);  /* vec_6_2704 */
        }
        /* image_vec_6_2705 */
        if (!image_vec_6_2705) {
            image_vec_6_2705 = assets_image(160);  /* vec_6_2705 */
        }
        /* image_vec_6_2706 */
        if (!image_vec_6_2706) {
            image_vec_6_2706 = assets_image(161);  /* vec_6_2706 */
        }
        /* image_vec_6_2707 */
        if (!image_vec_6_2707) {
            image_vec_6_2707 = assets_image(162);  /* vec_6_2707 */
        }
        /* image_vec_6_2708 */
        if (!image_vec_6_2708) {
            image_vec_6_2708 = assets_image(163);  /* vec_6_2708 */
        }
        /* image_vec_6_2709 */
        if (!image_vec_6_2709) {
            image_vec_6_2709 = assets_image(164);  /* vec_6_2709 */
        }
        /* image_vec_6_2710 */
        if (!image_vec_6_2710) {
            image_vec_6_2710 = assets_image(165);  /* vec_6_2710 */
        }
        /* image_vec_6_2711 */
        if (!image_vec_6_2711) {
            image_vec_6_2711 = assets_image(166);  /* vec_6_2711 */
        }
        /* image_vec_6_2712 */
        if (!image_vec_6_2712) {
            image_vec_6_2712 = assets_image(167);  /* vec_6_2712 */
        }
        /* image_vec_6_2713 */
        if (!image_vec_6_2713) {
            image_vec_6_2713 = assets_image(168);  /* vec_6_2713 */
        }
        /* image_vec_6_2714 */
        if (!image_vec_6_2714) {
            image_vec_6_2714 = assets_image(169);  /* vec_6_2714 */
        }
        /* image_vec_6_2715 */
        if (!image_vec_6_2715) {
            image_vec_6_2715 = assets_image(170);  /* vec_6_2715 */
        }
        /* image_vec_6_2716 */
        if (!image_vec_6_2716) {
            image_vec_6_2716 = assets_image(171);  /* vec_6_2716 */
        }
        /* image_vec_6_2717 */
        if (!image_vec_6_2717) {
            image_vec_6_2717 = assets_image(172);  /* vec_6_2717 */
        }
        /* image_vec_6_2718 */
        if (!image_vec_6_2718) {
            image_vec_6_2718 = assets_image(173);  /* vec_6_2718 */
        }
        /* image_vec_6_2719 */
        if (!image_vec_6_2719) {
            image_vec_6_2719 = assets_image(174);  /* vec_6_2719 */
        }
        /* image_vec_6_2720 */
        if (!image_vec_6_2720) {
            image_vec_6_2720 = assets_image(175);  /* vec_6_2720 */
        }
        /* image_vec_6_2721 */
        if (!image_vec_6_2721) {
            image_vec_6_2721 = assets_image(176);  /* vec_6_2721 */
        }
        /* image_vec_6_2722 */
        if (!image_vec_6_2722) {
            image_vec_6_2722 = assets_image(177);  /* vec_6_2722 */
        }
        /* image_vec_6_2723 */
        if (!image_vec_6_2723) {
            image_vec_6_2723 = assets_image(178);  /* vec_6_2723 */
        }
        /* image_vec_6_2724 */
        if (!image_vec_6_2724) {
            image_vec_6_2724 = assets_image(179);  /* vec_6_2724 */
        }
        /* image_vec_6_2725 */
        if (!image_vec_6_2725) {
            image_vec_6_2725 = assets_image(180);  /* vec_6_2725 */
        }
        /* image_vec_6_2726 */
        if (!image_vec_6_2726) {
            image_vec_6_2726 = assets_image(181);  /* vec_6_2726 */
        }
        /* image_vec_6_2727 */
        if (!image_vec_6_2727) {
            image_vec_6_2727 = assets_image(182);  /* vec_6_2727 */
        }
        /* image_vec_6_2728 */
        if (!image_vec_6_2728) {
            image_vec_6_2728 = assets_image(183);  /* vec_6_2728 */
        }
        /* image_vec_6_2729 */
        if (!image_vec_6_2729) {
            image_vec_6_2729 = assets_image(184);  /* vec_6_2729 */
        }
        /* image_vec_6_2730 */
        if (!image_vec_6_2730) {
            image_vec_6_2730 = assets_image(185);  /* vec_6_2730 */
        }
        /* image_vec_6_2731 */
        if (!image_vec_6_2731) {
            image_vec_6_2731 = assets_image(186);  /* vec_6_2731 */
        }
        /* image_vec_6_2732 */
        if (!image_vec_6_2732) {
            image_vec_6_2732 = assets_image(187);  /* vec_6_2732 */
        }
        /* image_vec_6_2733 */
        if (!image_vec_6_2733) {
            image_vec_6_2733 = assets_image(188);  /* vec_6_2733 */
        }
        /* image_vec_6_2734 */
        if (!image_vec_6_2734) {
            image_vec_6_2734 = assets_image(189);  /* vec_6_2734 */
        }
        /* image_vec_6_2735 */
        if (!image_vec_6_2735) {
            image_vec_6_2735 = assets_image(190);  /* vec_6_2735 */
        }
        /* image_vec_6_2736 */
        if (!image_vec_6_2736) {
            image_vec_6_2736 = assets_image(191);  /* vec_6_2736 */
        }
        /* image_vec_6_2737 */
        if (!image_vec_6_2737) {
            image_vec_6_2737 = assets_image(192);  /* vec_6_2737 */
        }
        /* image_vec_6_2738 */
        if (!image_vec_6_2738) {
            image_vec_6_2738 = assets_image(193);  /* vec_6_2738 */
        }
        /* image_vec_6_2739 */
        if (!image_vec_6_2739) {
            image_vec_6_2739 = assets_image(194);  /* vec_6_2739 */
        }
        /* image_vec_6_2740 */
        if (!image_vec_6_2740) {
            image_vec_6_2740 = assets_image(195);  /* vec_6_2740 */
        }
        /* image_vec_6_2741 */
        if (!image_vec_6_2741) {
            image_vec_6_2741 = assets_image(196);  /* vec_6_2741 */
        }
        /* image_vec_6_2742 */
        if (!image_vec_6_2742) {
            image_vec_6_2742 = assets_image(197);  /* vec_6_2742 */
        }
        /* image_vec_6_2743 */
        if (!image_vec_6_2743) {
            image_vec_6_2743 = assets_image(198);  /* vec_6_2743 */
        }
        /* image_vec_6_2744 */
        if (!image_vec_6_2744) {
            image_vec_6_2744 = assets_image(199);  /* vec_6_2744 */
        }
        /* image_vec_6_2745 */
        if (!image_vec_6_2745) {
            image_vec_6_2745 = assets_image(200);  /* vec_6_2745 */
        }
        /* image_vec_6_2746 */
        if (!image_vec_6_2746) {
            image_vec_6_2746 = assets_image(201);  /* vec_6_2746 */
        }
        /* image_vec_6_2747 */
        if (!image_vec_6_2747) {
            image_vec_6_2747 = assets_image(202);  /* vec_6_2747 */
        }
        /* image_vec_6_2748 */
        if (!image_vec_6_2748) {
            image_vec_6_2748 = assets_image(203);  /* vec_6_2748 */
        }
        /* image_vec_6_2749 */
        if (!image_vec_6_2749) {
            image_vec_6_2749 = assets_image(204);  /* vec_6_2749 */
        }
        /* image_vec_6_2750 */
        if (!image_vec_6_2750) {
            image_vec_6_2750 = assets_image(205);  /* vec_6_2750 */
        }
        /* image_vec_6_2751 */
        if (!image_vec_6_2751) {
            image_vec_6_2751 = assets_image(206);  /* vec_6_2751 */
        }
        /* image_vec_6_2752 */
        if (!image_vec_6_2752) {
            image_vec_6_2752 = assets_image(207);  /* vec_6_2752 */
        }
        /* image_vec_6_2753 */
        if (!image_vec_6_2753) {
            image_vec_6_2753 = assets_image(208);  /* vec_6_2753 */
        }
        /* image_vec_6_2754 */
        if (!image_vec_6_2754) {
            image_vec_6_2754 = assets_image(209);  /* vec_6_2754 */
        }
        /* image_vec_6_2755 */
        if (!image_vec_6_2755) {
            image_vec_6_2755 = assets_image(210);  /* vec_6_2755 */
        }
        /* image_vec_6_2756 */
        if (!image_vec_6_2756) {
            image_vec_6_2756 = assets_image(211);  /* vec_6_2756 */
        }
        /* image_vec_6_2757 */
        if (!image_vec_6_2757) {
            image_vec_6_2757 = assets_image(212);  /* vec_6_2757 */
        }
        /* image_vec_6_2758 */
        if (!image_vec_6_2758) {
            image_vec_6_2758 = assets_image(213);  /* vec_6_2758 */
        }
        /* image_vec_6_2759 */
        if (!image_vec_6_2759) {
            image_vec_6_2759 = assets_image(214);  /* vec_6_2759 */
        }
        /* image_vec_6_2760 */
        if (!image_vec_6_2760) {
            image_vec_6_2760 = assets_image(215);  /* vec_6_2760 */
        }
        /* image_vec_6_2761 */
        if (!image_vec_6_2761) {
            image_vec_6_2761 = assets_image(216);  /* vec_6_2761 */
        }
        /* image_vec_6_2762 */
        if (!image_vec_6_2762) {
            image_vec_6_2762 = assets_image(217);  /* vec_6_2762 */
        }
        /* image_vec_6_2763 */
        if (!image_vec_6_2763) {
            image_vec_6_2763 = assets_image(218);  /* vec_6_2763 */
        }
        /* image_vec_6_2764 */
        if (!image_vec_6_2764) {
            image_vec_6_2764 = assets_image(219);  /* vec_6_2764 */
        }
        /* image_vec_6_2765 */
        if (!image_vec_6_2765) {
            image_vec_6_2765 = assets_image(220);  /* vec_6_2765 */
        }
        /* image_vec_6_2766 */
        if (!image_vec_6_2766) {
            image_vec_6_2766 = assets_image(221);  /* vec_6_2766 */
        }
        /* image_vec_6_2767 */
        if (!image_vec_6_2767) {
            image_vec_6_2767 = assets_image(222);  /* vec_6_2767 */
        }
        /* image_vec_6_2768 */
        if (!image_vec_6_2768) {
            image_vec_6_2768 = assets_image(223);  /* vec_6_2768 */
        }
        /* image_vec_6_2769 */
        if (!image_vec_6_2769) {
            image_vec_6_2769 = assets_image(224);  /* vec_6_2769 */
        }
        /* image_vec_6_2770 */
        if (!image_vec_6_2770) {
            image_vec_6_2770 = assets_image(225);  /* vec_6_2770 */
        }
        /* image_vec_6_2771 */
        if (!image_vec_6_2771) {
            image_vec_6_2771 = assets_image(226);  /* vec_6_2771 */
        }
        /* image_vec_6_2772 */
        if (!image_vec_6_2772) {
            image_vec_6_2772 = assets_image(227);  /* vec_6_2772 */
        }
        /* image_vec_6_2773 */
        if (!image_vec_6_2773) {
            image_vec_6_2773 = assets_image(228);  /* vec_6_2773 */
        }
        /* image_vec_6_2774 */
        if (!image_vec_6_2774) {
            image_vec_6_2774 = assets_image(229);  /* vec_6_2774 */
        }
        /* image_vec_6_2775 */
        if (!image_vec_6_2775) {
            image_vec_6_2775 = assets_image(230);  /* vec_6_2775 */
        }
        /* image_vec_6_2776 */
        if (!image_vec_6_2776) {
            image_vec_6_2776 = assets_image(231);  /* vec_6_2776 */
        }
        /* image_vec_6_2777 */
        if (!image_vec_6_2777) {
            image_vec_6_2777 = assets_image(232);  /* vec_6_2777 */
        }
        /* image_vec_6_2778 */
        if (!image_vec_6_2778) {
            image_vec_6_2778 = assets_image(233);  /* vec_6_2778 */
        }
        /* image_vec_6_2779 */
        if (!image_vec_6_2779) {
            image_vec_6_2779 = assets_image(234);  /* vec_6_2779 */
        }
        /* image_vec_6_2780 */
        if (!image_vec_6_2780) {
            image_vec_6_2780 = assets_image(235);  /* vec_6_2780 */
        }
        /* image_vec_6_2781 */
        if (!image_vec_6_2781) {
            image_vec_6_2781 = assets_image(236);  /* vec_6_2781 */
        }
        /* image_vec_6_2782 */
        if (!image_vec_6_2782) {
            image_vec_6_2782 = assets_image(237);  /* vec_6_2782 */
        }
        /* image_vec_6_2783 */
        if (!image_vec_6_2783) {
            image_vec_6_2783 = assets_image(238);  /* vec_6_2783 */
        }
        /* image_vec_6_2784 */
        if (!image_vec_6_2784) {
            image_vec_6_2784 = assets_image(239);  /* vec_6_2784 */
        }
        /* image_vec_6_2785 */
        if (!image_vec_6_2785) {
            image_vec_6_2785 = assets_image(240);  /* vec_6_2785 */
        }
        /* image_vec_6_2786 */
        if (!image_vec_6_2786) {
            image_vec_6_2786 = assets_image(241);  /* vec_6_2786 */
        }
        /* image_vec_6_2787 */
        if (!image_vec_6_2787) {
            image_vec_6_2787 = assets_image(242);  /* vec_6_2787 */
        }
        /* image_vec_6_2788 */
        if (!image_vec_6_2788) {
            image_vec_6_2788 = assets_image(243);  /* vec_6_2788 */
        }
        /* image_vec_6_2789 */
        if (!image_vec_6_2789) {
            image_vec_6_2789 = assets_image(244);  /* vec_6_2789 */
        }
        /* image_vec_6_2790 */
        if (!image_vec_6_2790) {
            image_vec_6_2790 = assets_image(245);  /* vec_6_2790 */
        }
        /* image_vec_6_2791 */
        if (!image_vec_6_2791) {
            image_vec_6_2791 = assets_image(246);  /* vec_6_2791 */
        }
        /* image_vec_6_2792 */
        if (!image_vec_6_2792) {
            image_vec_6_2792 = assets_image(247);  /* vec_6_2792 */
        }
        /* image_vec_6_2793 */
        if (!image_vec_6_2793) {
            image_vec_6_2793 = assets_image(248);  /* vec_6_2793 */
        }
        /* image_vec_6_2794 */
        if (!image_vec_6_2794) {
            image_vec_6_2794 = assets_image(249);  /* vec_6_2794 */
        }
        /* image_vec_6_2795 */
        if (!image_vec_6_2795) {
            image_vec_6_2795 = assets_image(250);  /* vec_6_2795 */
        }
        /* image_vec_6_2796 */
        if (!image_vec_6_2796) {
            image_vec_6_2796 = assets_image(251);  /* vec_6_2796 */
        }
        /* image_vec_6_2797 */
        if (!image_vec_6_2797) {
            image_vec_6_2797 = assets_image(252);  /* vec_6_2797 */
        }
        /* image_vec_6_2798 */
        if (!image_vec_6_2798) {
            image_vec_6_2798 = assets_image(253);  /* vec_6_2798 */
        }
        /* image_vec_6_2799 */
        if (!image_vec_6_2799) {
            image_vec_6_2799 = assets_image(254);  /* vec_6_2799 */
        }
        /* image_vec_6_2800 */
        if (!image_vec_6_2800) {
            image_vec_6_2800 = assets_image(255);  /* vec_6_2800 */
        }
        /* image_vec_6_2801 */
        if (!image_vec_6_2801) {
            image_vec_6_2801 = assets_image(256);  /* vec_6_2801 */
        }
        /* image_vec_6_2802 */
        if (!image_vec_6_2802) {
            image_vec_6_2802 = assets_image(257);  /* vec_6_2802 */
        }
        /* image_vec_6_2803 */
        if (!image_vec_6_2803) {
            image_vec_6_2803 = assets_image(258);  /* vec_6_2803 */
        }
        /* image_vec_6_2804 */
        if (!image_vec_6_2804) {
            image_vec_6_2804 = assets_image(259);  /* vec_6_2804 */
        }
        /* image_vec_6_2805 */
        if (!image_vec_6_2805) {
            image_vec_6_2805 = assets_image(260);  /* vec_6_2805 */
        }
        /* image_vec_6_2806 */
        if (!image_vec_6_2806) {
            image_vec_6_2806 = assets_image(261);  /* vec_6_2806 */
        }
        /* image_vec_6_2807 */
        if (!image_vec_6_2807) {
            image_vec_6_2807 = assets_image(262);  /* vec_6_2807 */
        }
        /* image_vec_6_2808 */
        if (!image_vec_6_2808) {
            image_vec_6_2808 = assets_image(263);  /* vec_6_2808 */
        }
        /* image_vec_6_2809 */
        if (!image_vec_6_2809) {
            image_vec_6_2809 = assets_image(264);  /* vec_6_2809 */
        }
        /* image_vec_6_2810 */
        if (!image_vec_6_2810) {
            image_vec_6_2810 = assets_image(265);  /* vec_6_2810 */
        }
        /* image_vec_6_2811 */
        if (!image_vec_6_2811) {
            image_vec_6_2811 = assets_image(266);  /* vec_6_2811 */
        }
        /* image_vec_6_2812 */
        if (!image_vec_6_2812) {
            image_vec_6_2812 = assets_image(267);  /* vec_6_2812 */
        }
        /* image_vec_6_2813 */
        if (!image_vec_6_2813) {
            image_vec_6_2813 = assets_image(268);  /* vec_6_2813 */
        }
        /* image_vec_6_2814 */
        if (!image_vec_6_2814) {
            image_vec_6_2814 = assets_image(269);  /* vec_6_2814 */
        }
        /* image_vec_6_2815 */
        if (!image_vec_6_2815) {
            image_vec_6_2815 = assets_image(270);  /* vec_6_2815 */
        }
        /* image_vec_6_2816 */
        if (!image_vec_6_2816) {
            image_vec_6_2816 = assets_image(271);  /* vec_6_2816 */
        }
        /* image_vec_6_2817 */
        if (!image_vec_6_2817) {
            image_vec_6_2817 = assets_image(272);  /* vec_6_2817 */
        }
        /* image_vec_6_2818 */
        if (!image_vec_6_2818) {
            image_vec_6_2818 = assets_image(273);  /* vec_6_2818 */
        }
        /* image_vec_6_2819 */
        if (!image_vec_6_2819) {
            image_vec_6_2819 = assets_image(274);  /* vec_6_2819 */
        }
        /* image_vec_6_2820 */
        if (!image_vec_6_2820) {
            image_vec_6_2820 = assets_image(275);  /* vec_6_2820 */
        }
        /* image_vec_6_2821 */
        if (!image_vec_6_2821) {
            image_vec_6_2821 = assets_image(276);  /* vec_6_2821 */
        }
        /* image_vec_6_2822 */
        if (!image_vec_6_2822) {
            image_vec_6_2822 = assets_image(277);  /* vec_6_2822 */
        }
        /* image_vec_6_2823 */
        if (!image_vec_6_2823) {
            image_vec_6_2823 = assets_image(278);  /* vec_6_2823 */
        }
        /* image_vec_6_2824 */
        if (!image_vec_6_2824) {
            image_vec_6_2824 = assets_image(279);  /* vec_6_2824 */
        }
        /* image_vec_6_2825 */
        if (!image_vec_6_2825) {
            image_vec_6_2825 = assets_image(280);  /* vec_6_2825 */
        }
        /* image_vec_6_2826 */
        if (!image_vec_6_2826) {
            image_vec_6_2826 = assets_image(281);  /* vec_6_2826 */
        }
        /* image_vec_6_2827 */
        if (!image_vec_6_2827) {
            image_vec_6_2827 = assets_image(282);  /* vec_6_2827 */
        }
        /* image_vec_6_2828 */
        if (!image_vec_6_2828) {
            image_vec_6_2828 = assets_image(283);  /* vec_6_2828 */
        }
        /* image_vec_6_2829 */
        if (!image_vec_6_2829) {
            image_vec_6_2829 = assets_image(284);  /* vec_6_2829 */
        }
        /* image_vec_6_2830 */
        if (!image_vec_6_2830) {
            image_vec_6_2830 = assets_image(285);  /* vec_6_2830 */
        }
        /* image_vec_6_2831 */
        if (!image_vec_6_2831) {
            image_vec_6_2831 = assets_image(286);  /* vec_6_2831 */
        }
        /* image_vec_6_2832 */
        if (!image_vec_6_2832) {
            image_vec_6_2832 = assets_image(287);  /* vec_6_2832 */
        }
        /* image_vec_6_2833 */
        if (!image_vec_6_2833) {
            image_vec_6_2833 = assets_image(288);  /* vec_6_2833 */
        }
        /* image_vec_6_2834 */
        if (!image_vec_6_2834) {
            image_vec_6_2834 = assets_image(289);  /* vec_6_2834 */
        }
        /* image_vec_6_2835 */
        if (!image_vec_6_2835) {
            image_vec_6_2835 = assets_image(290);  /* vec_6_2835 */
        }
        /* image_vec_6_2836 */
        if (!image_vec_6_2836) {
            image_vec_6_2836 = assets_image(291);  /* vec_6_2836 */
        }
        /* image_vec_6_2837 */
        if (!image_vec_6_2837) {
            image_vec_6_2837 = assets_image(292);  /* vec_6_2837 */
        }
        /* image_vec_6_2838 */
        if (!image_vec_6_2838) {
            image_vec_6_2838 = assets_image(293);  /* vec_6_2838 */
        }
        /* image_vec_6_2839 */
        if (!image_vec_6_2839) {
            image_vec_6_2839 = assets_image(294);  /* vec_6_2839 */
        }
        /* image_vec_6_2840 */
        if (!image_vec_6_2840) {
            image_vec_6_2840 = assets_image(295);  /* vec_6_2840 */
        }
        /* image_vec_6_2841 */
        if (!image_vec_6_2841) {
            image_vec_6_2841 = assets_image(296);  /* vec_6_2841 */
        }
        /* image_vec_6_2842 */
        if (!image_vec_6_2842) {
            image_vec_6_2842 = assets_image(297);  /* vec_6_2842 */
        }
        /* image_vec_6_2843 */
        if (!image_vec_6_2843) {
            image_vec_6_2843 = assets_image(298);  /* vec_6_2843 */
        }
        /* image_vec_6_2844 */
        if (!image_vec_6_2844) {
            image_vec_6_2844 = assets_image(299);  /* vec_6_2844 */
        }
        /* image_vec_6_2845 */
        if (!image_vec_6_2845) {
            image_vec_6_2845 = assets_image(300);  /* vec_6_2845 */
        }
        /* image_vec_6_2846 */
        if (!image_vec_6_2846) {
            image_vec_6_2846 = assets_image(301);  /* vec_6_2846 */
        }
        /* image_vec_6_2847 */
        if (!image_vec_6_2847) {
            image_vec_6_2847 = assets_image(302);  /* vec_6_2847 */
        }
        /* image_vec_6_2848 */
        if (!image_vec_6_2848) {
            image_vec_6_2848 = assets_image(303);  /* vec_6_2848 */
        }
        /* image_vec_6_2849 */
        if (!image_vec_6_2849) {
            image_vec_6_2849 = assets_image(304);  /* vec_6_2849 */
        }
        /* image_vec_6_2850 */
        if (!image_vec_6_2850) {
            image_vec_6_2850 = assets_image(305);  /* vec_6_2850 */
        }
        /* image_vec_6_2851 */
        if (!image_vec_6_2851) {
            image_vec_6_2851 = assets_image(306);  /* vec_6_2851 */
        }
        /* image_vec_6_2852 */
        if (!image_vec_6_2852) {
            image_vec_6_2852 = assets_image(307);  /* vec_6_2852 */
        }
        /* image_vec_6_2853 */
        if (!image_vec_6_2853) {
            image_vec_6_2853 = assets_image(308);  /* vec_6_2853 */
        }
        /* image_vec_6_2854 */
        if (!image_vec_6_2854) {
            image_vec_6_2854 = assets_image(309);  /* vec_6_2854 */
        }
        /* image_vec_6_2855 */
        if (!image_vec_6_2855) {
            image_vec_6_2855 = assets_image(310);  /* vec_6_2855 */
        }
        /* image_vec_6_2856 */
        if (!image_vec_6_2856) {
            image_vec_6_2856 = assets_image(311);  /* vec_6_2856 */
        }
        /* image_vec_6_2857 */
        if (!image_vec_6_2857) {
            image_vec_6_2857 = assets_image(312);  /* vec_6_2857 */
        }
        /* image_vec_6_2858 */
        if (!image_vec_6_2858) {
            image_vec_6_2858 = assets_image(313);  /* vec_6_2858 */
        }
        /* image_vec_6_2859 */
        if (!image_vec_6_2859) {
            image_vec_6_2859 = assets_image(314);  /* vec_6_2859 */
        }
        /* image_vec_6_2860 */
        if (!image_vec_6_2860) {
            image_vec_6_2860 = assets_image(315);  /* vec_6_2860 */
        }
        /* image_vec_6_2861 */
        if (!image_vec_6_2861) {
            image_vec_6_2861 = assets_image(316);  /* vec_6_2861 */
        }
        /* image_vec_6_2862 */
        if (!image_vec_6_2862) {
            image_vec_6_2862 = assets_image(317);  /* vec_6_2862 */
        }
        /* image_vec_6_2863 */
        if (!image_vec_6_2863) {
            image_vec_6_2863 = assets_image(318);  /* vec_6_2863 */
        }
        /* image_vec_6_2864 */
        if (!image_vec_6_2864) {
            image_vec_6_2864 = assets_image(319);  /* vec_6_2864 */
        }
        /* image_vec_6_2865 */
        if (!image_vec_6_2865) {
            image_vec_6_2865 = assets_image(320);  /* vec_6_2865 */
        }
        /* image_vec_6_2866 */
        if (!image_vec_6_2866) {
            image_vec_6_2866 = assets_image(321);  /* vec_6_2866 */
        }
        /* image_vec_6_2867 */
        if (!image_vec_6_2867) {
            image_vec_6_2867 = assets_image(322);  /* vec_6_2867 */
        }
        /* image_vec_6_2868 */
        if (!image_vec_6_2868) {
            image_vec_6_2868 = assets_image(323);  /* vec_6_2868 */
        }
        /* image_vec_6_2869 */
        if (!image_vec_6_2869) {
            image_vec_6_2869 = assets_image(324);  /* vec_6_2869 */
        }
        /* image_vec_6_2870 */
        if (!image_vec_6_2870) {
            image_vec_6_2870 = assets_image(325);  /* vec_6_2870 */
        }
        /* image_vec_6_2871 */
        if (!image_vec_6_2871) {
            image_vec_6_2871 = assets_image(326);  /* vec_6_2871 */
        }
        /* image_vec_6_2872 */
        if (!image_vec_6_2872) {
            image_vec_6_2872 = assets_image(327);  /* vec_6_2872 */
        }
        /* image_vec_6_2873 */
        if (!image_vec_6_2873) {
            image_vec_6_2873 = assets_image(328);  /* vec_6_2873 */
        }
        /* image_vec_6_2874 */
        if (!image_vec_6_2874) {
            image_vec_6_2874 = assets_image(329);  /* vec_6_2874 */
        }
        /* image_vec_6_2875 */
        if (!image_vec_6_2875) {
            image_vec_6_2875 = assets_image(330);  /* vec_6_2875 */
        }
        /* image_vec_6_2876 */
        if (!image_vec_6_2876) {
            image_vec_6_2876 = assets_image(331);  /* vec_6_2876 */
        }
        /* image_vec_6_2877 */
        if (!image_vec_6_2877) {
            image_vec_6_2877 = assets_image(332);  /* vec_6_2877 */
        }
        /* image_vec_6_2878 */
        if (!image_vec_6_2878) {
            image_vec_6_2878 = assets_image(333);  /* vec_6_2878 */
        }
        /* image_vec_6_2879 */
        if (!image_vec_6_2879) {
            image_vec_6_2879 = assets_image(334);  /* vec_6_2879 */
        }
        /* image_vec_6_2880 */
        if (!image_vec_6_2880) {
            image_vec_6_2880 = assets_image(335);  /* vec_6_2880 */
        }
        /* image_vec_6_2881 */
        if (!image_vec_6_2881) {
            image_vec_6_2881 = assets_image(336);  /* vec_6_2881 */
        }
        /* image_vec_6_2882 */
        if (!image_vec_6_2882) {
            image_vec_6_2882 = assets_image(337);  /* vec_6_2882 */
        }
        /* image_vec_6_2883 */
        if (!image_vec_6_2883) {
            image_vec_6_2883 = assets_image(338);  /* vec_6_2883 */
        }
        /* image_vec_6_2884 */
        if (!image_vec_6_2884) {
            image_vec_6_2884 = assets_image(339);  /* vec_6_2884 */
        }
        /* image_vec_6_2885 */
        if (!image_vec_6_2885) {
            image_vec_6_2885 = assets_image(340);  /* vec_6_2885 */
        }
        /* image_vec_6_2886 */
        if (!image_vec_6_2886) {
            image_vec_6_2886 = assets_image(341);  /* vec_6_2886 */
        }
        /* image_vec_6_2887 */
        if (!image_vec_6_2887) {
            image_vec_6_2887 = assets_image(342);  /* vec_6_2887 */
        }
        /* image_vec_6_2888 */
        if (!image_vec_6_2888) {
            image_vec_6_2888 = assets_image(343);  /* vec_6_2888 */
        }
        /* image_vec_6_2889 */
        if (!image_vec_6_2889) {
            image_vec_6_2889 = assets_image(344);  /* vec_6_2889 */
        }
        /* image_vec_6_2890 */
        if (!image_vec_6_2890) {
            image_vec_6_2890 = assets_image(345);  /* vec_6_2890 */
        }
        /* image_vec_6_2891 */
        if (!image_vec_6_2891) {
            image_vec_6_2891 = assets_image(346);  /* vec_6_2891 */
        }
        /* image_vec_6_2892 */
        if (!image_vec_6_2892) {
            image_vec_6_2892 = assets_image(347);  /* vec_6_2892 */
        }
        /* image_vec_6_2893 */
        if (!image_vec_6_2893) {
            image_vec_6_2893 = assets_image(348);  /* vec_6_2893 */
        }
        /* image_vec_6_2894 */
        if (!image_vec_6_2894) {
            image_vec_6_2894 = assets_image(349);  /* vec_6_2894 */
        }
        /* image_vec_6_2895 */
        if (!image_vec_6_2895) {
            image_vec_6_2895 = assets_image(350);  /* vec_6_2895 */
        }
        /* image_vec_6_2896 */
        if (!image_vec_6_2896) {
            image_vec_6_2896 = assets_image(351);  /* vec_6_2896 */
        }
        /* image_vec_6_2897 */
        if (!image_vec_6_2897) {
            image_vec_6_2897 = assets_image(352);  /* vec_6_2897 */
        }
        /* image_vec_6_2898 */
        if (!image_vec_6_2898) {
            image_vec_6_2898 = assets_image(353);  /* vec_6_2898 */
        }
        /* image_vec_6_2899 */
        if (!image_vec_6_2899) {
            image_vec_6_2899 = assets_image(354);  /* vec_6_2899 */
        }
        /* image_vec_6_2900 */
        if (!image_vec_6_2900) {
            image_vec_6_2900 = assets_image(355);  /* vec_6_2900 */
        }
        /* image_vec_6_2901 */
        if (!image_vec_6_2901) {
            image_vec_6_2901 = assets_image(356);  /* vec_6_2901 */
        }
        /* image_vec_6_2902 */
        if (!image_vec_6_2902) {
            image_vec_6_2902 = assets_image(357);  /* vec_6_2902 */
        }
        /* image_vec_6_2903 */
        if (!image_vec_6_2903) {
            image_vec_6_2903 = assets_image(358);  /* vec_6_2903 */
        }
        /* image_vec_6_2904 */
        if (!image_vec_6_2904) {
            image_vec_6_2904 = assets_image(359);  /* vec_6_2904 */
        }
        /* image_vec_6_2905 */
        if (!image_vec_6_2905) {
            image_vec_6_2905 = assets_image(360);  /* vec_6_2905 */
        }
        /* image_vec_6_2906 */
        if (!image_vec_6_2906) {
            image_vec_6_2906 = assets_image(361);  /* vec_6_2906 */
        }
        /* image_vec_6_2907 */
        if (!image_vec_6_2907) {
            image_vec_6_2907 = assets_image(362);  /* vec_6_2907 */
        }
        /* image_vec_6_2908 */
        if (!image_vec_6_2908) {
            image_vec_6_2908 = assets_image(363);  /* vec_6_2908 */
        }
        /* image_vec_6_2909 */
        if (!image_vec_6_2909) {
            image_vec_6_2909 = assets_image(364);  /* vec_6_2909 */
        }
        /* image_vec_6_2910 */
        if (!image_vec_6_2910) {
            image_vec_6_2910 = assets_image(365);  /* vec_6_2910 */
        }
        /* image_vec_6_2911 */
        if (!image_vec_6_2911) {
            image_vec_6_2911 = assets_image(366);  /* vec_6_2911 */
        }
        /* image_vec_6_2912 */
        if (!image_vec_6_2912) {
            image_vec_6_2912 = assets_image(367);  /* vec_6_2912 */
        }
        /* image_vec_6_2913 */
        if (!image_vec_6_2913) {
            image_vec_6_2913 = assets_image(368);  /* vec_6_2913 */
        }
        /* image_vec_6_2914 */
        if (!image_vec_6_2914) {
            image_vec_6_2914 = assets_image(369);  /* vec_6_2914 */
        }
        /* image_vec_6_2915 */
        if (!image_vec_6_2915) {
            image_vec_6_2915 = assets_image(370);  /* vec_6_2915 */
        }
        /* image_vec_6_2916 */
        if (!image_vec_6_2916) {
            image_vec_6_2916 = assets_image(371);  /* vec_6_2916 */
        }
        /* image_vec_6_2917 */
        if (!image_vec_6_2917) {
            image_vec_6_2917 = assets_image(372);  /* vec_6_2917 */
        }
        /* image_vec_6_2918 */
        if (!image_vec_6_2918) {
            image_vec_6_2918 = assets_image(373);  /* vec_6_2918 */
        }
        /* image_vec_6_2919 */
        if (!image_vec_6_2919) {
            image_vec_6_2919 = assets_image(374);  /* vec_6_2919 */
        }
        /* image_vec_6_2920 */
        if (!image_vec_6_2920) {
            image_vec_6_2920 = assets_image(375);  /* vec_6_2920 */
        }
        /* image_vec_6_2921 */
        if (!image_vec_6_2921) {
            image_vec_6_2921 = assets_image(376);  /* vec_6_2921 */
        }
        /* image_vec_6_2922 */
        if (!image_vec_6_2922) {
            image_vec_6_2922 = assets_image(377);  /* vec_6_2922 */
        }
        /* image_vec_6_2923 */
        if (!image_vec_6_2923) {
            image_vec_6_2923 = assets_image(378);  /* vec_6_2923 */
        }
        /* image_vec_6_2924 */
        if (!image_vec_6_2924) {
            image_vec_6_2924 = assets_image(379);  /* vec_6_2924 */
        }
        /* image_vec_6_2925 */
        if (!image_vec_6_2925) {
            image_vec_6_2925 = assets_image(380);  /* vec_6_2925 */
        }
        /* image_vec_6_2926 */
        if (!image_vec_6_2926) {
            image_vec_6_2926 = assets_image(381);  /* vec_6_2926 */
        }
        /* image_vec_6_2927 */
        if (!image_vec_6_2927) {
            image_vec_6_2927 = assets_image(382);  /* vec_6_2927 */
        }
        /* image_vec_6_2928 */
        if (!image_vec_6_2928) {
            image_vec_6_2928 = assets_image(383);  /* vec_6_2928 */
        }
        /* image_vec_6_2929 */
        if (!image_vec_6_2929) {
            image_vec_6_2929 = assets_image(384);  /* vec_6_2929 */
        }
        /* image_vec_6_2930 */
        if (!image_vec_6_2930) {
            image_vec_6_2930 = assets_image(385);  /* vec_6_2930 */
        }
        /* image_vec_6_2931 */
        if (!image_vec_6_2931) {
            image_vec_6_2931 = assets_image(386);  /* vec_6_2931 */
        }
        /* image_vec_6_2932 */
        if (!image_vec_6_2932) {
            image_vec_6_2932 = assets_image(387);  /* vec_6_2932 */
        }
        /* image_vec_6_2933 */
        if (!image_vec_6_2933) {
            image_vec_6_2933 = assets_image(388);  /* vec_6_2933 */
        }
        /* image_vec_6_2934 */
        if (!image_vec_6_2934) {
            image_vec_6_2934 = assets_image(389);  /* vec_6_2934 */
        }
        /* image_vec_6_2935 */
        if (!image_vec_6_2935) {
            image_vec_6_2935 = assets_image(390);  /* vec_6_2935 */
        }
        /* image_vec_6_2936 */
        if (!image_vec_6_2936) {
            image_vec_6_2936 = assets_image(391);  /* vec_6_2936 */
        }
        /* image_vec_6_2937 */
        if (!image_vec_6_2937) {
            image_vec_6_2937 = assets_image(392);  /* vec_6_2937 */
        }
        /* image_vec_6_2938 */
        if (!image_vec_6_2938) {
            image_vec_6_2938 = assets_image(393);  /* vec_6_2938 */
        }
        /* image_vec_6_2939 */
        if (!image_vec_6_2939) {
            image_vec_6_2939 = assets_image(394);  /* vec_6_2939 */
        }
        /* image_vec_6_2940 */
        if (!image_vec_6_2940) {
            image_vec_6_2940 = assets_image(395);  /* vec_6_2940 */
        }
        /* image_vec_6_2943 */
        if (!image_vec_6_2943) {
            image_vec_6_2943 = assets_image(396);  /* vec_6_2943 */
        }
        /* image_vec_6_2944 */
        if (!image_vec_6_2944) {
            image_vec_6_2944 = assets_image(397);  /* vec_6_2944 */
        }
        /* image_vec_6_2947 */
        if (!image_vec_6_2947) {
            image_vec_6_2947 = assets_image(398);  /* vec_6_2947 */
        }
        /* image_vec_6_2948 */
        if (!image_vec_6_2948) {
            image_vec_6_2948 = assets_image(399);  /* vec_6_2948 */
        }
        /* image_vec_6_2951 */
        if (!image_vec_6_2951) {
            image_vec_6_2951 = assets_image(400);  /* vec_6_2951 */
        }
        /* image_vec_6_2952 */
        if (!image_vec_6_2952) {
            image_vec_6_2952 = assets_image(401);  /* vec_6_2952 */
        }
        /* image_vec_6_2955 */
        if (!image_vec_6_2955) {
            image_vec_6_2955 = assets_image(402);  /* vec_6_2955 */
        }
        /* image_vec_6_2956 */
        if (!image_vec_6_2956) {
            image_vec_6_2956 = assets_image(403);  /* vec_6_2956 */
        }
        /* image_vec_6_2959 */
        if (!image_vec_6_2959) {
            image_vec_6_2959 = assets_image(404);  /* vec_6_2959 */
        }
        /* image_vec_6_2960 */
        if (!image_vec_6_2960) {
            image_vec_6_2960 = assets_image(405);  /* vec_6_2960 */
        }
        /* image_vec_6_2963 */
        if (!image_vec_6_2963) {
            image_vec_6_2963 = assets_image(406);  /* vec_6_2963 */
        }
        /* image_vec_6_2964 */
        if (!image_vec_6_2964) {
            image_vec_6_2964 = assets_image(407);  /* vec_6_2964 */
        }
        /* image_vec_25_1105 */
        if (!image_vec_25_1105) {
            image_vec_25_1105 = assets_image(17);  /* vec_25_1105 */
        }
        /* image_vec_7_1412 */
        if (!image_vec_7_1412) {
            image_vec_7_1412 = assets_image(408);  /* vec_7_1412 */
        }
        /* image_vec_1_241 */
        if (!image_vec_1_241) {
            image_vec_1_241 = assets_image(11);  /* vec_1_241 */
        }
        /* image_vec_7_1491 */
        if (!image_vec_7_1491) {
            image_vec_7_1491 = assets_image(410);  /* vec_7_1491 */
        }
        /* image_vec_7_1493 */
        if (!image_vec_7_1493) {
            image_vec_7_1493 = assets_image(411);  /* vec_7_1493 */
        }
        /* image_vec_1_790 */
        if (!image_vec_1_790) {
            image_vec_1_790 = assets_image(12);  /* vec_1_790 */
        }
        /* image_vec_1_882 */
        if (!image_vec_1_882) {
            image_vec_1_882 = assets_image(13);  /* vec_1_882 */
        }
        /* image_vec_25_1004 */
        if (!image_vec_25_1004) {
            image_vec_25_1004 = assets_image(16);  /* vec_25_1004 */
        }
        /* image_vec_7_1415 */
        if (!image_vec_7_1415) {
            image_vec_7_1415 = assets_image(409);  /* vec_7_1415 */
        }
        /* image_vec_23_214 */
        if (!image_vec_23_214) {
            image_vec_23_214 = assets_image(14);  /* vec_23_214 */
        }
        /* image_vec_42_2416 */
        if (!image_vec_42_2416) {
            image_vec_42_2416 = assets_image(21);  /* vec_42_2416 */
        }
        /* image_vec_42_2418 */
        if (!image_vec_42_2418) {
            image_vec_42_2418 = assets_image(22);  /* vec_42_2418 */
        }
        /* image_vec_34_869 */
        if (!image_vec_34_869) {
            image_vec_34_869 = assets_image(18);  /* vec_34_869 */
        }
        /* image_vec_34_872 */
        if (!image_vec_34_872) {
            image_vec_34_872 = assets_image(19);  /* vec_34_872 */
        }
        /* image_vec_23_372 */
        if (!image_vec_23_372) {
            image_vec_23_372 = assets_image(15);  /* vec_23_372 */
        }
        /* image_vec_42_877 */
        if (!image_vec_42_877) {
            image_vec_42_877 = assets_image(24);  /* vec_42_877 */
        }
        /* image_vec_12_212 */
        if (!image_vec_12_212) {
            image_vec_12_212 = assets_image(10);  /* vec_12_212 */
        }
        /* image_vec_42_862 */
        if (!image_vec_42_862) {
            image_vec_42_862 = assets_image(23);  /* vec_42_862 */
        }
        /* image_vec_7_1590 */
        if (!image_vec_7_1590) {
            image_vec_7_1590 = assets_image(412);  /* vec_7_1590 */
        }
        /* image_vec_46_963 */
        if (!image_vec_46_963) {
            image_vec_46_963 = assets_image(25);  /* vec_46_963 */
        }
        /* image_vec_46_964 */
        if (!image_vec_46_964) {
            image_vec_46_964 = assets_image(26);  /* vec_46_964 */
        }
        /* image_vec_46_965 */
        if (!image_vec_46_965) {
            image_vec_46_965 = assets_image(27);  /* vec_46_965 */
        }
        /* image_vec_46_966 */
        if (!image_vec_46_966) {
            image_vec_46_966 = assets_image(28);  /* vec_46_966 */
        }
        /* image_vec_46_967 */
        if (!image_vec_46_967) {
            image_vec_46_967 = assets_image(29);  /* vec_46_967 */
        }
        /* image_vec_46_968 */
        if (!image_vec_46_968) {
            image_vec_46_968 = assets_image(30);  /* vec_46_968 */
        }
        /* image_vec_46_969 */
        if (!image_vec_46_969) {
            image_vec_46_969 = assets_image(31);  /* vec_46_969 */
        }
        /* image_vec_46_970 */
        if (!image_vec_46_970) {
            image_vec_46_970 = assets_image(32);  /* vec_46_970 */
        }
        /* image_vec_46_971 */
        if (!image_vec_46_971) {
            image_vec_46_971 = assets_image(33);  /* vec_46_971 */
        }
        /* image_vec_46_972 */
        if (!image_vec_46_972) {
            image_vec_46_972 = assets_image(34);  /* vec_46_972 */
        }
        /* image_vec_46_973 */
        if (!image_vec_46_973) {
            image_vec_46_973 = assets_image(35);  /* vec_46_973 */
        }
        /* image_vec_46_974 */
        if (!image_vec_46_974) {
            image_vec_46_974 = assets_image(36);  /* vec_46_974 */
        }
        /* image_vec_46_975 */
        if (!image_vec_46_975) {
            image_vec_46_975 = assets_image(37);  /* vec_46_975 */
        }
        /* image_vec_46_976 */
        if (!image_vec_46_976) {
            image_vec_46_976 = assets_image(38);  /* vec_46_976 */
        }
        /* image_vec_46_977 */
        if (!image_vec_46_977) {
            image_vec_46_977 = assets_image(39);  /* vec_46_977 */
        }
        /* image_vec_46_978 */
        if (!image_vec_46_978) {
            image_vec_46_978 = assets_image(40);  /* vec_46_978 */
        }
        /* image_vec_46_979 */
        if (!image_vec_46_979) {
            image_vec_46_979 = assets_image(41);  /* vec_46_979 */
        }
        /* image_vec_46_980 */
        if (!image_vec_46_980) {
            image_vec_46_980 = assets_image(42);  /* vec_46_980 */
        }
        /* image_vec_46_981 */
        if (!image_vec_46_981) {
            image_vec_46_981 = assets_image(43);  /* vec_46_981 */
        }
        /* image_vec_46_982 */
        if (!image_vec_46_982) {
            image_vec_46_982 = assets_image(44);  /* vec_46_982 */
        }
        /* image_vec_46_983 */
        if (!image_vec_46_983) {
            image_vec_46_983 = assets_image(45);  /* vec_46_983 */
        }
        /* image_vec_46_984 */
        if (!image_vec_46_984) {
            image_vec_46_984 = assets_image(46);  /* vec_46_984 */
        }
        /* image_vec_46_985 */
        if (!image_vec_46_985) {
            image_vec_46_985 = assets_image(47);  /* vec_46_985 */
        }
        /* image_vec_46_986 */
        if (!image_vec_46_986) {
            image_vec_46_986 = assets_image(48);  /* vec_46_986 */
        }
        /* image_vec_46_987 */
        if (!image_vec_46_987) {
            image_vec_46_987 = assets_image(49);  /* vec_46_987 */
        }
        /* image_vec_46_988 */
        if (!image_vec_46_988) {
            image_vec_46_988 = assets_image(50);  /* vec_46_988 */
        }
        /* image_vec_46_989 */
        if (!image_vec_46_989) {
            image_vec_46_989 = assets_image(51);  /* vec_46_989 */
        }
        /* image_vec_46_990 */
        if (!image_vec_46_990) {
            image_vec_46_990 = assets_image(52);  /* vec_46_990 */
        }
        /* image_vec_46_991 */
        if (!image_vec_46_991) {
            image_vec_46_991 = assets_image(53);  /* vec_46_991 */
        }
        /* image_vec_46_992 */
        if (!image_vec_46_992) {
            image_vec_46_992 = assets_image(54);  /* vec_46_992 */
        }
        /* image_vec_46_993 */
        if (!image_vec_46_993) {
            image_vec_46_993 = assets_image(55);  /* vec_46_993 */
        }
        /* image_vec_46_994 */
        if (!image_vec_46_994) {
            image_vec_46_994 = assets_image(56);  /* vec_46_994 */
        }
        /* image_vec_46_995 */
        if (!image_vec_46_995) {
            image_vec_46_995 = assets_image(57);  /* vec_46_995 */
        }
        /* image_vec_46_996 */
        if (!image_vec_46_996) {
            image_vec_46_996 = assets_image(58);  /* vec_46_996 */
        }
        /* image_vec_46_997 */
        if (!image_vec_46_997) {
            image_vec_46_997 = assets_image(59);  /* vec_46_997 */
        }
        /* image_vec_46_998 */
        if (!image_vec_46_998) {
            image_vec_46_998 = assets_image(60);  /* vec_46_998 */
        }
    }
    #endif

    /*----------------
     * Global styles
     *----------------*/

    static bool style_inited = false;

    if (!style_inited) {
        /*Init all styles*/
        lv_style_init(&style_screen_base_global);
        lv_style_init(&style_state_on);
        lv_style_init(&style_state_good);
        lv_style_init(&style_state_off);
        lv_style_init(&style_state_warn);
        lv_style_init(&style_dot_on);
        lv_style_init(&style_dot_off);

        lv_style_set_border_width(&style_screen_base_global, 0);
        lv_style_set_radius(&style_screen_base_global, 0);
        lv_style_set_shadow_width(&style_screen_base_global, 0);
        lv_style_set_shadow_opa(&style_screen_base_global, 0);
        lv_style_set_text_color(&style_state_on, lv_color_hex(0x34C759));
        lv_style_set_text_color(&style_state_good, lv_color_hex(0x59D173));
        lv_style_set_text_color(&style_state_off, lv_color_hex(0x8E8E93));
        lv_style_set_text_color(&style_state_warn, lv_color_hex(0xFF9F0A));
        lv_style_set_bg_color(&style_dot_on, lv_color_hex(0x59D173));
        lv_style_set_bg_color(&style_dot_off, lv_color_hex(0x5A5A5A));

        style_inited = true;
    }

    /*----------------
     * Subjects
     *----------------*/
    lv_subject_init_int(&brightness_percent, 50);
    lv_subject_init_int(&battery_percent, 82);
    static char time_text_buf[UI_SUBJECT_STRING_LENGTH];
    static char time_text_prev_buf[UI_SUBJECT_STRING_LENGTH];
    lv_subject_init_string(&time_text,
                           time_text_buf,
                           time_text_prev_buf,
                           UI_SUBJECT_STRING_LENGTH,
                           "9:41"
                          );
    static char ampm_text_buf[UI_SUBJECT_STRING_LENGTH];
    static char ampm_text_prev_buf[UI_SUBJECT_STRING_LENGTH];
    lv_subject_init_string(&ampm_text,
                           ampm_text_buf,
                           ampm_text_prev_buf,
                           UI_SUBJECT_STRING_LENGTH,
                           "AM"
                          );
    static char date_text_buf[UI_SUBJECT_STRING_LENGTH];
    static char date_text_prev_buf[UI_SUBJECT_STRING_LENGTH];
    lv_subject_init_string(&date_text,
                           date_text_buf,
                           date_text_prev_buf,
                           UI_SUBJECT_STRING_LENGTH,
                           "Wed Apr 1"
                          );
    static char wifi_status_buf[UI_SUBJECT_STRING_LENGTH];
    static char wifi_status_prev_buf[UI_SUBJECT_STRING_LENGTH];
    lv_subject_init_string(&wifi_status,
                           wifi_status_buf,
                           wifi_status_prev_buf,
                           UI_SUBJECT_STRING_LENGTH,
                           "Off"
                          );
    static char wifi_name_buf[UI_SUBJECT_STRING_LENGTH];
    static char wifi_name_prev_buf[UI_SUBJECT_STRING_LENGTH];
    lv_subject_init_string(&wifi_name,
                           wifi_name_buf,
                           wifi_name_prev_buf,
                           UI_SUBJECT_STRING_LENGTH,
                           "Not set up"
                          );
    lv_subject_init_int(&wifi_state, 2);
    lv_subject_init_int(&bluetooth_on, 0);
    lv_subject_init_int(&usb_power, 1);
    lv_subject_init_int(&power_state, 0);
    static char power_mode_text_buf[UI_SUBJECT_STRING_LENGTH];
    static char power_mode_text_prev_buf[UI_SUBJECT_STRING_LENGTH];
    lv_subject_init_string(&power_mode_text,
                           power_mode_text_buf,
                           power_mode_text_prev_buf,
                           UI_SUBJECT_STRING_LENGTH,
                           "Active"
                          );
    static char sd_text_buf[UI_SUBJECT_STRING_LENGTH];
    static char sd_text_prev_buf[UI_SUBJECT_STRING_LENGTH];
    lv_subject_init_string(&sd_text,
                           sd_text_buf,
                           sd_text_prev_buf,
                           UI_SUBJECT_STRING_LENGTH,
                           "19.8 / 32 GB"
                          );
    lv_subject_init_int(&sd_percent, 62);
    static char pin_storage_text_buf[UI_SUBJECT_STRING_LENGTH];
    static char pin_storage_text_prev_buf[UI_SUBJECT_STRING_LENGTH];
    lv_subject_init_string(&pin_storage_text,
                           pin_storage_text_buf,
                           pin_storage_text_prev_buf,
                           UI_SUBJECT_STRING_LENGTH,
                           "0.3 / 4.4 MB"
                          );
    lv_subject_init_int(&pin_storage_percent, 7);

    /*----------------
     * Translations
     *----------------*/

#if defined(LV_USE_XML) && LV_USE_XML
    /* Register widgets */

    /* Check all fonts / default if needed. This prevents fonts that are used in one target but
       defined in another from causing assertion failures during rendering of the Preview. */
    check_font(&font_ibm_plex_mono_regular_26, "font_ibm_plex_mono_regular_26");
    check_font(&font_ibm_plex_mono_semibold_150, "font_ibm_plex_mono_semibold_150");
    check_font(&font_inter_medium_24_460227966308594, "font_inter_medium_24_460227966308594");
    check_font(&font_roboto_semibold_22, "font_roboto_semibold_22");
    check_font(&font_inter_semi_bold_12, "font_inter_semi_bold_12");
    check_font(&font_inter_bold_28, "font_inter_bold_28");
    check_font(&font_inter_semi_bold_16, "font_inter_semi_bold_16");
    check_font(&font_inter_semi_bold_14, "font_inter_semi_bold_14");
    check_font(&font_inter_medium_11, "font_inter_medium_11");
    check_font(&font_inter_bold_14, "font_inter_bold_14");
    check_font(&font_inter_bold_20, "font_inter_bold_20");
    check_font(&font_inter_bold_23, "font_inter_bold_23");
    check_font(&font_inter_semi_bold_13, "font_inter_semi_bold_13");
    check_font(&font_playwrite_us_trad_regular_40, "font_playwrite_us_trad_regular_40");
    check_font(&font_playwrite_us_trad_regular_52, "font_playwrite_us_trad_regular_52");
    check_font(&font_inter_semi_bold_8, "font_inter_semi_bold_8");
    check_font(&font_inter_semi_bold_11, "font_inter_semi_bold_11");
    check_font(&font_roboto_medium_14, "font_roboto_medium_14");
    check_font(&font_ibm_plex_mono_regular_36, "font_ibm_plex_mono_regular_36");
    check_font(&font_roboto_medium_16, "font_roboto_medium_16");
    check_font(&font_ibm_plex_mono_medium_14, "font_ibm_plex_mono_medium_14");
    check_font(&font_ibm_plex_mono_regular_29, "font_ibm_plex_mono_regular_29");
    check_font(&font_inter_medium_24_manual, "font_inter_medium_24_manual");
    check_font(&font_inter_semi_bold_22_manual, "font_inter_semi_bold_22_manual");

    /* Register fonts */
    lv_xml_register_font(NULL, "font_ibm_plex_mono_regular_26", font_ibm_plex_mono_regular_26);
    lv_xml_register_font(NULL, "font_ibm_plex_mono_semibold_150", font_ibm_plex_mono_semibold_150);
    lv_xml_register_font(NULL, "font_inter_medium_24_460227966308594", font_inter_medium_24_460227966308594);
    lv_xml_register_font(NULL, "font_roboto_semibold_22", font_roboto_semibold_22);
    lv_xml_register_font(NULL, "font_inter_semi_bold_12", font_inter_semi_bold_12);
    lv_xml_register_font(NULL, "font_inter_bold_28", font_inter_bold_28);
    lv_xml_register_font(NULL, "font_inter_semi_bold_16", font_inter_semi_bold_16);
    lv_xml_register_font(NULL, "font_inter_semi_bold_14", font_inter_semi_bold_14);
    lv_xml_register_font(NULL, "font_inter_medium_11", font_inter_medium_11);
    lv_xml_register_font(NULL, "font_inter_bold_14", font_inter_bold_14);
    lv_xml_register_font(NULL, "font_inter_bold_20", font_inter_bold_20);
    lv_xml_register_font(NULL, "font_inter_bold_23", font_inter_bold_23);
    lv_xml_register_font(NULL, "font_inter_semi_bold_13", font_inter_semi_bold_13);
    lv_xml_register_font(NULL, "font_playwrite_us_trad_regular_40", font_playwrite_us_trad_regular_40);
    lv_xml_register_font(NULL, "font_playwrite_us_trad_regular_52", font_playwrite_us_trad_regular_52);
    lv_xml_register_font(NULL, "font_inter_semi_bold_8", font_inter_semi_bold_8);
    lv_xml_register_font(NULL, "font_inter_semi_bold_11", font_inter_semi_bold_11);
    lv_xml_register_font(NULL, "font_roboto_medium_14", font_roboto_medium_14);
    lv_xml_register_font(NULL, "font_ibm_plex_mono_regular_36", font_ibm_plex_mono_regular_36);
    lv_xml_register_font(NULL, "font_roboto_medium_16", font_roboto_medium_16);
    lv_xml_register_font(NULL, "font_ibm_plex_mono_medium_14", font_ibm_plex_mono_medium_14);
    lv_xml_register_font(NULL, "font_ibm_plex_mono_regular_29", font_ibm_plex_mono_regular_29);
    lv_xml_register_font(NULL, "font_inter_medium_24_manual", font_inter_medium_24_manual);
    lv_xml_register_font(NULL, "font_inter_semi_bold_22_manual", font_inter_semi_bold_22_manual);

    /* Register subjects */
    lv_xml_register_subject(NULL, "brightness_percent", &brightness_percent);
    lv_xml_register_subject(NULL, "battery_percent", &battery_percent);
    lv_xml_register_subject(NULL, "time_text", &time_text);
    lv_xml_register_subject(NULL, "ampm_text", &ampm_text);
    lv_xml_register_subject(NULL, "date_text", &date_text);
    lv_xml_register_subject(NULL, "wifi_status", &wifi_status);
    lv_xml_register_subject(NULL, "wifi_name", &wifi_name);
    lv_xml_register_subject(NULL, "wifi_state", &wifi_state);
    lv_xml_register_subject(NULL, "bluetooth_on", &bluetooth_on);
    lv_xml_register_subject(NULL, "usb_power", &usb_power);
    lv_xml_register_subject(NULL, "power_state", &power_state);
    lv_xml_register_subject(NULL, "power_mode_text", &power_mode_text);
    lv_xml_register_subject(NULL, "sd_text", &sd_text);
    lv_xml_register_subject(NULL, "sd_percent", &sd_percent);
    lv_xml_register_subject(NULL, "pin_storage_text", &pin_storage_text);
    lv_xml_register_subject(NULL, "pin_storage_percent", &pin_storage_percent);

    /* Register callbacks */
#endif

    /* Register all the global assets so that they won't be created again when globals.xml is parsed.
     * While running in the editor skip this step to update the preview when the XML changes */
#if defined(LV_USE_XML) && LV_USE_XML && !defined(LV_EDITOR_PREVIEW)
    /* Register images */
    lv_xml_register_image(NULL, "image_img_02c5506b", image_img_02c5506b);
    lv_xml_register_image(NULL, "image_img_45c6bb3a", image_img_45c6bb3a);
    lv_xml_register_image(NULL, "image_vec_37_864", image_vec_37_864);
    lv_xml_register_image(NULL, "image_vec_6_2604", image_vec_6_2604);
    lv_xml_register_image(NULL, "image_vec_6_2605", image_vec_6_2605);
    lv_xml_register_image(NULL, "image_vec_6_2608", image_vec_6_2608);
    lv_xml_register_image(NULL, "image_vec_6_2609", image_vec_6_2609);
    lv_xml_register_image(NULL, "image_vec_6_2610", image_vec_6_2610);
    lv_xml_register_image(NULL, "image_vec_6_2611", image_vec_6_2611);
    lv_xml_register_image(NULL, "image_vec_6_2612", image_vec_6_2612);
    lv_xml_register_image(NULL, "image_vec_6_2613", image_vec_6_2613);
    lv_xml_register_image(NULL, "image_vec_6_2614", image_vec_6_2614);
    lv_xml_register_image(NULL, "image_vec_6_2615", image_vec_6_2615);
    lv_xml_register_image(NULL, "image_vec_6_2616", image_vec_6_2616);
    lv_xml_register_image(NULL, "image_vec_6_2617", image_vec_6_2617);
    lv_xml_register_image(NULL, "image_vec_6_2618", image_vec_6_2618);
    lv_xml_register_image(NULL, "image_vec_6_2619", image_vec_6_2619);
    lv_xml_register_image(NULL, "image_vec_6_2620", image_vec_6_2620);
    lv_xml_register_image(NULL, "image_vec_6_2621", image_vec_6_2621);
    lv_xml_register_image(NULL, "image_vec_6_2622", image_vec_6_2622);
    lv_xml_register_image(NULL, "image_vec_6_2623", image_vec_6_2623);
    lv_xml_register_image(NULL, "image_vec_6_2624", image_vec_6_2624);
    lv_xml_register_image(NULL, "image_vec_6_2625", image_vec_6_2625);
    lv_xml_register_image(NULL, "image_vec_6_2626", image_vec_6_2626);
    lv_xml_register_image(NULL, "image_vec_6_2627", image_vec_6_2627);
    lv_xml_register_image(NULL, "image_vec_6_2628", image_vec_6_2628);
    lv_xml_register_image(NULL, "image_vec_6_2629", image_vec_6_2629);
    lv_xml_register_image(NULL, "image_vec_6_2630", image_vec_6_2630);
    lv_xml_register_image(NULL, "image_vec_6_2631", image_vec_6_2631);
    lv_xml_register_image(NULL, "image_vec_6_2632", image_vec_6_2632);
    lv_xml_register_image(NULL, "image_vec_6_2633", image_vec_6_2633);
    lv_xml_register_image(NULL, "image_vec_6_2634", image_vec_6_2634);
    lv_xml_register_image(NULL, "image_vec_6_2635", image_vec_6_2635);
    lv_xml_register_image(NULL, "image_vec_6_2636", image_vec_6_2636);
    lv_xml_register_image(NULL, "image_vec_6_2637", image_vec_6_2637);
    lv_xml_register_image(NULL, "image_vec_6_2638", image_vec_6_2638);
    lv_xml_register_image(NULL, "image_vec_6_2639", image_vec_6_2639);
    lv_xml_register_image(NULL, "image_vec_6_2640", image_vec_6_2640);
    lv_xml_register_image(NULL, "image_vec_6_2641", image_vec_6_2641);
    lv_xml_register_image(NULL, "image_vec_6_2642", image_vec_6_2642);
    lv_xml_register_image(NULL, "image_vec_6_2643", image_vec_6_2643);
    lv_xml_register_image(NULL, "image_vec_6_2644", image_vec_6_2644);
    lv_xml_register_image(NULL, "image_vec_6_2645", image_vec_6_2645);
    lv_xml_register_image(NULL, "image_vec_6_2646", image_vec_6_2646);
    lv_xml_register_image(NULL, "image_vec_6_2647", image_vec_6_2647);
    lv_xml_register_image(NULL, "image_vec_6_2648", image_vec_6_2648);
    lv_xml_register_image(NULL, "image_vec_6_2649", image_vec_6_2649);
    lv_xml_register_image(NULL, "image_vec_6_2650", image_vec_6_2650);
    lv_xml_register_image(NULL, "image_vec_6_2651", image_vec_6_2651);
    lv_xml_register_image(NULL, "image_vec_6_2652", image_vec_6_2652);
    lv_xml_register_image(NULL, "image_vec_6_2653", image_vec_6_2653);
    lv_xml_register_image(NULL, "image_vec_6_2654", image_vec_6_2654);
    lv_xml_register_image(NULL, "image_vec_6_2655", image_vec_6_2655);
    lv_xml_register_image(NULL, "image_vec_6_2656", image_vec_6_2656);
    lv_xml_register_image(NULL, "image_vec_6_2657", image_vec_6_2657);
    lv_xml_register_image(NULL, "image_vec_6_2658", image_vec_6_2658);
    lv_xml_register_image(NULL, "image_vec_6_2659", image_vec_6_2659);
    lv_xml_register_image(NULL, "image_vec_6_2660", image_vec_6_2660);
    lv_xml_register_image(NULL, "image_vec_6_2661", image_vec_6_2661);
    lv_xml_register_image(NULL, "image_vec_6_2662", image_vec_6_2662);
    lv_xml_register_image(NULL, "image_vec_6_2663", image_vec_6_2663);
    lv_xml_register_image(NULL, "image_vec_6_2664", image_vec_6_2664);
    lv_xml_register_image(NULL, "image_vec_6_2665", image_vec_6_2665);
    lv_xml_register_image(NULL, "image_vec_6_2666", image_vec_6_2666);
    lv_xml_register_image(NULL, "image_vec_6_2667", image_vec_6_2667);
    lv_xml_register_image(NULL, "image_vec_6_2668", image_vec_6_2668);
    lv_xml_register_image(NULL, "image_vec_6_2669", image_vec_6_2669);
    lv_xml_register_image(NULL, "image_vec_6_2670", image_vec_6_2670);
    lv_xml_register_image(NULL, "image_vec_6_2671", image_vec_6_2671);
    lv_xml_register_image(NULL, "image_vec_6_2672", image_vec_6_2672);
    lv_xml_register_image(NULL, "image_vec_6_2673", image_vec_6_2673);
    lv_xml_register_image(NULL, "image_vec_6_2674", image_vec_6_2674);
    lv_xml_register_image(NULL, "image_vec_6_2675", image_vec_6_2675);
    lv_xml_register_image(NULL, "image_vec_6_2676", image_vec_6_2676);
    lv_xml_register_image(NULL, "image_vec_6_2677", image_vec_6_2677);
    lv_xml_register_image(NULL, "image_vec_6_2678", image_vec_6_2678);
    lv_xml_register_image(NULL, "image_vec_6_2679", image_vec_6_2679);
    lv_xml_register_image(NULL, "image_vec_6_2680", image_vec_6_2680);
    lv_xml_register_image(NULL, "image_vec_6_2681", image_vec_6_2681);
    lv_xml_register_image(NULL, "image_vec_6_2682", image_vec_6_2682);
    lv_xml_register_image(NULL, "image_vec_6_2683", image_vec_6_2683);
    lv_xml_register_image(NULL, "image_vec_6_2684", image_vec_6_2684);
    lv_xml_register_image(NULL, "image_vec_6_2685", image_vec_6_2685);
    lv_xml_register_image(NULL, "image_vec_6_2686", image_vec_6_2686);
    lv_xml_register_image(NULL, "image_vec_6_2687", image_vec_6_2687);
    lv_xml_register_image(NULL, "image_vec_6_2688", image_vec_6_2688);
    lv_xml_register_image(NULL, "image_vec_6_2689", image_vec_6_2689);
    lv_xml_register_image(NULL, "image_vec_6_2690", image_vec_6_2690);
    lv_xml_register_image(NULL, "image_vec_6_2691", image_vec_6_2691);
    lv_xml_register_image(NULL, "image_vec_6_2692", image_vec_6_2692);
    lv_xml_register_image(NULL, "image_vec_6_2693", image_vec_6_2693);
    lv_xml_register_image(NULL, "image_vec_6_2694", image_vec_6_2694);
    lv_xml_register_image(NULL, "image_vec_6_2695", image_vec_6_2695);
    lv_xml_register_image(NULL, "image_vec_6_2696", image_vec_6_2696);
    lv_xml_register_image(NULL, "image_vec_6_2697", image_vec_6_2697);
    lv_xml_register_image(NULL, "image_vec_6_2698", image_vec_6_2698);
    lv_xml_register_image(NULL, "image_vec_6_2699", image_vec_6_2699);
    lv_xml_register_image(NULL, "image_vec_6_2700", image_vec_6_2700);
    lv_xml_register_image(NULL, "image_vec_6_2701", image_vec_6_2701);
    lv_xml_register_image(NULL, "image_vec_6_2702", image_vec_6_2702);
    lv_xml_register_image(NULL, "image_vec_6_2703", image_vec_6_2703);
    lv_xml_register_image(NULL, "image_vec_6_2704", image_vec_6_2704);
    lv_xml_register_image(NULL, "image_vec_6_2705", image_vec_6_2705);
    lv_xml_register_image(NULL, "image_vec_6_2706", image_vec_6_2706);
    lv_xml_register_image(NULL, "image_vec_6_2707", image_vec_6_2707);
    lv_xml_register_image(NULL, "image_vec_6_2708", image_vec_6_2708);
    lv_xml_register_image(NULL, "image_vec_6_2709", image_vec_6_2709);
    lv_xml_register_image(NULL, "image_vec_6_2710", image_vec_6_2710);
    lv_xml_register_image(NULL, "image_vec_6_2711", image_vec_6_2711);
    lv_xml_register_image(NULL, "image_vec_6_2712", image_vec_6_2712);
    lv_xml_register_image(NULL, "image_vec_6_2713", image_vec_6_2713);
    lv_xml_register_image(NULL, "image_vec_6_2714", image_vec_6_2714);
    lv_xml_register_image(NULL, "image_vec_6_2715", image_vec_6_2715);
    lv_xml_register_image(NULL, "image_vec_6_2716", image_vec_6_2716);
    lv_xml_register_image(NULL, "image_vec_6_2717", image_vec_6_2717);
    lv_xml_register_image(NULL, "image_vec_6_2718", image_vec_6_2718);
    lv_xml_register_image(NULL, "image_vec_6_2719", image_vec_6_2719);
    lv_xml_register_image(NULL, "image_vec_6_2720", image_vec_6_2720);
    lv_xml_register_image(NULL, "image_vec_6_2721", image_vec_6_2721);
    lv_xml_register_image(NULL, "image_vec_6_2722", image_vec_6_2722);
    lv_xml_register_image(NULL, "image_vec_6_2723", image_vec_6_2723);
    lv_xml_register_image(NULL, "image_vec_6_2724", image_vec_6_2724);
    lv_xml_register_image(NULL, "image_vec_6_2725", image_vec_6_2725);
    lv_xml_register_image(NULL, "image_vec_6_2726", image_vec_6_2726);
    lv_xml_register_image(NULL, "image_vec_6_2727", image_vec_6_2727);
    lv_xml_register_image(NULL, "image_vec_6_2728", image_vec_6_2728);
    lv_xml_register_image(NULL, "image_vec_6_2729", image_vec_6_2729);
    lv_xml_register_image(NULL, "image_vec_6_2730", image_vec_6_2730);
    lv_xml_register_image(NULL, "image_vec_6_2731", image_vec_6_2731);
    lv_xml_register_image(NULL, "image_vec_6_2732", image_vec_6_2732);
    lv_xml_register_image(NULL, "image_vec_6_2733", image_vec_6_2733);
    lv_xml_register_image(NULL, "image_vec_6_2734", image_vec_6_2734);
    lv_xml_register_image(NULL, "image_vec_6_2735", image_vec_6_2735);
    lv_xml_register_image(NULL, "image_vec_6_2736", image_vec_6_2736);
    lv_xml_register_image(NULL, "image_vec_6_2737", image_vec_6_2737);
    lv_xml_register_image(NULL, "image_vec_6_2738", image_vec_6_2738);
    lv_xml_register_image(NULL, "image_vec_6_2739", image_vec_6_2739);
    lv_xml_register_image(NULL, "image_vec_6_2740", image_vec_6_2740);
    lv_xml_register_image(NULL, "image_vec_6_2741", image_vec_6_2741);
    lv_xml_register_image(NULL, "image_vec_6_2742", image_vec_6_2742);
    lv_xml_register_image(NULL, "image_vec_6_2743", image_vec_6_2743);
    lv_xml_register_image(NULL, "image_vec_6_2744", image_vec_6_2744);
    lv_xml_register_image(NULL, "image_vec_6_2745", image_vec_6_2745);
    lv_xml_register_image(NULL, "image_vec_6_2746", image_vec_6_2746);
    lv_xml_register_image(NULL, "image_vec_6_2747", image_vec_6_2747);
    lv_xml_register_image(NULL, "image_vec_6_2748", image_vec_6_2748);
    lv_xml_register_image(NULL, "image_vec_6_2749", image_vec_6_2749);
    lv_xml_register_image(NULL, "image_vec_6_2750", image_vec_6_2750);
    lv_xml_register_image(NULL, "image_vec_6_2751", image_vec_6_2751);
    lv_xml_register_image(NULL, "image_vec_6_2752", image_vec_6_2752);
    lv_xml_register_image(NULL, "image_vec_6_2753", image_vec_6_2753);
    lv_xml_register_image(NULL, "image_vec_6_2754", image_vec_6_2754);
    lv_xml_register_image(NULL, "image_vec_6_2755", image_vec_6_2755);
    lv_xml_register_image(NULL, "image_vec_6_2756", image_vec_6_2756);
    lv_xml_register_image(NULL, "image_vec_6_2757", image_vec_6_2757);
    lv_xml_register_image(NULL, "image_vec_6_2758", image_vec_6_2758);
    lv_xml_register_image(NULL, "image_vec_6_2759", image_vec_6_2759);
    lv_xml_register_image(NULL, "image_vec_6_2760", image_vec_6_2760);
    lv_xml_register_image(NULL, "image_vec_6_2761", image_vec_6_2761);
    lv_xml_register_image(NULL, "image_vec_6_2762", image_vec_6_2762);
    lv_xml_register_image(NULL, "image_vec_6_2763", image_vec_6_2763);
    lv_xml_register_image(NULL, "image_vec_6_2764", image_vec_6_2764);
    lv_xml_register_image(NULL, "image_vec_6_2765", image_vec_6_2765);
    lv_xml_register_image(NULL, "image_vec_6_2766", image_vec_6_2766);
    lv_xml_register_image(NULL, "image_vec_6_2767", image_vec_6_2767);
    lv_xml_register_image(NULL, "image_vec_6_2768", image_vec_6_2768);
    lv_xml_register_image(NULL, "image_vec_6_2769", image_vec_6_2769);
    lv_xml_register_image(NULL, "image_vec_6_2770", image_vec_6_2770);
    lv_xml_register_image(NULL, "image_vec_6_2771", image_vec_6_2771);
    lv_xml_register_image(NULL, "image_vec_6_2772", image_vec_6_2772);
    lv_xml_register_image(NULL, "image_vec_6_2773", image_vec_6_2773);
    lv_xml_register_image(NULL, "image_vec_6_2774", image_vec_6_2774);
    lv_xml_register_image(NULL, "image_vec_6_2775", image_vec_6_2775);
    lv_xml_register_image(NULL, "image_vec_6_2776", image_vec_6_2776);
    lv_xml_register_image(NULL, "image_vec_6_2777", image_vec_6_2777);
    lv_xml_register_image(NULL, "image_vec_6_2778", image_vec_6_2778);
    lv_xml_register_image(NULL, "image_vec_6_2779", image_vec_6_2779);
    lv_xml_register_image(NULL, "image_vec_6_2780", image_vec_6_2780);
    lv_xml_register_image(NULL, "image_vec_6_2781", image_vec_6_2781);
    lv_xml_register_image(NULL, "image_vec_6_2782", image_vec_6_2782);
    lv_xml_register_image(NULL, "image_vec_6_2783", image_vec_6_2783);
    lv_xml_register_image(NULL, "image_vec_6_2784", image_vec_6_2784);
    lv_xml_register_image(NULL, "image_vec_6_2785", image_vec_6_2785);
    lv_xml_register_image(NULL, "image_vec_6_2786", image_vec_6_2786);
    lv_xml_register_image(NULL, "image_vec_6_2787", image_vec_6_2787);
    lv_xml_register_image(NULL, "image_vec_6_2788", image_vec_6_2788);
    lv_xml_register_image(NULL, "image_vec_6_2789", image_vec_6_2789);
    lv_xml_register_image(NULL, "image_vec_6_2790", image_vec_6_2790);
    lv_xml_register_image(NULL, "image_vec_6_2791", image_vec_6_2791);
    lv_xml_register_image(NULL, "image_vec_6_2792", image_vec_6_2792);
    lv_xml_register_image(NULL, "image_vec_6_2793", image_vec_6_2793);
    lv_xml_register_image(NULL, "image_vec_6_2794", image_vec_6_2794);
    lv_xml_register_image(NULL, "image_vec_6_2795", image_vec_6_2795);
    lv_xml_register_image(NULL, "image_vec_6_2796", image_vec_6_2796);
    lv_xml_register_image(NULL, "image_vec_6_2797", image_vec_6_2797);
    lv_xml_register_image(NULL, "image_vec_6_2798", image_vec_6_2798);
    lv_xml_register_image(NULL, "image_vec_6_2799", image_vec_6_2799);
    lv_xml_register_image(NULL, "image_vec_6_2800", image_vec_6_2800);
    lv_xml_register_image(NULL, "image_vec_6_2801", image_vec_6_2801);
    lv_xml_register_image(NULL, "image_vec_6_2802", image_vec_6_2802);
    lv_xml_register_image(NULL, "image_vec_6_2803", image_vec_6_2803);
    lv_xml_register_image(NULL, "image_vec_6_2804", image_vec_6_2804);
    lv_xml_register_image(NULL, "image_vec_6_2805", image_vec_6_2805);
    lv_xml_register_image(NULL, "image_vec_6_2806", image_vec_6_2806);
    lv_xml_register_image(NULL, "image_vec_6_2807", image_vec_6_2807);
    lv_xml_register_image(NULL, "image_vec_6_2808", image_vec_6_2808);
    lv_xml_register_image(NULL, "image_vec_6_2809", image_vec_6_2809);
    lv_xml_register_image(NULL, "image_vec_6_2810", image_vec_6_2810);
    lv_xml_register_image(NULL, "image_vec_6_2811", image_vec_6_2811);
    lv_xml_register_image(NULL, "image_vec_6_2812", image_vec_6_2812);
    lv_xml_register_image(NULL, "image_vec_6_2813", image_vec_6_2813);
    lv_xml_register_image(NULL, "image_vec_6_2814", image_vec_6_2814);
    lv_xml_register_image(NULL, "image_vec_6_2815", image_vec_6_2815);
    lv_xml_register_image(NULL, "image_vec_6_2816", image_vec_6_2816);
    lv_xml_register_image(NULL, "image_vec_6_2817", image_vec_6_2817);
    lv_xml_register_image(NULL, "image_vec_6_2818", image_vec_6_2818);
    lv_xml_register_image(NULL, "image_vec_6_2819", image_vec_6_2819);
    lv_xml_register_image(NULL, "image_vec_6_2820", image_vec_6_2820);
    lv_xml_register_image(NULL, "image_vec_6_2821", image_vec_6_2821);
    lv_xml_register_image(NULL, "image_vec_6_2822", image_vec_6_2822);
    lv_xml_register_image(NULL, "image_vec_6_2823", image_vec_6_2823);
    lv_xml_register_image(NULL, "image_vec_6_2824", image_vec_6_2824);
    lv_xml_register_image(NULL, "image_vec_6_2825", image_vec_6_2825);
    lv_xml_register_image(NULL, "image_vec_6_2826", image_vec_6_2826);
    lv_xml_register_image(NULL, "image_vec_6_2827", image_vec_6_2827);
    lv_xml_register_image(NULL, "image_vec_6_2828", image_vec_6_2828);
    lv_xml_register_image(NULL, "image_vec_6_2829", image_vec_6_2829);
    lv_xml_register_image(NULL, "image_vec_6_2830", image_vec_6_2830);
    lv_xml_register_image(NULL, "image_vec_6_2831", image_vec_6_2831);
    lv_xml_register_image(NULL, "image_vec_6_2832", image_vec_6_2832);
    lv_xml_register_image(NULL, "image_vec_6_2833", image_vec_6_2833);
    lv_xml_register_image(NULL, "image_vec_6_2834", image_vec_6_2834);
    lv_xml_register_image(NULL, "image_vec_6_2835", image_vec_6_2835);
    lv_xml_register_image(NULL, "image_vec_6_2836", image_vec_6_2836);
    lv_xml_register_image(NULL, "image_vec_6_2837", image_vec_6_2837);
    lv_xml_register_image(NULL, "image_vec_6_2838", image_vec_6_2838);
    lv_xml_register_image(NULL, "image_vec_6_2839", image_vec_6_2839);
    lv_xml_register_image(NULL, "image_vec_6_2840", image_vec_6_2840);
    lv_xml_register_image(NULL, "image_vec_6_2841", image_vec_6_2841);
    lv_xml_register_image(NULL, "image_vec_6_2842", image_vec_6_2842);
    lv_xml_register_image(NULL, "image_vec_6_2843", image_vec_6_2843);
    lv_xml_register_image(NULL, "image_vec_6_2844", image_vec_6_2844);
    lv_xml_register_image(NULL, "image_vec_6_2845", image_vec_6_2845);
    lv_xml_register_image(NULL, "image_vec_6_2846", image_vec_6_2846);
    lv_xml_register_image(NULL, "image_vec_6_2847", image_vec_6_2847);
    lv_xml_register_image(NULL, "image_vec_6_2848", image_vec_6_2848);
    lv_xml_register_image(NULL, "image_vec_6_2849", image_vec_6_2849);
    lv_xml_register_image(NULL, "image_vec_6_2850", image_vec_6_2850);
    lv_xml_register_image(NULL, "image_vec_6_2851", image_vec_6_2851);
    lv_xml_register_image(NULL, "image_vec_6_2852", image_vec_6_2852);
    lv_xml_register_image(NULL, "image_vec_6_2853", image_vec_6_2853);
    lv_xml_register_image(NULL, "image_vec_6_2854", image_vec_6_2854);
    lv_xml_register_image(NULL, "image_vec_6_2855", image_vec_6_2855);
    lv_xml_register_image(NULL, "image_vec_6_2856", image_vec_6_2856);
    lv_xml_register_image(NULL, "image_vec_6_2857", image_vec_6_2857);
    lv_xml_register_image(NULL, "image_vec_6_2858", image_vec_6_2858);
    lv_xml_register_image(NULL, "image_vec_6_2859", image_vec_6_2859);
    lv_xml_register_image(NULL, "image_vec_6_2860", image_vec_6_2860);
    lv_xml_register_image(NULL, "image_vec_6_2861", image_vec_6_2861);
    lv_xml_register_image(NULL, "image_vec_6_2862", image_vec_6_2862);
    lv_xml_register_image(NULL, "image_vec_6_2863", image_vec_6_2863);
    lv_xml_register_image(NULL, "image_vec_6_2864", image_vec_6_2864);
    lv_xml_register_image(NULL, "image_vec_6_2865", image_vec_6_2865);
    lv_xml_register_image(NULL, "image_vec_6_2866", image_vec_6_2866);
    lv_xml_register_image(NULL, "image_vec_6_2867", image_vec_6_2867);
    lv_xml_register_image(NULL, "image_vec_6_2868", image_vec_6_2868);
    lv_xml_register_image(NULL, "image_vec_6_2869", image_vec_6_2869);
    lv_xml_register_image(NULL, "image_vec_6_2870", image_vec_6_2870);
    lv_xml_register_image(NULL, "image_vec_6_2871", image_vec_6_2871);
    lv_xml_register_image(NULL, "image_vec_6_2872", image_vec_6_2872);
    lv_xml_register_image(NULL, "image_vec_6_2873", image_vec_6_2873);
    lv_xml_register_image(NULL, "image_vec_6_2874", image_vec_6_2874);
    lv_xml_register_image(NULL, "image_vec_6_2875", image_vec_6_2875);
    lv_xml_register_image(NULL, "image_vec_6_2876", image_vec_6_2876);
    lv_xml_register_image(NULL, "image_vec_6_2877", image_vec_6_2877);
    lv_xml_register_image(NULL, "image_vec_6_2878", image_vec_6_2878);
    lv_xml_register_image(NULL, "image_vec_6_2879", image_vec_6_2879);
    lv_xml_register_image(NULL, "image_vec_6_2880", image_vec_6_2880);
    lv_xml_register_image(NULL, "image_vec_6_2881", image_vec_6_2881);
    lv_xml_register_image(NULL, "image_vec_6_2882", image_vec_6_2882);
    lv_xml_register_image(NULL, "image_vec_6_2883", image_vec_6_2883);
    lv_xml_register_image(NULL, "image_vec_6_2884", image_vec_6_2884);
    lv_xml_register_image(NULL, "image_vec_6_2885", image_vec_6_2885);
    lv_xml_register_image(NULL, "image_vec_6_2886", image_vec_6_2886);
    lv_xml_register_image(NULL, "image_vec_6_2887", image_vec_6_2887);
    lv_xml_register_image(NULL, "image_vec_6_2888", image_vec_6_2888);
    lv_xml_register_image(NULL, "image_vec_6_2889", image_vec_6_2889);
    lv_xml_register_image(NULL, "image_vec_6_2890", image_vec_6_2890);
    lv_xml_register_image(NULL, "image_vec_6_2891", image_vec_6_2891);
    lv_xml_register_image(NULL, "image_vec_6_2892", image_vec_6_2892);
    lv_xml_register_image(NULL, "image_vec_6_2893", image_vec_6_2893);
    lv_xml_register_image(NULL, "image_vec_6_2894", image_vec_6_2894);
    lv_xml_register_image(NULL, "image_vec_6_2895", image_vec_6_2895);
    lv_xml_register_image(NULL, "image_vec_6_2896", image_vec_6_2896);
    lv_xml_register_image(NULL, "image_vec_6_2897", image_vec_6_2897);
    lv_xml_register_image(NULL, "image_vec_6_2898", image_vec_6_2898);
    lv_xml_register_image(NULL, "image_vec_6_2899", image_vec_6_2899);
    lv_xml_register_image(NULL, "image_vec_6_2900", image_vec_6_2900);
    lv_xml_register_image(NULL, "image_vec_6_2901", image_vec_6_2901);
    lv_xml_register_image(NULL, "image_vec_6_2902", image_vec_6_2902);
    lv_xml_register_image(NULL, "image_vec_6_2903", image_vec_6_2903);
    lv_xml_register_image(NULL, "image_vec_6_2904", image_vec_6_2904);
    lv_xml_register_image(NULL, "image_vec_6_2905", image_vec_6_2905);
    lv_xml_register_image(NULL, "image_vec_6_2906", image_vec_6_2906);
    lv_xml_register_image(NULL, "image_vec_6_2907", image_vec_6_2907);
    lv_xml_register_image(NULL, "image_vec_6_2908", image_vec_6_2908);
    lv_xml_register_image(NULL, "image_vec_6_2909", image_vec_6_2909);
    lv_xml_register_image(NULL, "image_vec_6_2910", image_vec_6_2910);
    lv_xml_register_image(NULL, "image_vec_6_2911", image_vec_6_2911);
    lv_xml_register_image(NULL, "image_vec_6_2912", image_vec_6_2912);
    lv_xml_register_image(NULL, "image_vec_6_2913", image_vec_6_2913);
    lv_xml_register_image(NULL, "image_vec_6_2914", image_vec_6_2914);
    lv_xml_register_image(NULL, "image_vec_6_2915", image_vec_6_2915);
    lv_xml_register_image(NULL, "image_vec_6_2916", image_vec_6_2916);
    lv_xml_register_image(NULL, "image_vec_6_2917", image_vec_6_2917);
    lv_xml_register_image(NULL, "image_vec_6_2918", image_vec_6_2918);
    lv_xml_register_image(NULL, "image_vec_6_2919", image_vec_6_2919);
    lv_xml_register_image(NULL, "image_vec_6_2920", image_vec_6_2920);
    lv_xml_register_image(NULL, "image_vec_6_2921", image_vec_6_2921);
    lv_xml_register_image(NULL, "image_vec_6_2922", image_vec_6_2922);
    lv_xml_register_image(NULL, "image_vec_6_2923", image_vec_6_2923);
    lv_xml_register_image(NULL, "image_vec_6_2924", image_vec_6_2924);
    lv_xml_register_image(NULL, "image_vec_6_2925", image_vec_6_2925);
    lv_xml_register_image(NULL, "image_vec_6_2926", image_vec_6_2926);
    lv_xml_register_image(NULL, "image_vec_6_2927", image_vec_6_2927);
    lv_xml_register_image(NULL, "image_vec_6_2928", image_vec_6_2928);
    lv_xml_register_image(NULL, "image_vec_6_2929", image_vec_6_2929);
    lv_xml_register_image(NULL, "image_vec_6_2930", image_vec_6_2930);
    lv_xml_register_image(NULL, "image_vec_6_2931", image_vec_6_2931);
    lv_xml_register_image(NULL, "image_vec_6_2932", image_vec_6_2932);
    lv_xml_register_image(NULL, "image_vec_6_2933", image_vec_6_2933);
    lv_xml_register_image(NULL, "image_vec_6_2934", image_vec_6_2934);
    lv_xml_register_image(NULL, "image_vec_6_2935", image_vec_6_2935);
    lv_xml_register_image(NULL, "image_vec_6_2936", image_vec_6_2936);
    lv_xml_register_image(NULL, "image_vec_6_2937", image_vec_6_2937);
    lv_xml_register_image(NULL, "image_vec_6_2938", image_vec_6_2938);
    lv_xml_register_image(NULL, "image_vec_6_2939", image_vec_6_2939);
    lv_xml_register_image(NULL, "image_vec_6_2940", image_vec_6_2940);
    lv_xml_register_image(NULL, "image_vec_6_2943", image_vec_6_2943);
    lv_xml_register_image(NULL, "image_vec_6_2944", image_vec_6_2944);
    lv_xml_register_image(NULL, "image_vec_6_2947", image_vec_6_2947);
    lv_xml_register_image(NULL, "image_vec_6_2948", image_vec_6_2948);
    lv_xml_register_image(NULL, "image_vec_6_2951", image_vec_6_2951);
    lv_xml_register_image(NULL, "image_vec_6_2952", image_vec_6_2952);
    lv_xml_register_image(NULL, "image_vec_6_2955", image_vec_6_2955);
    lv_xml_register_image(NULL, "image_vec_6_2956", image_vec_6_2956);
    lv_xml_register_image(NULL, "image_vec_6_2959", image_vec_6_2959);
    lv_xml_register_image(NULL, "image_vec_6_2960", image_vec_6_2960);
    lv_xml_register_image(NULL, "image_vec_6_2963", image_vec_6_2963);
    lv_xml_register_image(NULL, "image_vec_6_2964", image_vec_6_2964);
    lv_xml_register_image(NULL, "image_vec_25_1105", image_vec_25_1105);
    lv_xml_register_image(NULL, "image_vec_7_1412", image_vec_7_1412);
    lv_xml_register_image(NULL, "image_vec_1_241", image_vec_1_241);
    lv_xml_register_image(NULL, "image_vec_7_1491", image_vec_7_1491);
    lv_xml_register_image(NULL, "image_vec_7_1493", image_vec_7_1493);
    lv_xml_register_image(NULL, "image_vec_1_790", image_vec_1_790);
    lv_xml_register_image(NULL, "image_vec_1_882", image_vec_1_882);
    lv_xml_register_image(NULL, "image_vec_25_1004", image_vec_25_1004);
    lv_xml_register_image(NULL, "image_vec_7_1415", image_vec_7_1415);
    lv_xml_register_image(NULL, "image_vec_23_214", image_vec_23_214);
    lv_xml_register_image(NULL, "image_vec_42_2416", image_vec_42_2416);
    lv_xml_register_image(NULL, "image_vec_42_2418", image_vec_42_2418);
    lv_xml_register_image(NULL, "image_vec_34_869", image_vec_34_869);
    lv_xml_register_image(NULL, "image_vec_34_872", image_vec_34_872);
    lv_xml_register_image(NULL, "image_vec_23_372", image_vec_23_372);
    lv_xml_register_image(NULL, "image_vec_42_877", image_vec_42_877);
    lv_xml_register_image(NULL, "image_vec_12_212", image_vec_12_212);
    lv_xml_register_image(NULL, "image_vec_42_862", image_vec_42_862);
    lv_xml_register_image(NULL, "image_vec_7_1590", image_vec_7_1590);
    lv_xml_register_image(NULL, "image_vec_46_963", image_vec_46_963);
    lv_xml_register_image(NULL, "image_vec_46_964", image_vec_46_964);
    lv_xml_register_image(NULL, "image_vec_46_965", image_vec_46_965);
    lv_xml_register_image(NULL, "image_vec_46_966", image_vec_46_966);
    lv_xml_register_image(NULL, "image_vec_46_967", image_vec_46_967);
    lv_xml_register_image(NULL, "image_vec_46_968", image_vec_46_968);
    lv_xml_register_image(NULL, "image_vec_46_969", image_vec_46_969);
    lv_xml_register_image(NULL, "image_vec_46_970", image_vec_46_970);
    lv_xml_register_image(NULL, "image_vec_46_971", image_vec_46_971);
    lv_xml_register_image(NULL, "image_vec_46_972", image_vec_46_972);
    lv_xml_register_image(NULL, "image_vec_46_973", image_vec_46_973);
    lv_xml_register_image(NULL, "image_vec_46_974", image_vec_46_974);
    lv_xml_register_image(NULL, "image_vec_46_975", image_vec_46_975);
    lv_xml_register_image(NULL, "image_vec_46_976", image_vec_46_976);
    lv_xml_register_image(NULL, "image_vec_46_977", image_vec_46_977);
    lv_xml_register_image(NULL, "image_vec_46_978", image_vec_46_978);
    lv_xml_register_image(NULL, "image_vec_46_979", image_vec_46_979);
    lv_xml_register_image(NULL, "image_vec_46_980", image_vec_46_980);
    lv_xml_register_image(NULL, "image_vec_46_981", image_vec_46_981);
    lv_xml_register_image(NULL, "image_vec_46_982", image_vec_46_982);
    lv_xml_register_image(NULL, "image_vec_46_983", image_vec_46_983);
    lv_xml_register_image(NULL, "image_vec_46_984", image_vec_46_984);
    lv_xml_register_image(NULL, "image_vec_46_985", image_vec_46_985);
    lv_xml_register_image(NULL, "image_vec_46_986", image_vec_46_986);
    lv_xml_register_image(NULL, "image_vec_46_987", image_vec_46_987);
    lv_xml_register_image(NULL, "image_vec_46_988", image_vec_46_988);
    lv_xml_register_image(NULL, "image_vec_46_989", image_vec_46_989);
    lv_xml_register_image(NULL, "image_vec_46_990", image_vec_46_990);
    lv_xml_register_image(NULL, "image_vec_46_991", image_vec_46_991);
    lv_xml_register_image(NULL, "image_vec_46_992", image_vec_46_992);
    lv_xml_register_image(NULL, "image_vec_46_993", image_vec_46_993);
    lv_xml_register_image(NULL, "image_vec_46_994", image_vec_46_994);
    lv_xml_register_image(NULL, "image_vec_46_995", image_vec_46_995);
    lv_xml_register_image(NULL, "image_vec_46_996", image_vec_46_996);
    lv_xml_register_image(NULL, "image_vec_46_997", image_vec_46_997);
    lv_xml_register_image(NULL, "image_vec_46_998", image_vec_46_998);
#endif

#if !defined(LV_USE_XML) || LV_USE_XML == 0
    /*--------------------
     *  Permanent screens
     *-------------------*/
    /* If XML is enabled it's assumed that the permanent screens are created
     * manually from XML using lv_xml_create() */
#endif
}

void plurality_pin_set_target(uint32_t target)
{
    plurality_pin_target = target;
}

uint32_t plurality_pin_get_target(void)
{
    return plurality_pin_target;
}

bool plurality_pin_check_target(uint32_t target)
{
    return (plurality_pin_target & target) ? true : false;
}

/* Callbacks */

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void check_font(lv_font_t ** font, const char * name)
{
    if (!(*font)) {
        *font = (lv_font_t *)LV_FONT_DEFAULT;
        LV_LOG_WARN("font `%s` was not set. Using `LV_FONT_DEFAULT` instead", name);
    }
}