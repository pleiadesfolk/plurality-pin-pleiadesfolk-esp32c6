# Handover: Plurality Pin

*Written 2026-11-25, for whoever picks up the dev board to prototype the
button board and case and fold a hardware test program into the main firmware.
Updated 2026-11-26 after the button daughterboard was brought up on the
`hw-test` branch.*

Read the [README](README.md) first for what the pin does, and the
[User guide](docs/USER_GUIDE.md) for how it's used. This file covers what
the README doesn't: the current state, what's half-done, how the code fits
together, and what to watch out for when adding hardware. The daughterboard,
case and stand have their own notes in [hardware/README.md](hardware/README.md).

---

## 1. Where things stand

**The firmware is feature-complete for daily use** and has been worn.
Everything below "Open issues" is polish or known limits, not blockers.

What works on hardware:

- Landscape 456×280 display (software rotation) and touch
- Fronter screen in three modes (namecard / image / image with name), clock,
  menu, Status, Settings, Connect (QR) screens, boot fade-in
- Side button (BOOT, GPIO9): 1 tap next member, 2 taps nobody, 3 taps or hold
  = clock, 10 s hold = remove dashboard password
- **Daughterboard buttons** (on `hw-test`, not yet on `main`): Up (GPIO6) =
  next member, Down (GPIO3) = previous member, like swiping
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

### Branches and uncommitted work

The owner's uncommitted work from the first handover (Playwrite NZ font,
"Redraw namecards" button, relay fronter page, `.gitignore` entries) was
committed to `main` in `0b42df3`, `6c2769f` and `1744e81`, and the stray
`pleiades@…` copies and `relay/__pycache__/` are gone.

**`hw-test`** (branched from `main` at `1744e81`, **not pushed yet**) holds the
button daughterboard work:

| Commit | What |
|---|---|
| `ac0d92c` | `firmware/daughterboard_test`: standalone test app for the daughterboard (section 3) |
| `8fbeba4` | `button.c`/`button.h`: buttons in a table; Up/Down step members, BOOT unchanged |
| `f7ff016` | First version of `hardware/README.md` |
| `87fae53` | This handover update; the new case (`casing2 w button.3mf`, `casing2 no button.3mf`) and modified stand base; `hardware/README.md` rewritten with casing, JLCPCB ordering, soldering and stand notes plus photos (`hardware/images/`); the button board's schematic PDF, 3D model and switch footprint library (`button.pretty/`, `fp-lib-table`) |

Nothing is uncommitted. `hardware/README.md` still lists GPIO0 as a free
pin, which is wrong (section 8). KiCad also writes `*-backups/` and
`fp-info-cache` next to the project; those belong in `.gitignore`, not in a
commit.

---

## 2. The dev board you have

