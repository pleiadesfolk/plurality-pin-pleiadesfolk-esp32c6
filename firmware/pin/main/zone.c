/*
 * Time zone (see zone.h). NVS ("pin"): "tz_pick" the zone picked on the
 * dashboard ("" or missing = follow PluralKit), "tz_pk" PluralKit's last
 * known zone. Turned into POSIX TZ strings with timezones.c.
 *
 * The C library's time zone (TZ) is changed in the LVGL task, which draws the
 * clocks; the names are guarded by a lock as they come from other tasks.
 */

#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "esp_log.h"
#include "nvs.h"
#include "cJSON.h"
#include "lvgl.h"
#include "timezones.h"
#include "zone.h"

static const char *TAG = "zone";

#define NVS_NAMESPACE   "pin"
#define DEFAULT_ZONE    "UTC"           /* until PluralKit's is known, unless one is picked */
#define ZONE_NAME_MAX        48

static SemaphoreHandle_t lock;
static char picked[ZONE_NAME_MAX];           /* "" = follow PluralKit */
static char pluralkit[ZONE_NAME_MAX];        /* "" = not read yet */
static char in_use[ZONE_NAME_MAX];

static void load_str(nvs_handle_t nvs, const char *key, char *dst, size_t size)
{
    if (nvs_get_str(nvs, key, dst, &size) != ESP_OK) {
        dst[0] = 0;
    }
}

static void save_str(const char *key, const char *value)
{
    nvs_handle_t nvs;
    if (nvs_open(NVS_NAMESPACE, NVS_READWRITE, &nvs) == ESP_OK) {
        nvs_set_str(nvs, key, value);
        nvs_commit(nvs);
        nvs_close(nvs);
    }
}

static void set_tz(const char *posix)
{
    setenv("TZ", posix, 1);
    tzset();
}

static void apply_async(void *posix)
{
    set_tz(posix);
    free(posix);
}

/* Use whichever zone is wanted now, if it changed (caller holds the lock) */
static void update(void)
{
    const char *name = picked[0] ? picked : pluralkit[0] ? pluralkit : DEFAULT_ZONE;
    const char *posix = timezones_posix(name);
    if (!posix || strcmp(name, in_use) == 0) {
        return;
    }
    strlcpy(in_use, name, sizeof(in_use));
    ESP_LOGI(TAG, "%s (%s)%s", name, posix, picked[0] ? ", picked on the dashboard" : "");
    char *copy = strdup(posix);
    if (copy && lv_async_call(apply_async, copy) != LV_RESULT_OK) {
        free(copy);
    }
}

void zone_init(void)
{
    lock = xSemaphoreCreateMutex();
    nvs_handle_t nvs;
    if (nvs_open(NVS_NAMESPACE, NVS_READONLY, &nvs) == ESP_OK) {
        load_str(nvs, "tz_pick", picked, sizeof(picked));
        load_str(nvs, "tz_pk", pluralkit, sizeof(pluralkit));
        nvs_close(nvs);
    }
    const char *name = picked[0] ? picked : pluralkit[0] ? pluralkit : DEFAULT_ZONE;
    if (!timezones_posix(name)) {
        name = DEFAULT_ZONE;            /* e.g. a zone dropped from a newer table */
    }
    strlcpy(in_use, name, sizeof(in_use));
    set_tz(timezones_posix(name));
}

void zone_from_pluralkit(const char *name)
{
    if (!timezones_posix(name)) {
        ESP_LOGW(TAG, "PluralKit's time zone \"%s\" isn't known here", name);
        return;
    }
    xSemaphoreTake(lock, portMAX_DELAY);
    if (strcmp(name, pluralkit) != 0) {
        strlcpy(pluralkit, name, sizeof(pluralkit));
        save_str("tz_pk", pluralkit);
        ESP_LOGI(TAG, "PluralKit's time zone: %s", name);
    }
    update();
    xSemaphoreGive(lock);
}

esp_err_t zone_set(const char *name)
{
    if (name[0] && !timezones_posix(name)) {
        return ESP_ERR_NOT_FOUND;
    }
    xSemaphoreTake(lock, portMAX_DELAY);
    strlcpy(picked, name, sizeof(picked));
    save_str("tz_pick", picked);
    update();
    xSemaphoreGive(lock);
    return ESP_OK;
}

char *zone_json(void)
{
    cJSON *root = cJSON_CreateObject();
    xSemaphoreTake(lock, portMAX_DELAY);
    cJSON_AddStringToObject(root, "picked", picked);
    cJSON_AddStringToObject(root, "pluralkit", pluralkit);
    cJSON_AddStringToObject(root, "zone", in_use);
    cJSON_AddStringToObject(root, "posix", timezones_posix(in_use) ?: "");
    xSemaphoreGive(lock);
    char *text = cJSON_PrintUnformatted(root);
    cJSON_Delete(root);
    return text;
}
