# Daughterboard test

A small ESP-IDF program that checks the button/LED daughterboard
(`hardware/electronics/badgebuttonboard`) once it is fitted to the
ESP32-C6-Touch-AMOLED-1.64. Results show on the screen and in the serial
log.

| Part | Pin | Level |
| --- | --- | --- |
| Up button (upper) | GPIO6 | active low |
| Down button (lower) | GPIO3 | active low |
| LED, red | GPIO2 | active low (pin low = lit) |
| LED, green and blue | not connected | no free GPIOs left (see `handover.md`) |

GPIO23 can't be used for a button: on this board it's wired to the display's
tearing-effect output (`OLED_TE`, through R3), which drives the line itself.

The program uses the pin firmware's board support package and drivers
straight from `firmware/pin/components` (see `CMakeLists.txt`) and the same
landscape display setup as `firmware/pin/main/display.c`, without touch.

Flashing this replaces the pin firmware's app. Members, history and photos
are in their own flash partitions and aren't touched (`partitions.csv` is a
copy of the pin's). Reflash `firmware/pin` afterwards to get the badge back.

## Build and flash

Load ESP-IDF 5.5 in the terminal first (the same version the pin firmware
uses), then from this folder:

```powershell
idf.py build
```

```powershell
idf.py -p COM8 flash monitor
```

Use the board's own port (Device Manager, under Ports). Press Ctrl+] to
leave the monitor. The first build downloads LVGL and the display drivers
and compiles everything, which takes several minutes; rebuilds take seconds.

## What it does

1. **Pin check** (automatic, first half second; don't press anything). Each
   of the three pins is driven low in turn while the others are read back,
   which finds solder bridges between them and pins stuck to GND or 3V3. The
   result shows at the top right: "Pins OK" or the number of faults (details
   in the serial log).
2. **LED check** (about 7 s, watch the LED). Off, on, off, on, then a fade up
   and a fade down. The red dot next to the LED text on the screen shows what
   the LED should be doing; the two should match.
3. **Button check** (press the buttons). Each button has a card that lights
   up while it's held and counts presses (Up on the left, Down on the
   right, GPIO number in the corner), and the LED lights while either
   button is held. After 5 presses on each, the bottom line turns green with
   PASS. Hold both buttons for a second to run the LED check again. A button
   that reads pressed for 5 seconds shows "STUCK?".

Each card also shows the most raw edges seen in one press. A perfectly clean
press makes 2 (one down, one up); more is bounce, shown in yellow. A few
extra edges are normal for these switches and are hidden by the 20 ms
software debounce; a button that's much worse than the other points to a
weak joint or a missing 100n capacitor. The count comes from an interrupt,
so very fast bounces can be undercounted, never overcounted.
