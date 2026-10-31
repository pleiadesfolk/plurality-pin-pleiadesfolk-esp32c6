/*
 * Members and front history in the "storage" partition (FAT with wear
 * levelling, mounted at /data).
 *
 *   /data/members.json   system name, members and the "nobody fronting" card
 *                        (written by the dashboard)
 *   /data/switches.bin   store_switch_t records, oldest first; the last one is
 *                        the current front
 *   /data/cards/<id>.bin   namecard text picture per member (store_card_header_t)
 *   /data/cards/<id>-l.bin text picture for the "image with name" screen
 *   <images>/<id>-f.bin    "image" mode photo, an LVGL .bin image (RGB565)
 *   <images>/<id>-s.bin    "image with name" circle, an LVGL .bin image (RGB565)
 * Photos go to a slot in the "photos" flash partition (photos.c), which can
 * be drawn straight from flash. Only when all slots are taken do they go to
 * <images>: /sdcard/pin on the SD card when one is inserted, otherwise
 * /data/img - slow to draw (0.5-5 s).
 *
 * The member list lives in RAM too (small: ~150 bytes per member). Front
 * history stays in flash; only its last record is kept in RAM.
 */

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <strings.h>
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "esp_log.h"
#include "esp_system.h"
#include "esp_heap_caps.h"
#include "esp_vfs_fat.h"
#include "cJSON.h"
#include "photos.h"
#include "storage_info.h"
#include "store.h"

static const char *TAG = "store";

#define MEMBERS_FILE        "/data/members.json"
#define MEMBERS_TMP_FILE    "/data/members.tmp"
#define SWITCHES_TMP_FILE   "/data/switches.tmp"
#define MAX_MEMBERS         128
#define MAX_SWITCH_BYTES    (2 * 1024 * 1024)
#define CARDS_DIR           "/data/cards"
#define SD_IMAGES_DIR       "/sdcard/pin"
#define DATA_IMAGES_DIR     "/data/img"
#define MAX_CARD_BYTES      (256 * 1024) /* largest picture upload (a 456x280 photo is 250 KB) */

typedef struct {
    char id[12];                        /* PluralKit member id */
    char name[48];
    char card[128];                     /* namecard text */
    uint32_t color;                     /* namecard colour, 0xRRGGBB */
    int32_t pk_color;                   /* colour in PluralKit, 0xRRGGBB; -1 = unknown */
    bool on_button;                     /* in the BOOT button's Quick Switch list */
    uint32_t messages;                  /* PluralKit message count: the button's order */
    uint8_t mode;                       /* store_mode_t */
    char label[64];                     /* text on the "image with name" screen */
    char avatar[128];                   /* PluralKit avatar URL (the dashboard fetches it) */
    char style[24];                     /* text style, for the dashboard: "font,weight,size,align" */
    char grad[64];                      /* background: "dir|RRGGBB,RRGGBB,...|animate" (fronter.c) */
    bool fast;                          /* photos in a flash slot (photos.c), not on the SD card */
} member_t;

static const char *const mode_names[] = { "card", "image", "image_text" };

static SemaphoreHandle_t lock;
static char system_name[64];
static member_t *members;               /* member_count entries */
static int member_count;
/* What shows while nobody fronts: a member-like card the dashboard sets up
 * (id STORE_NOBODY_ID); id "" = not set up, show the system name */
static member_t nobody;
static store_switch_t front;            /* last switch; time 0 = none yet */
static uint32_t switch_count;
static bool front_changed = true;       /* tell the UI on first poll */

static FILE *upload;                    /* one upload at a time (the web server is single-threaded) */
static bool upload_to_slot;             /* this upload goes to photos.c instead of a file */
static store_picture_t upload_kind;       /* what's being uploaded, and whose */
static char upload_member[12];
static size_t upload_bytes;
static char card_path[64], card_tmp_path[64];

/* ---------- helpers ---------- */

static void copy_string(char *dst, size_t size, const cJSON *item)
{
    const char *s = cJSON_IsString(item) ? item->valuestring : "";
    strlcpy(dst, s, size);
}

