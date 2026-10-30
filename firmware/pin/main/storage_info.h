#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef struct {
    bool present;                       /* SD card: inserted and readable */
    uint64_t total;                     /* bytes */
    uint64_t used;
} storage_usage_t;

/**
 * Start checking storage in the background: mounts a microSD card when one is
 * inserted (at /sdcard) and measures it and the pin's own storage (/data)
 * every 30 s. Call after the display (the SD card shares its SPI bus) and
 * store_init().
 */
void storage_info_start(void);

/** True while an SD card is mounted at /sdcard. */
bool storage_info_sd_ready(void);

/** Latest measurements; safe from any task. */
void storage_info_get(storage_usage_t *sd, storage_usage_t *pin);
