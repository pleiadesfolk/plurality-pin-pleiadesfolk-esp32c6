#pragma once

#include <stdbool.h>
#include <stddef.h>
#include "esp_err.h"

#define WIFI_MAX_NETWORKS 6

typedef enum {
    WIFI_OFF,                           /* no network saved */
    WIFI_DISABLED,                      /* turned off on the Settings screen */
    WIFI_CONNECTING,
    WIFI_CONNECTED,
    WIFI_FAILED,                        /* several attempts failed; still retrying */
} wifi_state_t;

/**
 * Join the first saved network that's in range and keep reconnecting if the
 * connection drops. Once connected, the clock is set from the internet (NTP).
 * Needs NVS to be initialised first.
 */
void wifi_start(void);

/** Turn Wi-Fi on or off; remembered across restarts. Turning it on also switches
 *  every saved network back on (undoes "skip"). */
void wifi_set_enabled(bool on);
bool wifi_is_enabled(void);

/* Safe to call from any task (e.g. the LVGL task polling for the UI) */
wifi_state_t wifi_get_state(void);
/** Name of the network being joined / joined ("" before the first). */
const char *wifi_get_ssid(void);
/** The pin's address while connected, e.g. "192.168.50.99"; false if not connected. */
bool wifi_get_ip(char *buf, size_t size);

/** Saved networks for the dashboard: {"networks":[{"ssid","skip","current"}],"ip"}
 *  - passwords are never included. free() the result. */
char *wifi_networks_json(void);
/** Scan for networks in range (takes a few seconds; the connection stays up):
 *  {"found":[{"ssid","rssi","open","saved"}]}, strongest first. NULL if Wi-Fi is
 *  off or busy joining a network. free() the result. */
char *wifi_scan_json(void);

/** Replace the saved networks: {"networks":[{"ssid","password"?,"skip"}]}, in
 *  the order to try them. A network without "password" keeps its saved one;
 *  "skip" keeps it saved but not joined. Leaves the current network if it's
 *  removed or skipped. */
esp_err_t wifi_set_networks_json(const char *json);
