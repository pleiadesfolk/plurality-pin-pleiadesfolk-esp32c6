const KEY_URL = "pk-relay-url";
const KEY_SECRET = "pk-relay-secret";
const REFRESH_MINUTES = 5;

const NAME_FONT = "PlaywriteNZ-Regular";
const DEFAULT_COLOR = "333333";
const NOBODY_TEXT = "Pleiadesfolk";
const DARKEN_PERCENT = 20;
const LOCK_CONTRAST = 10;
const LOCK_DARKEN = 2.5;
const LOCK_INVERT = "false";
const SMALL_AVATAR = 56;
const SMALL_LINE_GAP = -6;
const LOCK_SIZE = 68;
const NAME_SUFFIX = " Ellis";

async function askSettings() {
  const alert = new Alert();
  alert.title = "PluralKit relay";
  alert.message = "Address from anywhere (https://…) and the relay secret.";
  alert.addTextField("https://your-relay.ts.net",
    Keychain.contains(KEY_URL) ? Keychain.get(KEY_URL) : "");
  alert.addSecureTextField("relay secret",
    Keychain.contains(KEY_SECRET) ? Keychain.get(KEY_SECRET) : "");
  alert.addAction("Save");
  alert.addCancelAction("Cancel");
  if (await alert.presentAlert() === -1) return false;
  const url = alert.textFieldValue(0).trim().replace(/\/+$/, "");
  const secret = alert.textFieldValue(1).trim();
  if (!url || !secret) return false;
  Keychain.set(KEY_URL, url);
  Keychain.set(KEY_SECRET, secret);
  return true;
}

async function askRelayToRefresh() {
  if (!Keychain.contains(KEY_URL) || !Keychain.contains(KEY_SECRET)) return;
  const req = new Request(Keychain.get(KEY_URL) + "/refresh");
  req.method = "POST";
  req.headers = { Authorization: "Bearer " + Keychain.get(KEY_SECRET) };
  req.timeoutInterval = 20;
  try { await req.loadString(); } catch (e) {}
}

function tapLink(size) {
  return "scriptable:///run/" + encodeURIComponent(Script.name()) + "?tap=" + size;
}

async function fetchFront() {
  if (!Keychain.contains(KEY_URL) || !Keychain.contains(KEY_SECRET)) {
    return { error: "Open Scriptable and run this script to set it up." };
  }
  const req = new Request(Keychain.get(KEY_URL) + "/now");
  req.headers = { Authorization: "Bearer " + Keychain.get(KEY_SECRET) };
  req.timeoutInterval = 15;
  let body;
  try {
    body = await req.loadString();
  } catch (e) {
    return { error: "Can't reach the relay." };
  }
  const code = req.response && req.response.statusCode;
  if (code === 401) return { error: "Wrong relay secret." };
  if (code === 404) return { error: "Relay is too old: update pk_relay.py." };
  if (code !== 200) return { error: "Relay answered " + code + "." };
  try {
    return JSON.parse(body);
  } catch (e) {
    return { error: "Unexpected answer from the relay." };
  }
}

function hexOf(color) {
  return /^[0-9a-fA-F]{6}$/.test(color || "") ? color : DEFAULT_COLOR;
}

const fullName = m => m.name + NAME_SUFFIX;

function darker(color) {
  const rgb = parseInt(hexOf(color), 16);
  const hex = [16, 8, 0].map(s => Math.round(((rgb >> s) & 255) * (100 - DARKEN_PERCENT) / 100)
    .toString(16).padStart(2, "0")).join("");
  return new Color("#" + hex);
}

function nameFont(size) {
  try { return new Font(NAME_FONT, size); } catch (e) { return Font.boldSystemFont(size); }
}

async function loadAvatar(url) {
  if (!url) return null;
  const fm = FileManager.local();
  let hash = 0;
  for (const ch of url) hash = (hash * 31 + ch.charCodeAt(0)) | 0;
  const path = fm.joinPath(fm.cacheDirectory(), `pk-avatar-${(hash >>> 0).toString(16)}.png`);
  if (fm.fileExists(path)) return fm.readImage(path);
  try {
    const img = await new Request(url).loadImage();
    const S = 160, scale = S / Math.min(img.size.width, img.size.height);
    const w = img.size.width * scale, h = img.size.height * scale;
    const ctx = new DrawContext();
    ctx.size = new Size(S, S);
    ctx.respectScreenScale = false;
    ctx.opaque = false;
    ctx.drawImageInRect(img, new Rect((S - w) / 2, (S - h) / 2, w, h));
    const small = ctx.getImage();
    fm.writeImage(path, small);
    return small;
  } catch (e) {
    return null;
  }
}

