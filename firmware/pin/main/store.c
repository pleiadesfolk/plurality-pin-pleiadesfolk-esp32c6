/*
 * Members and front history in the "storage" partition (FAT with wear
 * levelling, mounted at /data).
 *
 *   /data/members.json   system name + members (written by the dashboard)
 *   /data/switches.bin   store_switch_t records, oldest first; the last one is
 *                        the current front
 *   /data/cards/<id>.bin namecard picture per member (store_card_header_t)
 *
 * The member list lives in RAM too (small: ~150 bytes per member). Front
 * history stays in flash; only its last record is kept in RAM.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <strings.h>
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "esp_log.h"
#include "esp_vfs_fat.h"
#include "cJSON.h"
#include "store.h"

static const char *TAG = "store";

#define MEMBERS_FILE        "/data/members.json"
#define SWITCHES_TMP_FILE   "/data/switches.tmp"
#define MAX_MEMBERS         128
#define MAX_SWITCH_BYTES    (2 * 1024 * 1024)
#define CARDS_DIR           "/data/cards"
#define MAX_CARD_BYTES      (128 * 1024)

typedef struct {
    char id[12];                        /* PluralKit member id */
    char name[48];
    char card[128];                     /* namecard text */
    char pronouns[48];
    uint32_t color;                     /* 0xRRGGBB */
    bool on_button;                     /* in the BOOT button's shortlist */
    uint32_t messages;                  /* PluralKit message count: the button's order */
} member_t;

static SemaphoreHandle_t lock;
static char system_name[64];
static member_t *members;               /* member_count entries */
static int member_count;
static store_switch_t front;            /* last switch; time 0 = none yet */
static uint32_t switch_count;
static bool front_changed = true;       /* tell the UI on first poll */

static FILE *upload;                    /* one upload at a time (the web server is single-threaded) */
static size_t upload_bytes;
static char card_path[48], card_tmp_path[48];

/* ---------- helpers ---------- */

static void copy_string(char *dst, size_t size, const cJSON *item)
{
    const char *s = cJSON_IsString(item) ? item->valuestring : "";
    strlcpy(dst, s, size);
}

/* Parse the dashboard's members JSON into a new array (*out, free() it); returns count or -1 */
static int members_from_json(const char *json, char *system, size_t system_size, member_t **out)
{
    cJSON *root = cJSON_Parse(json);
    if (!root) {
        return -1;
    }
    const cJSON *list = cJSON_GetObjectItem(root, "members");
    if (!cJSON_IsArray(list) || cJSON_GetArraySize(list) > MAX_MEMBERS) {
        cJSON_Delete(root);
        return -1;
    }
    copy_string(system, system_size, cJSON_GetObjectItem(root, "system"));

    *out = calloc(cJSON_GetArraySize(list) + 1, sizeof(member_t));
    if (!*out) {
        cJSON_Delete(root);
        return -1;
    }
    int n = 0;
    const cJSON *item;
    cJSON_ArrayForEach(item, list) {
        member_t *m = &(*out)[n++];
        copy_string(m->id, sizeof(m->id), cJSON_GetObjectItem(item, "id"));
        copy_string(m->name, sizeof(m->name), cJSON_GetObjectItem(item, "name"));
        copy_string(m->card, sizeof(m->card), cJSON_GetObjectItem(item, "card"));
        copy_string(m->pronouns, sizeof(m->pronouns), cJSON_GetObjectItem(item, "pronouns"));
        m->on_button = cJSON_IsTrue(cJSON_GetObjectItem(item, "button"));
        const cJSON *messages = cJSON_GetObjectItem(item, "messages");
        m->messages = cJSON_IsNumber(messages) && messages->valuedouble > 0 ? (uint32_t)messages->valuedouble : 0;
        const cJSON *color = cJSON_GetObjectItem(item, "color");
        m->color = cJSON_IsString(color) ? strtoul(color->valuestring, NULL, 16) : 0x468DC3;
    }
    cJSON_Delete(root);
    return n;
}

static char *members_to_json(void)
{
    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "system", system_name);
    cJSON *list = cJSON_AddArrayToObject(root, "members");
    for (int i = 0; i < member_count; i++) {
        const member_t *m = &members[i];
        cJSON *item = cJSON_CreateObject();
        char color[8];
        snprintf(color, sizeof(color), "%06lX", (unsigned long)(m->color & 0xFFFFFF));
        cJSON_AddStringToObject(item, "id", m->id);
        cJSON_AddStringToObject(item, "name", m->name);
        cJSON_AddStringToObject(item, "card", m->card);
        cJSON_AddStringToObject(item, "pronouns", m->pronouns);
        cJSON_AddBoolToObject(item, "button", m->on_button);
        cJSON_AddNumberToObject(item, "messages", m->messages);
        cJSON_AddStringToObject(item, "color", color);
        cJSON_AddItemToArray(list, item);
    }
    char *json = cJSON_PrintUnformatted(root);
    cJSON_Delete(root);
    return json;
}

