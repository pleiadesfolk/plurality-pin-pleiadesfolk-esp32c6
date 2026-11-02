/*
 * Settings screen: tapping the Wi-Fi card turns Wi-Fi off/on; the Bluetooth
 * card says Bluetooth isn't available yet (the pin doesn't use it). Their
 * labels and dots follow the wifi_state / bluetooth_on subjects in the XML.
 */

#include "settings.h"
#include "brightness.h"
#include "nav.h"
#include "status.h"
#include "wifi.h"

static void wifi_tapped(lv_event_t *e)
{
    bool on = !wifi_is_enabled();
    wifi_set_enabled(on);
    nav_toast(on ? "Wi-Fi on" : "Wi-Fi off - the dashboard is unreachable");
}

static void bluetooth_tapped(lv_event_t *e)
{
    nav_toast("Bluetooth isn’t available yet");
}

static void make_unclickable(lv_obj_t *obj)
{
    for (uint32_t i = 0; i < lv_obj_get_child_count(obj); i++) {
        lv_obj_t *child = lv_obj_get_child(obj, i);
        lv_obj_remove_flag(child, LV_OBJ_FLAG_CLICKABLE);
        make_unclickable(child);
    }
}

/* The card itself takes the tap (not what's inside it) and dims while pressed */
static void make_button(lv_obj_t *card, lv_event_cb_t cb)
{
    make_unclickable(card);
    lv_obj_add_flag(card, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_opa(card, LV_OPA_60, LV_STATE_PRESSED);
    lv_obj_add_event_cb(card, cb, LV_EVENT_CLICKED, NULL);
}

void settings_attach(lv_obj_t *scr)
{
    brightness_attach(scr);

    /* Generated layout (see settings.xml):
     * screen > [background, column > [title row, row > [Wi-Fi, Bluetooth, battery], brightness]] */
    lv_obj_t *cards = lv_obj_get_child(lv_obj_get_child(scr, 1), 1);
    make_button(lv_obj_get_child(cards, 0), wifi_tapped);
    /* Wi-Fi card > column > [column > icon, ...] */
    status_wifi_icon(lv_obj_get_child(lv_obj_get_child(lv_obj_get_child(lv_obj_get_child(cards, 0), 0), 0), 0), true);
    make_button(lv_obj_get_child(cards, 1), bluetooth_tapped);
    /* battery card > [card > icon, column] */
    status_battery_icon(lv_obj_get_child(lv_obj_get_child(lv_obj_get_child(cards, 2), 0), 0), false);
    /* battery card > [card > icon, column > ["Battery", row > percent]] */
    status_charging_label(lv_obj_get_child(lv_obj_get_child(lv_obj_get_child(cards, 2), 1), 0));
}
