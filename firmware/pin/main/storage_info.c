/*
 * Storage gauges for the Status screen.
 *
 * The microSD slot shares its SPI wires with the display (the SPI driver
 * takes turns between them). Mounting a card or counting its free space can
 * take a while, so it happens in this low-priority task, never in the LVGL
 * task. The board's DIP switch JP8 pin 2 must be ON for the slot to work.
 */

#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_vfs_fat.h"
#include "bsp/esp-bsp.h"
#include "storage_info.h"

static const char *TAG = "storage";

#define CHECK_PERIOD_MS 30000

static storage_usage_t sd, pin;
static portMUX_TYPE lock = portMUX_INITIALIZER_UNLOCKED;
static volatile bool sd_mounted;

static void measure(const char *path, storage_usage_t *out)
{
    uint64_t total = 0, free_bytes = 0;
    bool ok = esp_vfs_fat_info(path, &total, &free_bytes) == ESP_OK;
    storage_usage_t u = { .present = ok, .total = total, .used = ok ? total - free_bytes : 0 };
    taskENTER_CRITICAL(&lock);
    *out = u;
    taskEXIT_CRITICAL(&lock);
}

static void task(void *arg)
{
    bool logged_missing = false;
    while (1) {
        if (!sd_mounted) {
            sd_mounted = bsp_sdcard_mount() == ESP_OK;
            if (sd_mounted) {
                ESP_LOGI(TAG, "SD card mounted");
                logged_missing = false;
            } else if (!logged_missing) {
                ESP_LOGI(TAG, "no SD card (checking again every %d s)", CHECK_PERIOD_MS / 1000);
                logged_missing = true;
            }
        }
        if (sd_mounted) {
            measure(BSP_SD_MOUNT_POINT, &sd);
            if (!sd.present) {
                ESP_LOGI(TAG, "SD card removed");
                bsp_sdcard_unmount();
                sd_mounted = false;
            }
        } else {
            taskENTER_CRITICAL(&lock);
            memset(&sd, 0, sizeof(sd));
            taskEXIT_CRITICAL(&lock);
        }
        measure("/data", &pin);
        vTaskDelay(pdMS_TO_TICKS(CHECK_PERIOD_MS));
    }
}

void storage_info_start(void)
{
    /* The SD driver logs an error for every failed mount attempt; an empty slot is normal */
    esp_log_level_set("sdspi_transaction", ESP_LOG_NONE);
    esp_log_level_set("sdmmc_common", ESP_LOG_NONE);
    esp_log_level_set("sdmmc_init", ESP_LOG_NONE);
    esp_log_level_set("vfs_fat_sdmmc", ESP_LOG_NONE);
    esp_log_level_set("ESP32-C6-Touch-AMOLED-1.64", ESP_LOG_NONE);   /* BSP; display setup is done by now */
    xTaskCreate(task, "storage", 4096, NULL, 2, NULL);
}

bool storage_info_sd_ready(void)
{
    return sd_mounted;
}

void storage_info_get(storage_usage_t *sd_out, storage_usage_t *pin_out)
{
    taskENTER_CRITICAL(&lock);
    *sd_out = sd;
    *pin_out = pin;
    taskEXIT_CRITICAL(&lock);
}
