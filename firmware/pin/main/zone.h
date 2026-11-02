#pragma once

#include "esp_err.h"

/**
 * The pin's time zone: PluralKit's (the system's time zone setting, read by
 * pksync.c), or one picked on the dashboard. Kept in NVS, so the clock is
 * right from the start. Until either is known: UTC.
 */

/** At start-up, after nvs_flash_init(): applies the saved time zone. */
void zone_init(void);

/** PluralKit's time zone (IANA name, e.g. "Asia/Hong_Kong"); any task. */
void zone_from_pluralkit(const char *name);

/** Pick a time zone by IANA name; "" = follow PluralKit. ESP_ERR_NOT_FOUND if unknown. */
esp_err_t zone_set(const char *name);

/**
 * For the dashboard (malloc'd, caller frees): {"picked" ("" = following
 * PluralKit), "pluralkit" (its last known zone, "" = not read yet), "zone"
 * (the one in use), "posix"}.
 */
char *zone_json(void);