async function lockScreenAvatar(url) {
  const raw = await loadAvatar(url);
  if (!raw) return null;
  const fm = FileManager.local();
  let hash = 0;
  for (const ch of `v3/${url}/${LOCK_CONTRAST}/${LOCK_DARKEN}/${LOCK_INVERT}`) hash = (hash * 31 + ch.charCodeAt(0)) | 0;
  const path = fm.joinPath(fm.cacheDirectory(), `pk-avatar-lock-${(hash >>> 0).toString(16)}.png`);
  if (fm.fileExists(path)) return fm.readImage(path);
  if (config.runsInWidget) return raw;
  try {
    const web = new WebView();
    await web.loadHTML("<canvas id=c></canvas>");
    const b64 = await web.evaluateJavaScript(`
      const img = new Image();
      img.onload = () => {
        const S = img.width, c = document.getElementById("c");
        c.width = c.height = S;
        const g = c.getContext("2d");
        g.beginPath(); g.arc(S / 2, S / 2, S / 2, 0, 2 * Math.PI); g.clip();
        g.drawImage(img, 0, 0, S, S);
        const d = g.getImageData(0, 0, S, S), px = d.data;
        const lum = new Float32Array(S * S), hist = new Array(256).fill(0);
        let n = 0;
        for (let i = 0; i < S * S; i++) {
          if (px[i * 4 + 3] < 128) { lum[i] = -1; continue; }
          lum[i] = 0.299 * px[i * 4] + 0.587 * px[i * 4 + 1] + 0.114 * px[i * 4 + 2];
          hist[Math.round(lum[i])]++; n++;
        }
        const level = q => { let a = 0; for (let v = 0; v < 256; v++) { a += hist[v]; if (a >= q * n) return v; } return 255; };
        const lo = level(0.02), hi = Math.max(level(0.98), lo + 1);
        let sum = 0;
        for (let i = 0; i < S * S; i++) if (lum[i] >= 0) sum += Math.min(1, Math.max(0, (lum[i] - lo) / (hi - lo)));
        const invert = ${JSON.stringify(LOCK_INVERT)} === "auto" ? sum / n > 0.5 : ${JSON.stringify(LOCK_INVERT)} === true;
        for (let i = 0; i < S * S; i++) {
          if (lum[i] < 0) continue;
          let v = Math.min(1, Math.max(0, (lum[i] - lo) / (hi - lo)));
          if (invert) v = 1 - v;
          v = 0.5 + (v - 0.5) * ${LOCK_CONTRAST};
          v = Math.pow(Math.min(1, Math.max(0, v)), ${LOCK_DARKEN});
          v = Math.round(v * 255);
          px[i * 4] = px[i * 4 + 1] = px[i * 4 + 2] = v;
        }
        g.putImageData(d, 0, 0);
        completion(c.toDataURL("image/png").split(",")[1]);
      };
      img.onerror = () => completion(null);
      img.src = "data:image/png;base64,${Data.fromPNG(raw).toBase64String()}";
    `, true);
    if (!b64) return raw;
    const out = Image.fromData(Data.fromBase64String(b64));
    fm.writeImage(path, out);
    return out;
  } catch (e) {
    return raw;
  }
}

function buildLockScreen(data, avatar) {
  const w = new ListWidget();
  w.refreshAfterDate = new Date(Date.now() + REFRESH_MINUTES * 60 * 1000);
  if (avatar && !data.error) {
    w.setPadding(0, 0, 0, 0);
    w.addAccessoryWidgetBackground = true;
    w.addSpacer();
    const img = w.addImage(avatar);
    img.imageSize = new Size(LOCK_SIZE, LOCK_SIZE);
    img.cornerRadius = LOCK_SIZE / 2;
    img.centerAlignImage();
    w.addSpacer();
    return w;
  }
  w.addAccessoryWidgetBackground = true;
  w.setPadding(4, 4, 4, 4);
  const members = (data && data.members) || [];
  w.addSpacer();
  const name = w.addText(data.error ? "!" : members[0] ? fullName(members[0]) : "Nobody");
  name.font = data.error ? Font.boldSystemFont(20) : nameFont(15);
  name.centerAlignText();
  name.lineLimit = 2;
  name.minimumScaleFactor = 0.5;
  if (!data.error && members.length > 1) {
    const more = w.addText("+" + (members.length - 1));
    more.font = Font.semiboldSystemFont(10);
    more.centerAlignText();
  }
  w.addSpacer();
  return w;
}

