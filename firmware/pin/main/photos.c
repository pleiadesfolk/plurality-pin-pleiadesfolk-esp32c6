/*
 * Photo slots in the "photos" partition (see photos.h).
 *
 * Layout: a 4 KB table at the start, then PHOTOS_SLOTS slots of SLOT_SIZE.
 * Each slot: the "image" photo (the whole photo fitted to the screen, up to
 * 456x280 RGB565, 250 KB) in the first FULL_SIZE bytes, then the "image with
 * name" circle (228x280 RGB565A8, 192 KB). Flash must be erased before it's written, so an upload erases its
 * half of the slot first.
 *
 * Only the web server writes (one upload at a time); the table is guarded by
 * a mutex because the LVGL task reads it.
 *
 * After the slots: a staging area for one photo of a member whose photos are
 * on the SD card. When such a member comes to the front, a background task
 * copies the photo there from the card (a few seconds, once), so it's then
 * drawn from flash like the others.
 */

#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "photos.h"

static const char *TAG = "photos";

#define TABLE_SIZE  0x1000
#define FULL_SIZE   0x3F000             /* 252 KB >= 12 + 456*280*2 */
#define SIDE_SIZE   0x30000             /* 192 KB >= 12 + 228*280*3 */
#define SLOT_SIZE   (FULL_SIZE + SIDE_SIZE)

typedef struct {
    char id[12];                        /* "" = free */
    uint32_t len[2];                    /* bytes stored per photo_kind_t; 0 = none */
} slot_t;

typedef struct {
    char magic[4];                      /* "PPH2" (PPH1: 11 smaller slots, square photos) */
    slot_t slots[PHOTOS_SLOTS];
    slot_t staged;                      /* what's in the staging area (added later: may read as 0xFF) */
} table_t;

#define STAGE_OFFSET (TABLE_SIZE + PHOTOS_SLOTS * SLOT_SIZE)
#define STAGE_SIZE   FULL_SIZE          /* fits either photo */

static const esp_partition_t *part;
static table_t table;
static SemaphoreHandle_t lock;

/* current upload */
static int up_slot = -1;
static photo_kind_t up_kind;
static size_t up_len;

/* staging: the latest request (guarded by lock) and the copying task */
static bool can_stage;
static TaskHandle_t stage_task;
static char want_id[12], want_path[64];
static photo_kind_t want_kind;
static volatile uint32_t stage_done;    /* counts finished copies */

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
    if (memcmp(table.magic, "PPH2", 4) != 0) {
        /* first start, or the old layout (its slots are elsewhere): empty table */
        memset(&table, 0, sizeof(table));
        memcpy(table.magic, "PPH2", 4);
        save_table();
    }
    can_stage = part->size >= STAGE_OFFSET + STAGE_SIZE;
    if (table.staged.len[0] > STAGE_SIZE || table.staged.len[1] > STAGE_SIZE) {
        memset(&table.staged, 0, sizeof(table.staged));    /* never used yet */
        save_table();
    }
    ESP_LOGI(TAG, "%d of %d photo slots free", photos_free_slots(), PHOTOS_SLOTS);
}

