#pragma once

#include "lvgl.h"

/**
 * Map the "assets" flash partition into memory. Call before plurality_pin_init().
 * The partition holds assets/images.bin, made by tools/sync_ui.py.
 */
void assets_init(void);

/** Image number `index` (see assets/index.txt), ready for lv_image_set_src(). */
const void *assets_image(uint32_t index);
