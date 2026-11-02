/*
 * QR code on the connect screen (connect.xml, "Open the dashboard"):
 * http://<the pin's address>/. The address changes with the network (home
 * Wi-Fi, a phone's hotspot), so it's checked every second and the code is
 * redrawn when it changes. The phone scanning it must be on the same network.
 *
 * While the pin has no saved network it runs its own setup network (wifi.h):
 * then the code joins a phone to it (WIFI:...; the camera app offers "Join"),
 * with its name and password written beside it in case, and once a phone has
 * joined, the code opens the dashboard there (WIFI_SETUP_URL).
 */

#include <string.h>
#include "connect.h"
#include "wifi.h"

#define QR_SIZE 150                     /* inside the 170 px white square: 10 px quiet zone */

typedef struct {
    lv_obj_t *qr;
    lv_obj_t *note;                     /* shown instead of the code while the pin is offline */
    lv_obj_t *heading;                  /* the designed text, changed for the setup network */
    lv_obj_t *details;                  /* setup network: how to join it */
    lv_timer_t *timer;
    char designed[64];                  /* the heading's text as designed */
    char shown[128];                    /* what's encoded now ("" = note shown) */
} connect_t;

static connect_t cn;

static void update(lv_timer_t *timer)
{
    char ip[16] = "", code[128] = "", ssid[33], password[65];
    const char *heading = cn.designed, *details = NULL;
    char text[128];
    if (wifi_get_ip(ip, sizeof(ip))) {
        snprintf(code, sizeof(code), "http://%s/", ip);
    } else if (wifi_setup_network(ssid, sizeof(ssid), password, sizeof(password))) {
        if (wifi_setup_phones() == 0) {
            /* The name and password have no characters that need escaping here */
            snprintf(code, sizeof(code), "WIFI:T:WPA;S:%s;P:%s;;", ssid, password);
            snprintf(text, sizeof(text), "Network: %s\nPassword: %s", ssid, password);
            heading = "Join the pin's Wi-Fi";
        } else {
            strlcpy(code, WIFI_SETUP_URL, sizeof(code));
            strlcpy(text, "Or type 192.168.4.1 in Safari. Then add your Wi-Fi on the Settings tab.", sizeof(text));
            heading = "Open the dashboard";
        }
        details = text;
    }
    if (timer && strcmp(code, cn.shown) == 0) {
        return;                         /* unchanged: don't redraw */
    }
    strlcpy(cn.shown, code, sizeof(cn.shown));
    lv_label_set_text(cn.heading, heading);
    if (details) {
        lv_label_set_text(cn.details, details);
        lv_obj_remove_flag(cn.details, LV_OBJ_FLAG_HIDDEN);
    } else {
        lv_obj_add_flag(cn.details, LV_OBJ_FLAG_HIDDEN);
    }
    if (code[0]) {
        lv_qrcode_update(cn.qr, code, strlen(code));
        lv_obj_remove_flag(cn.qr, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(cn.note, LV_OBJ_FLAG_HIDDEN);
    } else {
        lv_obj_add_flag(cn.qr, LV_OBJ_FLAG_HIDDEN);
        lv_obj_remove_flag(cn.note, LV_OBJ_FLAG_HIDDEN);
    }
}

static void deleted(lv_event_t *e)
{
    lv_timer_delete(cn.timer);
    memset(&cn, 0, sizeof(cn));
}

void connect_attach(lv_obj_t *scr)
{
    memset(&cn, 0, sizeof(cn));

    /* Generated layout (connect.xml): screen > row > [qrcode_b square, container > text] */
    lv_obj_t *row = lv_obj_get_child(scr, 0);
    lv_obj_t *square = lv_obj_get_child(row, 0);
    lv_obj_t *text = lv_obj_get_child(row, 1);

    cn.qr = lv_qrcode_create(square);
    lv_qrcode_set_size(cn.qr, QR_SIZE);
    lv_qrcode_set_dark_color(cn.qr, lv_color_black());
    lv_qrcode_set_light_color(cn.qr, lv_color_white());
    lv_obj_center(cn.qr);

    cn.note = lv_label_create(square);
    lv_obj_set_width(cn.note, QR_SIZE);
    lv_label_set_long_mode(cn.note, LV_LABEL_LONG_MODE_WRAP);
    lv_label_set_text(cn.note, "The pin isn't on Wi-Fi");
    lv_obj_set_style_text_align(cn.note, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_style_text_color(cn.note, lv_color_hex(0x333333), 0);
    lv_obj_set_style_text_font(cn.note, &lv_font_montserrat_14, 0);
    lv_obj_center(cn.note);

    /* Heading and details stacked, centred as the heading alone was */
    cn.heading = lv_obj_get_child(text, 0);
    strlcpy(cn.designed, lv_label_get_text(cn.heading), sizeof(cn.designed));
    lv_obj_set_flex_flow(text, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(text, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_set_style_pad_row(text, 12, 0);

    cn.details = lv_label_create(text);
    lv_obj_set_width(cn.details, lv_obj_get_style_width(cn.heading, 0));
    lv_label_set_long_mode(cn.details, LV_LABEL_LONG_MODE_WRAP);
    lv_obj_set_style_text_color(cn.details, lv_color_hex(0xC7C7CC), 0);
    lv_obj_set_style_text_font(cn.details, &lv_font_montserrat_18, 0);
    lv_obj_add_flag(cn.details, LV_OBJ_FLAG_HIDDEN);

    update(NULL);
    cn.timer = lv_timer_create(update, 1000, NULL);
    lv_obj_add_event_cb(scr, deleted, LV_EVENT_DELETE, NULL);
}
