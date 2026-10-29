#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "esp_err.h"

/*
 * Members and front history, kept in the "storage" flash partition (/data).
 * Written by the web dashboard (web.c), read by the UI (status of the namecard).
 * All functions are safe to call from any task.
 */

#define STORE_FRONT_MAX     4           /* fronters per switch */
#define STORE_NO_MEMBER     0xFFFF

/* One switch: who fronted from `time` on. 12 bytes, also the file and upload format. */
typedef struct __attribute__((packed)) {
    uint32_t time;                      /* unix time, seconds */
    uint16_t members[STORE_FRONT_MAX];  /* indexes into the member list, STORE_NO_MEMBER = empty */
} store_switch_t;

#define STORE_SWITCHES_FILE "/data/switches.bin"

/** Mount the storage partition and load members and the current front. */
void store_init(void);

/*
 * Members, as JSON (format: see members_from_json() in store.c and the dashboard):
 * {"system": "...", "members": [{"id","name","card","pronouns","color":"RRGGBB"}]}
 */
esp_err_t store_set_members_json(const char *json);
/** {"system","members":[...],"front":[i..],"front_since":t,"switches":n}; free() the result. */
char *store_get_state_json(void);

/* Front history upload: begin, write raw store_switch_t records (any chunking), end. */
esp_err_t store_switches_begin(void);
esp_err_t store_switches_write(const void *data, size_t len);
esp_err_t store_switches_end(bool ok);

/** Record a new switch now. `members` may be empty (nobody fronting). */
esp_err_t store_add_switch(const uint16_t *members, int count);

/**
 * Delete member `index`, take them out of the front history (later members'
 * indexes move down by one) and delete their card picture.
 * Adding and editing members goes through store_set_members_json().
 */
esp_err_t store_delete_member(int index);

/*
 * Namecard pictures, drawn by the dashboard (see dashboard/index.html, renderCard):
 * header {"PC1\0", u16 w, h, patch_x, patch_y, patch_w, patch_h}, then the text as
 * 4-bit alpha (2 pixels per byte, left pixel in the high nibble, rows padded to
 * a whole byte), then an optional colour patch for emoji: RGB565 pixels followed
 * by 8-bit alpha (LVGL's RGB565A8).
 */
typedef struct __attribute__((packed)) {
    char magic[4];                      /* "PC1" */
    uint16_t w, h;
    uint16_t patch_x, patch_y, patch_w, patch_h;
} store_card_header_t;

/** Card upload for member `id` (PluralKit id): begin, write chunks, end. */
esp_err_t store_card_begin(const char *id);
esp_err_t store_card_write(const void *data, size_t len);
esp_err_t store_card_end(bool ok);

/**
 * Read the current fronter's card picture. Returns a malloc'd buffer holding
 * the header followed by the data (free() it), or NULL if there is none.
 */
void *store_load_front_card(size_t *size);

/**
 * For the namecard: the current fronter's card text and colour (0xRRGGBB).
 * With nobody fronting it gives the system name and returns false.
 * *changed is true once after each change of front, members or cards, so the
 * UI can poll this cheaply.
 */
bool store_get_front_card(char *text, size_t text_size, uint32_t *color, bool *changed);
