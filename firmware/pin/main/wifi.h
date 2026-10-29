#pragma once

typedef enum {
    WIFI_OFF,                           /* no network configured */
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

/* Safe to call from any task (e.g. the LVGL task polling for the UI) */
wifi_state_t wifi_get_state(void);
const char *wifi_get_ssid(void);