static char *read_file(const char *path)
{
    FILE *f = fopen(path, "rb");
    if (!f) {
        return NULL;
    }
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);
    char *buf = malloc(size + 1);
    if (buf && fread(buf, 1, size, f) == size) {
        buf[size] = '\0';
    } else {
        free(buf);
        buf = NULL;
    }
    fclose(f);
    return buf;
}

/* Re-read the last switch and the count from the file (caller holds the lock) */
static void load_front(void)
{
    memset(&front, 0, sizeof(front));
    switch_count = 0;
    struct stat st;
    if (stat(STORE_SWITCHES_FILE, &st) != 0 || st.st_size < sizeof(store_switch_t)) {
        return;
    }
    switch_count = st.st_size / sizeof(store_switch_t);
    FILE *f = fopen(STORE_SWITCHES_FILE, "rb");
    if (f) {
        fseek(f, (long)(switch_count - 1) * sizeof(store_switch_t), SEEK_SET);
        fread(&front, sizeof(front), 1, f);
        fclose(f);
    }
}

/* ---------- public ---------- */

void store_init(void)
{
    lock = xSemaphoreCreateMutex();

    const esp_vfs_fat_mount_config_t cfg = {
        .format_if_mount_failed = true, /* first start: create the filesystem */
        .max_files = 3,                 /* one shared sector buffer (CONFIG_FATFS_PER_FILE_CACHE off) */
        .allocation_unit_size = 4096,
    };
    wl_handle_t wl;
    ESP_ERROR_CHECK(esp_vfs_fat_spiflash_mount_rw_wl("/data", "storage", &cfg, &wl));
    mkdir(CARDS_DIR, 0755);

    char *json = read_file(MEMBERS_FILE);
    if (json) {
        int n = members_from_json(json, system_name, sizeof(system_name), &members);
        member_count = n < 0 ? 0 : n;
        free(json);
    }
    load_front();
    ESP_LOGI(TAG, "%d members, %lu switches", member_count, (unsigned long)switch_count);
}

esp_err_t store_set_members_json(const char *json)
{
    member_t *parsed = NULL;
    char system[sizeof(system_name)];
    int n = members_from_json(json, system, sizeof(system), &parsed);
    if (n < 0) {
        return ESP_ERR_INVALID_ARG;
    }

    xSemaphoreTake(lock, portMAX_DELAY);
    member_t *old = members;
    members = parsed;
    member_count = n;
    strlcpy(system_name, system, sizeof(system_name));
    front_changed = true;
    char *out = members_to_json();
    xSemaphoreGive(lock);
    free(old);

    esp_err_t err = ESP_FAIL;
    FILE *f = fopen(MEMBERS_FILE, "wb");
    if (f && out) {
        err = fwrite(out, 1, strlen(out), f) == strlen(out) ? ESP_OK : ESP_FAIL;
    }
    if (f) {
        fclose(f);
    }
    free(out);
    ESP_LOGI(TAG, "saved %d members", n);
    return err;
}

char *store_get_state_json(void)
{
    xSemaphoreTake(lock, portMAX_DELAY);
    char *members_json = members_to_json();
    cJSON *root = cJSON_Parse(members_json);
    free(members_json);
    cJSON *list = cJSON_AddArrayToObject(root, "front");
    for (int i = 0; i < STORE_FRONT_MAX && front.time; i++) {
        if (front.members[i] != STORE_NO_MEMBER) {
            cJSON_AddItemToArray(list, cJSON_CreateNumber(front.members[i]));
        }
    }
    cJSON_AddNumberToObject(root, "front_since", front.time);
    cJSON_AddNumberToObject(root, "switches", switch_count);
    cJSON_AddNumberToObject(root, "now", (double)time(NULL));
    xSemaphoreGive(lock);

    char *json = cJSON_PrintUnformatted(root);
    cJSON_Delete(root);
    return json;
}

esp_err_t store_switches_begin(void)
{
    upload = fopen(SWITCHES_TMP_FILE, "wb");
    upload_bytes = 0;
    return upload ? ESP_OK : ESP_FAIL;
}

esp_err_t store_switches_write(const void *data, size_t len)
{
    upload_bytes += len;
    if (!upload || upload_bytes > MAX_SWITCH_BYTES) {
        return ESP_ERR_INVALID_SIZE;
    }
    return fwrite(data, 1, len, upload) == len ? ESP_OK : ESP_FAIL;
}

