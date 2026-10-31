# PluralKit relay

Lets PluralKit tell the pin about a switch the moment it happens. PluralKit
can't reach the pin directly, so this small program runs on an always-on
computer (here: a NanoPi with Debian/Ubuntu/Armbian), receives PluralKit's
"dispatch webhook" messages, and passes the front on to the pin.

```
PluralKit ──https──> Tailscale Funnel ──> relay (NanoPi :8787) <── pin (home: http, away: https via Funnel)
```

Your PluralKit token lives on the NanoPi (in `/etc/pk-relay.env`, readable by
root only). The pin only needs the relay's addresses and a secret.

## 1. Copy the relay to the NanoPi

From the Mac, in this repository (replace `USER` and `NANOPI-IP`):

```bash
scp relay/pk_relay.py relay/pk-relay.service USER@NANOPI-IP:~
```

Then log in to the NanoPi and check Python is 3.9 or newer:

```bash
ssh USER@NANOPI-IP
python3 --version
```

## 2. Install it as a service

On the NanoPi:

```bash
sudo mkdir -p /opt/pk-relay
sudo cp ~/pk_relay.py /opt/pk-relay/
sudo cp ~/pk-relay.service /etc/systemd/system/
```

Make up a secret for the pin (copy what it prints; you'll type it into the
pin's dashboard later):

```bash
python3 -c "import secrets; print(secrets.token_hex(16))"
```

Create the settings file:

```bash
sudo nano /etc/pk-relay.env
```

with these two lines (your PluralKit token from `pk;token`, and the secret):

```
PK_TOKEN=your-pluralkit-token
PIN_SECRET=the-secret-you-made
```

Save (Ctrl+O, Enter, Ctrl+X), then lock it down and start the relay:

```bash
sudo chmod 600 /etc/pk-relay.env
sudo systemctl daemon-reload
sudo systemctl enable --now pk-relay
journalctl -u pk-relay -n 20 --no-pager
```

The log should end with `front is now [...]` (your current fronters' IDs).
`PluralKit answered 401` means the token is wrong.

## 3. Make it reachable from the internet (Tailscale Funnel)

```bash
curl -fsSL https://tailscale.com/install.sh | sh
sudo tailscale up
```

Open the link it prints and sign in (a free Tailscale account). Then:

```bash
sudo tailscale funnel --bg 8787
```

The first time, it prints a link to turn Funnel on for your account: open it,
allow it, and run the command again. It then shows your address, like
`https://nanopi.tail1234.ts.net`. Check it from your phone (on mobile data):
`https://nanopi.tail1234.ts.net/health` should say `ok`.

## 4. Tell PluralKit about it

In a DM with PluralKit on Discord:

```
pk;system webhook https://nanopi.tail1234.ts.net/pk
```

PluralKit checks the address right away. The relay log
(`journalctl -u pk-relay -n 5 --no-pager`) should say
`webhook registered: signing token saved`.

## 5. Tell the pin

Find the NanoPi's address on your home network (`hostname -I`, the first
one). Ideally give it a fixed address in your router's DHCP settings, so it
doesn't change.

In the pin's dashboard, Import tab, "Instant, through your relay":

- Address at home: `http://NANOPI-IP:8787`
- Address from anywhere: `https://nanopi.tail1234.ts.net`
- Relay secret: the secret from step 2

Save. Within a minute it should say "Connected at home". Then switch with
`pk;switch` and the pin should change within a second or two.

## Useful later

```bash
journalctl -u pk-relay -f            # watch the log live (Ctrl+C to stop)
sudo systemctl restart pk-relay      # after changing /etc/pk-relay.env
sudo tailscale funnel status         # is the public address on?
```

If you ever reset the webhook in PluralKit, delete the remembered signing
token so the relay accepts the new one:
`sudo rm /var/lib/private/pk-relay/state.json && sudo systemctl restart pk-relay`
