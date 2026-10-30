/*
 * Web server for the dashboard.
 *
 *   GET  /                 the dashboard page (dashboard/index.html, built in)
 *   GET  /playwrite.ttf    namecard font, for drawing cards in the browser
 *   GET  /api/state        system, members, current front (store_get_state_json)
 *   PUT  /api/members      replace the member list (JSON)
 *   PUT  /api/switches     replace front history (raw store_switch_t records)
 *   GET  /api/switches     front history, same format
 *   POST /api/front        record a switch now: {"members": [index, ...]}
 *   PUT  /api/card?id=ID&kind=K  picture for member ID; K = card (default),
 *                          label, full or side (see store_picture_t)
 *   GET  /api/card?id=ID&kind=K  the same picture back (for the dashboard's previews)
 *   DELETE /api/member?index=N  delete member N (also from front history)
 *   GET  /api/wifi         saved Wi-Fi networks (no passwords) and the pin's address
 *   PUT  /api/wifi         replace the saved networks (see wifi_set_networks_json)
 *   GET  /api/wifi/scan    networks in range (see wifi_scan_json)
 *
 * There's no login: anyone on the same Wi-Fi network can use it.
 */

#include <string.h>
#include <stdlib.h>
#include "esp_log.h"
#include "esp_http_server.h"
#include "cJSON.h"
#include "status.h"
#include "photos.h"
#include "store.h"
#include "wifi.h"
#include "web.h"

static const char *TAG = "web";

#define MAX_JSON_BYTES  (64 * 1024)
#define CHUNK           2048

extern const char index_html_start[] asm("_binary_index_html_start");
extern const char index_html_end[]   asm("_binary_index_html_end");
extern const uint8_t font_start[]    asm("_binary_PlaywriteUSTrad_Regular_ttf_start");
extern const uint8_t font_end[]      asm("_binary_PlaywriteUSTrad_Regular_ttf_end");

/* ---------- helpers ---------- */

static esp_err_t send_error(httpd_req_t *req, const char *status, const char *message)
{
    httpd_resp_set_status(req, status);
    httpd_resp_set_type(req, "text/plain");
    return httpd_resp_sendstr(req, message);
}

static esp_err_t send_ok(httpd_req_t *req)
{
    httpd_resp_set_type(req, "application/json");
    return httpd_resp_sendstr(req, "{\"ok\":true}");
}

/* Read a whole (small) request body as a string; free() the result */
static char *read_body(httpd_req_t *req)
{
    if (req->content_len > MAX_JSON_BYTES) {
        return NULL;
    }
    char *buf = malloc(req->content_len + 1);
    size_t got = 0;
    while (buf && got < req->content_len) {
        int n = httpd_req_recv(req, buf + got, req->content_len - got);
        if (n == HTTPD_SOCK_ERR_TIMEOUT) {
            continue;
        }
        if (n <= 0) {
            free(buf);
            return NULL;
        }
        got += n;
    }
    if (buf) {
        buf[got] = '\0';
    }
    return buf;
}

/* Stream a request body into begin/write/end functions without holding it in RAM */
static esp_err_t receive_stream(httpd_req_t *req, esp_err_t (*write)(const void *, size_t),
                                esp_err_t (*end)(bool))
{
    char *buf = malloc(CHUNK);
    size_t left = req->content_len;
    bool ok = buf != NULL;
    while (ok && left > 0) {
        int n = httpd_req_recv(req, buf, left < CHUNK ? left : CHUNK);
        if (n == HTTPD_SOCK_ERR_TIMEOUT) {
            continue;
        }
        ok = n > 0 && write(buf, n) == ESP_OK;
        left -= n > 0 ? n : 0;
    }
    free(buf);
    if (end(ok) != ESP_OK) {
        return send_error(req, "400 Bad Request", "upload rejected");
    }
    return send_ok(req);
}

/* ---------- handlers ---------- */

static esp_err_t get_index(httpd_req_t *req)
{
    httpd_resp_set_type(req, "text/html; charset=utf-8");
    return httpd_resp_send(req, index_html_start, index_html_end - index_html_start);
}

static esp_err_t get_font(httpd_req_t *req)
{
    httpd_resp_set_type(req, "font/ttf");
    httpd_resp_set_hdr(req, "Cache-Control", "max-age=86400");
    return httpd_resp_send(req, (const char *)font_start, font_end - font_start);
}

