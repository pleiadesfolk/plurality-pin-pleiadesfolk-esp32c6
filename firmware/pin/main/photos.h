#pragma once

#include <stdbool.h>
#include <stddef.h>
#include "esp_err.h"
#include "esp_partition.h"

/*
 * Member photos in the "photos" flash partition, so they can be drawn straight
 * from flash (memory-mapped) instead of being read from the SD card while
 * drawing, which takes 0.5-5 s per screen. Fixed slots, one per member that
 * uses an image mode; each slot holds both photos as LVGL .bin images.
 */

#define PHOTOS_SLOTS 11

typedef enum { PHOTO_FULL, PHOTO_SIDE } photo_kind_t;

void photos_init(void);

/* Upload: begin (finds or takes a slot; false when none is free), write, end */
esp_err_t photos_begin(const char *id, photo_kind_t kind);
esp_err_t photos_write(const void *data, size_t len);
esp_err_t photos_end(bool ok);

/** Whether member `id` has this photo in a slot. */
bool photos_has(const char *id, photo_kind_t kind);

/**
 * Map member `id`'s photo into memory: returns the LVGL .bin data (12-byte
 * header + pixels) and its length, or NULL. Unmap with photos_unmap(handle).
 */
const void *photos_map(const char *id, photo_kind_t kind, size_t *len, esp_partition_mmap_handle_t *handle);
void photos_unmap(esp_partition_mmap_handle_t handle);

/** Free member `id`'s slot. */
void photos_delete(const char *id);