esp_err_t store_switches_end(bool ok)
{
    if (upload) {
        fclose(upload);
        upload = NULL;
    }
    if (!ok || upload_bytes % sizeof(store_switch_t) != 0) {
        unlink(SWITCHES_TMP_FILE);
        return ESP_ERR_INVALID_SIZE;
    }

    xSemaphoreTake(lock, portMAX_DELAY);
    unlink(STORE_SWITCHES_FILE);        /* FAT can't rename over an existing file */
    int err = rename(SWITCHES_TMP_FILE, STORE_SWITCHES_FILE);
    load_front();
    front_changed = true;
    xSemaphoreGive(lock);
    ESP_LOGI(TAG, "saved %lu switches", (unsigned long)switch_count);
    return err == 0 ? ESP_OK : ESP_FAIL;
}

esp_err_t store_add_switch(const uint16_t *list, int count)
{
    store_switch_t sw = { .time = (uint32_t)time(NULL) };
    for (int i = 0; i < STORE_FRONT_MAX; i++) {
        sw.members[i] = i < count ? list[i] : STORE_NO_MEMBER;
    }

    xSemaphoreTake(lock, portMAX_DELAY);
    for (int i = 0; i < count && i < STORE_FRONT_MAX; i++) {
        if (list[i] >= member_count) {
            xSemaphoreGive(lock);
            return ESP_ERR_INVALID_ARG;
        }
    }
    FILE *f = fopen(STORE_SWITCHES_FILE, "ab");
    esp_err_t err = f && fwrite(&sw, sizeof(sw), 1, f) == 1 ? ESP_OK : ESP_FAIL;
    if (f) {
        fclose(f);
    }
    if (err == ESP_OK) {
        front = sw;
        switch_count++;
        front_changed = true;
    }
    xSemaphoreGive(lock);
    return err;
}

static bool valid_id(const char *id);

/*
 * Remove member `index`. Switches refer to members by index, so the history
 * file is rewritten: the member is taken out of every switch and later
 * indexes move down by one. A switch that only had this member becomes
 * "nobody fronting", so the other members' times stay right.
 */
esp_err_t store_delete_member(int index)
{
    xSemaphoreTake(lock, portMAX_DELAY);
    if (index < 0 || index >= member_count) {
        xSemaphoreGive(lock);
        return ESP_ERR_INVALID_ARG;
    }

    esp_err_t err = ESP_OK;
    FILE *in = fopen(STORE_SWITCHES_FILE, "rb");
    if (in) {
        FILE *out = fopen(SWITCHES_TMP_FILE, "wb");
        /* In blocks: one record at a time takes many seconds on flash */
        enum { BLOCK = 256 };
        store_switch_t *buf = malloc(BLOCK * sizeof(store_switch_t));
        size_t got;
        if (!out || !buf) {
            err = ESP_FAIL;
        }
        while (err == ESP_OK && (got = fread(buf, sizeof(store_switch_t), BLOCK, in)) > 0) {
            for (size_t r = 0; r < got; r++) {
                store_switch_t *sw = &buf[r];
                int n = 0;
                for (int k = 0; k < STORE_FRONT_MAX; k++) {
                    uint16_t m = sw->members[k];
                    if (m != STORE_NO_MEMBER && m != index) {
                        sw->members[n++] = m > index ? m - 1 : m;
                    }
                }
                for (; n < STORE_FRONT_MAX; n++) {
                    sw->members[n] = STORE_NO_MEMBER;
                }
            }
            if (fwrite(buf, sizeof(store_switch_t), got, out) != got) {
                err = ESP_FAIL;
            }
        }
        free(buf);
        fclose(in);
        if (out) {
            fclose(out);
        }
        if (err == ESP_OK) {
            unlink(STORE_SWITCHES_FILE);
            err = rename(SWITCHES_TMP_FILE, STORE_SWITCHES_FILE) == 0 ? ESP_OK : ESP_FAIL;
        } else {
            unlink(SWITCHES_TMP_FILE);
        }
    }
    if (err != ESP_OK) {
        xSemaphoreGive(lock);
        return err;
    }

    char card[48] = "";
    if (valid_id(members[index].id)) {
        snprintf(card, sizeof(card), CARDS_DIR "/%s.bin", members[index].id);
    }
    memmove(&members[index], &members[index + 1], sizeof(member_t) * (member_count - index - 1));
    member_count--;
    load_front();
    front_changed = true;
    char *json = members_to_json();
    xSemaphoreGive(lock);

    if (card[0]) {
        unlink(card);
    }
    FILE *f = fopen(MEMBERS_FILE, "wb");
    if (!f || !json || fwrite(json, 1, strlen(json), f) != strlen(json)) {
        err = ESP_FAIL;
    }
    if (f) {
        fclose(f);
    }
    free(json);
    ESP_LOGI(TAG, "deleted member %d, %d left", index, member_count);
    return err;
}

/* Button order: most messages first, then by name. True if a comes before b. */
static bool button_before(const member_t *a, const member_t *b)
{
    if (a->messages != b->messages) {
        return a->messages > b->messages;
    }
    return strcasecmp(a->name, b->name) < 0;
}

