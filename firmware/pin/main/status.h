#pragma once

#include <stdint.h>
#include "lvgl.h"

/**
 * Keep the device-status subjects up to date (battery_percent, time_text,
 * ampm_text, date_text, wifi_status, wifi_name - see the Editor's globals.xml).
 * Screens bind their labels to these in XML, so they update by themselves.
 * Call after plurality_pin_init(), from the LVGL task.
 */
void status_init(void);

/** Last measured battery-pin voltage (for the dashboard); safe from any task. */
float status_battery_volts(void);

/* Battery log: one entry a minute, oldest first, the last few days */
#define STATUS_BATTERY_LOG "/data/battery.bin"
typedef struct __attribute__((packed)) {
    uint32_t time;                      /* unix seconds */
    uint16_t millivolts;                /* battery pin; ~4900 = on USB, not the battery */
    uint8_t usb;                        /* on USB power */
    uint8_t unused;
} status_log_entry_t;

/** Delete the battery log (e.g. to start a fresh run). */
void status_battery_log_clear(void);

/** Wire up the Status screen: Wi-Fi icon states, tap the Wi-Fi card for the next network. */
void status_attach(lv_obj_t *status_screen);

/**
 * Make a Wi-Fi icon follow wifi_state: as drawn when connected, faded while
 * connecting, faded and crossed out when off or failing. `tinted`: the icon is
 * coloured (green) and turns grey when not connected.
 */
void status_wifi_icon(lv_obj_t *icon, bool tinted);
