#pragma once

#include <stdbool.h>

/* Above this the battery pin reads the USB charger, not the battery */
#define POWER_USB_VOLTS     4.4f

/**
 * Low-battery protection. When the battery runs low the pin shows the battery
 * screen (crash_screen) with the red bar flashing, then turns the screen and
 * Wi-Fi off and goes into deep sleep. It wakes every couple of minutes, and
 * goes straight back to sleep until USB is plugged in; then it starts as
 * usual and shows the charging bolt for a moment. (The BOOT button can't wake
 * it: GPIO9 isn't one of the C6's deep-sleep wake pins.)
 *
 * Call first thing in app_main: sets up the battery ADC and, after a
 * low-battery sleep, goes back to sleep unless USB is plugged in.
 */
void power_boot_check(void);

/** After start-up (LVGL task): shows the charging bolt if USB woke the pin. */
void power_after_boot(void);

/**
 * A new battery measurement (status.c, LVGL task): `volts` is the averaged
 * reading, `settled` false until there are a few of them since USB was unplugged.
 */
void power_battery_update(bool usb, float volts, bool settled);