static void member_from_json(const cJSON *item, member_t *m)
{
    copy_string(m->id, sizeof(m->id), cJSON_GetObjectItem(item, "id"));
    copy_string(m->name, sizeof(m->name), cJSON_GetObjectItem(item, "name"));
    copy_string(m->card, sizeof(m->card), cJSON_GetObjectItem(item, "card"));
    m->on_button = cJSON_IsTrue(cJSON_GetObjectItem(item, "button"));
    m->fast = cJSON_IsTrue(cJSON_GetObjectItem(item, "fast"));
    copy_string(m->label, sizeof(m->label), cJSON_GetObjectItem(item, "label"));
    copy_string(m->avatar, sizeof(m->avatar), cJSON_GetObjectItem(item, "avatar"));
    copy_string(m->style, sizeof(m->style), cJSON_GetObjectItem(item, "style"));
    copy_string(m->grad, sizeof(m->grad), cJSON_GetObjectItem(item, "grad"));
    const cJSON *mode = cJSON_GetObjectItem(item, "mode");
    m->mode = STORE_MODE_CARD;
    for (int k = 0; k < 3 && cJSON_IsString(mode); k++) {
        if (strcmp(mode->valuestring, mode_names[k]) == 0) {
            m->mode = k;
        }
    }
    const cJSON *messages = cJSON_GetObjectItem(item, "messages");
    m->messages = cJSON_IsNumber(messages) && messages->valuedouble > 0 ? (uint32_t)messages->valuedouble : 0;
    const cJSON *color = cJSON_GetObjectItem(item, "color");
    m->color = cJSON_IsString(color) ? strtoul(color->valuestring, NULL, 16) : 0x468DC3;
    const cJSON *pk_color = cJSON_GetObjectItem(item, "pk_color");
    m->pk_color = cJSON_IsString(pk_color) && pk_color->valuestring[0] ? (int32_t)strtoul(pk_color->valuestring, NULL, 16) : -1;
}

/* Parse the dashboard's members JSON into a new array (*out, free() it); returns
 * count or -1. *has_nobody: whether it had a "nobody" card (then in *nobody_out). */
static int members_from_json(const char *json, char *system, size_t system_size, member_t **out,
                             member_t *nobody_out, bool *has_nobody)
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
    const cJSON *none = cJSON_GetObjectItem(root, "nobody");
    *has_nobody = cJSON_IsObject(none);
    memset(nobody_out, 0, sizeof(*nobody_out));
    if (*has_nobody) {
        member_from_json(none, nobody_out);
        strlcpy(nobody_out->id, STORE_NOBODY_ID, sizeof(nobody_out->id));
        nobody_out->on_button = false;
    }

    *out = calloc(cJSON_GetArraySize(list) + 1, sizeof(member_t));
    if (!*out) {
        cJSON_Delete(root);
        return -1;
    }
    int n = 0;
    const cJSON *item;
    cJSON_ArrayForEach(item, list) {
        member_from_json(item, &(*out)[n++]);
    }
    cJSON_Delete(root);
    return n;
}

static cJSON *member_to_json(const member_t *m)
{
    cJSON *item = cJSON_CreateObject();
    char color[8];
    snprintf(color, sizeof(color), "%06lX", (unsigned long)(m->color & 0xFFFFFF));
    cJSON_AddStringToObject(item, "id", m->id);
    cJSON_AddStringToObject(item, "name", m->name);
    cJSON_AddStringToObject(item, "card", m->card);
    cJSON_AddBoolToObject(item, "button", m->on_button);
    cJSON_AddBoolToObject(item, "fast", m->fast);
    cJSON_AddNumberToObject(item, "messages", m->messages);
    cJSON_AddStringToObject(item, "mode", mode_names[m->mode]);
    cJSON_AddStringToObject(item, "label", m->label);
    cJSON_AddStringToObject(item, "avatar", m->avatar);
    cJSON_AddStringToObject(item, "style", m->style);
    cJSON_AddStringToObject(item, "grad", m->grad);
    cJSON_AddStringToObject(item, "color", color);
    if (m->pk_color >= 0) {
        snprintf(color, sizeof(color), "%06lX", (unsigned long)(m->pk_color & 0xFFFFFF));
        cJSON_AddStringToObject(item, "pk_color", color);
    }
    return item;
}

/* Hand `item` to emit as JSON text (frees item) */
static bool emit_json(cJSON *item, store_emit_t emit, void *ctx)
{
    char *text = item ? cJSON_PrintUnformatted(item) : NULL;
    cJSON_Delete(item);
    bool ok = text && emit(text, strlen(text), ctx);
    free(text);
    return ok;
}

