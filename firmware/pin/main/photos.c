/*
 * Photo slots in the "photos" partition (see photos.h).
 *
 * Layout: a 4 KB table at the start, then PHOTOS_SLOTS slots of SLOT_SIZE.
 * Each slot: the "image" photo (280x280 RGB565, 157 KB) in the first
 * FULL_SIZE bytes, then the "image with name" circle (228x280 RGB565A8,
 * 192 KB). Flash must be erased before it's written, so an upload erases its
 * half of the slot first.
 *
 * Only the web server writes (one upload at a time); the table is guarded by
 * a mutex because the LVGL task reads it.
 */

#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "esp_log.h"
#include "photos.h"

static const char *TAG = "photos";

#define TABLE_SIZE  0x1000
#define FULL_SIZE   0x28000             /* 160 KB >= 12 + 280*280*2 */
#define SIDE_SIZE   0x30000             /* 192 KB >= 12 + 228*280*3 */
#define SLOT_SIZE   (FULL_SIZE + SIDE_SIZE)

typedef struct {
    char id[12];                        /* "" = free */
    uint32_t len[2];                    /* bytes stored per photo_kind_t; 0 = none */
} slot_t;

typedef struct {
    char magic[4];                      /* "PPH1" */
    slot_t slots[PHOTOS_SLOTS];
} table_t;

static const esp_partition_t *part;
static table_t table;
static SemaphoreHandle_t lock;

/* current upload */
static int up_slot = -1;
static photo_kind_t up_kind;
static size_t up_len;

static size_t region_offset(int slot, photo_kind_t kind)
{
    return TABLE_SIZE + (size_t)slot * SLOT_SIZE + (kind == PHOTO_SIDE ? FULL_SIZE : 0);
}

static size_t region_size(photo_kind_t kind)
{
    return kind == PHOTO_SIDE ? SIDE_SIZE : FULL_SIZE;
}

static esp_err_t save_table(void)
{
    esp_err_t err = esp_partition_erase_range(part, 0, TABLE_SIZE);
    return err == ESP_OK ? esp_partition_write(part, 0, &table, sizeof(table)) : err;
}

static int find_slot(const char *id)
{
    for (int i = 0; i < PHOTOS_SLOTS; i++) {
        if (strcmp(table.slots[i].id, id) == 0) {
            return i;
        }
    }
    return -1;
}

void photos_init(void)
{
    lock = xSemaphoreCreateMutex();
    part = esp_partition_find_first(ESP_PARTITION_TYPE_DATA, ESP_PARTITION_SUBTYPE_ANY, "photos");
    if (!part) {
        ESP_LOGW(TAG, "no photos partition; photos stay on the SD card");
        return;
    }
    esp_partition_read(part, 0, &table, sizeof(table));
    if (memcmp(table.magic, "PPH1", 4) != 0) {
        memset(&table, 0, sizeof(table));       /* first start: empty table */
        memcpy(table.magic, "PPH1", 4);
        save_table();
    }
    int used = 0;
    for (int i = 0; i < PHOTOS_SLOTS; i++) {
        used += table.slots[i].id[0] != 0;
    }
    ESP_LOGI(TAG, "%d of %d photo slots used", used, PHOTOS_SLOTS);
}

esp_err_t photos_begin(const char *id, photo_kind_t kind)
{
    if (!part || strlen(id) >= sizeof(table.slots[0].id)) {
        return ESP_ERR_NOT_SUPPORTED;
    }
    xSemaphoreTake(lock, portMAX_DELAY);
    int slot = find_slot(id);
    if (slot < 0) {
        slot = find_slot("");           /* a free slot */
        if (slot >= 0) {
            strlcpy(table.slots[slot].id, id, sizeof(table.slots[slot].id));
            table.slots[slot].len[0] = table.slots[slot].len[1] = 0;
        }
    }
    esp_err_t err = ESP_ERR_NO_MEM;
    if (slot >= 0) {
        table.slots[slot].len[kind] = 0;    /* invalid until the upload completes */
        err = save_table();
        if (err == ESP_OK) {
            err = esp_partition_erase_range(part, region_offset(slot, kind), region_size(kind));
        }
    }
    xSemaphoreGive(lock);
    if (err != ESP_OK) {
        return err;
    }
    up_slot = slot;
    up_kind = kind;
    up_len = 0;
    return ESP_OK;
}

esp_err_t photos_write(const void *data, size_t len)
{
    if (up_slot < 0 || up_len + len > region_size(up_kind)) {
        return ESP_ERR_INVALID_SIZE;
    }
    esp_err_t err = esp_partition_write(part, region_offset(up_slot, up_kind) + up_len, data, len);
    up_len += len;
    return err;
}

esp_err_t photos_end(bool ok)
{
    if (up_slot < 0) {
        return ESP_FAIL;
    }
    esp_err_t err = ESP_ERR_INVALID_SIZE;
    if (ok && up_len > 12) {
        xSemaphoreTake(lock, portMAX_DELAY);
        table.slots[up_slot].len[up_kind] = up_len;
        err = save_table();
        xSemaphoreGive(lock);
    }
    up_slot = -1;
    return err;
}

bool photos_has(const char *id, photo_kind_t kind)
{
    if (!part) {
        return false;
    }
    xSemaphoreTake(lock, portMAX_DELAY);
    int slot = find_slot(id);
    bool has = slot >= 0 && table.slots[slot].len[kind] > 0;
    xSemaphoreGive(lock);
    return has;
}

const void *photos_map(const char *id, photo_kind_t kind, size_t *len, esp_partition_mmap_handle_t *handle)
{
    if (!part) {
        return NULL;
    }
    xSemaphoreTake(lock, portMAX_DELAY);
    int slot = find_slot(id);
    size_t n = slot >= 0 ? table.slots[slot].len[kind] : 0;
    xSemaphoreGive(lock);
    const void *p = NULL;
    if (n && esp_partition_mmap(part, region_offset(slot, kind), n, ESP_PARTITION_MMAP_DATA, &p, handle) == ESP_OK) {
        *len = n;
        return p;
    }
    return NULL;
}

void photos_unmap(esp_partition_mmap_handle_t handle)
{
    esp_partition_munmap(handle);
}

void photos_delete(const char *id)
{
    if (!part) {
        return;
    }
    xSemaphoreTake(lock, portMAX_DELAY);
    int slot = find_slot(id);
    if (slot >= 0) {
        memset(&table.slots[slot], 0, sizeof(table.slots[slot]));
        save_table();
    }
    xSemaphoreGive(lock);
}
