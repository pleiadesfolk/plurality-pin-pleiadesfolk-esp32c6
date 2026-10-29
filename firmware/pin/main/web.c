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
 *   PUT  /api/card?id=ID   namecard picture for member ID (store_card_header_t ...)
 *   DELETE /api/member?index=N  delete member N (also from front history)
 *
 * There's no login: anyone on the same Wi-Fi network can use it.
 */

#include <string.h>
#include <stdlib.h>
#include "esp_log.h"
#include "esp_http_server.h"
#include "cJSON.h"
#include "store.h"
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
    char *json = store_get_state_json();
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

static esp_err_t put_card(httpd_req_t *req)
{
    char query[32], id[16];
    if (httpd_req_get_url_query_str(req, query, sizeof(query)) != ESP_OK
            || httpd_query_key_value(query, "id", id, sizeof(id)) != ESP_OK
            || store_card_begin(id) != ESP_OK) {
        return send_error(req, "400 Bad Request", "missing or invalid id");
    }
    return receive_stream(req, store_card_write, store_card_end);
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

/* ---------- start ---------- */

void web_start(void)
{
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    config.stack_size = 8192;           /* JSON handling needs more than the default */
    config.max_uri_handlers = 12;
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
        { .uri = "/api/member",    .method = HTTP_DELETE, .handler = delete_member },
    };
    for (int i = 0; i < sizeof(routes) / sizeof(routes[0]); i++) {
        httpd_register_uri_handler(server, &routes[i]);
    }
    ESP_LOGI(TAG, "dashboard ready");
}
