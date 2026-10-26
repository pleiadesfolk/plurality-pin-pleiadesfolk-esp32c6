/**
 * @file building_blocks_track_stop_gen.h
 */

#ifndef LVGL_PRO_BUILDING_BLOCKS_TRACK_STOP_GEN_H
#define LVGL_PRO_BUILDING_BLOCKS_TRACK_STOP_GEN_H

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

lv_obj_t * building_blocks_track_stop_create(lv_obj_t * parent, bool show_stops, bool show_icon, bool show_value_indicator);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LVGL_PRO_BUILDING_BLOCKS_TRACK_STOP_GEN_H*/