**Waveshare ESP32-C6-Touch-AMOLED-1.64** ([docs](https://docs.waveshare.com/ESP32-C6-Touch-AMOLED-1.64)).
The vendor package (schematic, examples, factory firmware) lives in
`ESP32-C6-Touch-AMOLED-1.64-main/` in the owner's checkout but is
**git-ignored**. The schematic is also on GitHub:
[ESP32-C6-Touch-AMOLED-1.64-schematic.pdf](https://github.com/waveshareteam/ESP32-C6-Touch-AMOLED-1.64/blob/main/hardware/schematics/ESP32-C6-Touch-AMOLED-1.64-schematic.pdf).
It's a single picture with no text layer, so search tools find nothing in
it; read it by eye. Its pin table (bottom left) lists every GPIO's use and
is the quickest way to check a pin.

| Thing | Detail |
|---|---|
| Chip | ESP32-C6, one 160 MHz RISC-V core, 512 KB RAM, 16 MB flash, **no PSRAM** |
| Screen | 1.64" AMOLED, 280×456 native, CO5300 over QSPI. Used **landscape** with software rotation (the panel's hardware rotation garbles the image; tested and abandoned) |
| Screen pins | CS 10, CLK 11, D0–D3 = 4 / 5 / 7 / 19, **RST 20** (the first handover said 21; the BSP and the schematic both say 20), panel enable `OLED_EN` 22, tearing-effect output `OLED_TE` **23**. No backlight pin; brightness is a panel command (0x51) |
| Touch | FocalTech, driven with the FT3168 driver, I²C address 0x38, interrupt GPIO1 |
| I²C bus | SCL **GPIO8**, SDA **GPIO18** (`I2C_NUM_0`, created by the BSP). Shared by touch and the QMI8658 IMU |
| IMU | QMI8658 6-axis, INT1 on **GPIO21** (`QMI_INT1`; not shared with the LCD reset, which is 20). Driver component is included (`components/waveshare__qmi8658`) but **unused** |
| microSD | SPI: CS 15, SCK 11, MOSI 4, MISO 5 — **shares pins with the screen**. DIP switch **JP8 pin 2 must be ON** for SD |
| BOOT button | **GPIO9**, 10 k pull-up and 100 nF, reads 0 when pressed. (The vendor BSP wrongly says GPIO0.) Strapping pin: held low at reset it starts the ROM download mode |
| PWR button | Goes to a hardware on/off controller, **not** to the ESP32. Firmware can't read it or power the board off |
| Battery ADC | **GPIO0** (divider 200 k / 100 k, ×3). Not free |
| UART0 | TX GPIO16, RX GPIO17, on header P2. Unused: the serial log goes over USB |
| Free GPIOs | **GPIO2, GPIO3, GPIO6**, now all used by the daughterboard (section 3). Left over: GPIO9 if the BOOT button is given up, and GPIO16/17 if the UART is. **GPIO23 is not free** even though it's on header P2: it's the display's TE output (below) |
| Battery | 3.7 V Li-ion, MX1.25 connector. **Check polarity** before plugging in a cell; vendor cables differ. On USB the battery ADC reads the charger rail (~4.9 V), so the level only updates on battery |
| USB | USB-C for power, flashing, serial log. macOS: `/dev/cu.usbmodem*`, changes with the socket. Windows: a `COMn` port (Device Manager → Ports) |

**GPIO23 and the display's TE signal.** The panel's tearing-effect output
reaches GPIO23 through R3, a 0 Ω link near the display connector. The BSP's
panel start-up turns TE on (`0x35` in `ESP32-C6-Touch-AMOLED-1.64.c`), so
while the screen runs, GPIO23 carries a pulse at the frame rate (~16 ms
period measured), and with the panel not set up it read low the whole time. Nothing in this repo reads TE (tear avoidance is off), so
removing R3 would free GPIO23 at no cost; it hasn't been done. A button on
GPIO23 was the first daughterboard attempt and it can't work: it reads
pressed, or flickers at the frame rate.

**Mechanical notes for the case**: the screen is used in landscape (long
side horizontal); "up" is fixed in `display.c` (`FLIP_180` = 0). Board
dimensions aren't on the Waveshare page; measure the board or ask Waveshare.
Leave access to USB-C, the PWR button, the microSD slot and the JP8 DIP switch
(or decide SD stays on/off permanently).

### Data on the board

The handed-over board still holds the owner's profile: 39 members, their
front history (~6,900 switches) and card pictures, and probably their saved
Wi-Fi networks, PluralKit token and dashboard password. It was deliberately
kept for testing the main firmware: none of the saved networks is in range
where the board is now, so it runs offline and never syncs. Switches made with
the buttons are only saved on the board; the firmware doesn't send switches to
PluralKit by itself (only the dashboard does).

Where things live (all survive flashing the app, including flashing
`daughterboard_test`, which uses the same partition table):

| What | Where |
|---|---|
| Members, system name, "nobody fronting" card | `storage` partition (FAT), `/data/members.json` |
| Namecard pictures | `/data/cards/` |
| Front history | `/data/switches.bin` |
| Photos | `photos` partition (8 fast slots), overflow on the SD card (`/sdcard/pin`) or `/data/img` |
| Wi-Fi, PluralKit token/relay secret, dashboard password | NVS |

To start clean (deletes all of the above, can't be undone):

```bash
idf.py -p /dev/cu.usbmodemXXXX erase-flash
```

then flash as normal and load members from a `pk;export` file on the
dashboard (that only reads the file; it doesn't link an account). The owner
should decide when that happens.

---

## 3. The button daughterboard

Details, ordering and soldering are in [hardware/README.md](hardware/README.md).
In short:

| Part | Dev board pin | Firmware |
|---|---|---|
| Up button (upper) | **GPIO6** | `button_switch(+1)`: next member |
| Down button (lower) | **GPIO3** | `button_switch(-1)`: previous member |
| LED, red | **GPIO2** | not used by the main firmware yet |
| LED, green and blue | not connected | no free pins |

- **Buttons** are active low: 10 k pull-up and 100 nF at the connector, 1 k to
  the switch, switch to GND. Pressed reads ~0.3 V. Measured unpowered: ~18 kΩ
  line-to-GND released (the pull-up plus the board's 3V3 rail; normal),
  ~1 kΩ pressed. The switches bounce a little (up to 4–5 raw edges per press
  against 2 for a clean one); the 20 ms debounce hides it.
- **LED** D1 (QLS6B-FKW) is common anode on 3V3, each cathode through 1 k to
  the connector: drive the pin low to light it. `daughterboard_test` drives
  it with LEDC PWM (`output_invert`) so it can dim and fade.
- **Schematic quirk**: D1 pin 6 is named `KR` in the symbol, like pin 4. By
  the anode/cathode pairing it's the green cathode. Only the name is wrong.
- **Which of B1/B2 (J1 pins 3/4) is Up** isn't recorded against the schematic;
  hardware/README.md gives it by position instead (top-right pin → GPIO6, the
  one to its left → GPIO3).

### `firmware/daughterboard_test`

A standalone app that checks the daughterboard and shows the results on the
screen (and the serial log). Build and flash it like the pin firmware, from
its own folder. It runs:

1. **Pin check** at power-up (don't press anything): each of GPIO2/3/6 driven
   low in turn while the others are read back, to catch shorts. Top right:
   "Pins OK" or the fault count.
2. **LED check**, ~7 s: off, on, off, on, fade up, fade down. A red dot on the
   screen shows what the LED should do.
3. **Button check**: an Up and a Down card light while held and count presses
   and bounce; the LED lights while either is held; PASS after 5 presses
   each. Holding both for 1 s repeats the LED check.

It uses `firmware/pin/components` directly (`EXTRA_COMPONENT_DIRS`) and the
pin's `partitions.csv`, so flashing it keeps the profile. On the current
board: pin check passed, both buttons passed, and the LED follows the buttons.

---

## 4. Getting set up

1. **Clone** the repo (`https://github.com/pleiadesfolk/plurality-pin-pleiadesfolk-esp32c6`)
   and work on your own branch. The daughterboard work is on `hw-test`.
2. **Install ESP-IDF v5.5.2** for the ESP32-C6
   ([guide](https://docs.espressif.com/projects/esp-idf/en/v5.5.2/esp32c6/get-started/index.html)),
   `./install.sh esp32c6`. In every new terminal: `. ~/esp/esp-idf/export.sh`
   (Windows: run `export.ps1` from the ESP-IDF folder, or use the ESP-IDF
   PowerShell shortcut).
3. **Optional Wi-Fi seed**: copy `firmware/pin/main/wifi_credentials.example.h`
   to `wifi_credentials.h` (git-ignored). Without it the pin starts its own
   setup Wi-Fi ("Plurality Pin setup", QR on the Connect screen) when no
   network is saved.
4. **Build and flash** from `firmware/pin`:

   ```bash
   idf.py build
   ```

   ```bash
   idf.py -p /dev/cu.usbmodemXXXX flash monitor
   ```

   Ctrl+] leaves the monitor. Opening the serial port resets the board.
   The first build in a fresh checkout downloads LVGL and the drivers and
   compiles everything: 5–10 minutes. Rebuilds take seconds.
5. **Only if you change the screens' design**: the UI is edited in the LVGL
   Editor (`test_project/ui/`, Ctrl+B to generate C), then
   `python3 tools/sync_ui.py` copies it into `main/ui/` and converts fonts and
   images. First time: `cd tools && npm ci --cache /tmp/npm-cache`. Don't hand-edit
   `main/ui/`; it gets overwritten.

`firmware/landscape_test/` proved the display and touch setup;
`firmware/daughterboard_test/` (section 3) is the button board's test app and
a template for small standalone tests with the screen.

---

## 5. How the firmware fits together

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

**Buttons** (`button.c`, on `hw-test`): a table of `{gpio, direction}`
polled every 20 ms from one LVGL timer with a 2-poll debounce. Direction 0 is
BOOT's tap/hold logic (unchanged); ±1 calls `button_switch()` on the press.
A new button is one table row. All three pins have the internal pull-up on,
so a board without the daughterboard reads them as released.

**Rules that will bite you:**

- **LVGL is single-threaded.** Only touch LVGL objects from the LVGL task.
  From another task, use `lv_async_call()`. Poll inputs from an `lv_timer`
  (that's how `button.c` does it) so the handler already runs in the LVGL task.
- **RAM is the binding constraint.** Free heap is only ~75–90 KB at runtime
  (83–97 KB seen while testing the buttons), less during TLS (~40 KB per
  session) or photo saves. Avoid big buffers, watch the
  `free heap … lowest so far` line in the log every 10 s. Stack for new tasks:
  start small, check with `uxTaskGetStackHighWaterMark`.
- **SPI bus is shared between the screen and the SD card.** Anything touching
  SPI2 must wrap its transfers in `display_bus_take()` / `display_bus_give()`
  (`display.h`), or the board crashes with a `spi_hal_setup_trans` assert.
- **I²C bus is shared with touch.** Get the existing bus with
  `i2c_master_get_bus_handle(BSP_I2C_NUM, &bus)` and add your device to it;
  don't create a second bus on GPIO8/18. Note the touch driver already logs
  an occasional `FT3168 I2C read failed` (about every 13 s, cause unknown) —
  don't mistake it for your device's fault, but do check whether a new device
  on the bus makes it worse.
- **The FreeRTOS tick is 100 Hz.** `pdMS_TO_TICKS()` of anything under 10 ms
  is 0, and `vTaskDelay(0)` doesn't wait at all. This broke the first
  daughterboard test's debounce. Keep delays at 10 ms or more, or add a
  `_Static_assert(pdMS_TO_TICKS(X) >= 1, …)`.
- **Swipe/tap/hold** come from raw touch in `display.c`
  (`display_set_swipe_cb`, `display_set_tap_cb`, `display_set_hold_cb`), not
  LVGL gestures (those get eaten by scrolling).
- **Screen actions** you'll want for buttons: `nav_show_fronter()`,
  `nav_toggle_clock()`, `nav_toast(text)`, `button_switch(+1/-1)` (step
  fronter), and the menu/Settings/Status screens through `nav.c`.
- New `.c` files must be added to `SRCS` in `main/CMakeLists.txt`.

---

## 6. Integrating the hardware test program — suggested approach

Goal: the test program ships inside the main firmware without getting in the
way of normal use. Progress so far: the buttons are wired in (step 3 done),
and `daughterboard_test` shows what the test screen should look like.

1. **Put it behind a switch.** Either a Kconfig option (`main/Kconfig.projbuild`,
   e.g. `CONFIG_PIN_HW_TEST`, off by default, set with `idf.py menuconfig`)
   or a hidden entry (e.g. a long hold on the Status screen). A compile-time
   option is simplest and costs nothing when off.
2. **Make it its own module**, e.g. `main/hwtest.c/.h`, with
   `hwtest_init()` called from `boot_done()` and a screen built in code
   (`lv_obj_create(NULL)` + labels), like `boot.c` or the power screen in
   `nav.c`. No need to go through the LVGL Editor for a test screen.
3. ~~**Generalise the button code instead of duplicating it.**~~ Done on
   `hw-test`: the test should read button states from `button.c` (add a
   getter, or a callback per press) rather than polling the pins itself.
4. **What the test should show**: each button's state and press count (port
   the cards from `daughterboard_test`), LED on/off/fade, touch coordinates
   (`landscape_test` has a touch dot), IMU readings if the case design uses
   tilt, battery volts (`status.c` / `/api/state` → `battery_volts`), SD
   mounted yes/no. **Don't port `daughterboard_test`'s display code**: it
   allocates its own draw buffers (~110 KB), which the main firmware can't
   afford. Draw through the existing `display.c`.
5. **If more parts are added later** (I/O expander, addressable LED), join the
   shared I²C bus as above. Plain GPIOs are used up (section 2).
6. Commit on `hw-test` and open a pull request into `main`.

---

## 7. Lessons from the daughterboard bring-up

- **Check the schematic's pin table before choosing a pin.** GPIO23 and
  GPIO0 both look free from the headers and aren't.
- **A software debounce only reads the pin.** If a button reads wrong with
  nobody touching it, the cause is electrical; the pin check in
  `daughterboard_test` and a multimeter find it faster than code changes.
- **On Windows, the board's USB serial port drops out for a moment after each
  flash.** Wait ~3 s before opening it. To reset the board from a script,
  toggle RTS and then rewrite DTR: the Windows `usbser` driver only sends the
  RTS change along with a DTR write (esptool does the same).

---

## 8. Open issues and future actionables

### Button board, case and hardware test
- [x] Decide button count and GPIOs: Up GPIO6, Down GPIO3, red LED GPIO2
- [x] Refactor `button.c` for multiple buttons; Up/Down = next/previous member
- [x] Standalone daughterboard test (`firmware/daughterboard_test`), passed on the board
- [x] Commit the hardware work (case, stand, README, KiCad files) on `hw-test`
- [ ] Add KiCad's `*-backups/` and `fp-info-cache` to `.gitignore`
- [ ] Fix `hardware/README.md`: it lists **GPIO0** as free, but GPIO0 is the
      battery ADC. The free pins were 2, 3 and 6 (plus 9 without BOOT)
- [ ] Push `hw-test` and open a pull request into `main` for the owner
- [ ] Decide what the LED means in normal use (e.g. flash on a switch, low
      battery, no Wi-Fi), then drive GPIO2 from the main firmware (LEDC PWM,
      active low). Until then the main firmware leaves GPIO2 unconfigured
- [ ] Decide whether red-only is enough. Full colour needs an addressable LED
      on one pin, GPIO16/17 (UART), or an I²C expander
- [ ] Hardware test inside the main firmware (section 6)
- [ ] Check a button switch is saved: switches are saved 5 s after the last
      press (`store_save_preview`, "switch saved" in the log); not yet seen
      during the button test
- [ ] Document Up/Down in the [User guide](docs/USER_GUIDE.md) once the case
      and button layout are final
- [ ] Print and fit the new case (`casing2 w button` / `no button`); check
      access to USB-C, PWR, microSD and JP8
- [ ] Optional: rename D1 pin 6 to `KG` in the KiCad symbol
- [ ] Optional: remove R3 if GPIO23 is ever needed (frees it from the display's TE)
- [ ] Confirm battery connector polarity and cell size for the case
- [ ] Possibly use the IMU (driver already present, unused): e.g. wake on lift
      or auto-flip the screen 180° (`FLIP_180` in `display.c`)

### Owner's housekeeping
- [x] Commit the uncommitted work from the first handover; delete the
      `pleiades@…` files and `relay/__pycache__/`
- [ ] Test the relay's new fronter page on the relay host
- [ ] Erase the handed-over board's flash when it no longer needs the stored
      profile for testing (section 2)

### Known limits / bugs (not urgent)
- Occasional `FT3168 I2C read failed` in the log; cause unknown, harmless so far
- At start-up the I²C driver warns `Please check pull-up resistances`.
  Seen while testing the buttons; not investigated, and the button work
  doesn't touch the I²C pins. Harmless so far
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

## 9. Who to ask

The PluralKit relay, the owner's Tailscale/NanoPi setup, the Figma file
(`plurality-pin.fig`) and design decisions are the owner's. Ask them for
relay addresses or secrets rather than looking for them in the repo; none are
committed.
