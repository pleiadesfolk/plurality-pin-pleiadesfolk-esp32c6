# Introduction

You know how the Internet works by now — it’s a series of servers and computers all around the world that takes electricity and power to run. The Cloud Costs Money, so API requests every minute to PluralKit is going to add up. We don’t want to be responsible for something that causes a degradation of a service that has been incredibly useful and that we don’t pay for, so this is a… more considerate solution. 

So here’s a relay program that lets the PK API respond to a switch, rather than have the pin or device reach out for a request to check if something’s change.

# PluralKit relay

Lets PluralKit tell the pin about a switch the moment it happens. PluralKit can’t reach the pin directly, so this small program runs on any always-on machine you control — a homelab box, a Raspberry Pi/NanoPi, a NAS, or a VPS — receives PluralKit’s dispatch webhooks, and passes the current front on to the pin.

```
PluralKit ──HTTPS──> your public URL ──> relay (:8787) <── pin (long poll, LAN and/or public URL)
```

Your PluralKit token stays on the relay host. The pin only needs the relay’s address(es) and a shared secret that you can generate on your computer. 

## What you need

- A machine that stays on, with **Python 3.9+** (standard library only, no `pip install`). Linux, macOS, BSD, Windows or a container all work.
- A way to give it a **public HTTPS URL** for PluralKit to call — a reverse proxy with your own domain, Tailscale Funnel, Cloudflare Tunnel, or similar.
- Your PluralKit token (`pk;token` in a DM with PluralKit).

