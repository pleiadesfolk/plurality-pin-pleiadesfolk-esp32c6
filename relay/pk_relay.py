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

Settings (environment variables, e.g. from /etc/pk-relay.env):
  PK_TOKEN    your PluralKit token (pk;token)
  PIN_SECRET  a password the pin sends with every request (make one up)
  PORT        default 8787
State (the remembered signing token) goes in $STATE_DIRECTORY or ./state.

Standard library only: runs on any Python 3.9+.
"""

import hmac
import json
import os
import sys
import threading
import time
import urllib.error
import urllib.request
from datetime import datetime
from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer
from urllib.parse import parse_qs, urlparse

PK_API = os.environ.get("PK_API", "https://api.pluralkit.me/v2")
PK_TOKEN = os.environ.get("PK_TOKEN", "")
PIN_SECRET = os.environ.get("PIN_SECRET", "")
PORT = int(os.environ.get("PORT", "8787"))
STATE_FILE = os.path.join(os.environ.get("STATE_DIRECTORY", "state"), "state.json")
USER_AGENT = "plurality-pin relay (self-hosted)"
WAIT_S = 50                 # long poll: answer at the latest after this long
REFRESH_S = 300             # also ask PluralKit this often, in case an event got lost
SWITCH_EVENTS = {"CREATE_SWITCH", "UPDATE_SWITCH", "DELETE_SWITCH", "DELETE_ALL_SWITCHES"}

front = {"seq": 0, "time": 0, "members": []}
changed = threading.Condition()
refresh_lock = threading.Lock()


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


def refresh(reason):
    """Ask PluralKit who's fronting; wake the pins if it changed"""
    with refresh_lock:
        request = urllib.request.Request(f"{PK_API}/systems/@me/fronters",
                                         headers={"Authorization": PK_TOKEN, "User-Agent": USER_AGENT})
        try:
            with urllib.request.urlopen(request, timeout=15) as res:
                body = res.read() if res.status == 200 else b""
        except urllib.error.HTTPError as e:
            log(f"PluralKit answered {e.code} ({reason})" + (" - check PK_TOKEN" if e.code == 401 else ""))
            return
        except (urllib.error.URLError, OSError) as e:
            log(f"couldn't reach PluralKit ({reason}): {e}")
            return
        if body:
            data = json.loads(body)
            when = parse_time(data["timestamp"])
            members = [m["id"] for m in data.get("members", [])]
        else:
            when, members = 0, []           # 204: no switches at all
        with changed:
            if when == front["time"] and members == front["members"]:
                return
            front.update(seq=front["seq"] + 1, time=when, members=members)
            changed.notify_all()
        log(f"front is now {members or 'nobody'} since {when} ({reason})")


def refresher():
    while True:
        refresh("regular check")
        time.sleep(REFRESH_S)


class Handler(BaseHTTPRequestHandler):
    server_version = "pk-relay"
    protocol_version = "HTTP/1.1"           # keep connections open: the pin asks again and again

    def reply(self, code, body=b"", kind="text/plain"):
        if isinstance(body, (dict, list)):
            body, kind = json.dumps(body).encode(), "application/json"
        elif isinstance(body, str):
            body = body.encode()
        self.send_response(code)
        self.send_header("Content-Type", kind)
        self.send_header("Content-Length", str(len(body)))
        self.end_headers()
        self.wfile.write(body)

    def log_message(self, fmt, *args):
        pass                                # quiet: the pin polls constantly

    def do_POST(self):
        if urlparse(self.path).path != "/pk":
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
            threading.Thread(target=refresh, args=(kind,), daemon=True).start()
        return self.reply(200, "ok")

    def do_GET(self):
        url = urlparse(self.path)
        if url.path == "/health":
            return self.reply(200, "ok")
        if url.path != "/front":
            return self.reply(404, "not found")
        given = self.headers.get("Authorization", "").removeprefix("Bearer ").strip()
        if not hmac.compare_digest(given, PIN_SECRET):
            return self.reply(401, "wrong pin secret")
        try:
            since = int(parse_qs(url.query).get("since", ["-1"])[0])
        except ValueError:
            since = -1
        with changed:
            changed.wait_for(lambda: front["seq"] != since, timeout=WAIT_S)
            answer = dict(front)
        self.reply(200, answer)


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
