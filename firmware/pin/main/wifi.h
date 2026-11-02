#pragma once

#include <stdbool.h>
#include <stddef.h>
#include "esp_err.h"

#define WIFI_MAX_NETWORKS 6

typedef enum {
    WIFI_OFF,                           /* no network saved (and no setup network) */
    WIFI_SETUP,                         /* no network saved: the setup network is up */
    WIFI_DISABLED,                      /* turned off on the Settings screen */
    WIFI_CONNECTING,
    WIFI_CONNECTED,
    WIFI_FAILED,                        /* several attempts failed; still retrying */
} wifi_state_t;

/**
 * Join the first saved network that's in range and keep reconnecting if the
 * connection drops. Once connected, the clock is set from the internet (NTP).
 * With no saved network, starts the setup network instead (wifi_setup_network).
 * Needs NVS to be initialised first.
 */
void wifi_start(void);

/** Turn Wi-Fi on or off; remembered across restarts. Turning it on also switches
 *  every saved network back on (undoes "skip"). */
void wifi_set_enabled(bool on);
bool wifi_is_enabled(void);

/**
 * Move to the next saved network after the current one (list order, skipping
 * switched-off ones) and write its name to `ssid`. If it isn't in range, the
 * one after it that is gets joined (possibly the current one again).
 * ESP_ERR_NOT_FOUND if there's no other network to try, ESP_ERR_INVALID_STATE
 * if Wi-Fi is off.
 */
esp_err_t wifi_switch_next(char *ssid, size_t size);

/* Safe to call from any task (e.g. the LVGL task polling for the UI) */
wifi_state_t wifi_get_state(void);
/** Name of the network being joined / joined ("" before the first). */
const char *wifi_get_ssid(void);
/** The pin's address while connected, e.g. "192.168.50.99"; false if not connected. */
bool wifi_get_ip(char *buf, size_t size);

/** The dashboard's address on the setup network */
#define WIFI_SETUP_URL "http://192.168.4.1/"

/**
 * While no network is saved, the pin runs its own Wi-Fi ("setup network") so
 * a phone can join it and add one on the dashboard. True while it's up, with
 * its name and password written to `ssid` and `password`.
 */
bool wifi_setup_network(char *ssid, size_t ssid_size, char *password, size_t password_size);
/** Phones joined to the setup network right now (0 when it's off). */
int wifi_setup_phones(void);

/** True once the clock has been set from the internet (NTP) since starting. */
bool wifi_clock_set(void);

/** Saved networks for the dashboard: {"networks":[{"ssid","skip","current"}],"ip","setup"}
 *  ("setup": the setup network is up)
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