int store_step_button_member(int direction, char *name, size_t name_size)
{
    xSemaphoreTake(lock, portMAX_DELAY);
    bool any = false;
    for (int i = 0; i < member_count; i++) {
        any |= members[i].on_button;
    }
    /* Candidates: the shortlist, or everyone if it's empty, in button order.
     * Forward: the closest candidate after the current fronter; backward: the
     * closest before it. "before(a, b)" flips with the direction. */
    bool back = direction < 0;
    #define BEFORE(a, b) (back ? button_before(b, a) : button_before(a, b))
    uint16_t cur = front.time ? front.members[0] : STORE_NO_MEMBER;
    int next = -1, first = -1;
    for (int i = 0; i < member_count; i++) {
        if (any && !members[i].on_button) {
            continue;
        }
        if (first < 0 || BEFORE(&members[i], &members[first])) {
            first = i;
        }
        bool after_current = cur >= member_count || BEFORE(&members[cur], &members[i]);
        if (after_current && i != cur && (next < 0 || BEFORE(&members[i], &members[next]))) {
            next = i;
        }
    }
    #undef BEFORE
    if (next < 0) {
        next = first;                   /* past the end: wrap around */
    }
    if (next >= 0) {
        strlcpy(name, members[next].name, name_size);
    }
    xSemaphoreGive(lock);
    return next;
}

/* PluralKit ids are short and alphanumeric; anything else could escape the folder */
static bool valid_id(const char *id)
{
    size_t n = strlen(id);
    if (n == 0 || n > 10) {
        return false;
    }
    for (size_t i = 0; i < n; i++) {
        char c = id[i];
        if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))) {
            return false;
        }
    }
    return true;
}

esp_err_t store_card_begin(const char *id)
{
    if (!valid_id(id)) {
        return ESP_ERR_INVALID_ARG;
    }
    snprintf(card_path, sizeof(card_path), CARDS_DIR "/%s.bin", id);
    snprintf(card_tmp_path, sizeof(card_tmp_path), CARDS_DIR "/%s.tmp", id);
    upload = fopen(card_tmp_path, "wb");
    upload_bytes = 0;
    return upload ? ESP_OK : ESP_FAIL;
}

esp_err_t store_card_write(const void *data, size_t len)
{
    upload_bytes += len;
    if (!upload || upload_bytes > MAX_CARD_BYTES) {
        return ESP_ERR_INVALID_SIZE;
    }
    return fwrite(data, 1, len, upload) == len ? ESP_OK : ESP_FAIL;
}

esp_err_t store_card_end(bool ok)
{
    if (upload) {
        fclose(upload);
        upload = NULL;
    }
    if (!ok || upload_bytes < sizeof(store_card_header_t)) {
        unlink(card_tmp_path);
        return ESP_ERR_INVALID_SIZE;
    }
    xSemaphoreTake(lock, portMAX_DELAY);
    unlink(card_path);
    int err = rename(card_tmp_path, card_path);
    front_changed = true;               /* the current fronter's card may have changed */
    xSemaphoreGive(lock);
    return err == 0 ? ESP_OK : ESP_FAIL;
}

void *store_load_front_card(size_t *size)
{
    char path[48] = "";
    xSemaphoreTake(lock, portMAX_DELAY);
    uint16_t first = front.time ? front.members[0] : STORE_NO_MEMBER;
    if (first < member_count && valid_id(members[first].id)) {
        snprintf(path, sizeof(path), CARDS_DIR "/%s.bin", members[first].id);
    }
    xSemaphoreGive(lock);
    if (!path[0]) {
        return NULL;
    }

    FILE *f = fopen(path, "rb");
    if (!f) {
        return NULL;
    }
    fseek(f, 0, SEEK_END);
    long len = ftell(f);
    fseek(f, 0, SEEK_SET);
    void *buf = len >= sizeof(store_card_header_t) && len <= MAX_CARD_BYTES ? malloc(len) : NULL;
    if (buf && fread(buf, 1, len, f) != len) {
        free(buf);
        buf = NULL;
    }
    fclose(f);
    *size = buf ? len : 0;
    return buf;
}

bool store_get_front_card(char *text, size_t text_size, uint32_t *color, bool *changed)
{
    xSemaphoreTake(lock, portMAX_DELAY);
    *changed = front_changed;
    front_changed = false;

    uint16_t first = front.time ? front.members[0] : STORE_NO_MEMBER;
    bool found = first < member_count;
    if (found) {
        const member_t *m = &members[first];
        strlcpy(text, m->card[0] ? m->card : m->name, text_size);
        *color = m->color;
    } else {
        strlcpy(text, system_name, text_size);
        *color = 0x468DC3;
    }
    xSemaphoreGive(lock);
    return found;
}
