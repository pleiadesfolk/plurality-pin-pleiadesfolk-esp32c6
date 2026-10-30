#pragma once

#include <stdbool.h>

typedef enum {
    WIFI_OFF,                           /* no network configured */
    WIFI_DISABLED,                      /* turned off on the Settings screen */
    WIFI_CONNECTING,
    WIFI_CONNECTED,
    WIFI_FAILED,                        /* several attempts failed; still retrying */
} wifi_state_t;

/**
 * Connect to the network in wifi_credentials.h and keep reconnecting if the
 * connection drops. Once connected, the clock is set from the internet (NTP).
 * Needs NVS to be initialised first.
 */
void wifi_start(void);

/** Turn Wi-Fi on or off; remembered across restarts. */
void wifi_set_enabled(bool on);
bool wifi_is_enabled(void);

/* Safe to call from any task (e.g. the LVGL task polling for the UI) */
wifi_state_t wifi_get_state(void);
const char *wifi_get_ssid(void);
