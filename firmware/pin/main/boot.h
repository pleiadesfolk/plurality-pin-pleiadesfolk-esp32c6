#pragma once

/**
 * Show the Editor's boot screen and fade it in from black as the pin starts
 * up: the screen being ready, the SD card mounting and Wi-Fi connecting each
 * bring it further. It's fully in after at most BOOT_MAX_MS even if the SD
 * card or Wi-Fi never come. Once fully in (and held briefly), `done` is called;
 * the boot screen is deleted when the next screen is loaded over it.
 * Call from the LVGL task.
 */
void boot_show(void (*done)(void));
