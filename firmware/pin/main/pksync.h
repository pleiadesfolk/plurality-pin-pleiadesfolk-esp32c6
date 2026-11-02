#pragma once

#include "esp_err.h"

/*
 * PluralKit -> pin front sync. Switches come from a relay (relay/pk_relay.py,
 * which PluralKit pushes to: instant), or failing that from PluralKit itself,
 * checked once a minute. When PluralKit's latest switch is newer than the
 * pin's current front and has different members, it's added to the pin's
 * history with PluralKit's time. Members the pin doesn't have are left out.
 * Nothing is ever sent to PluralKit. Runs while Wi-Fi is up and the clock set.
 */

/** Start the sync task. Needs NVS; call after wifi_start(). */
void pksync_start(void);

typedef enum {
    PKSYNC_REFRESH_CHANGED,             /* the pin now shows PluralKit's fronter */
    PKSYNC_REFRESH_SAME,                /* it already did */
    PKSYNC_REFRESH_UNKNOWN,             /* PluralKit's fronters aren't on the pin */
    PKSYNC_REFRESH_NO_RELAY,            /* no relay set up */
    PKSYNC_REFRESH_BUSY,                /* already asking */
    PKSYNC_REFRESH_FAILED,              /* the relay or PluralKit couldn't be reached */
} pksync_refresh_t;

/**
 * Ask the relay to check PluralKit now (POST /refresh) and make the pin's
 * current fronter PluralKit's: switches on the pin newer than PluralKit's
 * current one are dropped, nothing new is logged (store_match_front). Runs in
 * its own task; `done` is called in the LVGL task (or straight away for
 * NO_RELAY / BUSY).
 */
void pksync_refresh_now(void (*done)(pksync_refresh_t result));

/**
 * Change settings, saved in flash; NULL leaves one as it is, "" clears it.
 *   ref    for asking PluralKit directly: a system ID (5-6 letters; the
 *          system's front must be public) or a PluralKit token (pk;token)
 *   home   the relay on the home network, e.g. "http://192.168.50.20:8787"
 *   net    the relay from anywhere, e.g. "https://nanopi.tail1234.ts.net"
 *   secret the relay's PIN_SECRET
 * ESP_ERR_INVALID_ARG if something is malformed.
 */
esp_err_t pksync_set(const char *ref, const char *home, const char *net, const char *secret);

/**
 * Status for the dashboard (malloc'd, caller frees): {"set", "token" (bool),
 * "system" (the ID, only when one was given instead of a token), "checked"
 * (unix time of the last direct check, 0 = none), "synced" (time of the last
 * switch taken from PluralKit), "error" ("" when fine), "relay_home",
 * "relay_net", "relay_secret" (bool), "relay_seen" (time of the last answer
 * from the relay), "relay_via" ("home"/"internet"/""), "relay_error"}.
 * Never contains the token or the secret.
 */
char *pksync_status_json(void);

/*
 * One request to PluralKit for the dashboard, with the saved system ID or
 * token (which stays on the pin): `method` "GET", "POST" or "DELETE" (POST
 * and DELETE need the token), `path` after /v2/systems/<system>, e.g.
 * "/switches?limit=100". The connection stays open for a few seconds after,
 * so a series of requests (a sync) doesn't set up TLS each time.
 * on_status gets PluralKit's HTTP status, then on_data the answer in pieces;
 * either returning an error stops it. ESP_ERR_NO_MEM: not enough free RAM for
 * a connection right now (try again shortly). ESP_ERR_INVALID_STATE: no system ID or
 * token saved; ESP_ERR_NOT_SUPPORTED: POST/DELETE with only a system ID.
 */
typedef esp_err_t (*pksync_status_cb_t)(int status, void *ctx);
typedef esp_err_t (*pksync_data_cb_t)(const char *data, int len, void *ctx);
esp_err_t pksync_pk_request(const char *method, const char *path, const char *body,
                            pksync_status_cb_t on_status, pksync_data_cb_t on_data, void *ctx);

/** Close the connection pksync_pk_request() keeps open (~40 KB of RAM), e.g.
 *  before something that needs a lot of memory. */
void pksync_pk_release(void);