On a budget? See [Cheapest setup](#cheapest-setup): it can cost nothing.

## How it works

| Endpoint | Who calls it | Auth |
| --- | --- | --- |
| `POST /pk` | PluralKit dispatch webhook | PluralKit’s signing token (learned from the first PING, then enforced) |
| `GET /front?since=N` | the pin, long poll (held up to 50 s) | `Authorization: Bearer <PIN_SECRET>` |
| `POST /refresh` | the pin, on double tap | `Authorization: Bearer <PIN_SECRET>` |
| `GET /now?key=…` | you, in a browser | `PAGE_KEY` in the link |
| `GET /now/wait?key=…&since=N` | that page, long poll (held up to 50 s) | `PAGE_KEY` in the link |
| `GET /health` | you / your monitoring | none, answers `ok` |

The relay also re-checks PluralKit every 15 minutes in case an event is lost.

### Configuration

All settings are environment variables:

| Variable | Required | Meaning |
| --- | --- | --- |
| `PK_TOKEN` | yes | your PluralKit token |
| `PIN_SECRET` | yes | a shared secret the pin sends with every request |
| `PAGE_KEY` | no | the key for the fronter page (see below); without it the page is off |
| `NAME_SUFFIX` | no | a word added after every name on the fronter page, e.g. a surname (`NAME_SUFFIX=Ellis` shows “Alex Ellis”) |
| `PORT` | no | listen port, default `8787` (binds `0.0.0.0`) |
| `STATE_DIRECTORY` | no | where `state.json` (the remembered webhook signing token) is kept; default `./state` |

Make up a secret with:

```bash
python3 -c "import secrets; print(secrets.token_hex(16))"
```

Treat `PK_TOKEN` like a password: keep it in a file only the service can read,

or in your platform’s secret store.

### Fronter page

Open `https://YOUR-PUBLIC-URL/now?key=YOUR-PAGE-KEY` in any browser to see
who's fronting now and the last 30 switches, with how long each lasted. It
changes by itself within a second or two of a switch (logged, edited or
deleted), the same way the pin does. Make the key the same way as the secret above,
add `PAGE_KEY=...` next to the other two settings, and restart the relay.

The page shows everything your token can see, private members included, so
only share the link with people who may see that. To lock everyone out
again, change `PAGE_KEY` and restart.

Opening the page doesn't ask PluralKit anything new each time: the relay
fetches the switch history and member list only after a switch, or every 15
minutes, and keeps them in memory. Names are written in Playwrite NZ,
loaded from Google Fonts.

## 1. Run the relay

Quick test, from this folder:

```bash
PK_TOKEN=... PIN_SECRET=... python3 pk_relay.py
```

It logs `listening on port 8787` and, after asking PluralKit,

`front is now […]`. `PluralKit answered 401` means the token is wrong.

For permanent use, run it under whatever supervisor you already use. It needs

to restart on failure and keep `STATE_DIRECTORY` between restarts. Some

examples:

### systemd (most Linux distributions)

A hardened unit is included ([pk-relay.service](pk-relay.service)). It runs

as a throwaway user, reads secrets from `/etc/pk-relay.env`, and keeps state

in `/var/lib/private/pk-relay`.

```bash
sudo mkdir -p /opt/pk-relay
sudo cp pk_relay.py /opt/pk-relay/
sudo cp pk-relay.service /etc/systemd/system/
sudo install -m 600 /dev/null /etc/pk-relay.env
sudoedit /etc/pk-relay.env        # add PK_TOKEN=... and PIN_SECRET=...
sudo systemctl daemon-reload
sudo systemctl enable --now pk-relay
journalctl -u pk-relay -f
```

### Docker / Podman

No image needed; the stock Python image is enough:

```bash
docker run -d --name pk-relay --restart unless-stopped \
  -p 8787:8787 \
  --env-file ./pk-relay.env \
  -e STATE_DIRECTORY=/state -v pk-relay-state:/state \
  -v "$PWD/pk_relay.py:/app/pk_relay.py:ro" \
  python:3.12-slim python3 -u /app/pk_relay.py
```

Or the same in Compose:

```yaml
services:
  pk-relay:
    image: python:3.12-slim
    command: python3 -u /app/pk_relay.py
    restart: unless-stopped
    ports: ["8787:8787"]
    env_file: ./pk-relay.env
    environment:
      STATE_DIRECTORY: /state
    volumes:
      - ./pk_relay.py:/app/pk_relay.py:ro
      - pk-relay-state:/state
volumes:
  pk-relay-state:
```

### Anything else

launchd, OpenRC, runit, supervisord, NSSM on Windows, a Proxmox LXC… The

recipe is the same: run `python3 pk_relay.py` with the two variables set, a

persistent `STATE_DIRECTORY`, and automatic restart.

## 2. Give it a public HTTPS address

PluralKit must reach `POST /pk` over HTTPS. If you also want the pin to work

away from home, it needs `GET /front` and `POST /refresh` on the same public

address. Pick whichever fits your setup:

- **Reverse proxy you already run** (Caddy, nginx, Traefik, HAProxy…): proxy a
  hostname to `http://RELAY-HOST:8787`. Caddy example:

  ```
  pk.example.com {
      reverse_proxy 127.0.0.1:8787
  }
  ```

- **Tailscale Funnel** (no open ports, no domain needed):
  `sudo tailscale funnel --bg 8787` → `https://HOST.TAILNET.ts.net`.
- **Cloudflare Tunnel**: add a public hostname pointing at
  `http://localhost:8787`.

Two things to check whichever you choose:

- **Timeouts:** the pin’s `GET /front` is held open for up to 50 seconds.
  Set the proxy’s read/idle timeout to at least 60 s (nginx:
  `proxy_read_timeout 75s;`), or the pin will see errors.
- **Pass the `Authorization` header through** unchanged.

Test it from outside your network (e.g. a phone on mobile data):

`https://YOUR-PUBLIC-URL/health` should say `ok`.

## 3. Register the webhook with PluralKit

In a DM with PluralKit on Discord:

```
pk;system webhook https://YOUR-PUBLIC-URL/pk
```

PluralKit sends a PING right away. The relay log should say

`webhook registered: signing token saved`. From then on, events signed with

any other token are rejected.

## 4. Point the pin at the relay

In the pin’s dashboard, Import tab, “Instant, through your relay”:

- **Address at home:** `http://RELAY-LAN-IP:8787` — the relay’s address on the
  pin’s home Wi-Fi. Give the host a fixed IP (a DHCP reservation in your
  router) so it doesn’t move. Leave empty if the relay isn’t on your home
  network (e.g. a VPS).
- **Address from anywhere:** `https://YOUR-PUBLIC-URL`
- **Relay secret:** your `PIN_SECRET`

Save. Within a minute the dashboard should say “Connected at home” (or

“Connected over the internet”). Log a switch with `pk;switch`; the pin should

change within a second or two.

## Cheapest setup

The relay is tiny: it uses about 20 MB of memory and almost no CPU, and

moves well under 100 MB of traffic a month. So whatever you run it on, the

expensive part is never the relay.

**If you already have something that stays on** (a Pi, NAS, home server, an

old laptop): use it. Add the relay with systemd or Docker as above and expose

it with Tailscale Funnel. Funnel’s free plan gives you HTTPS and a public name

with no domain, no open ports and no router changes. Total extra cost:

nothing, plus a little electricity.

**If you don’t**, a free cloud VM does the job. Google Cloud’s Always Free

`e2-micro` is the best fit: it doesn’t expire and isn’t taken away for being

idle (Oracle Cloud’s Always Free VMs are bigger, but Oracle can reclaim

instances that look idle, and a relay looks idle). Recipe:

### Free Google Cloud VM + Tailscale Funnel

1. **Create an account** at <https://cloud.google.com/free>. It asks for a
   card to verify you, but the resources below stay inside the free tier.
2. **Set a spending alert first** so a mistake can’t surprise you: Billing →
   Budgets & alerts → Create budget, amount `1` (in your currency), keep the
   default email alerts.
3. **Create the VM:** Compute Engine → VM instances → Create instance
   (enable the Compute Engine API if asked). Change only these:
   - **Region:** `us-central1`, `us-west1` or `us-east1`. Other regions are
     not free.
   - **Machine type:** E2 → `e2-micro`.
   - **Boot disk:** Change → Debian (latest), disk type **Standard persistent
     disk**, 10 GB. The default *Balanced* disk is **not** free; this is the
     easiest thing to get wrong.
   - Leave networking as it is (ephemeral external IP, no firewall rules
     needed: Funnel only makes outgoing connections).

   The page’s monthly estimate may still show a price; the free-tier

   discount is applied on your bill.

4. **Open a terminal on it:** click **SSH** next to the VM. In that window,
   use the upload button (top right) to upload `pk_relay.py` and
   `pk-relay.service` from this folder. They land in your home directory.
5. **Install the relay:**

   ```bash
   sudo mkdir -p /opt/pk-relay
   sudo cp ~/pk_relay.py /opt/pk-relay/
   sudo cp ~/pk-relay.service /etc/systemd/system/
   python3 -c "import secrets; print(secrets.token_hex(16))"   # your PIN_SECRET, copy it
   sudo install -m 600 /dev/null /etc/pk-relay.env
   sudo nano /etc/pk-relay.env
   ```

   Put in two lines, `PK_TOKEN=your-pluralkit-token` and

   `PIN_SECRET=the-secret-you-copied`, save (Ctrl+O, Enter, Ctrl+X), then:

   ```bash
   sudo systemctl daemon-reload
   sudo systemctl enable --now pk-relay
   journalctl -u pk-relay -n 20 --no-pager
   ```

   Look for `front is now […]`.

6. **Make it public:**

   ```bash
   curl -fsSL https://tailscale.com/install.sh | sh
   sudo tailscale up
   sudo tailscale funnel --bg 8787
   ```

   Open the sign-in link `tailscale up` prints (free account). The first

   `funnel` run prints another link to allow Funnel; open it, then run the

   command again. It shows your address, e.g. `https://pk-relay.tail1234.ts.net`.

7. Continue with [step 3](#3-register-the-webhook-with-pluralkit) and
   [step 4](#4-point-the-pin-at-the-relay). In the pin’s dashboard, leave
   **Address at home** empty and put the Funnel address in **Address from
   anywhere**.

Now and then, log in with **SSH** and run `sudo apt update && sudo apt upgrade`

to keep the VM patched. Free-tier terms can change; the budget alert is your

safety net.

## Maintenance

- **Changed the token or secret:** update the environment and restart the
  relay.
- **Re-registered or reset the webhook in PluralKit:** PluralKit generates a
  new signing token, which the relay will reject. Delete `state.json` in
  `STATE_DIRECTORY` and restart, then run `pk;system webhook …` again.
  (systemd unit: `/var/lib/private/pk-relay/state.json`.)
- **Monitoring:** `GET /health` returns `ok` with no auth, handy for Uptime
  Kuma or similar.
- **Moving hosts:** copy `state.json` along, or reset the webhook as above.
