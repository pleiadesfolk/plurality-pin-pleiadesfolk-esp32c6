# Handover: Plurality Pin

*Written 2026-11-25, for whoever picks up the dev board to prototype the
button board and case and fold a hardware test program into the main firmware.*

Read the [README](README.md) first for what the pin does, and the
[User guide](docs/USER_GUIDE.md) for how it's used. This file covers what
the README doesn't: the current state, what's half-done, how the code fits
together, and what to watch out for when adding hardware.

---

## 1. Where things stand

**The firmware is feature-complete for daily use** and has been worn. Last
commit: `594c550` (Dashboard: regroup Import and Settings). Everything below
"Open issues" is polish or known limits, not blockers.

What works on hardware:

- Landscape 456×280 display (software rotation) and touch
- Fronter screen in three modes (namecard / image / image with name), clock,
  menu, Status, Settings, Connect (QR) screens, boot fade-in
- Side button (BOOT, GPIO9): 1 tap next member, 2 taps nobody, 3 taps or hold
  = clock, 10 s hold = remove dashboard password
- Touch gestures: swipe left/right to switch fronter, swipe down for the menu,
  press-and-hold for "switch mode" between main screens, double tap = take
  PluralKit's current fronter
- Wi-Fi (6 saved networks, phone hotspots, setup access point when none
  saved), NTP time, time zone from PluralKit or dashboard
- Web dashboard (phone browser) with optional password
- PluralKit: import from `pk;export`, one-way front polling, instant updates
  through the self-hosted relay, two-way history sync (last day), member
  updates, adding new members
- Battery log, low-battery warning and deep sleep below 3.40 V (~6 h 25 min
  per charge measured with a 600 mAh cell)
- microSD for photos (optional)

### Uncommitted work in the owner's checkout (commit before branching!)

These changes are on disk but **not committed**, so a fresh clone won't have
them:

| Change | Files | State |
|---|---|---|
| Handwriting font switched from Playwrite US Trad to **Playwrite NZ** (pin bitmap fonts + dashboard) and a "Redraw namecards" button on the Members tab | `firmware/pin/dashboard/*`, `firmware/pin/main/CMakeLists.txt`, `main/web.c`, `main/ui/**`, `test_project/ui/**` | Built from the Editor; check it's been flashed and looks right before committing |
| Relay rewrite: generic setup guide (systemd, Docker, etc.) and a browser **fronter page** (`/now?key=…`) | `relay/README.md`, `relay/pk_relay.py` | Needs a test on the relay host |
| `.gitignore` entry for `relay/widget/` (iPhone widget, kept private) | `.gitignore` | Ready |
| Four stray files `pleiades@192.168.50.33`, `pleiades@pleiadesfolk`, … in the repo root | — | **Accidental copies of `pk_relay.py`** from mistyped `scp` commands. Delete them; don't commit |
| `relay/__pycache__/` | — | Python cache; add to `.gitignore` or delete |

---

## 2. The dev board you have

