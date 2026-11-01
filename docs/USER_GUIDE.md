# Plurality Pin: user guide

This guide covers wearing and using the pin day to day. To build and flash the
firmware, see the [README](../README.md).

- [Quick start](#quick-start)
- [Using the pin](#using-the-pin)
- [The dashboard](#the-dashboard)
- [PluralKit](#pluralkit)
- [Battery and charging](#battery-and-charging)
- [Troubleshooting](#troubleshooting)

---

## Quick start

You need: the pin (charged, or on USB), a phone on the same Wi-Fi network as
the pin, and your PluralKit export if you use PluralKit.

1. **Turn it on.** Press the **PWR** button. A starry boot screen fades in
   for a few seconds while the pin joins Wi-Fi and sets its clock.

2. **Open the dashboard.** On the pin, **swipe down** to open the menu and tap
   **Connect to pin**. Scan the QR code with your phone's camera and open the
   link. You can also type the address (like `http://192.168.1.42/`) into
   your phone's browser.

3. **Import your system.** In Discord, DM PluralKit `pk;export` and save the
   file it sends. In the dashboard, open **Import**, pick the file, check the
   preview and confirm. This adds your members and front history.

4. **Optional: add avatars.** Still in **Import**, under *Photos from
   PluralKit*, tap **Import photos**.

5. **Optional: keep in sync.** Still in **Import**, under *Sync with
   PluralKit*, enter your system ID (public front) or your token (DM
   PluralKit `pk;token`) and tap **Save**. The pin now picks up switches
   within a minute.

6. **Optional: set a password.** In **Wi-Fi** → *Dashboard password*, so
   nobody else on the network can change your pin.

That's it: the pin now shows whoever is fronting.

---

## Using the pin

### Screens

| Screen | How to get there |
|---|---|
| **Fronter**: the current fronter's namecard or photo. The pin starts here. | Default |
| **Clock**: time and date | Press the side button 3 times, or hold it |
| **Menu**: Status, Settings, Connect to pin | Swipe **down** on the fronter |
| **Status**: battery, Wi-Fi, storage | Menu → Status |
| **Settings**: brightness, Wi-Fi on/off | Menu → Settings |
| **Connect to pin**: QR code for the dashboard | Menu → Connect to pin |

When a screen opens, its name shows briefly at the bottom.

### Touch gestures

| On… | Gesture | Does |
|---|---|---|
| Fronter | Swipe left / right | Next / previous member |
| Fronter | Swipe down | Open the menu |
| Fronter | Double tap | Ask PluralKit for the current fronter now (needs the relay) |
| Fronter or Clock | Press and hold | **Switch mode**: dots appear, swipe left/right to move between Fronter and Clock, tap to finish |
| Clock | Swipe left / right | Back to the fronter |
| Menu | Swipe up | Back to the fronter |
| Status, Settings, Connect | Swipe right | Back to the menu |
| Status, Settings, Connect | Swipe up | Straight back to the fronter |

### The side button (BOOT)

| Press | Does |
|---|---|
| Once | Switch to the next **Quick Switch** member |
| Twice | Nobody fronting |
| Three times, or hold | Clock (and back to the fronter) |
| Hold for 10 seconds | Removes the dashboard password (a warning appears at 4 s) |

Which members the button and swipes step through: the members marked **Quick
Switch** in the dashboard, most PluralKit messages first. If nobody is marked,
it goes through everyone.

**Switches wait 5 seconds before they're saved.** The new fronter shows straight
away, but it's only written to the front history once you've stopped pressing
or swiping for 5 seconds. You can step past several members to reach the one
you want without logging each of them.

### Settings and Status

- **Brightness**: drag the slider on Settings. The pin remembers it.
- **Wi-Fi card (Settings)**: tap to turn Wi-Fi off or on. With Wi-Fi off,
  the dashboard and PluralKit sync stop. Turning it back on also re-enables
  any networks you told the pin to skip.
- **Wi-Fi card (Status)**: tap to move to the next saved network.
- **Status** also shows the battery level, the "Charging" tag on USB, and how
  full the SD card and the pin's own storage are.

---

## The dashboard

Open it from **Menu → Connect to pin** (scan the QR code). Your phone must be
on the same network as the pin. It has five tabs.

### Front

- **Switch to**: tap a member (or *Nobody*) to switch now. Dashboard
  switches are saved right away.
- **Add member**: creates a new member and opens the editor.

### Members

The member list. Tap a member to edit them:

- **Name**, and **Shown on the pin as**: *Namecard*, *Image* or *Image with name*.
- **Namecard**: the text, font, weight, largest text size (long text shrinks
  to fit), alignment, background colour, and text colour (white, or a gradient
  that can slowly animate). The preview matches the pin. Any language or
  emoji works, because your phone draws the card.
- **Photo** (image modes): *Use PluralKit avatar* or *Upload a photo*. For
  *Image with name*, use the zoom slider and drag the preview to frame it, and
  enter the **name beside the photo**.
- **Fast photo**: keeps the photo in the pin's own memory instead of the SD
  card, so it appears instantly. There are 8 fast slots, so use them for the
  members who front most.
- **Quick Switch**: includes the member in the side button and swipe list.
- **Delete**: removes the member and takes them out of every past switch.

Saving a member with a photo takes a few seconds.

### History

- **Recent switches**, and **Sync with PluralKit…** to compare the pin's last
  day of switches with PluralKit's (see [two-way sync](#two-way-history-sync)).
- **Time fronting**: chart for 24 h, 7 days, 30 days or all time.
- **Battery**: the pin's battery voltage over the last 4 days. *Download*
  saves it, *Clear log* starts fresh.

### Wi-Fi

- **Saved networks** (up to 6): the pin joins the first one in range, top to
  bottom. Use the arrows to reorder. Untick **Use this network** to have the
  pin ignore one for a while.
- **Add a network**: *Find networks nearby* lists what the pin can see; tap one
  to fill in the name, add the password, then **Save to the pin**.
- **Dashboard password**: set, remove, or log out.

**Using a phone hotspot**: the pin only does 2.4 GHz. On an iPhone, go to
Settings → Personal Hotspot, turn on **Maximize Compatibility**, and keep that
screen open until the pin has joined. Add the hotspot as a network first,
while the pin is still on your home Wi-Fi.

### Import

- **Import a PluralKit export**: members and front history from `pk;export`.
  Importing again later updates members and keeps your pin-only settings
  (display mode, Quick Switch and so on).
- **Photos from PluralKit**: everyone's avatar as their photo. Tick *Skip
  members who already have a photo* to keep the ones you've set.
- **Sync with PluralKit** and **Instant, through your relay**: see below.

---

## PluralKit

### Sync from PluralKit (one minute)

Import tab → *Sync with PluralKit*. Enter either:

- your **system ID** (5–6 letters) if your front is public, or
- your **token** (DM PluralKit `pk;token`) to also work with a private front.

When you switch in PluralKit (for example `pk;switch Alex`), the pin adds it to
its history within about a minute. This only reads from PluralKit and never
changes anything there. The token stays on the pin and isn't shown again.

### Instant sync with the relay (optional)

If you have an always-on computer at home (a Raspberry Pi, NanoPi or similar),
the relay tells the pin about a switch within a second or two, at home or on
your hotspot. Set it up with [relay/README.md](../relay/README.md), then fill
in *Instant, through your relay* on the Import tab.

With the relay set up, **double tap the fronter** to fetch PluralKit's current
fronter right away. If the pin had switched to someone else in the meantime,
it goes back to PluralKit's fronter.

### Two-way history sync

Switches made on the pin (button, swipes, dashboard) stay on the pin only, until you
sync them. History tab → **Sync with PluralKit…** compares the last day and shows:

- *Only on the pin*: switches PluralKit doesn't have
- *Only in PluralKit*: switches the pin doesn't have

Pick **Overwrite PluralKit**, **Overwrite the pin** or **Do nothing**, or choose
switch by switch. This needs your token, not just the system ID.

---

## Battery and charging

- A full charge lasts about **6 hours** of use.
- Charge with any USB-C cable. On USB, the Status screen shows **Charging**.
- The battery percentage only updates while the pin runs on battery (on USB
  the pin can only measure the charger).
- **Low battery**: when the battery gets low, a red bar flashes for 10 seconds,
  then the screen and Wi-Fi turn off and the pin sleeps so the battery isn't
  run flat. Plug in USB: within about 2 minutes it notices and starts again.
- To turn the pin off completely, use the **PWR** button.

---

## Troubleshooting

**The dashboard won't open.**
Check your phone is on the same Wi-Fi network as the pin (Menu → Status shows
the network's name). Check Wi-Fi is on in Settings. Rescan the QR code: the
address can change when the pin moves to another network.

**The pin isn't on any network.**
On the pin, Settings → tap the Wi-Fi card off, then on again. That re-enables
every saved network. For a hotspot, see [Using a phone hotspot](#wi-fi).

**I forgot the dashboard password.**
Hold the side button for 10 seconds (the clock opens first, keep holding). The
password is removed and the dashboard opens without one.

**PluralKit switches don't show up.**
Make sure the pin has Wi-Fi and the right time (the clock). A member you
created in PluralKit after your last import isn't on the pin yet. Import again.
With the relay, its address and secret must match the relay's settings.

**A photo is slow to appear.**
Photos on the SD card take a moment to load. Tick **Fast photo** for that
member (8 slots).

**The wrong person got saved after swiping.**
Switch to the right member. If you swiped past someone, they weren't saved as
long as you kept going within 5 seconds. To correct the history, use
History → Sync with PluralKit… → Overwrite the pin.

**Text looks wrong on the namecard.**
Open the member in the dashboard and save again. The phone redraws the card
picture.
