#pragma once

#include "lvgl.h"
#include "store.h"

/** Take over a fronter screen (namecard or one of the image screens) when it's shown. */
void fronter_attach(lv_obj_t *screen, store_mode_t mode);

/** Check for a new front, member list or pictures; call regularly from the LVGL task. */
void fronter_poll(void);
