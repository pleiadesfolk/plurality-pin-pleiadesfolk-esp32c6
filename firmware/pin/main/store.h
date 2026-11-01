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
/* The "nobody fronting" card's id for its pictures: PluralKit ids are letters
 * only, so it can't clash with a member's */
#define STORE_NOBODY_ID     "nobody0"

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
 * {"system": "...", "members": [{"id","name","card","color":"RRGGBB","pk_color":"RRGGBB",...}],
 *  "nobody": {...}}  - "nobody": what shows while nobody fronts, same fields as a
 *  member (optional: without it, the one already saved is kept)
 */
esp_err_t store_set_members_json(const char *json);
/** Receives JSON text in pieces; returns false to stop. */
typedef bool (*store_emit_t)(const char *text, size_t len, void *ctx);
/** Send {"system","members":[...],"front":[i..],"front_since":t,"switches":n,"now":t<extra>}
 *  in pieces (`extra`: more fields, starting with a comma, or ""). */
bool store_send_state(store_emit_t emit, void *ctx, const char *extra);
/** Which members have photos, for the dashboard: {"free_slots", "sd_card",
 *  "photos": {id: "fs"}} (f = "image" photo, s = "image with name"; capital
 *  = in a fast flash slot, small = on the SD card). free() it. */
char *store_photos_json(void);

/**
 * Make the current front `list` (PluralKit's, switched in at `time`): switches
 * newer than that are dropped (they never reached PluralKit), and the switch
 * is added unless the pin's newest one already is it (same members, within a
 * minute). `dropped` / `added` say what was done.
 */
esp_err_t store_match_front(uint32_t time, const uint16_t *list, int count, int *dropped, bool *added);

/* Front history upload: begin, write raw store_switch_t records (any chunking), end. */
esp_err_t store_switches_begin(void);
esp_err_t store_switches_write(const void *data, size_t len);
esp_err_t store_switches_end(bool ok);

/** Record a new switch now. `members` may be empty (nobody fronting). */
esp_err_t store_add_switch(const uint16_t *members, int count);
/** Record a switch that happened at `time` (unix seconds), e.g. one made in PluralKit. */
esp_err_t store_add_switch_at(uint32_t time, const uint16_t *members, int count);
/**
 * Show a switch without saving it yet (the side button and swipes): the
 * screen and store_front_* see it, the file doesn't. store_save_preview()
 * saves it; any other switch, or a new front history, drops it.
 */
esp_err_t store_preview_switch(const uint16_t *members, int count);
/** Save the switch from store_preview_switch(), unless it's back to who was
 *  fronting before. True if a switch was saved. */
bool store_save_preview(void);
/** When the current front started (unix seconds); 0 if there's no history. */
uint32_t store_front_time(void);
/** True if exactly these members (in any order) are fronting now. */
bool store_front_is(const uint16_t *members, int count);
/** Index of the member with PluralKit id `id`; -1 if the pin doesn't have them. */
int store_member_index(const char *id);

/**
 * The member the BOOT button switches to next: the one after the current
 * fronter among members marked "Quick Switch" (JSON "button") on the dashboard (or all members if
 * none are), ordered by PluralKit message count (most first), then name.
 * direction < 0 steps backwards instead.
 * Returns its index and copies its name, or -1.
 */
int store_step_button_member(int direction, char *name, size_t name_size);

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

/* How a member is shown on the fronter screen (member JSON "mode") */
typedef enum {
    STORE_MODE_CARD,                    /* "card": namecard */
    STORE_MODE_IMAGE,                   /* "image": photo */
    STORE_MODE_IMAGE_TEXT,              /* "image_text": photo in a circle + name */
} store_mode_t;

/* A member's pictures, all drawn by the dashboard */
typedef enum {
    STORE_PICTURE_CARD,                 /* namecard text (store_card_header_t format) */
    STORE_PICTURE_LABEL,                /* name text for "image with name" (same format) */
    STORE_PICTURE_FULL,                 /* photo for "image": LVGL .bin, RGB565, fitted within 456x280 */
    STORE_PICTURE_SIDE,                 /* visible part of the circle photo: LVGL .bin, RGB565, 228x280 */
} store_picture_t;

/** Path of member `id`'s picture of `kind`; false if there's none. */
bool store_picture_file(const char *id, store_picture_t kind, char *path, size_t size);

/** Picture upload for member `id` (PluralKit id): begin, write chunks, end. */
esp_err_t store_picture_begin(const char *id, store_picture_t kind);
esp_err_t store_picture_write(const void *data, size_t len);
esp_err_t store_picture_end(bool ok);

/** Path of the current fronter's picture of `kind`; false if there's none. */
bool store_front_picture_file(store_picture_t kind, char *path, size_t size);

/** The current fronter's member id; false if nobody fronts. */
bool store_front_id(char *id, size_t size);

/** LVGL file path ("A:/...") of the current fronter's FULL or SIDE photo when it's
 *  in a file (photos normally live in photos.c's slots); false if there's none. */
bool store_front_image_src(store_picture_t kind, char *src, size_t size);

/** The current fronter's display mode (namecard when nobody fronts). */
store_mode_t store_front_mode(void);

/** The current fronter's background gradient text ("dir|RRGGBB,...|animate", may be ""). */
void store_front_grad(char *text, size_t size);

/** The current fronter's "image with name" text (the system name when nobody fronts). */
void store_front_label(char *text, size_t size);

/**
 * For the namecard: the current fronter's card text and colour (0xRRGGBB).
 * With nobody fronting it gives the system name and returns false.
 * *changed is true once after each change of front, members or cards, so the
 * UI can poll this cheaply.
 */
bool store_get_front_card(char *text, size_t text_size, uint32_t *color, bool *changed);
