/*
 * Dashboard password and login sessions (see auth.h).
 */

#include <string.h>
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "esp_log.h"
#include "esp_random.h"
#include "esp_timer.h"
#include "mbedtls/pkcs5.h"
#include "mbedtls/constant_time.h"
#include "nvs.h"
#include "auth.h"

static const char *TAG = "auth";

#define NVS_NAMESPACE   "pin"
#define ITERATIONS      10000           /* PBKDF2 rounds: ~0.1 s per check on the C6 */
#define MAX_FAILS       5               /* wrong passwords in a row before a pause */
#define LOCK_US         (30 * 1000000LL)

typedef struct {
    uint8_t salt[16];
    uint8_t hash[32];
} password_t;

typedef struct {
    uint8_t tokens[AUTH_SESSIONS][16];  /* all zero = unused */
    uint8_t next;                       /* slot the next login replaces */
} sessions_t;

static SemaphoreHandle_t lock;
static bool have_password;
static password_t pw;
static sessions_t sessions;
static int fails;
static int64_t locked_until;

static void save(void)
{
    nvs_handle_t nvs;
    if (nvs_open(NVS_NAMESPACE, NVS_READWRITE, &nvs) != ESP_OK) {
        return;
    }
    if (have_password) {
        nvs_set_blob(nvs, "dash_pw", &pw, sizeof(pw));
    } else {
        nvs_erase_key(nvs, "dash_pw");
    }
    nvs_set_blob(nvs, "dash_sess", &sessions, sizeof(sessions));
    nvs_commit(nvs);
    nvs_close(nvs);
}

static void hash(const char *password, const uint8_t salt[16], uint8_t out[32])
{
    mbedtls_pkcs5_pbkdf2_hmac_ext(MBEDTLS_MD_SHA256, (const unsigned char *)password, strlen(password),
                                  salt, 16, ITERATIONS, 32, out);
}

static bool from_hex(const char *text, uint8_t out[16])
{
    if (!text || strlen(text) != AUTH_TOKEN_LEN) {
        return false;
    }
    for (int i = 0; i < 16; i++) {
        unsigned v;
        if (sscanf(text + i * 2, "%2x", &v) != 1) {
            return false;
        }
        out[i] = (uint8_t)v;
    }
    return true;
}

/* Index of the session `token`, or -1 (lock held) */
static int find(const char *token)
{
    static const uint8_t unused[16];
    uint8_t raw[16];
    if (!from_hex(token, raw) || memcmp(raw, unused, 16) == 0) {
        return -1;
    }
    for (int i = 0; i < AUTH_SESSIONS; i++) {
        if (mbedtls_ct_memcmp(raw, sessions.tokens[i], 16) == 0) {
            return i;
        }
    }
    return -1;
}

/* Start a session and write its token (lock held) */
static void new_session(char *token)
{
    uint8_t *t = sessions.tokens[sessions.next];
    esp_fill_random(t, 16);
    sessions.next = (sessions.next + 1) % AUTH_SESSIONS;
    for (int i = 0; i < 16; i++) {
        sprintf(token + i * 2, "%02x", t[i]);
    }
}

void auth_init(void)
{
    lock = xSemaphoreCreateMutex();
    nvs_handle_t nvs;
    if (nvs_open(NVS_NAMESPACE, NVS_READONLY, &nvs) == ESP_OK) {
        size_t size = sizeof(pw);
        have_password = nvs_get_blob(nvs, "dash_pw", &pw, &size) == ESP_OK && size == sizeof(pw);
        size = sizeof(sessions);
        if (nvs_get_blob(nvs, "dash_sess", &sessions, &size) != ESP_OK || size != sizeof(sessions)) {
            memset(&sessions, 0, sizeof(sessions));
        }
        sessions.next %= AUTH_SESSIONS;
        nvs_close(nvs);
    }
    ESP_LOGI(TAG, "dashboard password %s", have_password ? "on" : "off");
}

bool auth_password_set(void)
{
    return have_password;
}

bool auth_session_ok(const char *token)
{
    xSemaphoreTake(lock, portMAX_DELAY);
    bool ok = !have_password || find(token) >= 0;
    xSemaphoreGive(lock);
    return ok;
}

esp_err_t auth_login(const char *password, char *token)
{
    xSemaphoreTake(lock, portMAX_DELAY);
    esp_err_t err;
    if (esp_timer_get_time() < locked_until) {
        err = ESP_ERR_INVALID_STATE;
    } else if (!have_password) {
        new_session(token);
        err = ESP_OK;
    } else {
        uint8_t h[32];
        hash(password, pw.salt, h);
        if (mbedtls_ct_memcmp(h, pw.hash, 32) == 0) {
            fails = 0;
            new_session(token);
            save();
            err = ESP_OK;
        } else {
            if (++fails >= MAX_FAILS) {
                fails = 0;
                locked_until = esp_timer_get_time() + LOCK_US;
                ESP_LOGW(TAG, "too many wrong passwords: logins paused for 30 s");
            }
            err = ESP_ERR_INVALID_ARG;
        }
    }
    xSemaphoreGive(lock);
    return err;
}

esp_err_t auth_set_password(const char *password, char *token)
{
    size_t n = strlen(password);
    if (n && (n < 4 || n > 64)) {
        return ESP_ERR_INVALID_ARG;
    }
    xSemaphoreTake(lock, portMAX_DELAY);
    memset(&sessions, 0, sizeof(sessions));         /* everyone logs in again */
    have_password = n > 0;
    if (have_password) {
        esp_fill_random(pw.salt, sizeof(pw.salt));
        hash(password, pw.salt, pw.hash);
        new_session(token);
    } else {
        memset(&pw, 0, sizeof(pw));
        token[0] = 0;
    }
    save();
    xSemaphoreGive(lock);
    ESP_LOGI(TAG, "dashboard password %s", have_password ? "set" : "removed");
    return ESP_OK;
}

void auth_logout(const char *token)
{
    xSemaphoreTake(lock, portMAX_DELAY);
    int i = find(token);
    if (i >= 0) {
        memset(sessions.tokens[i], 0, 16);
        save();
    }
    xSemaphoreGive(lock);
}

void auth_reset(void)
{
    char unused[AUTH_TOKEN_LEN + 1];
    auth_set_password("", unused);
}
