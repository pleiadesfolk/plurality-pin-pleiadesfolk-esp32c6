#pragma once

#include <stdbool.h>
#include "esp_err.h"

/*
 * Dashboard password and login sessions.
 *
 * The password is kept as a salted PBKDF2-SHA256 hash in NVS ("pin"/"dash_pw").
 * Logging in gives a random session token (32 hex characters), kept by the
 * phone as a cookie; the pin remembers the last AUTH_SESSIONS of them in NVS,
 * so logins survive restarts. Without a password, everything is open.
 * Safe to call from any task.
 */

#define AUTH_SESSIONS   6
#define AUTH_TOKEN_LEN  32              /* hex characters */

/** Load the password and sessions. Needs NVS. */
void auth_init(void);

bool auth_password_set(void);

/** True if `token` is a current session (or there's no password at all). */
bool auth_session_ok(const char *token);

/**
 * Check `password`; on success writes a new session token (AUTH_TOKEN_LEN + 1
 * bytes) to `token`. ESP_ERR_INVALID_ARG if wrong, ESP_ERR_INVALID_STATE while
 * locked after too many wrong tries.
 */
esp_err_t auth_login(const char *password, char *token);

/**
 * Set a new password (4-64 characters) or remove it (""). Ends every session;
 * with a new password, writes a fresh session token for the caller to `token`.
 */
esp_err_t auth_set_password(const char *password, char *token);

/** End one session (log out). */
void auth_logout(const char *token);

/** Remove the password (from the pin itself: holding the side button). */
void auth_reset(void);