int photos_free_slots(void)
{
    if (!part) {
        return 0;
    }
    xSemaphoreTake(lock, portMAX_DELAY);
    int free_slots = 0;
    for (int i = 0; i < PHOTOS_SLOTS; i++) {
        free_slots += table.slots[i].id[0] == 0;
    }
    xSemaphoreGive(lock);
    return free_slots;
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

void photos_delete_kind(const char *id, photo_kind_t kind)
{
    if (!part) {
        return;
    }
    xSemaphoreTake(lock, portMAX_DELAY);
    int slot = find_slot(id);
    if (slot >= 0) {
        table.slots[slot].len[kind] = 0;
        if (!table.slots[slot].len[!kind]) {
            memset(&table.slots[slot], 0, sizeof(table.slots[slot]));   /* empty: free it */
        }
        save_table();
    }
    xSemaphoreGive(lock);
}

/* ---------- staging ---------- */

/* Copy `path` into the staging area (lock not held) */
static void stage_copy(const char *id, photo_kind_t kind, const char *path)
{
    xSemaphoreTake(lock, portMAX_DELAY);
    memset(&table.staged, 0, sizeof(table.staged));         /* invalid while copying */
    save_table();
    xSemaphoreGive(lock);

    FILE *f = fopen(path, "rb");
    char *buf = malloc(4096);
    size_t len = 0, n;
    bool ok = f && buf && esp_partition_erase_range(part, STAGE_OFFSET, STAGE_SIZE) == ESP_OK;
    while (ok && (n = fread(buf, 1, 4096, f)) > 0) {
        ok = len + n <= STAGE_SIZE && esp_partition_write(part, STAGE_OFFSET + len, buf, n) == ESP_OK;
        len += n;
    }
    free(buf);
    if (f) {
        fclose(f);
    }
    if (ok && len > 12) {
        xSemaphoreTake(lock, portMAX_DELAY);
        strlcpy(table.staged.id, id, sizeof(table.staged.id));
        table.staged.len[kind] = len;
        save_table();
        xSemaphoreGive(lock);
    } else {
        ESP_LOGW(TAG, "couldn't copy %s", path);
    }
}

static void stage_main(void *arg)
{
    for (;;) {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        char id[12], path[64];
        photo_kind_t kind;
        xSemaphoreTake(lock, portMAX_DELAY);
        strlcpy(id, want_id, sizeof(id));
        strlcpy(path, want_path, sizeof(path));
        kind = want_kind;
        xSemaphoreGive(lock);
        int64_t start = esp_log_timestamp();
        stage_copy(id, kind, path);
        ESP_LOGI(TAG, "copied %s from the SD card in %d ms", path, (int)(esp_log_timestamp() - start));
        stage_done++;
    }
}

void photos_stage(const char *id, photo_kind_t kind, const char *path)
{
    if (!part || !can_stage) {
        return;
    }
    xSemaphoreTake(lock, portMAX_DELAY);
    bool same = strcmp(want_id, id) == 0 && want_kind == kind && strcmp(want_path, path) == 0;
    strlcpy(want_id, id, sizeof(want_id));
    strlcpy(want_path, path, sizeof(want_path));
    want_kind = kind;
    xSemaphoreGive(lock);
    if (!stage_task) {
        xTaskCreate(stage_main, "photo_stage", 4096, NULL, 2, &stage_task);
    }
    if (!same) {                        /* else it's being copied, done, or failed */
        xTaskNotifyGive(stage_task);
    }
}

uint32_t photos_stage_count(void)
{
    return stage_done;
}

bool photos_staged(const char *id, photo_kind_t kind)
{
    if (!part) {
        return false;
    }
    xSemaphoreTake(lock, portMAX_DELAY);
    bool has = strcmp(table.staged.id, id) == 0 && table.staged.len[kind] > 0;
    xSemaphoreGive(lock);
    return has;
}

const void *photos_map_staged(const char *id, photo_kind_t kind, size_t *len, esp_partition_mmap_handle_t *handle)
{
    if (!part) {
        return NULL;
    }
    xSemaphoreTake(lock, portMAX_DELAY);
    size_t n = strcmp(table.staged.id, id) == 0 ? table.staged.len[kind] : 0;
    xSemaphoreGive(lock);
    const void *p = NULL;
    if (n && esp_partition_mmap(part, STAGE_OFFSET, n, ESP_PARTITION_MMAP_DATA, &p, handle) == ESP_OK) {
        *len = n;
        return p;
    }
    return NULL;
}

void photos_unstage(const char *id)
{
    if (!part) {
        return;
    }
    xSemaphoreTake(lock, portMAX_DELAY);
    if (strcmp(table.staged.id, id) == 0) {
        memset(&table.staged, 0, sizeof(table.staged));
        save_table();
    }
    if (strcmp(want_id, id) == 0) {
        want_id[0] = 0;                 /* copy it again next time */
    }
    xSemaphoreGive(lock);
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
