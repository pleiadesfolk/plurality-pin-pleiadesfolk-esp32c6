/**
 * @file plurality_pin.c
 *
 * Firmware stand-in for the Editor's plurality_pin_gen.c: creates the fonts and
 * global styles the generated screens refer to.
 *
 * Fonts: the Editor loads TTF files from disk with lv_tiny_ttf_create_file().
 * The firmware embeds the same TTF files in flash (main/fonts, see
 * main/CMakeLists.txt) and uses lv_tiny_ttf_create_data() instead, so no
 * filesystem is needed.
 */

#include "plurality_pin.h"

/* Embedded font files (symbols created by EMBED_FILES in main/CMakeLists.txt) */
extern const uint8_t ibm_plex_mono_regular_ttf_start[]   asm("_binary_IBMPlexMono_Regular_ttf_start");
extern const uint8_t ibm_plex_mono_regular_ttf_end[]     asm("_binary_IBMPlexMono_Regular_ttf_end");
extern const uint8_t ibm_plex_mono_semibold_ttf_start[]  asm("_binary_IBMPlexMono_SemiBold_ttf_start");
extern const uint8_t ibm_plex_mono_semibold_ttf_end[]    asm("_binary_IBMPlexMono_SemiBold_ttf_end");

lv_font_t * font_ibm_plex_mono_regular_26;
lv_font_t * font_ibm_plex_mono_semibold_150;

lv_style_t style_screen_base_global;

static lv_font_t * ttf(const uint8_t * start, const uint8_t * end, int32_t size)
{
    lv_font_t * font = lv_tiny_ttf_create_data(start, end - start, size);
    LV_ASSERT_NULL(font);
    return font;
}

void plurality_pin_init(void)
{
    font_ibm_plex_mono_regular_26 = ttf(ibm_plex_mono_regular_ttf_start, ibm_plex_mono_regular_ttf_end, 26);
    font_ibm_plex_mono_semibold_150 = ttf(ibm_plex_mono_semibold_ttf_start, ibm_plex_mono_semibold_ttf_end, 150);

    /* Same as the Editor's style_screen_base_global */
    lv_style_init(&style_screen_base_global);
    lv_style_set_border_width(&style_screen_base_global, 0);
    lv_style_set_radius(&style_screen_base_global, 0);
    lv_style_set_shadow_width(&style_screen_base_global, 0);
    lv_style_set_shadow_opa(&style_screen_base_global, 0);
}

bool plurality_pin_check_target(uint32_t target)
{
    return (target & PLURALITY_PIN_TARGET_ALL) != 0;
}
