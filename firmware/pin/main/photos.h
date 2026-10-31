#pragma once

#include <stdbool.h>
#include <stddef.h>
#include "esp_err.h"
#include "esp_partition.h"

/*
 * Member photos in the "photos" flash partition, so they can be drawn straight
 * from flash (memory-mapped) instead of being read from the SD card while
 * drawing, which takes 0.5-5 s per screen. Fixed slots for the members marked
 * "fast" on the dashboard; each slot holds both photos as LVGL .bin images.
 * Everyone else's photos are on the SD card and get copied to a staging area
 * when needed (below).
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
/** Remove one of member `id`'s photos from its slot (the slot is freed once empty). */
void photos_delete_kind(const char *id, photo_kind_t kind);
/** How many slots are free. */
int photos_free_slots(void);

/*
 * Staging (photos on the SD card): photos_stage() asks a background task to
 * copy member `id`'s photo file into the staging area; photos_stage_count()
 * goes up each time a copy finishes. Then photos_map_staged() maps it like a
 * slot. Only one photo is staged at a time; photos_unstage() forgets member
 * `id`'s when its file changes.
 */
void photos_stage(const char *id, photo_kind_t kind, const char *path);
uint32_t photos_stage_count(void);
bool photos_staged(const char *id, photo_kind_t kind);
const void *photos_map_staged(const char *id, photo_kind_t kind, size_t *len, esp_partition_mmap_handle_t *handle);
void photos_unstage(const char *id);
