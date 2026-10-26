/*
 * Images from the "assets" flash partition.
 *
 * The partition is mapped into the CPU's address space, so LVGL reads image
 * pixels straight from flash, exactly like images compiled into the app, but
 * without making the app bigger. (Reading them as files through a filesystem
 * was ~800 ms per full-screen image; mapped, it's as fast as built-in images.)
 *
 * Layout of the partition: see tools/sync_ui.py.
 */

#include <string.h>
#include "assets.h"
#include "esp_log.h"
#include "esp_partition.h"

static const char *TAG = "assets";

typedef struct {
    char magic[4];                      /* "PPA1" */
    uint32_t count;
    uint32_t total_size;
} assets_header_t;

typedef struct {
    uint32_t offset;
    uint32_t size;
} assets_entry_t;

static const uint8_t *base;
static uint32_t count;
static lv_image_dsc_t *images;          /* one descriptor per image, pointing into flash */

void assets_init(void)
{
    const esp_partition_t *part = esp_partition_find_first(ESP_PARTITION_TYPE_DATA,
                                                           ESP_PARTITION_SUBTYPE_ANY, "assets");
    ESP_ERROR_CHECK(part ? ESP_OK : ESP_ERR_NOT_FOUND);

    assets_header_t header;
    ESP_ERROR_CHECK(esp_partition_read(part, 0, &header, sizeof(header)));
    if (memcmp(header.magic, "PPA1", 4) != 0 || header.total_size > part->size) {
        ESP_LOGE(TAG, "assets partition is empty or invalid - run tools/sync_ui.py and idf.py flash");
        return;
    }

    esp_partition_mmap_handle_t handle;
    ESP_ERROR_CHECK(esp_partition_mmap(part, 0, header.total_size, ESP_PARTITION_MMAP_DATA,
                                       (const void **)&base, &handle));

    count = header.count;
    images = calloc(count, sizeof(lv_image_dsc_t));
    assert(images);
    const assets_entry_t *table = (const assets_entry_t *)(base + sizeof(assets_header_t));
    for (uint32_t i = 0; i < count; i++) {
        const uint8_t *p = base + table[i].offset;
        memcpy(&images[i].header, p, sizeof(lv_image_header_t));
        images[i].data = p + sizeof(lv_image_header_t);
        images[i].data_size = table[i].size - sizeof(lv_image_header_t);
    }
    ESP_LOGI(TAG, "%u images, %u KB mapped", (unsigned)count, (unsigned)(header.total_size / 1024));
}

const void *assets_image(uint32_t index)
{
    return index < count ? &images[index] : NULL;
}