**Waveshare ESP32-C6-Touch-AMOLED-1.64** ([docs](https://docs.waveshare.com/ESP32-C6-Touch-AMOLED-1.64)).
The vendor package (schematic, examples, factory firmware) lives in
`ESP32-C6-Touch-AMOLED-1.64-main/` in the owner's checkout but is
**git-ignored**; download it from Waveshare if you need it. The schematic is
in its `hardware/` folder.

| Thing | Detail |
|---|---|
| Chip | ESP32-C6, one 160 MHz RISC-V core, 512 KB RAM, 16 MB flash, **no PSRAM** |
| Screen | 1.64" AMOLED, 280×456 native, CO5300 over QSPI. Used **landscape** with software rotation (the panel's hardware rotation garbles the image; tested and abandoned) |
| Screen pins | CS 10, CLK 11, D0–D3 = 4 / 5 / 7 / 19, RST 21. No backlight pin; brightness is a panel command (0x51) |
| Touch | FocalTech, driven with the FT3168 driver, I²C address 0x38 |
| I²C bus | SCL **GPIO8**, SDA **GPIO18** (`I2C_NUM_0`, created by the BSP). Shared by touch and the QMI8658 IMU |
| IMU | QMI8658 6-axis, interrupt on GPIO21 (shared with LCD RST net per schematic table — double-check). Driver component is included (`components/waveshare__qmi8658`) but **unused** |
| microSD | SPI: CS 15, SCK 11, MOSI 4, MISO 5 — **shares pins with the screen**. DIP switch **JP8 pin 2 must be ON** for SD |
| BOOT button | **GPIO9**, 10 k pull-up, reads 0 when pressed. (The vendor BSP wrongly says GPIO0.) |
| PWR button | Goes to a hardware on/off controller, **not** to the ESP32. Firmware can't read it or power the board off |
| Battery ADC | GPIO0 (divider 200 k / 100 k, ×3) |
| Free GPIOs | **GPIO2, GPIO3, GPIO6** (and GPIO9 if the BOOT button is replaced). Check the schematic before using any other pin |
| Battery | 3.7 V Li-ion, MX1.25 connector. **Check polarity** before plugging in a cell; vendor cables differ. On USB the battery ADC reads the charger rail (~4.9 V), so the level only updates on battery |
| USB | USB-C for power, flashing, serial log. The port name on macOS changes with the socket (`ls /dev/cu.usbmodem*`) |

**Mechanical notes for the case**: the screen is used in landscape (long
side horizontal); "up" is fixed in `display.c` (`FLIP_180` = 0). Board
dimensions aren't on the Waveshare page; measure the board or ask Waveshare.
Leave access to USB-C, the PWR button, the microSD slot and the JP8 DIP switch
(or decide SD stays on/off permanently).

### Data on the board

If the board was used by the owner, its flash may still hold their members,
front history, photos, saved Wi-Fi passwords, PluralKit token and dashboard
password. Flashing the app **keeps** these (they're in separate partitions).
To start clean:

```bash
idf.py -p /dev/cu.usbmodemXXXX erase-flash
```

then flash as normal. (Owner: decide whether that's already been done.)

---

## 3. Getting set up

1. **Clone** the repo (`https://github.com/pleiadesfolk/plurality-pin-pleiadesfolk-esp32c6`)
   and work on your own branch, e.g. `git switch -c hw-test`.
2. **Install ESP-IDF v5.5.2** for the ESP32-C6
   ([guide](https://docs.espressif.com/projects/esp-idf/en/v5.5.2/esp32c6/get-started/index.html)),
   `./install.sh esp32c6`. In every new terminal: `. ~/esp/esp-idf/export.sh`.
3. **Optional Wi-Fi seed**: copy `firmware/pin/main/wifi_credentials.example.h`
   to `wifi_credentials.h` (git-ignored). Without it the pin starts its own
   setup Wi-Fi ("Plurality Pin setup", QR on the Connect screen).
4. **Build and flash** from `firmware/pin`:

   ```bash
   idf.py build
   ```

   ```bash
   idf.py -p /dev/cu.usbmodemXXXX flash monitor
   ```

   Ctrl+] leaves the monitor. Opening the serial port resets the board.
5. **Only if you change the screens' design**: the UI is edited in the LVGL
   Editor (`test_project/ui/`, Ctrl+B to generate C), then
   `python3 tools/sync_ui.py` copies it into `main/ui/` and converts fonts and
   images. First time: `cd tools && npm ci --cache /tmp/npm-cache`. Don't hand-edit
   `main/ui/`; it gets overwritten.

`firmware/landscape_test/` is a small standalone project that proved the
display and touch setup. It's a good template if you want a **separate**
throwaway test app before integrating.

---

## 4. How the firmware fits together

One module per job in `firmware/pin/main/` (table in the README). The pieces
that matter for adding hardware:

**Start-up order** (`main.c`):

1. `app_main`: NVS → time zone → assets → photos → store → LVGL → text
   decoder → display + touch → dashboard auth → Wi-Fi/web/PluralKit tasks →
   `lvgl_task`.
2. `lvgl_task`: UI init → brightness → status → boot screen.
3. `boot_done()` (after the boot fade): `nav_init`, **`button_init()`**,
   power, timers. **New input hardware should be initialised here**, next to
   `button_init()`.

**Rules that will bite you:**

- **LVGL is single-threaded.** Only touch LVGL objects from the LVGL task.
  From another task, use `lv_async_call()`. Poll inputs from an `lv_timer`
  (that's how `button.c` does it, every 20 ms with 2-poll debounce) so the
  handler already runs in the LVGL task.
- **RAM is the binding constraint.** Free heap is only ~75–90 KB at runtime,
  less during TLS (~40 KB per session) or photo saves. Avoid big buffers,
  watch the `free heap … lowest so far` line in the log every 10 s. Stack for
  new tasks: start small, check with `uxTaskGetStackHighWaterMark`.
- **SPI bus is shared between the screen and the SD card.** Anything touching
  SPI2 must wrap its transfers in `display_bus_take()` / `display_bus_give()`
  (`display.h`), or the board crashes with a `spi_hal_setup_trans` assert.
- **I²C bus is shared with touch.** Get the existing bus with
  `i2c_master_get_bus_handle(BSP_I2C_NUM, &bus)` and add your device to it;
  don't create a second bus on GPIO8/18. Note the touch driver already logs
  an occasional `FT3168 I2C read failed` (about every 13 s, cause unknown) —
  don't mistake it for your device's fault, but do check whether a new device
  on the bus makes it worse.
- **Swipe/tap/hold** come from raw touch in `display.c`
  (`display_set_swipe_cb`, `display_set_tap_cb`, `display_set_hold_cb`), not
  LVGL gestures (those get eaten by scrolling).
- **Screen actions** you'll want for buttons: `nav_show_fronter()`,
  `nav_toggle_clock()`, `nav_toast(text)`, `button_switch(+1/-1)` (step
  fronter), and the menu/Settings/Status screens through `nav.c`.
- New `.c` files must be added to `SRCS` in `main/CMakeLists.txt`.

---

## 5. Integrating the hardware test program — suggested approach

Goal: the test program ships inside the main firmware without getting in the
way of normal use.

1. **Put it behind a switch.** Either a Kconfig option (`main/Kconfig.projbuild`,
   e.g. `CONFIG_PIN_HW_TEST`, off by default, set with `idf.py menuconfig`)
   or a hidden entry (e.g. a long hold on the Status screen). A compile-time
   option is simplest and costs nothing when off.
2. **Make it its own module**, e.g. `main/hwtest.c/.h`, with
   `hwtest_init()` called from `boot_done()` and a screen built in code
   (`lv_obj_create(NULL)` + labels), like `boot.c` or the power screen in
   `nav.c`. No need to go through the LVGL Editor for a test screen.
3. **Generalise the button code instead of duplicating it.** `button.c` is
   hard-wired to one GPIO. If the new board adds buttons, refactor it into a
   small table of `{gpio, action}` with the same debounce/tap/hold logic, so
   the test program and the normal UI share one input path. Keep BOOT
   (GPIO9) working: it's also the password-reset hold.
4. **What the test should show**: each button's raw state and press count,
   touch coordinates (`landscape_test` already does a touch dot), IMU
   readings if the case design uses tilt, battery volts (`status.c` /
   `/api/state` → `battery_volts`), SD mounted yes/no.
5. **If the button board uses an I/O expander or other I²C part**, join the
   shared bus as above; if it uses plain GPIOs, only 2, 3, 6 (and 9) are free.
6. Commit on your branch and open a pull request into `main`.

---

## 6. Open issues and future actionables

### For the hardware/case work
- [ ] Decide button count and which GPIOs (2, 3, 6, 9) or an I²C expander
- [ ] Refactor `button.c` for multiple buttons; map new buttons to actions
      (next/previous fronter, nobody, clock, menu)
- [ ] Add the hardware test program (section 5)
- [ ] Measure the board and design the case around USB-C, PWR, microSD, JP8
- [ ] Confirm battery connector polarity and cell size for the case
- [ ] Possibly use the IMU (driver already present, unused): e.g. wake on lift
      or auto-flip the screen 180° (`FLIP_180` in `display.c`)

### Owner's housekeeping
- [ ] Commit (or discard) the uncommitted work in section 1; delete the four
      `pleiades@…` files and `relay/__pycache__/`
- [ ] Test the relay's new fronter page on the relay host
- [ ] Erase the handed-over board's flash if it still holds personal data

### Known limits / bugs (not urgent)
- Occasional `FT3168 I2C read failed` in the log; cause unknown, harmless so far
- Battery level can't be read while on USB; "no battery" can't be detected
- No OTA partition: updates are USB only (the old `ota_0` space now holds photos)
- Setup Wi-Fi only starts when **no** network is saved; if all saved networks
  are out of range, the only fix is reflashing with `wifi_credentials.h`
- Hidden Wi-Fi networks can't be added from the dashboard (scan-only)
- Dashboard doesn't warn when all 8 fast-photo slots are full
- Bluetooth is unused (the Settings card shows "isn't available yet")
- Dashboard is plain HTTP on the local network (password optional);
  HTTPS only via the owner's Tailscale setup
- Ideas never started: dashboard export (CSV), image library, front history
  charts on the pin itself

---

## 7. Who to ask

The PluralKit relay, the owner's Tailscale/NanoPi setup, the Figma file
(`plurality-pin.fig`) and design decisions are the owner's. Ask them for
relay addresses or secrets rather than looking for them in the repo; none are
committed.
