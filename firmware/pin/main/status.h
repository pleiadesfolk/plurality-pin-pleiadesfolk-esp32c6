#pragma once

/**
 * Keep the device-status subjects up to date (battery_percent, time_text,
 * ampm_text, date_text, wifi_status, wifi_name - see the Editor's globals.xml).
 * Screens bind their labels to these in XML, so they update by themselves.
 * Call after plurality_pin_init(), from the LVGL task.
 */
void status_init(void);

/** Last measured battery-pin voltage (for the dashboard); safe from any task. */
float status_battery_volts(void);