static esp_err_t get_state(httpd_req_t *req)
{
    char *state = store_get_state_json();
    if (!state) {
        return send_error(req, "500 Internal Server Error", "out of memory");
    }
    /* Add device readings (battery voltage, for checking the battery reading) */
    cJSON *root = cJSON_Parse(state);
    free(state);
    cJSON_AddNumberToObject(root, "battery_volts", (int)(status_battery_volts() * 1000) / 1000.0);
    char *json = cJSON_PrintUnformatted(root);
    cJSON_Delete(root);
    if (!json) {
        return send_error(req, "500 Internal Server Error", "out of memory");
    }
    httpd_resp_set_type(req, "application/json");
    httpd_resp_set_hdr(req, "Cache-Control", "no-store");
    esp_err_t err = httpd_resp_sendstr(req, json);
    free(json);
    return err;
}

static esp_err_t put_members(httpd_req_t *req)
{
    char *body = read_body(req);
    if (!body) {
        return send_error(req, "400 Bad Request", "body missing or too big");
    }
    esp_err_t err = store_set_members_json(body);
    free(body);
    return err == ESP_OK ? send_ok(req) : send_error(req, "400 Bad Request", "invalid member list");
}

static esp_err_t put_switches(httpd_req_t *req)
{
    if (store_switches_begin() != ESP_OK) {
        return send_error(req, "500 Internal Server Error", "storage error");
    }
    return receive_stream(req, store_switches_write, store_switches_end);
}

static esp_err_t get_switches(httpd_req_t *req)
{
    FILE *f = fopen(STORE_SWITCHES_FILE, "rb");
    httpd_resp_set_type(req, "application/octet-stream");
    httpd_resp_set_hdr(req, "Cache-Control", "no-store");
    if (!f) {
        return httpd_resp_send(req, NULL, 0);
    }
    char *buf = malloc(CHUNK);
    size_t n;
    while (buf && (n = fread(buf, 1, CHUNK, f)) > 0) {
        if (httpd_resp_send_chunk(req, buf, n) != ESP_OK) {
            break;
        }
    }
    free(buf);
    fclose(f);
    return httpd_resp_send_chunk(req, NULL, 0);
}

static esp_err_t post_front(httpd_req_t *req)
{
    char *body = read_body(req);
    cJSON *root = body ? cJSON_Parse(body) : NULL;
    free(body);
    const cJSON *list = cJSON_GetObjectItem(root, "members");
    if (!cJSON_IsArray(list)) {
        cJSON_Delete(root);
        return send_error(req, "400 Bad Request", "expected {\"members\": [...]}");
    }
    uint16_t members[STORE_FRONT_MAX];
    int count = 0;
    const cJSON *item;
    cJSON_ArrayForEach(item, list) {
        if (count < STORE_FRONT_MAX && cJSON_IsNumber(item)) {
            members[count++] = (uint16_t)item->valueint;
        }
    }
    cJSON_Delete(root);
    return store_add_switch(members, count) == ESP_OK ? send_ok(req)
           : send_error(req, "400 Bad Request", "unknown member");
}

/* Parse ?id=...&kind=... (kind defaults to card); false if missing or unknown */
static bool picture_query(httpd_req_t *req, char *id, size_t id_size, store_picture_t *kind)
{
    static const char *const kinds[] = { "card", "label", "full", "side" };
    char query[48], kind_name[8] = "card";
    if (httpd_req_get_url_query_str(req, query, sizeof(query)) != ESP_OK
            || httpd_query_key_value(query, "id", id, id_size) != ESP_OK) {
        return false;
    }
    httpd_query_key_value(query, "kind", kind_name, sizeof(kind_name));
    for (int i = 0; i < 4; i++) {
        if (strcmp(kind_name, kinds[i]) == 0) {
            *kind = (store_picture_t)i;
            return true;
        }
    }
    return false;
}

static esp_err_t get_card(httpd_req_t *req)
{
    char id[16], path[64];
    store_picture_t kind;
    if (!picture_query(req, id, sizeof(id), &kind)) {
        return send_error(req, "404 Not Found", "no such picture");
    }
    if (kind >= STORE_PICTURE_FULL) {       /* photos normally live in a flash slot */
        size_t len;
        esp_partition_mmap_handle_t map;
        const void *p = photos_map(id, kind == STORE_PICTURE_SIDE ? PHOTO_SIDE : PHOTO_FULL, &len, &map);
        if (p) {
            httpd_resp_set_type(req, "application/octet-stream");
            httpd_resp_set_hdr(req, "Cache-Control", "no-store");
            esp_err_t err = httpd_resp_send(req, p, len);
            photos_unmap(map);
            return err;
        }
    }
    if (!store_picture_file(id, kind, path, sizeof(path))) {
        return send_error(req, "404 Not Found", "no such picture");
    }
    FILE *f = fopen(path, "rb");
    if (!f) {
        return send_error(req, "404 Not Found", "no such picture");
    }
    httpd_resp_set_type(req, "application/octet-stream");
    httpd_resp_set_hdr(req, "Cache-Control", "no-store");
    char *buf = malloc(CHUNK);
    size_t n;
    while (buf && (n = fread(buf, 1, CHUNK, f)) > 0) {
        if (httpd_resp_send_chunk(req, buf, n) != ESP_OK) {
            break;
        }
    }
    free(buf);
    fclose(f);
    return httpd_resp_send_chunk(req, NULL, 0);
}