/*
 * The members as JSON, {"system":"...","members":[...],"nobody":{...} without the closing
 * brace, one member at a time: printing it all at once needs one 20+ KB
 * block of memory, which the pin often doesn't have in one piece.
 * Caller holds the lock.
 */
static bool emit_members(store_emit_t emit, void *ctx)
{
    bool ok = emit("{\"system\":", 10, ctx) && emit_json(cJSON_CreateString(system_name), emit, ctx)
              && emit(",\"members\":[", 12, ctx);
    for (int i = 0; ok && i < member_count; i++) {
        ok = (i == 0 || emit(",", 1, ctx)) && emit_json(member_to_json(&members[i]), emit, ctx);
    }
    ok = ok && emit("]", 1, ctx);
    if (ok && nobody.id[0]) {
        ok = emit(",\"nobody\":", 10, ctx) && emit_json(member_to_json(&nobody), emit, ctx);
    }
    return ok;
}

static bool emit_to_file(const char *text, size_t len, void *f)
{
    return fwrite(text, 1, len, f) == len;
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

/* Save the members (caller holds the lock): a new file, then swapped in, so
 * a failed write (full storage, out of memory) can't lose them */
static esp_err_t save_members_file(void)
{
    FILE *f = fopen(MEMBERS_TMP_FILE, "wb");
    esp_err_t err = ESP_FAIL;
    if (f) {
        setvbuf(f, NULL, _IOFBF, 1024);
        err = emit_members(emit_to_file, f) && emit_to_file("}", 1, f) ? ESP_OK : ESP_FAIL;
        if (fclose(f) != 0) {
            err = ESP_FAIL;
        }
    }
    int why = errno;
    if (err == ESP_OK) {
        unlink(MEMBERS_FILE);
        err = rename(MEMBERS_TMP_FILE, MEMBERS_FILE) == 0 ? ESP_OK : ESP_FAIL;
    } else {
        unlink(MEMBERS_TMP_FILE);
    }
    if (err == ESP_OK) {
        ESP_LOGI(TAG, "saved %d members", member_count);
    } else {
        ESP_LOGE(TAG, "couldn't save %d members (errno %d, free heap %u, largest block %u)", member_count,
                 why, (unsigned)esp_get_free_heap_size(), (unsigned)heap_caps_get_largest_free_block(MALLOC_CAP_8BIT));
    }
    return err;
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
        bool has_nobody;
        int n = members_from_json(json, system_name, sizeof(system_name), &members, &nobody, &has_nobody);
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
    member_t *new_nobody = malloc(sizeof(member_t)), *old_nobody = malloc(sizeof(member_t));
    bool has_nobody;
    int n = new_nobody && old_nobody
            ? members_from_json(json, system, sizeof(system), &parsed, new_nobody, &has_nobody) : -1;
    if (n < 0) {
        free(new_nobody);
        free(old_nobody);
        return ESP_ERR_INVALID_ARG;
    }

    xSemaphoreTake(lock, portMAX_DELAY);
    member_t *old = members;
    int old_count = member_count;
    char old_system[sizeof(system_name)];
    strlcpy(old_system, system_name, sizeof(old_system));
    *old_nobody = nobody;
    members = parsed;
    member_count = n;
    strlcpy(system_name, system, sizeof(system_name));
    if (has_nobody) {                   /* without "nobody", keep the one there is */
        nobody = *new_nobody;
    }
    esp_err_t err = save_members_file();
    if (err != ESP_OK) {                /* keep what's saved */
        members = old;
        member_count = old_count;
        strlcpy(system_name, old_system, sizeof(system_name));
        nobody = *old_nobody;
        old = parsed;
    }
    front_changed = true;
    xSemaphoreGive(lock);
    free(old);
    free(new_nobody);
    free(old_nobody);
    return err;
}

bool store_send_state(store_emit_t emit, void *ctx, const char *extra)
{
    xSemaphoreTake(lock, portMAX_DELAY);
    bool ok = emit_members(emit, ctx);
    char text[160];
    int n = snprintf(text, sizeof(text), ",\"front\":[");
    for (int i = 0, first = 1; i < STORE_FRONT_MAX && front.time; i++) {
        if (front.members[i] != STORE_NO_MEMBER) {
            n += snprintf(text + n, sizeof(text) - n, "%s%u", first ? "" : ",", front.members[i]);
            first = 0;
        }
    }
    snprintf(text + n, sizeof(text) - n, "],\"front_since\":%lu,\"switches\":%lu,\"now\":%lld%s}",
             (unsigned long)front.time, (unsigned long)switch_count, (long long)time(NULL), extra);
    xSemaphoreGive(lock);
    return ok && emit(text, strlen(text), ctx);
}

char *store_photos_json(void)
{
    xSemaphoreTake(lock, portMAX_DELAY);
    int n = member_count;
    char (*ids)[12] = malloc((n + 1) * sizeof(*ids));
    for (int i = 0; ids && i < n; i++) {
        strlcpy(ids[i], members[i].id, sizeof(ids[i]));
    }
    if (ids && nobody.id[0]) {
        strlcpy(ids[n++], nobody.id, sizeof(ids[0]));
    }
    xSemaphoreGive(lock);
    if (!ids) {
        return NULL;
    }
    cJSON *root = cJSON_CreateObject();
    cJSON_AddNumberToObject(root, "free_slots", photos_free_slots());
    cJSON_AddBoolToObject(root, "sd_card", storage_info_sd_ready());
    cJSON *list = cJSON_AddObjectToObject(root, "photos");
    for (int i = 0; i < n; i++) {
        char have[4] = "", path[64];
        if (photos_has(ids[i], PHOTO_FULL)) {
            strcat(have, "F");
        } else if (store_picture_file(ids[i], STORE_PICTURE_FULL, path, sizeof(path))) {
            strcat(have, "f");
        }
        if (photos_has(ids[i], PHOTO_SIDE)) {
            strcat(have, "S");
        } else if (store_picture_file(ids[i], STORE_PICTURE_SIDE, path, sizeof(path))) {
            strcat(have, "s");
        }
        if (have[0]) {
            cJSON_AddStringToObject(list, ids[i], have);
        }
    }
    free(ids);
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
    return store_add_switch_at((uint32_t)time(NULL), list, count);
}

uint32_t store_front_time(void)
{
    xSemaphoreTake(lock, portMAX_DELAY);
    uint32_t t = front.time;
    xSemaphoreGive(lock);
    return t;
}

bool store_front_is(const uint16_t *list, int count)
{
    xSemaphoreTake(lock, portMAX_DELAY);
    int now = 0, found = 0;
    for (int i = 0; i < STORE_FRONT_MAX; i++) {
        if (front.members[i] == STORE_NO_MEMBER) {
            continue;
        }
        now++;
        for (int k = 0; k < count; k++) {
            found += list[k] == front.members[i];
        }
    }
    xSemaphoreGive(lock);
    return now == count && found == count;
}

int store_member_index(const char *id)
{
    xSemaphoreTake(lock, portMAX_DELAY);
    int index = -1;
    for (int i = 0; i < member_count && index < 0; i++) {
        if (strcmp(members[i].id, id) == 0) {
            index = i;
        }
    }
    xSemaphoreGive(lock);
    return index;
}

esp_err_t store_add_switch_at(uint32_t time, const uint16_t *list, int count)
{
    store_switch_t sw = { .time = time };
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
static void delete_pictures(const char *id);

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

    char id[sizeof(members[index].id)] = "";
    if (valid_id(members[index].id)) {
        strlcpy(id, members[index].id, sizeof(id));
    }
    memmove(&members[index], &members[index + 1], sizeof(member_t) * (member_count - index - 1));
    member_count--;
    load_front();
    front_changed = true;
    err = save_members_file();
    xSemaphoreGive(lock);

    if (id[0]) {
        delete_pictures(id);
    }
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

/* Where member `id`'s picture of `kind` lives. Photos go to the SD card when
 * one is inserted. For reading, an existing file on the SD card wins. */
static void picture_path(const char *id, store_picture_t kind, bool writing, char *out, size_t size)
{
    static const char *const suffix[] = { ".bin", "-l.bin", "-f.bin", "-s.bin" };
    if (kind == STORE_PICTURE_CARD || kind == STORE_PICTURE_LABEL) {
        snprintf(out, size, CARDS_DIR "/%s%s", id, suffix[kind]);
        return;
    }
    struct stat st;
    snprintf(out, size, SD_IMAGES_DIR "/%s%s", id, suffix[kind]);
    if (storage_info_sd_ready() && (writing || stat(out, &st) == 0)) {
        if (writing) {
            mkdir(SD_IMAGES_DIR, 0755);
        }
        return;
    }
    snprintf(out, size, DATA_IMAGES_DIR "/%s%s", id, suffix[kind]);
    if (writing) {
        mkdir(DATA_IMAGES_DIR, 0755);
    }
}

static bool member_is_fast(const char *id)
{
    bool fast = false;
    xSemaphoreTake(lock, portMAX_DELAY);
    for (int i = 0; i < member_count; i++) {
        if (strcmp(members[i].id, id) == 0) {
            fast = members[i].fast;
        }
    }
    if (strcmp(nobody.id, id) == 0 && id[0]) {
        fast = nobody.fast;
    }
    xSemaphoreGive(lock);
    return fast;
}

/* Delete a member's photo files of `kind` (SD card and pin storage) */
static void delete_photo_files(const char *id, store_picture_t kind)
{
    static const char *const suffix[] = { "", "", "-f.bin", "-s.bin" };
    char path[64];
    snprintf(path, sizeof(path), SD_IMAGES_DIR "/%s%s", id, suffix[kind]);
    unlink(path);
    snprintf(path, sizeof(path), DATA_IMAGES_DIR "/%s%s", id, suffix[kind]);
    unlink(path);
}

esp_err_t store_picture_begin(const char *id, store_picture_t kind)
{
    if (!valid_id(id) || kind < 0 || kind > STORE_PICTURE_SIDE) {
        return ESP_ERR_INVALID_ARG;
    }
    upload_kind = kind;
    strlcpy(upload_member, id, sizeof(upload_member));
    /* Photos of "fast" members go to a flash slot, everyone else's to the SD card */
    upload_to_slot = kind >= STORE_PICTURE_FULL && member_is_fast(id);
    if (upload_to_slot) {
        return photos_begin(id, kind == STORE_PICTURE_SIDE ? PHOTO_SIDE : PHOTO_FULL) == ESP_OK
               ? ESP_OK : ESP_ERR_NO_MEM;
    }
    picture_path(id, kind, true, card_path, sizeof(card_path));
    snprintf(card_tmp_path, sizeof(card_tmp_path), "%.*s.tmp", (int)strlen(card_path) - 4, card_path);
    upload = fopen(card_tmp_path, "wb");
    if (upload) {
        setvbuf(upload, NULL, _IOFBF, 8192);    /* the default 128 bytes makes SD writes very slow */
    }
    upload_bytes = 0;
    return upload ? ESP_OK : ESP_FAIL;
}

esp_err_t store_picture_write(const void *data, size_t len)
{
    if (upload_to_slot) {
        return photos_write(data, len);
    }
    upload_bytes += len;
    if (!upload || upload_bytes > MAX_CARD_BYTES) {
        return ESP_ERR_INVALID_SIZE;
    }
    return fwrite(data, 1, len, upload) == len ? ESP_OK : ESP_FAIL;
}

esp_err_t store_picture_end(bool ok)
{
    if (upload_to_slot) {
        upload_to_slot = false;
        esp_err_t err = photos_end(ok);
        if (err == ESP_OK) {            /* moved from the SD card: drop the old copy */
            delete_photo_files(upload_member, upload_kind);
            photos_unstage(upload_member);
        }
        xSemaphoreTake(lock, portMAX_DELAY);
        front_changed = true;
        xSemaphoreGive(lock);
        return err;
    }
    if (upload) {
        fclose(upload);
        upload = NULL;
    }
    if (!ok || upload_bytes < sizeof(store_card_header_t)) {
        unlink(card_tmp_path);
        return ESP_ERR_INVALID_SIZE;
    }
    if (upload_kind >= STORE_PICTURE_FULL) {
        /* moved out of a flash slot, or a new photo: the old copies are stale */
        photos_delete_kind(upload_member, upload_kind == STORE_PICTURE_SIDE ? PHOTO_SIDE : PHOTO_FULL);
        photos_unstage(upload_member);
    }
    xSemaphoreTake(lock, portMAX_DELAY);
    unlink(card_path);
    int err = rename(card_tmp_path, card_path);
    front_changed = true;               /* the current fronter's pictures may have changed */
    xSemaphoreGive(lock);
    return err == 0 ? ESP_OK : ESP_FAIL;
}

/* Delete all of a member's pictures, wherever they are (caller passes a valid id) */
static void delete_pictures(const char *id)
{
    photos_delete(id);
    photos_unstage(id);
    char path[64];
    for (store_picture_t kind = STORE_PICTURE_CARD; kind <= STORE_PICTURE_SIDE; kind++) {
        picture_path(id, kind, false, path, sizeof(path));
        unlink(path);
        if (kind >= STORE_PICTURE_FULL) {   /* a copy may also be in the other place */
            char other[64];
            snprintf(other, sizeof(other), "%s%s", strncmp(path, SD_IMAGES_DIR, strlen(SD_IMAGES_DIR)) == 0
                     ? DATA_IMAGES_DIR : SD_IMAGES_DIR, strrchr(path, '/'));
            unlink(other);
        }
    }
}

/* Who's shown: the first fronter, the "nobody fronting" card, or NULL for
 * the plain system name (caller holds the lock) */
static const member_t *front_member(void)
{
    uint16_t first = front.time ? front.members[0] : STORE_NO_MEMBER;
    return first < member_count ? &members[first] : nobody.id[0] ? &nobody : NULL;
}

/* Current fronter's id, or "" (caller holds the lock) */
static const char *front_id(void)
{
    const member_t *m = front_member();
    return m && valid_id(m->id) ? m->id : "";
}

bool store_picture_file(const char *id, store_picture_t kind, char *path, size_t size)
{
    if (!valid_id(id) || kind < 0 || kind > STORE_PICTURE_SIDE) {
        return false;
    }
    picture_path(id, kind, false, path, size);
    struct stat st;
    return stat(path, &st) == 0;
}

bool store_front_picture_file(store_picture_t kind, char *path, size_t size)
{
    char id[sizeof(((member_t *)0)->id)];
    xSemaphoreTake(lock, portMAX_DELAY);
    strlcpy(id, front_id(), sizeof(id));
    xSemaphoreGive(lock);
    return id[0] && store_picture_file(id, kind, path, size);
}

bool store_front_id(char *id, size_t size)
{
    xSemaphoreTake(lock, portMAX_DELAY);
    strlcpy(id, front_id(), size);
    xSemaphoreGive(lock);
    return id[0] != 0;
}

bool store_front_image_src(store_picture_t kind, char *src, size_t size)
{
    char path[64] = "";
    xSemaphoreTake(lock, portMAX_DELAY);
    if (front_id()[0]) {
        picture_path(front_id(), kind, false, path, sizeof(path));
    }
    xSemaphoreGive(lock);
    struct stat st;
    if (!path[0] || stat(path, &st) != 0) {
        return false;
    }
    snprintf(src, size, "A:%s", path);  /* LVGL's file driver (drive A = the whole filesystem) */
    return true;
}

store_mode_t store_front_mode(void)
{
    xSemaphoreTake(lock, portMAX_DELAY);
    const member_t *m = front_member();
    store_mode_t mode = m ? m->mode : STORE_MODE_CARD;
    xSemaphoreGive(lock);
    return mode;
}

void store_front_grad(char *text, size_t size)
{
    xSemaphoreTake(lock, portMAX_DELAY);
    const member_t *m = front_member();
    strlcpy(text, m ? m->grad : "", size);
    xSemaphoreGive(lock);
}

void store_front_label(char *text, size_t size)
{
    xSemaphoreTake(lock, portMAX_DELAY);
    const member_t *m = front_member();
    strlcpy(text, !m ? system_name : m->label[0] ? m->label : m->name, size);
    xSemaphoreGive(lock);
}

bool store_get_front_card(char *text, size_t text_size, uint32_t *color, bool *changed)
{
    xSemaphoreTake(lock, portMAX_DELAY);
    *changed = front_changed;
    front_changed = false;

    uint16_t first = front.time ? front.members[0] : STORE_NO_MEMBER;
    bool found = first < member_count;
    const member_t *m = front_member();
    if (m) {
        strlcpy(text, m->card[0] ? m->card : m == &nobody ? system_name : m->name, text_size);
        *color = m->color;
    } else {
        strlcpy(text, system_name, text_size);
        *color = 0x468DC3;
    }
    xSemaphoreGive(lock);
    return found;
}
