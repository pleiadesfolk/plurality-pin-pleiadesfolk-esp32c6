/*
 * Screen brightness.
 *
 * The value lives in the brightness_percent subject (defined in the Editor's
 * globals.xml). The Settings slider and its "50%" label are bound to it in the
 * XML, so the UI updates itself; this file applies the value to the panel and
 * keeps it in NVS (flash) so it survives a restart.
 */

#include "brightness.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "display.h"
#include "ui/plurality_pin.h"

static const char *TAG = "brightness";

#define NVS_NAMESPACE   "pin"
#define NVS_KEY         "brightness"
#define SAVE_DELAY_MS   1000            /* save once the slider has been still this long */
#define SLIDER_TOUCH_PAD 20             /* extra touch area around the 6 px slider */

static lv_timer_t *save_timer;

static void save(lv_timer_t *timer)
{
    nvs_handle_t nvs;
    if (nvs_open(NVS_NAMESPACE, NVS_READWRITE, &nvs) == ESP_OK) {
        nvs_set_u8(nvs, NVS_KEY, (uint8_t)lv_subject_get_int(&brightness_percent));
        nvs_commit(nvs);
        nvs_close(nvs);
    }
}

static void on_change(lv_observer_t *observer, lv_subject_t *subject)
{
    display_set_brightness((uint8_t)lv_subject_get_int(subject));
    /* Don't write flash on every step while dragging */
    lv_timer_reset(save_timer);
    lv_timer_resume(save_timer);
}

void brightness_init(void)
{
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK(err);

    nvs_handle_t nvs;
    uint8_t saved;
    if (nvs_open(NVS_NAMESPACE, NVS_READONLY, &nvs) == ESP_OK) {
        if (nvs_get_u8(nvs, NVS_KEY, &saved) == ESP_OK) {
            lv_subject_set_int(&brightness_percent, saved);
        }
        nvs_close(nvs);
    }
    ESP_LOGI(TAG, "%d %%", (int)lv_subject_get_int(&brightness_percent));

    save_timer = lv_timer_create(save, SAVE_DELAY_MS, NULL);
    lv_timer_set_repeat_count(save_timer, -1);
    lv_timer_pause(save_timer);
    lv_timer_set_auto_delete(save_timer, false);

    /* Also called right away, which applies the starting value */
    lv_subject_add_observer(&brightness_percent, on_change, NULL);
    lv_timer_pause(save_timer);         /* ...but nothing to save yet */
}

static lv_obj_t *find_slider(lv_obj_t *obj)
{
    if (lv_obj_check_type(obj, &lv_slider_class)) {
        return obj;
    }
    for (uint32_t i = 0; i < lv_obj_get_child_count(obj); i++) {
        lv_obj_t *found = find_slider(lv_obj_get_child(obj, i));
        if (found) {
            return found;
        }
    }
    return NULL;
}

void brightness_attach(lv_obj_t *settings_screen)
{
    lv_obj_t *slider = find_slider(settings_screen);
    if (slider) {
        lv_obj_set_ext_click_area(slider, SLIDER_TOUCH_PAD);
    }
}