static esp_err_t put_card(httpd_req_t *req)
{
    char id[16];
    store_picture_t kind;
    if (!picture_query(req, id, sizeof(id), &kind) || store_picture_begin(id, kind) != ESP_OK) {
        return send_error(req, "400 Bad Request", "invalid id or kind");
    }
    return receive_stream(req, store_picture_write, store_picture_end);
}

static esp_err_t delete_member(httpd_req_t *req)
{
    char query[32], value[8];
    if (httpd_req_get_url_query_str(req, query, sizeof(query)) != ESP_OK
            || httpd_query_key_value(query, "index", value, sizeof(value)) != ESP_OK) {
        return send_error(req, "400 Bad Request", "missing index");
    }
    return store_delete_member(atoi(value)) == ESP_OK ? send_ok(req)
           : send_error(req, "400 Bad Request", "could not delete member");
}

static esp_err_t get_wifi(httpd_req_t *req)
{
    char *json = wifi_networks_json();
    if (!json) {
        return send_error(req, "500 Internal Server Error", "out of memory");
    }
    httpd_resp_set_type(req, "application/json");
    httpd_resp_set_hdr(req, "Cache-Control", "no-store");
    esp_err_t err = httpd_resp_sendstr(req, json);
    free(json);
    return err;
}

static esp_err_t get_wifi_scan(httpd_req_t *req)
{
    char *json = wifi_scan_json();
    if (!json) {
        return send_error(req, "503 Service Unavailable", "the pin can't scan right now - try again in a moment");
    }
    httpd_resp_set_type(req, "application/json");
    httpd_resp_set_hdr(req, "Cache-Control", "no-store");
    esp_err_t err = httpd_resp_sendstr(req, json);
    free(json);
    return err;
}

static esp_err_t put_wifi(httpd_req_t *req)
{
    char *body = read_body(req);
    if (!body) {
        return send_error(req, "400 Bad Request", "body missing or too big");
    }
    esp_err_t err = wifi_set_networks_json(body);
    free(body);
    return err == ESP_OK ? send_ok(req)
           : send_error(req, "400 Bad Request", "invalid network list (names up to 32 bytes, passwords 8-63 characters or none)");
}

/* ---------- start ---------- */

void web_start(void)
{
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    config.stack_size = 8192;           /* JSON handling needs more than the default */
    config.max_uri_handlers = 16;
    config.lru_purge_enable = true;     /* phones keep connections open; recycle them */
    config.recv_wait_timeout = 10;

    httpd_handle_t server;
    if (httpd_start(&server, &config) != ESP_OK) {
        ESP_LOGE(TAG, "could not start the web server");
        return;
    }

    static const httpd_uri_t routes[] = {
        { .uri = "/",              .method = HTTP_GET,  .handler = get_index },
        { .uri = "/playwrite.ttf", .method = HTTP_GET,  .handler = get_font },
        { .uri = "/api/state",     .method = HTTP_GET,  .handler = get_state },
        { .uri = "/api/members",   .method = HTTP_PUT,  .handler = put_members },
        { .uri = "/api/switches",  .method = HTTP_PUT,  .handler = put_switches },
        { .uri = "/api/switches",  .method = HTTP_GET,  .handler = get_switches },
        { .uri = "/api/front",     .method = HTTP_POST, .handler = post_front },
        { .uri = "/api/card",      .method = HTTP_PUT,  .handler = put_card },
        { .uri = "/api/card",      .method = HTTP_GET,  .handler = get_card },
        { .uri = "/api/member",    .method = HTTP_DELETE, .handler = delete_member },
        { .uri = "/api/wifi",      .method = HTTP_GET,  .handler = get_wifi },
        { .uri = "/api/wifi",      .method = HTTP_PUT,  .handler = put_wifi },
        { .uri = "/api/wifi/scan", .method = HTTP_GET,  .handler = get_wifi_scan },
    };
    for (int i = 0; i < sizeof(routes) / sizeof(routes[0]); i++) {
        httpd_register_uri_handler(server, &routes[i]);
    }
    ESP_LOGI(TAG, "dashboard ready");
}
