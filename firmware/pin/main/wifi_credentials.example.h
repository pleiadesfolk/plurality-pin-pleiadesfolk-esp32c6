/*
 * Template for wifi_credentials.h, which holds the real Wi-Fi network name and
 * password. That file is NOT in git (see .gitignore), so passwords never end
 * up in the project history.
 *
 * To set up: copy this file to wifi_credentials.h (same folder) and fill in.
 * Optional: without wifi_credentials.h (or with these left empty) the pin
 * starts with no saved network and runs its own setup Wi-Fi, "Plurality Pin
 * setup": join it with the QR code on the pin's Connect screen and add your
 * network on the dashboard's Settings tab (see wifi.c).
 */
#pragma once

#define WIFI_SSID       ""
#define WIFI_PASSWORD   ""
