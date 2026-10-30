/*
 * QR code on the connect screen (connect.xml, "Open the dashboard"):
 * http://<the pin's address>/. The address changes with the network (home
 * Wi-Fi, a phone's hotspot), so it's checked every second and the code is
 * redrawn when it changes. The phone scanning it must be on the same network.
 */

#include <string.h>
#include "connect.h"
#include "wifi.h"

#define QR_SIZE 150                     /* inside the 170 px white square: 10 px quiet zone */

typedef struct {
    lv_obj_t *qr;
    lv_obj_t *note;                     /* shown instead of the code while the pin is offline */
    lv_timer_t *timer;
    char shown[32];                     /* the address currently encoded ("" = note shown) */
} connect_t;

static connect_t cn;

static void update(lv_timer_t *timer)
{
    char ip[16] = "", url[32] = "";
    if (wifi_get_ip(ip, sizeof(ip))) {
        snprintf(url, sizeof(url), "http://%s/", ip);
    }
    if (timer && strcmp(url, cn.shown) == 0) {
        return;                         /* unchanged: don't redraw */
    }
    strlcpy(cn.shown, url, sizeof(cn.shown));
    if (url[0]) {
        lv_qrcode_update(cn.qr, url, strlen(url));
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

    /* Generated layout (connect.xml): screen > row > [qrcode_b square, text] */
    lv_obj_t *square = lv_obj_get_child(lv_obj_get_child(scr, 0), 0);

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

    update(NULL);
    cn.timer = lv_timer_create(update, 1000, NULL);
    lv_obj_add_event_cb(scr, deleted, LV_EVENT_DELETE, NULL);
}
