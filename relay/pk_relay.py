#!/usr/bin/env python3
"""
PluralKit -> plurality pin relay.

PluralKit can't reach the pin (it's behind a router or a phone hotspot), so
this small server, running on an always-on computer, sits in between:

  PluralKit --(dispatch webhook, POST /pk)--> relay --(GET /front, long poll)--> pin

1. PluralKit sends an event to POST /pk whenever a switch is logged, edited or
   deleted. Each event carries a signing token; the first PING (sent when the
   webhook is registered with `pk;system webhook <url>/pk`) is trusted and its
   token remembered, later events must match it.
2. On a switch event the relay asks PluralKit who's fronting now (with your
   PluralKit token, which stays here instead of on the pin).
3. The pin keeps asking GET /front?since=<seq>: the answer comes straight away
   if the front changed since `seq`, otherwise after up to WAIT_S seconds.
   Answer: {"seq": n, "time": unix seconds, "members": ["abcde", ...]}.
4. GET /now (the phone widget): who's fronting now, with names and colours,
   answered straight away: {"time": unix seconds,
   "members": [{"id", "name", "color", "avatar"}, ...], "system_avatar": URL or null}
   (avatars: image URLs or null; the system's is checked once a day).
   Opened in a browser as /now?key=<PAGE_KEY> instead (no Authorization
   header), it's a web page: the main fronter and the front history. The page
   waits on GET /now/wait (a long poll like /front) and reloads after a switch.
5. POST /refresh (from the pin, when it's double-tapped): ask PluralKit now,
   and answer like GET /front plus "changed" (true/false). The pin then makes
   its own current fronter match PluralKit's.

Settings (environment variables, e.g. from /etc/pk-relay.env):
  PK_TOKEN    your PluralKit token (pk;token)
  PIN_SECRET  a password the pin sends with every request (make one up)
  PORT        default 8787
  PAGE_KEY    the key for the /now web page (make one up; no key = page off)
  NAME_SUFFIX a word added after every name on that page, e.g. a surname
State (the remembered signing token) goes in $STATE_DIRECTORY or ./state.

Standard library only: runs on any Python 3.9+.
"""

import hmac
import html
import json
import os
import sys
import threading
import time
import urllib.error
import urllib.request
from datetime import datetime, timezone
from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer
from urllib.parse import parse_qs, urlparse

PK_API = os.environ.get("PK_API", "https://api.pluralkit.me/v2")
PK_TOKEN = os.environ.get("PK_TOKEN", "")
PIN_SECRET = os.environ.get("PIN_SECRET", "")
PORT = int(os.environ.get("PORT", "8787"))
PAGE_KEY = os.environ.get("PAGE_KEY", "")
NAME_SUFFIX = os.environ.get("NAME_SUFFIX", "").strip()  # added after each name on the /now page
STATE_FILE = os.path.join(os.environ.get("STATE_DIRECTORY", "state"), "state.json")
USER_AGENT = "plurality-pin relay (self-hosted)"
WAIT_S = 50                 # long poll: answer at the latest after this long
REFRESH_S = 900             # also ask PluralKit this often (15 min), in case an event got lost
SYSTEM_REFRESH_S = 86400    # check the system's avatar this often (once a day)
HISTORY_COUNT = 30          # switches shown on the /now page
SWITCH_EVENTS = {"CREATE_SWITCH", "UPDATE_SWITCH", "DELETE_SWITCH", "DELETE_ALL_SWITCHES"}

front = {"seq": 0, "time": 0, "members": []}
names = []                  # [{"id", "name", "color", "avatar"}] for GET /now (the phone widget)
system = {"avatar": None, "checked": 0}  # the system's own avatar, for GET /now when nobody is fronting
changed = threading.Condition()
refresh_lock = threading.Lock()
page = {"seq": 0}           # goes up on every switch event, waking open /now pages
history = {"at": 0, "seq": -1, "switches": [], "members": {}}  # for the /now page
history_lock = threading.Lock()


