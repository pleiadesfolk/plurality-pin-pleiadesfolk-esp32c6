/**
 * @file pull_down_menu_connected_gen.h
 */

#ifndef LVGL_PRO_PULL_DOWN_MENU_CONNECTED_GEN_H
#define LVGL_PRO_PULL_DOWN_MENU_CONNECTED_GEN_H

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

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/



lv_obj_t * pull_down_menu_connected_create(void);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LVGL_PRO_PULL_DOWN_MENU_CONNECTED_GEN_H*/