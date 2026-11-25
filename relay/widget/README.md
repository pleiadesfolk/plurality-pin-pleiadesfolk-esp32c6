# Who's fronting: Scriptable widget

A widget for the Scriptable app (iPhone/iPad) that asks your PluralKit relay
(`GET /now`) who's fronting and shows them the way the pin's namecard does.

| Size | Where | What it shows |
| --- | --- | --- |
| Medium (4x2) | Home Screen, Mac desktop | The name in the pin's font on the member's colour, with co-fronters and how long ago the switch was along the bottom |
| Small (2x2) | Home Screen, Mac desktop | The avatar in a circle at the top, the name below it, "+N" for co-fronters. Without an avatar, just the name in a bigger size |
| Small round (1x1) | Lock Screen | The first fronter's avatar filling the circle. When nobody is fronting, the system's PluralKit avatar. Without an avatar, the name and "+N" |

## Setup

1. Install `PlaywriteNZ.mobileconfig` from this folder (the pin's font).
   Without it, names show in the system font.
2. Paste all of `front-widget.js` into a new script in Scriptable.
3. Run it once in the app. It asks for the relay's address from anywhere
   (`https://…`) and the relay secret, and keeps both in the iPhone's
   Keychain.
4. Add a Scriptable widget and pick this script. In the widget settings
   (long-press → Edit Widget), set **When Interacting** to **Run Script**.

To change the address or secret later, run the script in the app again and
choose **Change address or secret**. Running it in the app also lets you
preview each size.

## Tapping a widget

A tap opens Scriptable, asks the relay to check PluralKit right now
(`POST /refresh`, the same thing a double tap on the pin does), and shows the
widget you tapped with the current fronter. Scriptable usually then updates
the widgets. If the relay can't reach PluralKit, it shows the last front the
relay knows about.

The tap finds the script by its name, so don't rename it after adding the
widget. Scriptable has no buttons inside widgets, so a tap always opens the
app.

## Settings

These are at the top of the script.

| Setting | Default | Meaning |
| --- | --- | --- |
| `REFRESH_MINUTES` | `5` | How often to refresh. iOS treats this as a request and decides when widgets actually refresh |
| `NAME_FONT` | `PlaywriteNZ-Regular` | The font for names, by PostScript name. Regular (weight 400) is the heaviest Playwrite NZ comes in. Any font installed on the phone works, e.g. `SnellRoundhand-Bold` (built into iOS, no install needed) |
| `DEFAULT_COLOR` | `333333` | The colour for members without one, and for "nobody fronting" |
| `NOBODY_TEXT` | `Pleiadesfolk` | Shown when no one is fronting |
| `DARKEN_PERCENT` | `20` | The background is the member's colour, this much darker |
| `NAME_SUFFIX` | `" Ellis"` | Added after every fronter's name |
| `SMALL_AVATAR` | `56` | 2x2: avatar size in points |
| `SMALL_LINE_GAP` | `-6` | 2x2: space between the name's lines. Negative pulls them closer, `0` is the font's own (loose) spacing, positive spreads them out |
| `LOCK_SIZE` | `68` | Lock Screen: avatar size in points (the round spot is about 70) |
| `LOCK_CONTRAST` | `2` | Lock Screen avatar: higher means stronger contrast (`1` = only evened out) |
| `LOCK_DARKEN` | `2.5` | Lock Screen avatar: higher means darker mid-tones (`1` = unchanged) |
| `LOCK_INVERT` | `"false"` | Lock Screen avatar: `"auto"` flips mostly-light pictures (such as drawings on white); or `true` / `false` |

## How it works

- **Errors:** the relay's answer is read as text first, because its error
  answers aren't JSON. 401 shows "Wrong relay secret", 404 "Relay is too old"
  (update `pk_relay.py`).
- **Avatars** are cropped square from the middle to 160 px and cached in
  Scriptable's cache folder, so they aren't downloaded on every refresh.
- **2x2 name lines:** Scriptable has no line-spacing setting, so the name is
  split into lines at spaces (about 11 characters per line and up to 2 lines
  with an avatar; 8 and 3 without). Each line is its own text, stacked with
  `SMALL_LINE_GAP` between them. Anything left over goes on the last line,
  which shrinks to fit.
- **Lock Screen avatar:** iOS draws Lock Screen widgets in one tint, by
  brightness only. Bright shows as solid and dark as see-through, so a photo
  with mid-tones comes out faint. The script makes the avatar black and
  white, stretches it from black to white, flips it if it's mostly light,
  adds contrast, darkens the mid-tones and cuts it round. Scriptable has no
  image filters, so a hidden web page does this. The result is cached; if it
  fails, the plain photo is used.
- The avatar is added as content, not as the widget background, because iOS
  removes widget backgrounds on the Lock Screen. iOS's frosted circle sits
  behind it so dark parts read as dark.
- The Lock Screen picture is only made when the script runs in the app
  (including after a tap), never inside the widget: Lock Screen widgets get
  very little memory and time, and the hidden web page is too much for them,
  so the widget came out blank. The widget only reads the prepared picture.
  If there isn't one yet (a new fronter since the app last ran), it shows the
  plain photo cut round until you tap it or open the script.
- In the app's preview, the Lock Screen widget shows in full colour; on the
  Lock Screen, iOS tints it.