def log(*args):
    print(time.strftime("%Y-%m-%d %H:%M:%S"), *args, flush=True)


def load_state():
    try:
        with open(STATE_FILE) as f:
            return json.load(f)
    except (OSError, ValueError):
        return {}


def save_state(state):
    os.makedirs(os.path.dirname(STATE_FILE) or ".", exist_ok=True)
    tmp = STATE_FILE + ".tmp"
    with open(tmp, "w") as f:
        json.dump(state, f)
    os.chmod(tmp, 0o600)
    os.replace(tmp, STATE_FILE)


def parse_time(text):
    """PluralKit's "2026-10-31T15:37:00.123456Z" -> unix seconds"""
    text = text.replace("Z", "+00:00")
    if "." in text:         # fromisoformat before 3.11 wants exactly 6 fraction digits or none
        head, rest = text.split(".", 1)
        tz = rest[next((i for i, c in enumerate(rest) if c in "+-"), len(rest)):]
        text = head + tz
    return int(datetime.fromisoformat(text).timestamp())


def refresh_system():
    """Remember the system's avatar (shown when nobody is fronting), at most once
    every SYSTEM_REFRESH_S. Best effort: tried again next round if it fails."""
    if time.time() - system["checked"] < SYSTEM_REFRESH_S:
        return
    request = urllib.request.Request(f"{PK_API}/systems/@me",
                                     headers={"Authorization": PK_TOKEN, "User-Agent": USER_AGENT})
    try:
        with urllib.request.urlopen(request, timeout=15) as res:
            system["avatar"] = json.loads(res.read()).get("avatar_url")
        system["checked"] = time.time()
    except (urllib.error.URLError, OSError, ValueError, AttributeError):
        pass


def refresh(reason):
    """Ask PluralKit who's fronting; wake the pins if it changed.
    True if it changed, False if not, None if PluralKit couldn't be asked."""
    with refresh_lock:
        request = urllib.request.Request(f"{PK_API}/systems/@me/fronters",
                                         headers={"Authorization": PK_TOKEN, "User-Agent": USER_AGENT})
        try:
            with urllib.request.urlopen(request, timeout=15) as res:
                body = res.read() if res.status == 200 else b""
        except urllib.error.HTTPError as e:
            log(f"PluralKit answered {e.code} ({reason})" + (" - check PK_TOKEN" if e.code == 401 else ""))
            return None
        except (urllib.error.URLError, OSError) as e:
            log(f"couldn't reach PluralKit ({reason}): {e}")
            return None
        if body:
            data = json.loads(body)
            when = parse_time(data["timestamp"])
            members = [m["id"] for m in data.get("members", [])]
            shown = [{"id": m["id"], "name": m.get("display_name") or m.get("name") or m["id"],
                      "color": m.get("color"), "avatar": m.get("avatar_url")}
                     for m in data.get("members", [])]
        else:
            when, members, shown = 0, [], []  # 204: no switches at all
        with changed:
            names[:] = shown                # always: names can change without a switch
            if when == front["time"] and members == front["members"]:
                return False
            front.update(seq=front["seq"] + 1, time=when, members=members)
            page["seq"] += 1
            changed.notify_all()
        log(f"front is now {members or 'nobody'} since {when} ({reason})")
        return True


def pk_get(path):
    """GET from PluralKit with the token: parsed JSON ([] for 204), None on failure."""
    request = urllib.request.Request(f"{PK_API}{path}",
                                     headers={"Authorization": PK_TOKEN, "User-Agent": USER_AGENT})
    try:
        with urllib.request.urlopen(request, timeout=15) as res:
            body = res.read()
            return json.loads(body) if res.status == 200 and body else []
    except urllib.error.HTTPError as e:
        log(f"PluralKit answered {e.code} for {path}")
    except (urllib.error.URLError, OSError, ValueError) as e:
        log(f"couldn't ask PluralKit for {path}: {e}")
    return None


