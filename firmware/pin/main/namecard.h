#pragma once

#include "lvgl.h"

/** Take over the namecard screen's text and background (call when it's shown). */
void namecard_attach(lv_obj_t *namecard_screen);

/** Check for a new front, member list or card picture; call regularly from the LVGL task. */
void namecard_poll(void);