function buildSmall(data, avatar) {
  const w = new ListWidget();
  w.setPadding(14, 14, 12, 14);
  w.refreshAfterDate = new Date(Date.now() + REFRESH_MINUTES * 60 * 1000);
  const members = (data && data.members) || [];
  const first = members[0];
  w.backgroundColor = darker(first ? first.color : DEFAULT_COLOR);
  if (data.error) {
    w.addSpacer();
    const t = w.addText(data.error);
    t.font = Font.semiboldSystemFont(13);
    t.textColor = Color.white();
    w.addSpacer();
    return w;
  }

  const top = w.addStack();
  top.centerAlignContent();
  if (avatar) {
    const img = top.addImage(avatar);
    img.imageSize = new Size(SMALL_AVATAR, SMALL_AVATAR);
    img.cornerRadius = SMALL_AVATAR / 2;
    img.borderWidth = 2;
    img.borderColor = new Color("#ffffff", 0.85);
  }
  top.addSpacer();
  if (members.length > 1) {
    const more = top.addText("+" + (members.length - 1));
    more.font = Font.semiboldSystemFont(13);
    more.textColor = new Color("#ffffff", 0.85);
  }

  w.addSpacer();
  const lines = splitLines(first ? fullName(first) : NOBODY_TEXT, avatar ? 11 : 8, avatar ? 2 : 3);
  const column = w.addStack();
  column.layoutVertically();
  column.spacing = SMALL_LINE_GAP;
  for (const line of lines) {
    const t = column.addText(line);
    t.font = nameFont(avatar ? 22 : 30);
    t.textColor = Color.white();
    t.minimumScaleFactor = 0.4;
    t.lineLimit = 1;
  }
  return w;
}

function splitLines(text, perLine, maxLines) {
  const lines = [];
  for (const word of text.split(/\s+/).filter(Boolean)) {
    const last = lines[lines.length - 1];
    if (last !== undefined && (last + " " + word).length <= perLine) lines[lines.length - 1] = last + " " + word;
    else lines.push(word);
  }
  while (lines.length > maxLines) lines.splice(maxLines - 1, 2, lines[maxLines - 1] + " " + lines[maxLines]);
  return lines.length ? lines : [text];
}

function buildWidget(data) {
  const w = new ListWidget();
  w.setPadding(12, 16, 12, 16);
  w.refreshAfterDate = new Date(Date.now() + REFRESH_MINUTES * 60 * 1000);
  const family = config.widgetFamily || "medium";
  const size = { small: 30, medium: 40, large: 52 }[family] || 40;
  const members = (data && data.members) || [];
  const first = members[0];
  w.backgroundColor = darker(first ? first.color : DEFAULT_COLOR);

  w.addSpacer();
  const name = w.addText(data.error ? data.error : first ? fullName(first) : NOBODY_TEXT);
  if (data.error) {
    name.font = Font.semiboldSystemFont(14);
  } else {
    name.font = nameFont(size);
    name.minimumScaleFactor = 0.4;
    name.lineLimit = family === "small" ? 3 : 2;
  }
  name.textColor = Color.white();
  name.leftAlignText();
  w.addSpacer();

  const others = members.slice(1).map(fullName);
  if (!data.error && (others.length || data.time)) {
    const row = w.addStack();
    row.centerAlignContent();
    const muted = new Color("#ffffff", 0.75);
    if (others.length) {
      const t = row.addText("+ " + others.join(", "));
      t.font = Font.semiboldSystemFont(11);
      t.textColor = muted;
      t.lineLimit = 1;
    }
    row.addSpacer();
    if (data.time && family !== "small") {
      const d = row.addDate(new Date(data.time * 1000));
      d.applyRelativeStyle();
      d.font = Font.mediumSystemFont(11);
      d.textColor = muted;
      d.rightAlignText();
    }
  }
  return w;
}

const tapped = (args.queryParameters || {}).tap;
let preview = "medium";
if (tapped) {
  preview = ["medium", "small", "lock"].includes(tapped) ? tapped : "medium";
  await askRelayToRefresh();
} else if (!config.runsInWidget) {
  const haveSettings = Keychain.contains(KEY_URL) && Keychain.contains(KEY_SECRET);
  let choice = 3;
  if (haveSettings) {
    const a = new Alert();
    a.title = "Who's fronting";
    a.addAction("Show widget (4x2)");
    a.addAction("Show small widget (2x2)");
    a.addAction("Show Lock Screen widget");
    a.addAction("Change address or secret");
    choice = await a.presentSheet();
  }
  if (choice === 3) await askSettings();
  preview = ["medium", "small", "lock"][choice] || "medium";
}

const data = await fetchFront();
const family = config.runsInWidget ? (config.widgetFamily || "medium") : preview;
const first = !data.error && data.members && data.members[0];
const lockAvatarUrl = data.error ? null : first ? first.avatar : data.system_avatar;
if (!config.runsInWidget && lockAvatarUrl) await lockScreenAvatar(lockAvatarUrl);
let widget;
if (family === "lock" || family.startsWith("accessory")) {
  widget = buildLockScreen(data, lockAvatarUrl ? await lockScreenAvatar(lockAvatarUrl) : null);
} else if (family === "small") {
  widget = buildSmall(data, first ? await loadAvatar(first.avatar) : null);
} else {
  widget = buildWidget(data);
}
widget.url = tapLink(family.startsWith("accessory") ? "lock" : family === "small" ? "small" : "medium");
if (config.runsInWidget) {
  Script.setWidget(widget);
} else if (family === "lock") {
  if (widget.presentAccessoryCircular) await widget.presentAccessoryCircular();
  else await widget.presentSmall();
} else if (family === "small") {
  await widget.presentSmall();
} else {
  await widget.presentMedium();
}
Script.complete();