def on_switch_event(kind):
    """A switch was logged, edited or deleted: update the front, and wake the
    open /now pages even if only an older switch changed (the history did)."""
    if not refresh(kind):                   # True: refresh() has woken them already
        with changed:
            page["seq"] += 1
            changed.notify_all()


def load_history():
    """Recent switches and all members, for the /now page. Asked again only
    after a switch event (or every REFRESH_S, for renamed members etc.); if
    PluralKit can't be asked, the last copy."""
    with history_lock:
        with changed:
            seq = page["seq"]
        if history["at"] and history["seq"] == seq and time.time() - history["at"] < REFRESH_S:
            return history
        switches = pk_get(f"/systems/@me/switches?limit={HISTORY_COUNT}")
        members = pk_get("/systems/@me/members")
        if isinstance(switches, list) and isinstance(members, list):
            history.update(at=time.time(), seq=seq, switches=switches,
                           members={m["id"]: m for m in members if "id" in m})
        return history


def ago(seconds):
    """1234567 -> "14 d 6 h" """
    seconds = max(0, int(seconds))
    if seconds < 60:
        return "under a minute"
    m, h, d = seconds // 60 % 60, seconds // 3600 % 24, seconds // 86400
    if d:
        return f"{d} d {h} h" if h else f"{d} d"
    if h:
        return f"{h} h {m} min" if m else f"{h} h"
    return f"{m} min"


