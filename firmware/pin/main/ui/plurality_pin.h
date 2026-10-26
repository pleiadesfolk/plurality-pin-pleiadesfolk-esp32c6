/**
 * @file plurality_pin.h
 *
 * Firmware stand-in for the LVGL Editor's plurality_pin.h / plurality_pin_gen.h.
 *
 * The Editor's own header pulls in every screen, component, font and image of
 * the project. The firmware only compiles the generated files it uses (see
 * tools/sync_ui.sh), so this header declares just what those files need.
 * Keep the names identical to the Editor's so the generated code compiles as is.
 */

#ifndef PLURALITY_PIN_H
#define PLURALITY_PIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

/* Targets (copied from plurality_pin_gen.h) */
#define PLURALITY_PIN_TARGET_UNDEFINED  (0 << 1)
#define PLURALITY_PIN_TARGET_TARGET1    (1 << 1)
#define PLURALITY_PIN_TARGET_ALL        0x0FFFFFFF

#ifndef PLURALITY_PIN_COMPILE_TARGET
#define PLURALITY_PIN_COMPILE_TARGET PLURALITY_PIN_TARGET_ALL
#endif

#define PLURALITY_PIN_CHECK_COMPILE_TARGET(target) (PLURALITY_PIN_COMPILE_TARGET & (target) ? 1 : 0)

bool plurality_pin_check_target(uint32_t target);

/* Constants (copied from plurality_pin_gen.h) */
#define CONST_BASELIB_ACCENT_GLOBAL lv_color_hex(0x70609C)
#define CONST_BASELIB_UNIT_SM_GLOBAL 4

/* Global styles */
extern lv_style_t style_screen_base_global;

/* Fonts used by the screens the firmware compiles */
extern lv_font_t * font_ibm_plex_mono_regular_26;
extern lv_font_t * font_ibm_plex_mono_semibold_150;

/* Components */
#include "components/base/container/container_gen.h"
#include "components/base/column/column_gen.h"
#include "components/base/row/row_gen.h"
#include "components/base/label/label_gen.h"

/* Screens */
#include "screens/watch_gen.h"

/** Create fonts and global styles. Call once after lv_init(). */
void plurality_pin_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*PLURALITY_PIN_H*/
