/**
 * @file plurality_pin_gen.c
 */

/*********************
 *      INCLUDES
 *********************/

#include "plurality_pin_gen.h"

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
const void * image_vec_42_2416 = NULL;
extern const void * image_vec_42_2416_data;
const void * image_vec_42_2418 = NULL;
extern const void * image_vec_42_2418_data;
const void * image_vec_23_214 = NULL;
extern const void * image_vec_23_214_data;

/*----------------
 * Global styles
 *----------------*/

lv_style_t style_screen_base_global;

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
            lv_snprintf(buf, 256, "%s%s", asset_path, "fonts/IBMPlexMono-Regular.ttf");
            font_ibm_plex_mono_regular_26 = lv_tiny_ttf_create_file(buf, 26);
        }
        if (!font_ibm_plex_mono_semibold_150) {
            /* font_ibm_plex_mono_semibold_150 */
            /* create tiny ttf font "font_ibm_plex_mono_semibold_150" from file */
            lv_snprintf(buf, 256, "%s%s", asset_path, "fonts/IBMPlexMono-SemiBold.ttf");
            font_ibm_plex_mono_semibold_150 = lv_tiny_ttf_create_file(buf, 150);
        }
        if (!font_inter_medium_24_460227966308594) {
            /* font_inter_medium_24_460227966308594 */
            /* create tiny ttf font "font_inter_medium_24_460227966308594" from file */
            lv_snprintf(buf, 256, "%s%s", asset_path, "fonts/Inter-Medium.ttf");
            font_inter_medium_24_460227966308594 = lv_tiny_ttf_create_file(buf, 24);
        }
        if (!font_roboto_semibold_22) {
            /* font_roboto_semibold_22 */
            /* create tiny ttf font "font_roboto_semibold_22" from file */
            lv_snprintf(buf, 256, "%s%s", asset_path, "fonts/Roboto-SemiBold.ttf");
            font_roboto_semibold_22 = lv_tiny_ttf_create_file(buf, 22);
        }
        if (!font_inter_semi_bold_12) {
            /* font_inter_semi_bold_12 */
            /* create tiny ttf font "font_inter_semi_bold_12" from file */
            lv_snprintf(buf, 256, "%s%s", asset_path, "fonts/Inter-SemiBold.ttf");
            font_inter_semi_bold_12 = lv_tiny_ttf_create_file(buf, 12);
        }
        if (!font_inter_bold_28) {
            /* font_inter_bold_28 */
            /* create tiny ttf font "font_inter_bold_28" from file */
            lv_snprintf(buf, 256, "%s%s", asset_path, "fonts/Inter-Bold.ttf");
            font_inter_bold_28 = lv_tiny_ttf_create_file(buf, 28);
        }
        if (!font_inter_semi_bold_16) {
            /* font_inter_semi_bold_16 */
            /* create tiny ttf font "font_inter_semi_bold_16" from file */
            lv_snprintf(buf, 256, "%s%s", asset_path, "fonts/Inter-SemiBold.ttf");
            font_inter_semi_bold_16 = lv_tiny_ttf_create_file(buf, 16);
        }
        if (!font_inter_semi_bold_14) {
            /* font_inter_semi_bold_14 */
            /* create tiny ttf font "font_inter_semi_bold_14" from file */
            lv_snprintf(buf, 256, "%s%s", asset_path, "fonts/Inter-SemiBold.ttf");
            font_inter_semi_bold_14 = lv_tiny_ttf_create_file(buf, 14);
        }
        if (!font_inter_medium_11) {
            /* font_inter_medium_11 */
            /* create tiny ttf font "font_inter_medium_11" from file */
            lv_snprintf(buf, 256, "%s%s", asset_path, "fonts/Inter-Medium.ttf");
            font_inter_medium_11 = lv_tiny_ttf_create_file(buf, 11);
        }
        if (!font_inter_bold_14) {
            /* font_inter_bold_14 */
            /* create tiny ttf font "font_inter_bold_14" from file */
            lv_snprintf(buf, 256, "%s%s", asset_path, "fonts/Inter-Bold.ttf");
            font_inter_bold_14 = lv_tiny_ttf_create_file(buf, 14);
        }
        if (!font_inter_bold_20) {
            /* font_inter_bold_20 */
            /* create tiny ttf font "font_inter_bold_20" from file */
            lv_snprintf(buf, 256, "%s%s", asset_path, "fonts/Inter-Bold.ttf");
            font_inter_bold_20 = lv_tiny_ttf_create_file(buf, 20);
        }
        if (!font_inter_bold_23) {
            /* font_inter_bold_23 */
            /* create tiny ttf font "font_inter_bold_23" from file */
            lv_snprintf(buf, 256, "%s%s", asset_path, "fonts/Inter-Bold.ttf");
            font_inter_bold_23 = lv_tiny_ttf_create_file(buf, 23);
        }
        if (!font_inter_semi_bold_13) {
            /* font_inter_semi_bold_13 */
            /* create tiny ttf font "font_inter_semi_bold_13" from file */
            lv_snprintf(buf, 256, "%s%s", asset_path, "fonts/Inter-SemiBold.ttf");
            font_inter_semi_bold_13 = lv_tiny_ttf_create_file(buf, 13);
        }
        if (!font_playwrite_us_trad_regular_40) {
            /* font_playwrite_us_trad_regular_40 */
            /* create tiny ttf font "font_playwrite_us_trad_regular_40" from file */
            lv_snprintf(buf, 256, "%s%s", asset_path, "fonts/PlaywriteUSTrad-Regular.ttf");
            font_playwrite_us_trad_regular_40 = lv_tiny_ttf_create_file(buf, 40);
        }
        if (!font_playwrite_us_trad_regular_52) {
            /* font_playwrite_us_trad_regular_52 */
            /* create tiny ttf font "font_playwrite_us_trad_regular_52" from file */
            lv_snprintf(buf, 256, "%s%s", asset_path, "fonts/PlaywriteUSTrad-Regular.ttf");
            font_playwrite_us_trad_regular_52 = lv_tiny_ttf_create_file(buf, 52);
        }
        if (!font_inter_semi_bold_8) {
            /* font_inter_semi_bold_8 */
            /* create tiny ttf font "font_inter_semi_bold_8" from file */
            lv_snprintf(buf, 256, "%s%s", asset_path, "fonts/Inter-SemiBold.ttf");
            font_inter_semi_bold_8 = lv_tiny_ttf_create_file(buf, 8);
        }
        if (!font_inter_semi_bold_11) {
            /* font_inter_semi_bold_11 */
            /* create tiny ttf font "font_inter_semi_bold_11" from file */
            lv_snprintf(buf, 256, "%s%s", asset_path, "fonts/Inter-SemiBold.ttf");
            font_inter_semi_bold_11 = lv_tiny_ttf_create_file(buf, 11);
        }
        if (!font_roboto_medium_14) {
            /* font_roboto_medium_14 */
            /* create tiny ttf font "font_roboto_medium_14" from file */
            lv_snprintf(buf, 256, "%s%s", asset_path, "fonts/Roboto-Medium.ttf");
            font_roboto_medium_14 = lv_tiny_ttf_create_file(buf, 14);
        }
        if (!font_ibm_plex_mono_regular_36) {
            /* font_ibm_plex_mono_regular_36 */
            /* create tiny ttf font "font_ibm_plex_mono_regular_36" from file */
            lv_snprintf(buf, 256, "%s%s", asset_path, "fonts/IBMPlexMono-Regular.ttf");
            font_ibm_plex_mono_regular_36 = lv_tiny_ttf_create_file(buf, 36);
        }
        if (!font_roboto_medium_16) {
            /* font_roboto_medium_16 */
            /* create tiny ttf font "font_roboto_medium_16" from file */
            lv_snprintf(buf, 256, "%s%s", asset_path, "fonts/Inter-Medium.ttf");
            font_roboto_medium_16 = lv_tiny_ttf_create_file(buf, 16);
        }
        if (!font_ibm_plex_mono_medium_14) {
            /* font_ibm_plex_mono_medium_14 */
            /* create tiny ttf font "font_ibm_plex_mono_medium_14" from file */
            lv_snprintf(buf, 256, "%s%s", asset_path, "fonts/IBMPlexMono-Medium.ttf");
            font_ibm_plex_mono_medium_14 = lv_tiny_ttf_create_file(buf, 14);
        }
        if (!font_ibm_plex_mono_regular_29) {
            /* font_ibm_plex_mono_regular_29 */
            /* create tiny ttf font "font_ibm_plex_mono_regular_29" from file */
            lv_snprintf(buf, 256, "%s%s", asset_path, "fonts/IBMPlexMono-Regular.ttf");
            font_ibm_plex_mono_regular_29 = lv_tiny_ttf_create_file(buf, 29);
        }
        if (!font_inter_medium_24_manual) {
            /* font_inter_medium_24_manual */
            /* create tiny ttf font "font_inter_medium_24_manual" from file */
            lv_snprintf(buf, 256, "%s%s", asset_path, "fonts/Inter-Medium.ttf");
            font_inter_medium_24_manual = lv_tiny_ttf_create_file(buf, 24);
        }
        if (!font_inter_semi_bold_22_manual) {
            /* font_inter_semi_bold_22_manual */
            /* create tiny ttf font "font_inter_semi_bold_22_manual" from file */
            lv_snprintf(buf, 256, "%s%s", asset_path, "fonts/Inter-SemiBold.ttf");
            font_inter_semi_bold_22_manual = lv_tiny_ttf_create_file(buf, 22);
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
            image_img_02c5506b = &image_img_02c5506b_data;
        }
        /* image_img_45c6bb3a */
        if (!image_img_45c6bb3a) {
            image_img_45c6bb3a = &image_img_45c6bb3a_data;
        }
        /* image_vec_37_864 */
        if (!image_vec_37_864) {
            image_vec_37_864 = &image_vec_37_864_data;
        }
        /* image_vec_6_2604 */
        if (!image_vec_6_2604) {
            image_vec_6_2604 = &image_vec_6_2604_data;
        }
        /* image_vec_6_2605 */
        if (!image_vec_6_2605) {
            image_vec_6_2605 = &image_vec_6_2605_data;
        }
        /* image_vec_6_2608 */
        if (!image_vec_6_2608) {
            image_vec_6_2608 = &image_vec_6_2608_data;
        }
        /* image_vec_6_2609 */
        if (!image_vec_6_2609) {
            image_vec_6_2609 = &image_vec_6_2609_data;
        }
        /* image_vec_6_2610 */
        if (!image_vec_6_2610) {
            image_vec_6_2610 = &image_vec_6_2610_data;
        }
        /* image_vec_6_2611 */
        if (!image_vec_6_2611) {
            image_vec_6_2611 = &image_vec_6_2611_data;
        }
        /* image_vec_6_2612 */
        if (!image_vec_6_2612) {
            image_vec_6_2612 = &image_vec_6_2612_data;
        }
        /* image_vec_6_2613 */
        if (!image_vec_6_2613) {
            image_vec_6_2613 = &image_vec_6_2613_data;
        }
        /* image_vec_6_2614 */
        if (!image_vec_6_2614) {
            image_vec_6_2614 = &image_vec_6_2614_data;
        }
        /* image_vec_6_2615 */
        if (!image_vec_6_2615) {
            image_vec_6_2615 = &image_vec_6_2615_data;
        }
        /* image_vec_6_2616 */
        if (!image_vec_6_2616) {
            image_vec_6_2616 = &image_vec_6_2616_data;
        }
        /* image_vec_6_2617 */
        if (!image_vec_6_2617) {
            image_vec_6_2617 = &image_vec_6_2617_data;
        }
        /* image_vec_6_2618 */
        if (!image_vec_6_2618) {
            image_vec_6_2618 = &image_vec_6_2618_data;
        }
        /* image_vec_6_2619 */
        if (!image_vec_6_2619) {
            image_vec_6_2619 = &image_vec_6_2619_data;
        }
        /* image_vec_6_2620 */
        if (!image_vec_6_2620) {
            image_vec_6_2620 = &image_vec_6_2620_data;
        }
        /* image_vec_6_2621 */
        if (!image_vec_6_2621) {
            image_vec_6_2621 = &image_vec_6_2621_data;
        }
        /* image_vec_6_2622 */
        if (!image_vec_6_2622) {
            image_vec_6_2622 = &image_vec_6_2622_data;
        }
        /* image_vec_6_2623 */
        if (!image_vec_6_2623) {
            image_vec_6_2623 = &image_vec_6_2623_data;
        }
        /* image_vec_6_2624 */
        if (!image_vec_6_2624) {
            image_vec_6_2624 = &image_vec_6_2624_data;
        }
        /* image_vec_6_2625 */
        if (!image_vec_6_2625) {
            image_vec_6_2625 = &image_vec_6_2625_data;
        }
        /* image_vec_6_2626 */
        if (!image_vec_6_2626) {
            image_vec_6_2626 = &image_vec_6_2626_data;
        }
        /* image_vec_6_2627 */
        if (!image_vec_6_2627) {
            image_vec_6_2627 = &image_vec_6_2627_data;
        }
        /* image_vec_6_2628 */
        if (!image_vec_6_2628) {
            image_vec_6_2628 = &image_vec_6_2628_data;
        }
        /* image_vec_6_2629 */
        if (!image_vec_6_2629) {
            image_vec_6_2629 = &image_vec_6_2629_data;
        }
        /* image_vec_6_2630 */
        if (!image_vec_6_2630) {
            image_vec_6_2630 = &image_vec_6_2630_data;
        }
        /* image_vec_6_2631 */
        if (!image_vec_6_2631) {
            image_vec_6_2631 = &image_vec_6_2631_data;
        }
        /* image_vec_6_2632 */
        if (!image_vec_6_2632) {
            image_vec_6_2632 = &image_vec_6_2632_data;
        }
        /* image_vec_6_2633 */
        if (!image_vec_6_2633) {
            image_vec_6_2633 = &image_vec_6_2633_data;
        }
        /* image_vec_6_2634 */
        if (!image_vec_6_2634) {
            image_vec_6_2634 = &image_vec_6_2634_data;
        }
        /* image_vec_6_2635 */
        if (!image_vec_6_2635) {
            image_vec_6_2635 = &image_vec_6_2635_data;
        }
        /* image_vec_6_2636 */
        if (!image_vec_6_2636) {
            image_vec_6_2636 = &image_vec_6_2636_data;
        }
        /* image_vec_6_2637 */
        if (!image_vec_6_2637) {
            image_vec_6_2637 = &image_vec_6_2637_data;
        }
        /* image_vec_6_2638 */
        if (!image_vec_6_2638) {
            image_vec_6_2638 = &image_vec_6_2638_data;
        }
        /* image_vec_6_2639 */
        if (!image_vec_6_2639) {
            image_vec_6_2639 = &image_vec_6_2639_data;
        }
        /* image_vec_6_2640 */
        if (!image_vec_6_2640) {
            image_vec_6_2640 = &image_vec_6_2640_data;
        }
        /* image_vec_6_2641 */
        if (!image_vec_6_2641) {
            image_vec_6_2641 = &image_vec_6_2641_data;
        }
        /* image_vec_6_2642 */
        if (!image_vec_6_2642) {
            image_vec_6_2642 = &image_vec_6_2642_data;
        }
        /* image_vec_6_2643 */
        if (!image_vec_6_2643) {
            image_vec_6_2643 = &image_vec_6_2643_data;
        }
        /* image_vec_6_2644 */
        if (!image_vec_6_2644) {
            image_vec_6_2644 = &image_vec_6_2644_data;
        }
        /* image_vec_6_2645 */
        if (!image_vec_6_2645) {
            image_vec_6_2645 = &image_vec_6_2645_data;
        }
        /* image_vec_6_2646 */
        if (!image_vec_6_2646) {
            image_vec_6_2646 = &image_vec_6_2646_data;
        }
        /* image_vec_6_2647 */
        if (!image_vec_6_2647) {
            image_vec_6_2647 = &image_vec_6_2647_data;
        }
        /* image_vec_6_2648 */
        if (!image_vec_6_2648) {
            image_vec_6_2648 = &image_vec_6_2648_data;
        }
        /* image_vec_6_2649 */
        if (!image_vec_6_2649) {
            image_vec_6_2649 = &image_vec_6_2649_data;
        }
        /* image_vec_6_2650 */
        if (!image_vec_6_2650) {
            image_vec_6_2650 = &image_vec_6_2650_data;
        }
        /* image_vec_6_2651 */
        if (!image_vec_6_2651) {
            image_vec_6_2651 = &image_vec_6_2651_data;
        }
        /* image_vec_6_2652 */
        if (!image_vec_6_2652) {
            image_vec_6_2652 = &image_vec_6_2652_data;
        }
        /* image_vec_6_2653 */
        if (!image_vec_6_2653) {
            image_vec_6_2653 = &image_vec_6_2653_data;
        }
        /* image_vec_6_2654 */
        if (!image_vec_6_2654) {
            image_vec_6_2654 = &image_vec_6_2654_data;
        }
        /* image_vec_6_2655 */
        if (!image_vec_6_2655) {
            image_vec_6_2655 = &image_vec_6_2655_data;
        }
        /* image_vec_6_2656 */
        if (!image_vec_6_2656) {
            image_vec_6_2656 = &image_vec_6_2656_data;
        }
        /* image_vec_6_2657 */
        if (!image_vec_6_2657) {
            image_vec_6_2657 = &image_vec_6_2657_data;
        }
        /* image_vec_6_2658 */
        if (!image_vec_6_2658) {
            image_vec_6_2658 = &image_vec_6_2658_data;
        }
        /* image_vec_6_2659 */
        if (!image_vec_6_2659) {
            image_vec_6_2659 = &image_vec_6_2659_data;
        }
        /* image_vec_6_2660 */
        if (!image_vec_6_2660) {
            image_vec_6_2660 = &image_vec_6_2660_data;
        }
        /* image_vec_6_2661 */
        if (!image_vec_6_2661) {
            image_vec_6_2661 = &image_vec_6_2661_data;
        }
        /* image_vec_6_2662 */
        if (!image_vec_6_2662) {
            image_vec_6_2662 = &image_vec_6_2662_data;
        }
        /* image_vec_6_2663 */
        if (!image_vec_6_2663) {
            image_vec_6_2663 = &image_vec_6_2663_data;
        }
        /* image_vec_6_2664 */
        if (!image_vec_6_2664) {
            image_vec_6_2664 = &image_vec_6_2664_data;
        }
        /* image_vec_6_2665 */
        if (!image_vec_6_2665) {
            image_vec_6_2665 = &image_vec_6_2665_data;
        }
        /* image_vec_6_2666 */
        if (!image_vec_6_2666) {
            image_vec_6_2666 = &image_vec_6_2666_data;
        }
        /* image_vec_6_2667 */
        if (!image_vec_6_2667) {
            image_vec_6_2667 = &image_vec_6_2667_data;
        }
        /* image_vec_6_2668 */
        if (!image_vec_6_2668) {
            image_vec_6_2668 = &image_vec_6_2668_data;
        }
        /* image_vec_6_2669 */
        if (!image_vec_6_2669) {
            image_vec_6_2669 = &image_vec_6_2669_data;
        }
        /* image_vec_6_2670 */
        if (!image_vec_6_2670) {
            image_vec_6_2670 = &image_vec_6_2670_data;
        }
        /* image_vec_6_2671 */
        if (!image_vec_6_2671) {
            image_vec_6_2671 = &image_vec_6_2671_data;
        }
        /* image_vec_6_2672 */
        if (!image_vec_6_2672) {
            image_vec_6_2672 = &image_vec_6_2672_data;
        }
        /* image_vec_6_2673 */
        if (!image_vec_6_2673) {
            image_vec_6_2673 = &image_vec_6_2673_data;
        }
        /* image_vec_6_2674 */
        if (!image_vec_6_2674) {
            image_vec_6_2674 = &image_vec_6_2674_data;
        }
        /* image_vec_6_2675 */
        if (!image_vec_6_2675) {
            image_vec_6_2675 = &image_vec_6_2675_data;
        }
        /* image_vec_6_2676 */
        if (!image_vec_6_2676) {
            image_vec_6_2676 = &image_vec_6_2676_data;
        }
        /* image_vec_6_2677 */
        if (!image_vec_6_2677) {
            image_vec_6_2677 = &image_vec_6_2677_data;
        }
        /* image_vec_6_2678 */
        if (!image_vec_6_2678) {
            image_vec_6_2678 = &image_vec_6_2678_data;
        }
        /* image_vec_6_2679 */
        if (!image_vec_6_2679) {
            image_vec_6_2679 = &image_vec_6_2679_data;
        }
        /* image_vec_6_2680 */
        if (!image_vec_6_2680) {
            image_vec_6_2680 = &image_vec_6_2680_data;
        }
        /* image_vec_6_2681 */
        if (!image_vec_6_2681) {
            image_vec_6_2681 = &image_vec_6_2681_data;
        }
        /* image_vec_6_2682 */
        if (!image_vec_6_2682) {
            image_vec_6_2682 = &image_vec_6_2682_data;
        }
        /* image_vec_6_2683 */
        if (!image_vec_6_2683) {
            image_vec_6_2683 = &image_vec_6_2683_data;
        }
        /* image_vec_6_2684 */
        if (!image_vec_6_2684) {
            image_vec_6_2684 = &image_vec_6_2684_data;
        }
        /* image_vec_6_2685 */
        if (!image_vec_6_2685) {
            image_vec_6_2685 = &image_vec_6_2685_data;
        }
        /* image_vec_6_2686 */
        if (!image_vec_6_2686) {
            image_vec_6_2686 = &image_vec_6_2686_data;
        }
        /* image_vec_6_2687 */
        if (!image_vec_6_2687) {
            image_vec_6_2687 = &image_vec_6_2687_data;
        }
        /* image_vec_6_2688 */
        if (!image_vec_6_2688) {
            image_vec_6_2688 = &image_vec_6_2688_data;
        }
        /* image_vec_6_2689 */
        if (!image_vec_6_2689) {
            image_vec_6_2689 = &image_vec_6_2689_data;
        }
        /* image_vec_6_2690 */
        if (!image_vec_6_2690) {
            image_vec_6_2690 = &image_vec_6_2690_data;
        }
        /* image_vec_6_2691 */
        if (!image_vec_6_2691) {
            image_vec_6_2691 = &image_vec_6_2691_data;
        }
        /* image_vec_6_2692 */
        if (!image_vec_6_2692) {
            image_vec_6_2692 = &image_vec_6_2692_data;
        }
        /* image_vec_6_2693 */
        if (!image_vec_6_2693) {
            image_vec_6_2693 = &image_vec_6_2693_data;
        }
        /* image_vec_6_2694 */
        if (!image_vec_6_2694) {
            image_vec_6_2694 = &image_vec_6_2694_data;
        }
        /* image_vec_6_2695 */
        if (!image_vec_6_2695) {
            image_vec_6_2695 = &image_vec_6_2695_data;
        }
        /* image_vec_6_2696 */
        if (!image_vec_6_2696) {
            image_vec_6_2696 = &image_vec_6_2696_data;
        }
        /* image_vec_6_2697 */
        if (!image_vec_6_2697) {
            image_vec_6_2697 = &image_vec_6_2697_data;
        }
        /* image_vec_6_2698 */
        if (!image_vec_6_2698) {
            image_vec_6_2698 = &image_vec_6_2698_data;
        }
        /* image_vec_6_2699 */
        if (!image_vec_6_2699) {
            image_vec_6_2699 = &image_vec_6_2699_data;
        }
        /* image_vec_6_2700 */
        if (!image_vec_6_2700) {
            image_vec_6_2700 = &image_vec_6_2700_data;
        }
        /* image_vec_6_2701 */
        if (!image_vec_6_2701) {
            image_vec_6_2701 = &image_vec_6_2701_data;
        }
        /* image_vec_6_2702 */
        if (!image_vec_6_2702) {
            image_vec_6_2702 = &image_vec_6_2702_data;
        }
        /* image_vec_6_2703 */
        if (!image_vec_6_2703) {
            image_vec_6_2703 = &image_vec_6_2703_data;
        }
        /* image_vec_6_2704 */
        if (!image_vec_6_2704) {
            image_vec_6_2704 = &image_vec_6_2704_data;
        }
        /* image_vec_6_2705 */
        if (!image_vec_6_2705) {
            image_vec_6_2705 = &image_vec_6_2705_data;
        }
        /* image_vec_6_2706 */
        if (!image_vec_6_2706) {
            image_vec_6_2706 = &image_vec_6_2706_data;
        }
        /* image_vec_6_2707 */
        if (!image_vec_6_2707) {
            image_vec_6_2707 = &image_vec_6_2707_data;
        }
        /* image_vec_6_2708 */
        if (!image_vec_6_2708) {
            image_vec_6_2708 = &image_vec_6_2708_data;
        }
        /* image_vec_6_2709 */
        if (!image_vec_6_2709) {
            image_vec_6_2709 = &image_vec_6_2709_data;
        }
        /* image_vec_6_2710 */
        if (!image_vec_6_2710) {
            image_vec_6_2710 = &image_vec_6_2710_data;
        }
        /* image_vec_6_2711 */
        if (!image_vec_6_2711) {
            image_vec_6_2711 = &image_vec_6_2711_data;
        }
        /* image_vec_6_2712 */
        if (!image_vec_6_2712) {
            image_vec_6_2712 = &image_vec_6_2712_data;
        }
        /* image_vec_6_2713 */
        if (!image_vec_6_2713) {
            image_vec_6_2713 = &image_vec_6_2713_data;
        }
        /* image_vec_6_2714 */
        if (!image_vec_6_2714) {
            image_vec_6_2714 = &image_vec_6_2714_data;
        }
        /* image_vec_6_2715 */
        if (!image_vec_6_2715) {
            image_vec_6_2715 = &image_vec_6_2715_data;
        }
        /* image_vec_6_2716 */
        if (!image_vec_6_2716) {
            image_vec_6_2716 = &image_vec_6_2716_data;
        }
        /* image_vec_6_2717 */
        if (!image_vec_6_2717) {
            image_vec_6_2717 = &image_vec_6_2717_data;
        }
        /* image_vec_6_2718 */
        if (!image_vec_6_2718) {
            image_vec_6_2718 = &image_vec_6_2718_data;
        }
        /* image_vec_6_2719 */
        if (!image_vec_6_2719) {
            image_vec_6_2719 = &image_vec_6_2719_data;
        }
        /* image_vec_6_2720 */
        if (!image_vec_6_2720) {
            image_vec_6_2720 = &image_vec_6_2720_data;
        }
        /* image_vec_6_2721 */
        if (!image_vec_6_2721) {
            image_vec_6_2721 = &image_vec_6_2721_data;
        }
        /* image_vec_6_2722 */
        if (!image_vec_6_2722) {
            image_vec_6_2722 = &image_vec_6_2722_data;
        }
        /* image_vec_6_2723 */
        if (!image_vec_6_2723) {
            image_vec_6_2723 = &image_vec_6_2723_data;
        }
        /* image_vec_6_2724 */
        if (!image_vec_6_2724) {
            image_vec_6_2724 = &image_vec_6_2724_data;
        }
        /* image_vec_6_2725 */
        if (!image_vec_6_2725) {
            image_vec_6_2725 = &image_vec_6_2725_data;
        }
        /* image_vec_6_2726 */
        if (!image_vec_6_2726) {
            image_vec_6_2726 = &image_vec_6_2726_data;
        }
        /* image_vec_6_2727 */
        if (!image_vec_6_2727) {
            image_vec_6_2727 = &image_vec_6_2727_data;
        }
        /* image_vec_6_2728 */
        if (!image_vec_6_2728) {
            image_vec_6_2728 = &image_vec_6_2728_data;
        }
        /* image_vec_6_2729 */
        if (!image_vec_6_2729) {
            image_vec_6_2729 = &image_vec_6_2729_data;
        }
        /* image_vec_6_2730 */
        if (!image_vec_6_2730) {
            image_vec_6_2730 = &image_vec_6_2730_data;
        }
        /* image_vec_6_2731 */
        if (!image_vec_6_2731) {
            image_vec_6_2731 = &image_vec_6_2731_data;
        }
        /* image_vec_6_2732 */
        if (!image_vec_6_2732) {
            image_vec_6_2732 = &image_vec_6_2732_data;
        }
        /* image_vec_6_2733 */
        if (!image_vec_6_2733) {
            image_vec_6_2733 = &image_vec_6_2733_data;
        }
        /* image_vec_6_2734 */
        if (!image_vec_6_2734) {
            image_vec_6_2734 = &image_vec_6_2734_data;
        }
        /* image_vec_6_2735 */
        if (!image_vec_6_2735) {
            image_vec_6_2735 = &image_vec_6_2735_data;
        }
        /* image_vec_6_2736 */
        if (!image_vec_6_2736) {
            image_vec_6_2736 = &image_vec_6_2736_data;
        }
        /* image_vec_6_2737 */
        if (!image_vec_6_2737) {
            image_vec_6_2737 = &image_vec_6_2737_data;
        }
        /* image_vec_6_2738 */
        if (!image_vec_6_2738) {
            image_vec_6_2738 = &image_vec_6_2738_data;
        }
        /* image_vec_6_2739 */
        if (!image_vec_6_2739) {
            image_vec_6_2739 = &image_vec_6_2739_data;
        }
        /* image_vec_6_2740 */
        if (!image_vec_6_2740) {
            image_vec_6_2740 = &image_vec_6_2740_data;
        }
        /* image_vec_6_2741 */
        if (!image_vec_6_2741) {
            image_vec_6_2741 = &image_vec_6_2741_data;
        }
        /* image_vec_6_2742 */
        if (!image_vec_6_2742) {
            image_vec_6_2742 = &image_vec_6_2742_data;
        }
        /* image_vec_6_2743 */
        if (!image_vec_6_2743) {
            image_vec_6_2743 = &image_vec_6_2743_data;
        }
        /* image_vec_6_2744 */
        if (!image_vec_6_2744) {
            image_vec_6_2744 = &image_vec_6_2744_data;
        }
        /* image_vec_6_2745 */
        if (!image_vec_6_2745) {
            image_vec_6_2745 = &image_vec_6_2745_data;
        }
        /* image_vec_6_2746 */
        if (!image_vec_6_2746) {
            image_vec_6_2746 = &image_vec_6_2746_data;
        }
        /* image_vec_6_2747 */
        if (!image_vec_6_2747) {
            image_vec_6_2747 = &image_vec_6_2747_data;
        }
        /* image_vec_6_2748 */
        if (!image_vec_6_2748) {
            image_vec_6_2748 = &image_vec_6_2748_data;
        }
        /* image_vec_6_2749 */
        if (!image_vec_6_2749) {
            image_vec_6_2749 = &image_vec_6_2749_data;
        }
        /* image_vec_6_2750 */
        if (!image_vec_6_2750) {
            image_vec_6_2750 = &image_vec_6_2750_data;
        }
        /* image_vec_6_2751 */
        if (!image_vec_6_2751) {
            image_vec_6_2751 = &image_vec_6_2751_data;
        }
        /* image_vec_6_2752 */
        if (!image_vec_6_2752) {
            image_vec_6_2752 = &image_vec_6_2752_data;
        }
        /* image_vec_6_2753 */
        if (!image_vec_6_2753) {
            image_vec_6_2753 = &image_vec_6_2753_data;
        }
        /* image_vec_6_2754 */
        if (!image_vec_6_2754) {
            image_vec_6_2754 = &image_vec_6_2754_data;
        }
        /* image_vec_6_2755 */
        if (!image_vec_6_2755) {
            image_vec_6_2755 = &image_vec_6_2755_data;
        }
        /* image_vec_6_2756 */
        if (!image_vec_6_2756) {
            image_vec_6_2756 = &image_vec_6_2756_data;
        }
        /* image_vec_6_2757 */
        if (!image_vec_6_2757) {
            image_vec_6_2757 = &image_vec_6_2757_data;
        }
        /* image_vec_6_2758 */
        if (!image_vec_6_2758) {
            image_vec_6_2758 = &image_vec_6_2758_data;
        }
        /* image_vec_6_2759 */
        if (!image_vec_6_2759) {
            image_vec_6_2759 = &image_vec_6_2759_data;
        }
        /* image_vec_6_2760 */
        if (!image_vec_6_2760) {
            image_vec_6_2760 = &image_vec_6_2760_data;
        }
        /* image_vec_6_2761 */
        if (!image_vec_6_2761) {
            image_vec_6_2761 = &image_vec_6_2761_data;
        }
        /* image_vec_6_2762 */
        if (!image_vec_6_2762) {
            image_vec_6_2762 = &image_vec_6_2762_data;
        }
        /* image_vec_6_2763 */
        if (!image_vec_6_2763) {
            image_vec_6_2763 = &image_vec_6_2763_data;
        }
        /* image_vec_6_2764 */
        if (!image_vec_6_2764) {
            image_vec_6_2764 = &image_vec_6_2764_data;
        }
        /* image_vec_6_2765 */
        if (!image_vec_6_2765) {
            image_vec_6_2765 = &image_vec_6_2765_data;
        }
        /* image_vec_6_2766 */
        if (!image_vec_6_2766) {
            image_vec_6_2766 = &image_vec_6_2766_data;
        }
        /* image_vec_6_2767 */
        if (!image_vec_6_2767) {
            image_vec_6_2767 = &image_vec_6_2767_data;
        }
        /* image_vec_6_2768 */
        if (!image_vec_6_2768) {
            image_vec_6_2768 = &image_vec_6_2768_data;
        }
        /* image_vec_6_2769 */
        if (!image_vec_6_2769) {
            image_vec_6_2769 = &image_vec_6_2769_data;
        }
        /* image_vec_6_2770 */
        if (!image_vec_6_2770) {
            image_vec_6_2770 = &image_vec_6_2770_data;
        }
        /* image_vec_6_2771 */
        if (!image_vec_6_2771) {
            image_vec_6_2771 = &image_vec_6_2771_data;
        }
        /* image_vec_6_2772 */
        if (!image_vec_6_2772) {
            image_vec_6_2772 = &image_vec_6_2772_data;
        }
        /* image_vec_6_2773 */
        if (!image_vec_6_2773) {
            image_vec_6_2773 = &image_vec_6_2773_data;
        }
        /* image_vec_6_2774 */
        if (!image_vec_6_2774) {
            image_vec_6_2774 = &image_vec_6_2774_data;
        }
        /* image_vec_6_2775 */
        if (!image_vec_6_2775) {
            image_vec_6_2775 = &image_vec_6_2775_data;
        }
        /* image_vec_6_2776 */
        if (!image_vec_6_2776) {
            image_vec_6_2776 = &image_vec_6_2776_data;
        }
        /* image_vec_6_2777 */
        if (!image_vec_6_2777) {
            image_vec_6_2777 = &image_vec_6_2777_data;
        }
        /* image_vec_6_2778 */
        if (!image_vec_6_2778) {
            image_vec_6_2778 = &image_vec_6_2778_data;
        }
        /* image_vec_6_2779 */
        if (!image_vec_6_2779) {
            image_vec_6_2779 = &image_vec_6_2779_data;
        }
        /* image_vec_6_2780 */
        if (!image_vec_6_2780) {
            image_vec_6_2780 = &image_vec_6_2780_data;
        }
        /* image_vec_6_2781 */
        if (!image_vec_6_2781) {
            image_vec_6_2781 = &image_vec_6_2781_data;
        }
        /* image_vec_6_2782 */
        if (!image_vec_6_2782) {
            image_vec_6_2782 = &image_vec_6_2782_data;
        }
        /* image_vec_6_2783 */
        if (!image_vec_6_2783) {
            image_vec_6_2783 = &image_vec_6_2783_data;
        }
        /* image_vec_6_2784 */
        if (!image_vec_6_2784) {
            image_vec_6_2784 = &image_vec_6_2784_data;
        }
        /* image_vec_6_2785 */
        if (!image_vec_6_2785) {
            image_vec_6_2785 = &image_vec_6_2785_data;
        }
        /* image_vec_6_2786 */
        if (!image_vec_6_2786) {
            image_vec_6_2786 = &image_vec_6_2786_data;
        }
        /* image_vec_6_2787 */
        if (!image_vec_6_2787) {
            image_vec_6_2787 = &image_vec_6_2787_data;
        }
        /* image_vec_6_2788 */
        if (!image_vec_6_2788) {
            image_vec_6_2788 = &image_vec_6_2788_data;
        }
        /* image_vec_6_2789 */
        if (!image_vec_6_2789) {
            image_vec_6_2789 = &image_vec_6_2789_data;
        }
        /* image_vec_6_2790 */
        if (!image_vec_6_2790) {
            image_vec_6_2790 = &image_vec_6_2790_data;
        }
        /* image_vec_6_2791 */
        if (!image_vec_6_2791) {
            image_vec_6_2791 = &image_vec_6_2791_data;
        }
        /* image_vec_6_2792 */
        if (!image_vec_6_2792) {
            image_vec_6_2792 = &image_vec_6_2792_data;
        }
        /* image_vec_6_2793 */
        if (!image_vec_6_2793) {
            image_vec_6_2793 = &image_vec_6_2793_data;
        }
        /* image_vec_6_2794 */
        if (!image_vec_6_2794) {
            image_vec_6_2794 = &image_vec_6_2794_data;
        }
        /* image_vec_6_2795 */
        if (!image_vec_6_2795) {
            image_vec_6_2795 = &image_vec_6_2795_data;
        }
        /* image_vec_6_2796 */
        if (!image_vec_6_2796) {
            image_vec_6_2796 = &image_vec_6_2796_data;
        }
        /* image_vec_6_2797 */
        if (!image_vec_6_2797) {
            image_vec_6_2797 = &image_vec_6_2797_data;
        }
        /* image_vec_6_2798 */
        if (!image_vec_6_2798) {
            image_vec_6_2798 = &image_vec_6_2798_data;
        }
        /* image_vec_6_2799 */
        if (!image_vec_6_2799) {
            image_vec_6_2799 = &image_vec_6_2799_data;
        }
        /* image_vec_6_2800 */
        if (!image_vec_6_2800) {
            image_vec_6_2800 = &image_vec_6_2800_data;
        }
        /* image_vec_6_2801 */
        if (!image_vec_6_2801) {
            image_vec_6_2801 = &image_vec_6_2801_data;
        }
        /* image_vec_6_2802 */
        if (!image_vec_6_2802) {
            image_vec_6_2802 = &image_vec_6_2802_data;
        }
        /* image_vec_6_2803 */
        if (!image_vec_6_2803) {
            image_vec_6_2803 = &image_vec_6_2803_data;
        }
        /* image_vec_6_2804 */
        if (!image_vec_6_2804) {
            image_vec_6_2804 = &image_vec_6_2804_data;
        }
        /* image_vec_6_2805 */
        if (!image_vec_6_2805) {
            image_vec_6_2805 = &image_vec_6_2805_data;
        }
        /* image_vec_6_2806 */
        if (!image_vec_6_2806) {
            image_vec_6_2806 = &image_vec_6_2806_data;
        }
        /* image_vec_6_2807 */
        if (!image_vec_6_2807) {
            image_vec_6_2807 = &image_vec_6_2807_data;
        }
        /* image_vec_6_2808 */
        if (!image_vec_6_2808) {
            image_vec_6_2808 = &image_vec_6_2808_data;
        }
        /* image_vec_6_2809 */
        if (!image_vec_6_2809) {
            image_vec_6_2809 = &image_vec_6_2809_data;
        }
        /* image_vec_6_2810 */
        if (!image_vec_6_2810) {
            image_vec_6_2810 = &image_vec_6_2810_data;
        }
        /* image_vec_6_2811 */
        if (!image_vec_6_2811) {
            image_vec_6_2811 = &image_vec_6_2811_data;
        }
        /* image_vec_6_2812 */
        if (!image_vec_6_2812) {
            image_vec_6_2812 = &image_vec_6_2812_data;
        }
        /* image_vec_6_2813 */
        if (!image_vec_6_2813) {
            image_vec_6_2813 = &image_vec_6_2813_data;
        }
        /* image_vec_6_2814 */
        if (!image_vec_6_2814) {
            image_vec_6_2814 = &image_vec_6_2814_data;
        }
        /* image_vec_6_2815 */
        if (!image_vec_6_2815) {
            image_vec_6_2815 = &image_vec_6_2815_data;
        }
        /* image_vec_6_2816 */
        if (!image_vec_6_2816) {
            image_vec_6_2816 = &image_vec_6_2816_data;
        }
        /* image_vec_6_2817 */
        if (!image_vec_6_2817) {
            image_vec_6_2817 = &image_vec_6_2817_data;
        }
        /* image_vec_6_2818 */
        if (!image_vec_6_2818) {
            image_vec_6_2818 = &image_vec_6_2818_data;
        }
        /* image_vec_6_2819 */
        if (!image_vec_6_2819) {
            image_vec_6_2819 = &image_vec_6_2819_data;
        }
        /* image_vec_6_2820 */
        if (!image_vec_6_2820) {
            image_vec_6_2820 = &image_vec_6_2820_data;
        }
        /* image_vec_6_2821 */
        if (!image_vec_6_2821) {
            image_vec_6_2821 = &image_vec_6_2821_data;
        }
        /* image_vec_6_2822 */
        if (!image_vec_6_2822) {
            image_vec_6_2822 = &image_vec_6_2822_data;
        }
        /* image_vec_6_2823 */
        if (!image_vec_6_2823) {
            image_vec_6_2823 = &image_vec_6_2823_data;
        }
        /* image_vec_6_2824 */
        if (!image_vec_6_2824) {
            image_vec_6_2824 = &image_vec_6_2824_data;
        }
        /* image_vec_6_2825 */
        if (!image_vec_6_2825) {
            image_vec_6_2825 = &image_vec_6_2825_data;
        }
        /* image_vec_6_2826 */
        if (!image_vec_6_2826) {
            image_vec_6_2826 = &image_vec_6_2826_data;
        }
        /* image_vec_6_2827 */
        if (!image_vec_6_2827) {
            image_vec_6_2827 = &image_vec_6_2827_data;
        }
        /* image_vec_6_2828 */
        if (!image_vec_6_2828) {
            image_vec_6_2828 = &image_vec_6_2828_data;
        }
        /* image_vec_6_2829 */
        if (!image_vec_6_2829) {
            image_vec_6_2829 = &image_vec_6_2829_data;
        }
        /* image_vec_6_2830 */
        if (!image_vec_6_2830) {
            image_vec_6_2830 = &image_vec_6_2830_data;
        }
        /* image_vec_6_2831 */
        if (!image_vec_6_2831) {
            image_vec_6_2831 = &image_vec_6_2831_data;
        }
        /* image_vec_6_2832 */
        if (!image_vec_6_2832) {
            image_vec_6_2832 = &image_vec_6_2832_data;
        }
        /* image_vec_6_2833 */
        if (!image_vec_6_2833) {
            image_vec_6_2833 = &image_vec_6_2833_data;
        }
        /* image_vec_6_2834 */
        if (!image_vec_6_2834) {
            image_vec_6_2834 = &image_vec_6_2834_data;
        }
        /* image_vec_6_2835 */
        if (!image_vec_6_2835) {
            image_vec_6_2835 = &image_vec_6_2835_data;
        }
        /* image_vec_6_2836 */
        if (!image_vec_6_2836) {
            image_vec_6_2836 = &image_vec_6_2836_data;
        }
        /* image_vec_6_2837 */
        if (!image_vec_6_2837) {
            image_vec_6_2837 = &image_vec_6_2837_data;
        }
        /* image_vec_6_2838 */
        if (!image_vec_6_2838) {
            image_vec_6_2838 = &image_vec_6_2838_data;
        }
        /* image_vec_6_2839 */
        if (!image_vec_6_2839) {
            image_vec_6_2839 = &image_vec_6_2839_data;
        }
        /* image_vec_6_2840 */
        if (!image_vec_6_2840) {
            image_vec_6_2840 = &image_vec_6_2840_data;
        }
        /* image_vec_6_2841 */
        if (!image_vec_6_2841) {
            image_vec_6_2841 = &image_vec_6_2841_data;
        }
        /* image_vec_6_2842 */
        if (!image_vec_6_2842) {
            image_vec_6_2842 = &image_vec_6_2842_data;
        }
        /* image_vec_6_2843 */
        if (!image_vec_6_2843) {
            image_vec_6_2843 = &image_vec_6_2843_data;
        }
        /* image_vec_6_2844 */
        if (!image_vec_6_2844) {
            image_vec_6_2844 = &image_vec_6_2844_data;
        }
        /* image_vec_6_2845 */
        if (!image_vec_6_2845) {
            image_vec_6_2845 = &image_vec_6_2845_data;
        }
        /* image_vec_6_2846 */
        if (!image_vec_6_2846) {
            image_vec_6_2846 = &image_vec_6_2846_data;
        }
        /* image_vec_6_2847 */
        if (!image_vec_6_2847) {
            image_vec_6_2847 = &image_vec_6_2847_data;
        }
        /* image_vec_6_2848 */
        if (!image_vec_6_2848) {
            image_vec_6_2848 = &image_vec_6_2848_data;
        }
        /* image_vec_6_2849 */
        if (!image_vec_6_2849) {
            image_vec_6_2849 = &image_vec_6_2849_data;
        }
        /* image_vec_6_2850 */
        if (!image_vec_6_2850) {
            image_vec_6_2850 = &image_vec_6_2850_data;
        }
        /* image_vec_6_2851 */
        if (!image_vec_6_2851) {
            image_vec_6_2851 = &image_vec_6_2851_data;
        }
        /* image_vec_6_2852 */
        if (!image_vec_6_2852) {
            image_vec_6_2852 = &image_vec_6_2852_data;
        }
        /* image_vec_6_2853 */
        if (!image_vec_6_2853) {
            image_vec_6_2853 = &image_vec_6_2853_data;
        }
        /* image_vec_6_2854 */
        if (!image_vec_6_2854) {
            image_vec_6_2854 = &image_vec_6_2854_data;
        }
        /* image_vec_6_2855 */
        if (!image_vec_6_2855) {
            image_vec_6_2855 = &image_vec_6_2855_data;
        }
        /* image_vec_6_2856 */
        if (!image_vec_6_2856) {
            image_vec_6_2856 = &image_vec_6_2856_data;
        }
        /* image_vec_6_2857 */
        if (!image_vec_6_2857) {
            image_vec_6_2857 = &image_vec_6_2857_data;
        }
        /* image_vec_6_2858 */
        if (!image_vec_6_2858) {
            image_vec_6_2858 = &image_vec_6_2858_data;
        }
        /* image_vec_6_2859 */
        if (!image_vec_6_2859) {
            image_vec_6_2859 = &image_vec_6_2859_data;
        }
        /* image_vec_6_2860 */
        if (!image_vec_6_2860) {
            image_vec_6_2860 = &image_vec_6_2860_data;
        }
        /* image_vec_6_2861 */
        if (!image_vec_6_2861) {
            image_vec_6_2861 = &image_vec_6_2861_data;
        }
        /* image_vec_6_2862 */
        if (!image_vec_6_2862) {
            image_vec_6_2862 = &image_vec_6_2862_data;
        }
        /* image_vec_6_2863 */
        if (!image_vec_6_2863) {
            image_vec_6_2863 = &image_vec_6_2863_data;
        }
        /* image_vec_6_2864 */
        if (!image_vec_6_2864) {
            image_vec_6_2864 = &image_vec_6_2864_data;
        }
        /* image_vec_6_2865 */
        if (!image_vec_6_2865) {
            image_vec_6_2865 = &image_vec_6_2865_data;
        }
        /* image_vec_6_2866 */
        if (!image_vec_6_2866) {
            image_vec_6_2866 = &image_vec_6_2866_data;
        }
        /* image_vec_6_2867 */
        if (!image_vec_6_2867) {
            image_vec_6_2867 = &image_vec_6_2867_data;
        }
        /* image_vec_6_2868 */
        if (!image_vec_6_2868) {
            image_vec_6_2868 = &image_vec_6_2868_data;
        }
        /* image_vec_6_2869 */
        if (!image_vec_6_2869) {
            image_vec_6_2869 = &image_vec_6_2869_data;
        }
        /* image_vec_6_2870 */
        if (!image_vec_6_2870) {
            image_vec_6_2870 = &image_vec_6_2870_data;
        }
        /* image_vec_6_2871 */
        if (!image_vec_6_2871) {
            image_vec_6_2871 = &image_vec_6_2871_data;
        }
        /* image_vec_6_2872 */
        if (!image_vec_6_2872) {
            image_vec_6_2872 = &image_vec_6_2872_data;
        }
        /* image_vec_6_2873 */
        if (!image_vec_6_2873) {
            image_vec_6_2873 = &image_vec_6_2873_data;
        }
        /* image_vec_6_2874 */
        if (!image_vec_6_2874) {
            image_vec_6_2874 = &image_vec_6_2874_data;
        }
        /* image_vec_6_2875 */
        if (!image_vec_6_2875) {
            image_vec_6_2875 = &image_vec_6_2875_data;
        }
        /* image_vec_6_2876 */
        if (!image_vec_6_2876) {
            image_vec_6_2876 = &image_vec_6_2876_data;
        }
        /* image_vec_6_2877 */
        if (!image_vec_6_2877) {
            image_vec_6_2877 = &image_vec_6_2877_data;
        }
        /* image_vec_6_2878 */
        if (!image_vec_6_2878) {
            image_vec_6_2878 = &image_vec_6_2878_data;
        }
        /* image_vec_6_2879 */
        if (!image_vec_6_2879) {
            image_vec_6_2879 = &image_vec_6_2879_data;
        }
        /* image_vec_6_2880 */
        if (!image_vec_6_2880) {
            image_vec_6_2880 = &image_vec_6_2880_data;
        }
        /* image_vec_6_2881 */
        if (!image_vec_6_2881) {
            image_vec_6_2881 = &image_vec_6_2881_data;
        }
        /* image_vec_6_2882 */
        if (!image_vec_6_2882) {
            image_vec_6_2882 = &image_vec_6_2882_data;
        }
        /* image_vec_6_2883 */
        if (!image_vec_6_2883) {
            image_vec_6_2883 = &image_vec_6_2883_data;
        }
        /* image_vec_6_2884 */
        if (!image_vec_6_2884) {
            image_vec_6_2884 = &image_vec_6_2884_data;
        }
        /* image_vec_6_2885 */
        if (!image_vec_6_2885) {
            image_vec_6_2885 = &image_vec_6_2885_data;
        }
        /* image_vec_6_2886 */
        if (!image_vec_6_2886) {
            image_vec_6_2886 = &image_vec_6_2886_data;
        }
        /* image_vec_6_2887 */
        if (!image_vec_6_2887) {
            image_vec_6_2887 = &image_vec_6_2887_data;
        }
        /* image_vec_6_2888 */
        if (!image_vec_6_2888) {
            image_vec_6_2888 = &image_vec_6_2888_data;
        }
        /* image_vec_6_2889 */
        if (!image_vec_6_2889) {
            image_vec_6_2889 = &image_vec_6_2889_data;
        }
        /* image_vec_6_2890 */
        if (!image_vec_6_2890) {
            image_vec_6_2890 = &image_vec_6_2890_data;
        }
        /* image_vec_6_2891 */
        if (!image_vec_6_2891) {
            image_vec_6_2891 = &image_vec_6_2891_data;
        }
        /* image_vec_6_2892 */
        if (!image_vec_6_2892) {
            image_vec_6_2892 = &image_vec_6_2892_data;
        }
        /* image_vec_6_2893 */
        if (!image_vec_6_2893) {
            image_vec_6_2893 = &image_vec_6_2893_data;
        }
        /* image_vec_6_2894 */
        if (!image_vec_6_2894) {
            image_vec_6_2894 = &image_vec_6_2894_data;
        }
        /* image_vec_6_2895 */
        if (!image_vec_6_2895) {
            image_vec_6_2895 = &image_vec_6_2895_data;
        }
        /* image_vec_6_2896 */
        if (!image_vec_6_2896) {
            image_vec_6_2896 = &image_vec_6_2896_data;
        }
        /* image_vec_6_2897 */
        if (!image_vec_6_2897) {
            image_vec_6_2897 = &image_vec_6_2897_data;
        }
        /* image_vec_6_2898 */
        if (!image_vec_6_2898) {
            image_vec_6_2898 = &image_vec_6_2898_data;
        }
        /* image_vec_6_2899 */
        if (!image_vec_6_2899) {
            image_vec_6_2899 = &image_vec_6_2899_data;
        }
        /* image_vec_6_2900 */
        if (!image_vec_6_2900) {
            image_vec_6_2900 = &image_vec_6_2900_data;
        }
        /* image_vec_6_2901 */
        if (!image_vec_6_2901) {
            image_vec_6_2901 = &image_vec_6_2901_data;
        }
        /* image_vec_6_2902 */
        if (!image_vec_6_2902) {
            image_vec_6_2902 = &image_vec_6_2902_data;
        }
        /* image_vec_6_2903 */
        if (!image_vec_6_2903) {
            image_vec_6_2903 = &image_vec_6_2903_data;
        }
        /* image_vec_6_2904 */
        if (!image_vec_6_2904) {
            image_vec_6_2904 = &image_vec_6_2904_data;
        }
        /* image_vec_6_2905 */
        if (!image_vec_6_2905) {
            image_vec_6_2905 = &image_vec_6_2905_data;
        }
        /* image_vec_6_2906 */
        if (!image_vec_6_2906) {
            image_vec_6_2906 = &image_vec_6_2906_data;
        }
        /* image_vec_6_2907 */
        if (!image_vec_6_2907) {
            image_vec_6_2907 = &image_vec_6_2907_data;
        }
        /* image_vec_6_2908 */
        if (!image_vec_6_2908) {
            image_vec_6_2908 = &image_vec_6_2908_data;
        }
        /* image_vec_6_2909 */
        if (!image_vec_6_2909) {
            image_vec_6_2909 = &image_vec_6_2909_data;
        }
        /* image_vec_6_2910 */
        if (!image_vec_6_2910) {
            image_vec_6_2910 = &image_vec_6_2910_data;
        }
        /* image_vec_6_2911 */
        if (!image_vec_6_2911) {
            image_vec_6_2911 = &image_vec_6_2911_data;
        }
        /* image_vec_6_2912 */
        if (!image_vec_6_2912) {
            image_vec_6_2912 = &image_vec_6_2912_data;
        }
        /* image_vec_6_2913 */
        if (!image_vec_6_2913) {
            image_vec_6_2913 = &image_vec_6_2913_data;
        }
        /* image_vec_6_2914 */
        if (!image_vec_6_2914) {
            image_vec_6_2914 = &image_vec_6_2914_data;
        }
        /* image_vec_6_2915 */
        if (!image_vec_6_2915) {
            image_vec_6_2915 = &image_vec_6_2915_data;
        }
        /* image_vec_6_2916 */
        if (!image_vec_6_2916) {
            image_vec_6_2916 = &image_vec_6_2916_data;
        }
        /* image_vec_6_2917 */
        if (!image_vec_6_2917) {
            image_vec_6_2917 = &image_vec_6_2917_data;
        }
        /* image_vec_6_2918 */
        if (!image_vec_6_2918) {
            image_vec_6_2918 = &image_vec_6_2918_data;
        }
        /* image_vec_6_2919 */
        if (!image_vec_6_2919) {
            image_vec_6_2919 = &image_vec_6_2919_data;
        }
        /* image_vec_6_2920 */
        if (!image_vec_6_2920) {
            image_vec_6_2920 = &image_vec_6_2920_data;
        }
        /* image_vec_6_2921 */
        if (!image_vec_6_2921) {
            image_vec_6_2921 = &image_vec_6_2921_data;
        }
        /* image_vec_6_2922 */
        if (!image_vec_6_2922) {
            image_vec_6_2922 = &image_vec_6_2922_data;
        }
        /* image_vec_6_2923 */
        if (!image_vec_6_2923) {
            image_vec_6_2923 = &image_vec_6_2923_data;
        }
        /* image_vec_6_2924 */
        if (!image_vec_6_2924) {
            image_vec_6_2924 = &image_vec_6_2924_data;
        }
        /* image_vec_6_2925 */
        if (!image_vec_6_2925) {
            image_vec_6_2925 = &image_vec_6_2925_data;
        }
        /* image_vec_6_2926 */
        if (!image_vec_6_2926) {
            image_vec_6_2926 = &image_vec_6_2926_data;
        }
        /* image_vec_6_2927 */
        if (!image_vec_6_2927) {
            image_vec_6_2927 = &image_vec_6_2927_data;
        }
        /* image_vec_6_2928 */
        if (!image_vec_6_2928) {
            image_vec_6_2928 = &image_vec_6_2928_data;
        }
        /* image_vec_6_2929 */
        if (!image_vec_6_2929) {
            image_vec_6_2929 = &image_vec_6_2929_data;
        }
        /* image_vec_6_2930 */
        if (!image_vec_6_2930) {
            image_vec_6_2930 = &image_vec_6_2930_data;
        }
        /* image_vec_6_2931 */
        if (!image_vec_6_2931) {
            image_vec_6_2931 = &image_vec_6_2931_data;
        }
        /* image_vec_6_2932 */
        if (!image_vec_6_2932) {
            image_vec_6_2932 = &image_vec_6_2932_data;
        }
        /* image_vec_6_2933 */
        if (!image_vec_6_2933) {
            image_vec_6_2933 = &image_vec_6_2933_data;
        }
        /* image_vec_6_2934 */
        if (!image_vec_6_2934) {
            image_vec_6_2934 = &image_vec_6_2934_data;
        }
        /* image_vec_6_2935 */
        if (!image_vec_6_2935) {
            image_vec_6_2935 = &image_vec_6_2935_data;
        }
        /* image_vec_6_2936 */
        if (!image_vec_6_2936) {
            image_vec_6_2936 = &image_vec_6_2936_data;
        }
        /* image_vec_6_2937 */
        if (!image_vec_6_2937) {
            image_vec_6_2937 = &image_vec_6_2937_data;
        }
        /* image_vec_6_2938 */
        if (!image_vec_6_2938) {
            image_vec_6_2938 = &image_vec_6_2938_data;
        }
        /* image_vec_6_2939 */
        if (!image_vec_6_2939) {
            image_vec_6_2939 = &image_vec_6_2939_data;
        }
        /* image_vec_6_2940 */
        if (!image_vec_6_2940) {
            image_vec_6_2940 = &image_vec_6_2940_data;
        }
        /* image_vec_6_2943 */
        if (!image_vec_6_2943) {
            image_vec_6_2943 = &image_vec_6_2943_data;
        }
        /* image_vec_6_2944 */
        if (!image_vec_6_2944) {
            image_vec_6_2944 = &image_vec_6_2944_data;
        }
        /* image_vec_6_2947 */
        if (!image_vec_6_2947) {
            image_vec_6_2947 = &image_vec_6_2947_data;
        }
        /* image_vec_6_2948 */
        if (!image_vec_6_2948) {
            image_vec_6_2948 = &image_vec_6_2948_data;
        }
        /* image_vec_6_2951 */
        if (!image_vec_6_2951) {
            image_vec_6_2951 = &image_vec_6_2951_data;
        }
        /* image_vec_6_2952 */
        if (!image_vec_6_2952) {
            image_vec_6_2952 = &image_vec_6_2952_data;
        }
        /* image_vec_6_2955 */
        if (!image_vec_6_2955) {
            image_vec_6_2955 = &image_vec_6_2955_data;
        }
        /* image_vec_6_2956 */
        if (!image_vec_6_2956) {
            image_vec_6_2956 = &image_vec_6_2956_data;
        }
        /* image_vec_6_2959 */
        if (!image_vec_6_2959) {
            image_vec_6_2959 = &image_vec_6_2959_data;
        }
        /* image_vec_6_2960 */
        if (!image_vec_6_2960) {
            image_vec_6_2960 = &image_vec_6_2960_data;
        }
        /* image_vec_6_2963 */
        if (!image_vec_6_2963) {
            image_vec_6_2963 = &image_vec_6_2963_data;
        }
        /* image_vec_6_2964 */
        if (!image_vec_6_2964) {
            image_vec_6_2964 = &image_vec_6_2964_data;
        }
        /* image_vec_25_1105 */
        if (!image_vec_25_1105) {
            image_vec_25_1105 = &image_vec_25_1105_data;
        }
        /* image_vec_34_869 */
        if (!image_vec_34_869) {
            image_vec_34_869 = &image_vec_34_869_data;
        }
        /* image_vec_34_872 */
        if (!image_vec_34_872) {
            image_vec_34_872 = &image_vec_34_872_data;
        }
        /* image_vec_23_372 */
        if (!image_vec_23_372) {
            image_vec_23_372 = &image_vec_23_372_data;
        }
        /* image_vec_42_877 */
        if (!image_vec_42_877) {
            image_vec_42_877 = &image_vec_42_877_data;
        }
        /* image_vec_12_212 */
        if (!image_vec_12_212) {
            image_vec_12_212 = &image_vec_12_212_data;
        }
        /* image_vec_42_862 */
        if (!image_vec_42_862) {
            image_vec_42_862 = &image_vec_42_862_data;
        }
        /* image_vec_7_1590 */
        if (!image_vec_7_1590) {
            image_vec_7_1590 = &image_vec_7_1590_data;
        }
        /* image_vec_7_1412 */
        if (!image_vec_7_1412) {
            image_vec_7_1412 = &image_vec_7_1412_data;
        }
        /* image_vec_1_241 */
        if (!image_vec_1_241) {
            image_vec_1_241 = &image_vec_1_241_data;
        }
        /* image_vec_7_1491 */
        if (!image_vec_7_1491) {
            image_vec_7_1491 = &image_vec_7_1491_data;
        }
        /* image_vec_7_1493 */
        if (!image_vec_7_1493) {
            image_vec_7_1493 = &image_vec_7_1493_data;
        }
        /* image_vec_1_790 */
        if (!image_vec_1_790) {
            image_vec_1_790 = &image_vec_1_790_data;
        }
        /* image_vec_1_882 */
        if (!image_vec_1_882) {
            image_vec_1_882 = &image_vec_1_882_data;
        }
        /* image_vec_25_1004 */
        if (!image_vec_25_1004) {
            image_vec_25_1004 = &image_vec_25_1004_data;
        }
        /* image_vec_7_1415 */
        if (!image_vec_7_1415) {
            image_vec_7_1415 = &image_vec_7_1415_data;
        }
        /* image_vec_42_2416 */
        if (!image_vec_42_2416) {
            image_vec_42_2416 = &image_vec_42_2416_data;
        }
        /* image_vec_42_2418 */
        if (!image_vec_42_2418) {
            image_vec_42_2418 = &image_vec_42_2418_data;
        }
        /* image_vec_23_214 */
        if (!image_vec_23_214) {
            image_vec_23_214 = &image_vec_23_214_data;
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

        lv_style_set_border_width(&style_screen_base_global, 0);
        lv_style_set_radius(&style_screen_base_global, 0);
        lv_style_set_shadow_width(&style_screen_base_global, 0);
        lv_style_set_shadow_opa(&style_screen_base_global, 0);

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
    lv_xml_register_image(NULL, "image_vec_34_869", image_vec_34_869);
    lv_xml_register_image(NULL, "image_vec_34_872", image_vec_34_872);
    lv_xml_register_image(NULL, "image_vec_23_372", image_vec_23_372);
    lv_xml_register_image(NULL, "image_vec_42_877", image_vec_42_877);
    lv_xml_register_image(NULL, "image_vec_12_212", image_vec_12_212);
    lv_xml_register_image(NULL, "image_vec_42_862", image_vec_42_862);
    lv_xml_register_image(NULL, "image_vec_7_1590", image_vec_7_1590);
    lv_xml_register_image(NULL, "image_vec_7_1412", image_vec_7_1412);
    lv_xml_register_image(NULL, "image_vec_1_241", image_vec_1_241);
    lv_xml_register_image(NULL, "image_vec_7_1491", image_vec_7_1491);
    lv_xml_register_image(NULL, "image_vec_7_1493", image_vec_7_1493);
    lv_xml_register_image(NULL, "image_vec_1_790", image_vec_1_790);
    lv_xml_register_image(NULL, "image_vec_1_882", image_vec_1_882);
    lv_xml_register_image(NULL, "image_vec_25_1004", image_vec_25_1004);
    lv_xml_register_image(NULL, "image_vec_7_1415", image_vec_7_1415);
    lv_xml_register_image(NULL, "image_vec_42_2416", image_vec_42_2416);
    lv_xml_register_image(NULL, "image_vec_42_2418", image_vec_42_2418);
    lv_xml_register_image(NULL, "image_vec_23_214", image_vec_23_214);
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