#pragma once

/**
 * The BOOT button (GPIO9, the side button that isn't PWR): each press switches
 * to the next member in the dashboard's button shortlist. Call from the LVGL
 * task after nav_init(). (PWR isn't connected to the chip: it switches the
 * board's power on and off in hardware.)
 */
void button_init(void);

/** Switch to the next (direction > 0) or previous shortlisted member; from the LVGL task. */
void button_switch(int direction);