def color_of(member, darken=20):
    """The member's colour, darkened like the widget; the default grey if none"""
    c = (member or {}).get("color") or ""
    if len(c) != 6 or any(ch not in "0123456789abcdefABCDEF" for ch in c):
        c = "333333"
    rgb = [int(c[i:i + 2], 16) * (100 - darken) // 100 for i in (0, 2, 4)]
    return "#%02x%02x%02x" % tuple(rgb)


def avatar_tag(url, size, cls="avatar"):
    if not url or not str(url).startswith("https://"):
        return f'<span class="{cls} none" style="width:{size}px;height:{size}px"></span>'
    return (f'<img class="{cls}" src="{html.escape(url)}" width="{size}" height="{size}" '
            f'alt="" loading="lazy">')


def dur_tag(start, end, now):
    """How long from start to end (None: until now, kept ticking by the page)"""
    to = f' data-to="{int(end)}"' if end is not None else ""
    return f'<span class="dur" data-from="{int(start)}"{to}>{ago((end or now) - start)}</span>'


def when_tag(unix):
    iso = datetime.fromtimestamp(unix, timezone.utc).strftime("%Y-%m-%dT%H:%M:%SZ")
    return f'<time datetime="{iso}" data-t="{int(unix)}">{iso.replace("T", " ")[:16]} UTC</time>'


def render_page():
    with changed:
        now_members = [dict(m) for m in names]
        since = front["time"]
        seq = page["seq"]
    data = load_history()
    known = data["members"]
    now = time.time()

    def full(name):
        return f"{name} {NAME_SUFFIX}" if NAME_SUFFIX else name

    def name_of(mid):
        m = known.get(mid)
        return full(m.get("display_name") or m.get("name") or mid) if m else "(deleted member)"

    first = now_members[0] if now_members else None
    if first:
        card_name = full(first["name"])
        card_avatar = first.get("avatar")
        others = ", ".join(full(m["name"]) for m in now_members[1:])
    else:
        card_name, card_avatar, others = "Nobody fronting", system["avatar"], ""
    card = [f'<section class="card" style="background:{color_of(first)}">',
            avatar_tag(card_avatar, 96),
            '<div><p class="label">Fronting now</p>',
            f'<h1>{html.escape(card_name)}</h1>']
    if others:
        card.append(f'<p class="with">with {html.escape(others)}</p>')
    if since:
        card.append(f'<p class="since">since {when_tag(since)} · {dur_tag(since, None, now)}</p>')
    card.append("</div></section>")

    rows = []
    switches = data["switches"]
    for i, sw in enumerate(switches):
        try:
            start = parse_time(sw["timestamp"])
        except (KeyError, ValueError, AttributeError):
            continue
        end = parse_time(switches[i - 1]["timestamp"]) if i else now
        ids = sw.get("members") or []
        faces = "".join(avatar_tag((known.get(mid) or {}).get("avatar_url"), 36, "face") for mid in ids[:4])
        who = ", ".join(html.escape(name_of(mid)) for mid in ids) or "<em>Nobody</em>"
        dot = color_of(known.get(ids[0]) if ids else None, 0)
        rows.append(f'<li style="--c:{dot}"><span class="faces">{faces}</span>'
                    f'<span class="who">{who}{" <b>now</b>" if i == 0 else ""}</span>'
                    f'<span class="time">{when_tag(start)}<br>{dur_tag(start, None if i == 0 else end, now)}</span></li>')
    if not rows:
        rows.append('<li class="empty">No switches yet, or PluralKit couldn\'t be asked.</li>')

    return (PAGE_HTML.replace("{CARD}", "".join(card)).replace("{ROWS}", "".join(rows))
            .replace("{SEQ}", str(seq)))


PAGE_HTML = """<!doctype html>
<html lang="en"><head><meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<meta name="referrer" content="no-referrer">
<meta name="robots" content="noindex, nofollow">
<title>Who's fronting</title>
<link rel="stylesheet" href="https://fonts.googleapis.com/css2?family=Playwrite+NZ&display=swap">
<style>
:root{--bg:#f4f4f6;--fg:#1c1c1e;--muted:#6b6b73;--row:#fff;--line:#e2e2e6}
@media (prefers-color-scheme:dark){:root{--bg:#111113;--fg:#f2f2f4;--muted:#9a9aa3;--row:#1c1c1f;--line:#2c2c30}}
*{box-sizing:border-box}
body{margin:0;background:var(--bg);color:var(--fg);font:16px/1.4 -apple-system,BlinkMacSystemFont,"Segoe UI",sans-serif}
main{max-width:640px;margin:0 auto;padding:24px 16px 40px}
.card{display:flex;gap:20px;align-items:center;color:#fff;border-radius:22px;padding:24px}
.card h1{font:400 clamp(30px,8vw,46px)/1.25 "Playwrite NZ",cursive;margin:4px 0 6px;overflow-wrap:anywhere}
.card p{margin:0;opacity:.85;font-size:14px}
.card .label{text-transform:uppercase;letter-spacing:.08em;font-size:12px;font-weight:600}
.avatar{border-radius:50%;object-fit:cover;flex:none;border:3px solid rgba(255,255,255,.85);background:rgba(255,255,255,.15)}
.avatar.none{display:inline-block}
h2{font-size:15px;text-transform:uppercase;letter-spacing:.08em;color:var(--muted);margin:32px 4px 10px}
ol{list-style:none;margin:0;padding:0;background:var(--row);border-radius:16px;overflow:hidden}
li{display:flex;align-items:center;gap:12px;padding:12px 14px;border-top:1px solid var(--line);border-left:5px solid var(--c)}
li:first-child{border-top:0}
li.empty{color:var(--muted);border-left-color:transparent}
.faces{display:flex;flex:none;min-width:36px}
.face{border-radius:50%;object-fit:cover;margin-right:-10px;border:2px solid var(--row);background:var(--line)}
.face.none{display:inline-block}
.who{flex:1;min-width:0;padding-left:8px;overflow-wrap:anywhere}
.who b{font-size:11px;text-transform:uppercase;background:var(--fg);color:var(--bg);border-radius:6px;padding:1px 6px;margin-left:6px;vertical-align:2px}
.time{flex:none;text-align:right;font-size:13px;color:var(--muted)}
footer{color:var(--muted);font-size:13px;margin:16px 4px 0}
@media (max-width:420px){.card{flex-direction:column;align-items:flex-start}}
</style></head><body><main>
{CARD}
<h2>Front history</h2>
<ol>{ROWS}</ol>
<footer id="status">Changes by itself when PluralKit logs a switch.</footer>
</main>
<script>
const KEY = new URLSearchParams(location.search).get("key") || "";
let seq = {SEQ};

function ago(s) {
  s = Math.max(0, Math.floor(s));
  if (s < 60) return "under a minute";
  const m = Math.floor(s / 60) % 60, h = Math.floor(s / 3600) % 24, d = Math.floor(s / 86400);
  if (d) return h ? `${d} d ${h} h` : `${d} d`;
  if (h) return m ? `${h} h ${m} min` : `${h} h`;
  return `${m} min`;
}
function tick() {
  const now = Date.now() / 1000;
  for (const el of document.querySelectorAll(".dur"))
    el.textContent = ago((el.dataset.to ? +el.dataset.to : now) - el.dataset.from);
}
setInterval(tick, 30000);

// Wait for the relay to say a switch happened (it holds the request until
// then, up to 50 s), then reload to show it
const sleep = ms => new Promise(r => setTimeout(r, ms));
async function watch() {
  for (;;) {
    try {
      const r = await fetch(`/now/wait?key=${encodeURIComponent(KEY)}&since=${seq}`, {cache: "no-store"});
      if (!r.ok) { await sleep(30000); continue; }
      const d = await r.json();
      if (d.seq !== seq) { location.reload(); return; }
      document.getElementById("status").textContent = "Changes by itself when PluralKit logs a switch.";
    } catch (e) {
      document.getElementById("status").textContent = "Can't reach the relay; trying again…";
      await sleep(10000);
    }
  }
}
watch();
// Phones pause pages in the background: catch up when it's shown again
document.addEventListener("visibilitychange", () => { if (!document.hidden) tick(); });

for (const el of document.querySelectorAll("time[data-t]")) {
  const d = new Date(el.dataset.t * 1000), today = new Date();
  const sameDay = d.toDateString() === today.toDateString();
  el.textContent = sameDay
    ? "today " + d.toLocaleTimeString([], {hour: "2-digit", minute: "2-digit"})
    : d.toLocaleString([], {month: "short", day: "numeric", hour: "2-digit", minute: "2-digit"});
}
</script>
</body></html>
"""

SIMPLE_PAGE = """<!doctype html><html lang="en"><head><meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1"><meta name="robots" content="noindex">
<title>Who's fronting</title></head>
<body style="font:16px -apple-system,sans-serif;max-width:480px;margin:40px auto;padding:0 16px">
<p>{TEXT}</p></body></html>"""


def refresher():
    while True:
        refresh_system()
        refresh("regular check")
        time.sleep(REFRESH_S)


class Handler(BaseHTTPRequestHandler):
    server_version = "pk-relay"
    protocol_version = "HTTP/1.1"           # keep connections open: the pin asks again and again

    def reply(self, code, body=b"", kind="text/plain", headers=None):
        if isinstance(body, (dict, list)):
            body, kind = json.dumps(body).encode(), "application/json"
        elif isinstance(body, str):
            body = body.encode()
        self.send_response(code)
        self.send_header("Content-Type", kind)
        self.send_header("Content-Length", str(len(body)))
        for name, value in (headers or {}).items():
            self.send_header(name, value)
        self.end_headers()
        self.wfile.write(body)

    def log_message(self, fmt, *args):
        pass                                # quiet: the pin polls constantly

    def pin_allowed(self):
        given = self.headers.get("Authorization", "").removeprefix("Bearer ").strip()
        return hmac.compare_digest(given, PIN_SECRET)

    def do_POST(self):
        path = urlparse(self.path).path
        if path == "/refresh":              # the pin asks: check PluralKit now (double tap)
            self.rfile.read(int(self.headers.get("Content-Length") or 0))
            if not self.pin_allowed():
                return self.reply(401, "wrong pin secret")
            result = refresh("the pin asked")
            if result is None:
                return self.reply(502, "couldn't ask PluralKit")
            with changed:
                answer = dict(front, changed=result)
            return self.reply(200, answer)
        if path != "/pk":
            return self.reply(404, "not found")
        length = int(self.headers.get("Content-Length") or 0)
        if length > 65536:
            return self.reply(413, "too big")
        try:
            event = json.loads(self.rfile.read(length))
            token = str(event.get("signing_token", ""))
            kind = str(event.get("type", ""))
        except (ValueError, AttributeError):
            return self.reply(400, "bad request")

        state = load_state()
        known = state.get("signing_token")
        if not known:
            if kind != "PING" or not token:
                return self.reply(401, "not set up yet")
            state["signing_token"] = token  # first PING: trust it (you just registered the webhook)
            save_state(state)
            log("webhook registered: signing token saved")
            return self.reply(200, "ok")
        if not hmac.compare_digest(token, known):
            return self.reply(401, "wrong signing token")
        if kind in SWITCH_EVENTS:
            threading.Thread(target=on_switch_event, args=(kind,), daemon=True).start()
        return self.reply(200, "ok")

    def do_GET(self):
        url = urlparse(self.path)
        if url.path == "/health":
            return self.reply(200, "ok")
        if url.path == "/now/wait":           # the page waits here for a switch
            return self.page(url, wait=True)
        if url.path == "/now" and "Authorization" not in self.headers:
            return self.page(url)           # a browser: the web page
        if url.path == "/now":              # the phone widget: who's fronting, with names, right away
            if not self.pin_allowed():
                return self.reply(401, "wrong pin secret")
            with changed:
                answer = {"time": front["time"], "members": list(names),
                          "system_avatar": system["avatar"]}
            return self.reply(200, answer)
        if url.path != "/front":
            return self.reply(404, "not found")
        if not self.pin_allowed():
            return self.reply(401, "wrong pin secret")
        try:
            since = int(parse_qs(url.query).get("since", ["-1"])[0])
        except ValueError:
            since = -1
        with changed:
            changed.wait_for(lambda: front["seq"] != since, timeout=WAIT_S)
            answer = dict(front)
        self.reply(200, answer)


    def page(self, url, wait=False):
        """GET /now?key=<PAGE_KEY> in a browser: the fronter and front history.
        GET /now/wait?key=…&since=<seq>: answers {"seq"} once it isn't `since`
        (a switch event), or after WAIT_S; the page then reloads if it changed."""
        headers = {"Cache-Control": "no-store", "X-Robots-Tag": "noindex",
                   "Referrer-Policy": "no-referrer"}
        kind = "text/html; charset=utf-8"
        if not PAGE_KEY:
            return self.reply(404, SIMPLE_PAGE.replace("{TEXT}", "This page is turned off."), kind, headers)
        given = parse_qs(url.query).get("key", [""])[0]
        if not hmac.compare_digest(given.encode(), PAGE_KEY.encode()):
            return self.reply(401, SIMPLE_PAGE.replace(
                "{TEXT}", "This page needs the key in its link: /now?key=…"), kind, headers)
        if wait:
            try:
                since = int(parse_qs(url.query).get("since", ["-1"])[0])
            except ValueError:
                since = -1
            with changed:
                changed.wait_for(lambda: page["seq"] != since, timeout=WAIT_S)
                seq = page["seq"]
            return self.reply(200, {"seq": seq}, headers=headers)
        return self.reply(200, render_page(), kind, headers)


def main():
    if not PK_TOKEN or not PIN_SECRET:
        sys.exit("PK_TOKEN and PIN_SECRET must be set (see /etc/pk-relay.env)")
    threading.Thread(target=refresher, daemon=True).start()
    server = ThreadingHTTPServer(("0.0.0.0", PORT), Handler)
    server.daemon_threads = True
    log(f"listening on port {PORT}")
    server.serve_forever()


if __name__ == "__main__":
    main()
