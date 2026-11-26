# Hardware

| Folder | What's in it |
| --- | --- |
| `electronics/` | The button daughterboard (`badgebuttonboard`): KiCad project, Gerbers, drill files, BOM and placement files for JLCPCB, and a STEP model of the TS24CA switch |
| `mechanical/` | The desk stand (base, lever, cable holder) as `.3mf`. The case is being redesigned for the larger buttons and isn't here yet |

The dev board itself (Waveshare ESP32-C6-Touch-AMOLED-1.64) is described in
`handover.md`, section 2.

## Button daughterboard

Two buttons and an RGB LED, connected to the dev board by two connectors.
The firmware uses the buttons to step through members (`firmware/pin/main/button.c`);
`firmware/daughterboard_test` checks the board on its own.

### Wiring to the dev board

| Daughterboard | Signal | Dev board | Firmware name |
| --- | --- | --- | --- |
| J1 pin 1 | GND | GND | |
| J1 pin 2 | 3V3 | 3V3 | |
| J1 pin 3 | B1 (SW1) | GPIO6 or GPIO3, see below | |
| J1 pin 4 | B2 (SW2) | GPIO6 or GPIO3, see below | |
| | Up button, the upper one | **GPIO6** | Up: next member |
| | Down button, the lower one | **GPIO3** | Down: previous member |
| J2 pin 1 | LED red cathode | **GPIO2** | |
| J2 pin 2 | LED green cathode | not connected | |
| J2 pin 3 | LED blue cathode | not connected | |

**Not recorded yet: which of B1/B2 is Up.** To find out, run
`firmware/daughterboard_test` and press SW1 (the switch on the B1 line): the
Up card lights if B1 goes to GPIO6, the Down card if it goes to GPIO3. Then
fill in the two J1 rows above.

Green and blue aren't connected because the dev board has no free GPIOs left.
GPIO2, 3 and 6 are the only free pins once GPIO9 stays the BOOT button.
For a full-colour LED, the options are an addressable LED on one pin, the
UART pins GPIO16/17 on header P2, or an I²C expander on the shared bus.

**GPIO23 can't be used**, although it's on header P2: the dev board wires it
to the display's tearing-effect output (`OLED_TE`, through the 0 Ω link R3),
which drives the line itself. A button on GPIO23 reads pressed or pulses at
the display's frame rate.

### Circuit

- **Buttons** are active low. Each line has a 10k pull-up to 3V3 (R4, R5) and
  100n to GND (C1, C2) at the connector, then 1k (R6, R7) to the switch
  (SW1, SW2, TS24CA), which goes to GND. Pressed reads about 0.3 V, released
  3.3 V. The firmware also turns on the chip's own pull-ups and debounces over
  20 ms.
- **LED** D1 (QLS6B-FKW) is common anode: all three anodes on 3V3, each
  cathode through 1k (R1–R3) to J2. A pin driven low lights its colour.
- Schematic quirk: D1 pin 6 is named `KR` in the symbol, the same as pin 4.
  From the anode/cathode pairing (1–2 blue, 3–4 red, 5–6 green) it's the
  green cathode. The wiring is right; only the pin name is wrong.

### Measured with the board fitted (unpowered)

- B line to GND, button released: about 18 kΩ, which is normal. Most likely
  the 10k pull-up in series with the dev board's 3V3 rail to GND, not a leak.
- B line to GND, button pressed: about 1 kΩ, the series resistor.
