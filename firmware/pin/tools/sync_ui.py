#!/usr/bin/env python3
"""
Bring the LVGL Editor's output into the firmware.

Run this after pressing Ctrl+B in the Editor:
    python3 tools/sync_ui.py

What it does:
  1. Copies the generated C code (screens, components, plurality_pin*.c/h) from
     test_project/ui into main/ui. main/ui is rebuilt from scratch every time,
     so don't edit files there by hand.
  2. Fonts: the Editor draws TTF files at runtime (lv_tiny_ttf), which is slow
     and eats RAM on the ESP32-C6. Instead every font+size the Editor uses is
     pre-rendered into a bitmap font (C file in main/ui/fonts, made with
     lv_font_conv from tools/node_modules), and plurality_pin_gen.c is changed
     to use those. node_modules isn't in git; to reinstall it:
         cd tools && npm ci --cache /tmp/npm-cache
  3. Images: the Editor writes each image as a C array (images/image_*_data.c).
     Those are packed into one file, assets/images.bin, which `idf.py flash`
     writes to the "assets" flash partition (see the top-level CMakeLists.txt).
     The firmware maps that partition into memory (main/assets.c), so images
     draw as fast as built-in ones without taking space in the app.
     plurality_pin_gen.c is changed to use assets_image(N) instead of the
     built-in array. Fonts (above) and images are the only changes made to
     the Editor's code. assets/index.txt lists which number is which image.

images.bin layout (little-endian):
    "PPA1", u32 image count, u32 total size
    per image: u32 offset, u32 size        (offsets from the start of the file)
    per image: LVGL image header (12 bytes) + pixel data, 4-byte aligned
"""

import re
import shutil
import struct
import subprocess
import sys
from pathlib import Path

FIRMWARE = Path(__file__).resolve().parent.parent
EDITOR_UI = FIRMWARE.parent.parent / "test_project" / "ui"
UI_DST = FIRMWARE / "main" / "ui"
ASSETS = FIRMWARE / "assets"
FONT_CONV = FIRMWARE / "tools" / "node_modules" / ".bin" / "lv_font_conv"

# Fonts up to this size get all printable ASCII characters. Bigger ones (the
# 150 px clock) would take hundreds of KB that way, so they only get BIG_FONT_CHARS.
FULL_FONT_MAX_SIZE = 60
BIG_FONT_CHARS = " 0123456789:/-"

LV_IMAGE_HEADER_MAGIC = 0x19
COLOR_FORMATS = {"LV_COLOR_FORMAT_RGB565": 0x12, "LV_COLOR_FORMAT_RGB565A8": 0x14}


def copy_code():
    if UI_DST.exists():
        shutil.rmtree(UI_DST)
    UI_DST.mkdir(parents=True)

    for name in ("plurality_pin.h", "plurality_pin.c", "plurality_pin_gen.h"):
        shutil.copy2(EDITOR_UI / name, UI_DST / name)

    count = 0
    for folder in ("screens", "components"):
        for src in (EDITOR_UI / folder).rglob("*_gen.[ch]"):
            dst = UI_DST / src.relative_to(EDITOR_UI)
            dst.parent.mkdir(parents=True, exist_ok=True)
            shutil.copy2(src, dst)
            count += 1
    print(f"code:   copied {count} generated screen/component files")


def convert_image(src: Path) -> bytes:
    """Turn an Editor image_*_data.c file into LVGL image bytes (header + pixels)."""
    text = src.read_text()

    def field(name):
        m = re.search(rf"\.{name}\s*=\s*([\w]+)", text)
        if not m:
            raise ValueError(f"{src.name}: no .{name}")
        return m.group(1)

    cf_name = field("cf")
    if cf_name not in COLOR_FORMATS:
        raise ValueError(f"{src.name}: unsupported colour format {cf_name}")
    w, h, stride = int(field("w")), int(field("h")), int(field("stride"))

    body = text[text.index("_data_map[] = {"):]
    body = body[:body.index("};")]
    data = bytes(int(b, 16) for b in re.findall(r"0x([0-9a-fA-F]{2})", body))

    cf = COLOR_FORMATS[cf_name]
    if cf_name == "LV_COLOR_FORMAT_RGB565A8":
        color_size = stride * h
        alpha = data[color_size:]
        # Fully opaque image: drop the alpha plane (smaller and faster to draw)
        if alpha and all(a == 0xFF for a in alpha):
            cf = COLOR_FORMATS["LV_COLOR_FORMAT_RGB565"]
            data = data[:color_size]

    # lv_image_header_t: magic:8 cf:8 flags:16 | w:16 h:16 | stride:16 reserved:16
    header = struct.pack("<BBHHHHH", LV_IMAGE_HEADER_MAGIC, cf, 0, w, h, stride, 0)
    return header + data


def editor_line_metrics(ttf: Path, size: int):
    """Line height and baseline exactly as LVGL's tiny_ttf (used by the Editor) computes them.

    lv_font_conv measures the glyphs it includes instead, which gives different
    numbers (much smaller for the digits-only clock font) and moves text up."""
    data = ttf.read_bytes()
    tables = {}
    for i in range(struct.unpack(">H", data[4:6])[0]):
        tag, _, offset, _ = struct.unpack(">4sIII", data[12 + 16 * i:28 + 16 * i])
        tables[tag] = offset
    units_per_em = struct.unpack(">H", data[tables[b"head"] + 18:tables[b"head"] + 20])[0]
    ascent, descent, line_gap = struct.unpack(">hhh", data[tables[b"hhea"] + 4:tables[b"hhea"] + 10])
    scale = size / units_per_em               # stbtt_ScaleForMappingEmToPixels
    return int(scale * (ascent - descent + line_gap)), int(scale * (line_gap - descent))


FONT_CREATE = re.compile(
    r'\s*lv_snprintf\(buf, 256, "%s%s", asset_path, "fonts/([^"]+)"\);\n'
    r'(\s*)(font_\w+) = lv_tiny_ttf_create_file\(buf, (\d+)\);')


def make_fonts(gen_c):
    """Pre-render every (TTF file, size) the Editor uses. Returns {(file, size): C symbol or None}."""
    out_dir = UI_DST / "fonts"
    out_dir.mkdir()
    symbols = {}
    for ttf, _, _, size in FONT_CREATE.findall(gen_c):
        size = int(size)
        if (ttf, size) in symbols:
            continue
        src = EDITOR_UI / "fonts" / ttf
        if not src.exists():
            print(f"fonts:  WARNING {ttf} is missing, its {size} px font falls back to the default font")
            symbols[(ttf, size)] = None
            continue
        symbol = "bitmap_" + re.sub(r"\W", "_", Path(ttf).stem).lower() + f"_{size}"
        chars = ["--range", "0x20-0x7E"] if size <= FULL_FONT_MAX_SIZE else ["--symbols", BIG_FONT_CHARS]
        subprocess.run([str(FONT_CONV), "--font", str(src), *chars, "--size", str(size),
                        "--bpp", "4", "--format", "lvgl", "--no-compress",
                        "--lv-font-name", symbol, "-o", str(out_dir / f"{symbol}.c")],
                       check=True, stdout=subprocess.DEVNULL)

        out = out_dir / f"{symbol}.c"
        line_height, base_line = editor_line_metrics(src, size)
        text = re.sub(r"\.line_height = -?\d+", f".line_height = {line_height}", out.read_text())
        text = re.sub(r"\.base_line = -?\d+", f".base_line = {base_line}", text)
        out.write_text(text)
        symbols[(ttf, size)] = symbol
    made = [s for s in symbols.values() if s]
    print(f"fonts:  made {len(made)} bitmap fonts")
    return symbols


def copy_assets():
    """Pack all images into assets/images.bin. Returns {image name: index}."""
    if ASSETS.exists():
        shutil.rmtree(ASSETS)
    ASSETS.mkdir()

    sources = sorted((EDITOR_UI / "images").glob("image_*_data.c"))
    names = [src.name[len("image_"):-len("_data.c")] for src in sources]
    blobs = [convert_image(src) for src in sources]

    table_size = 12 + 8 * len(blobs)
    offset = (table_size + 3) & ~3
    table, data = b"", b""
    for blob in blobs:
        table += struct.pack("<II", offset, len(blob))
        padded = blob + b"\0" * (-len(blob) % 4)
        data += padded
        offset += len(padded)
    head = struct.pack("<4sII", b"PPA1", len(blobs), offset) + table
    head += b"\0" * (-len(head) % 4)
    (ASSETS / "images.bin").write_bytes(head + data)
    (ASSETS / "index.txt").write_text("".join(f"{i:4d}  {n}\n" for i, n in enumerate(names)))

    print(f"images: packed {len(blobs)} images, {offset / 1024 / 1024:.1f} MB")
    return {name: i for i, name in enumerate(names)}


def patch_init(files):
    """Copy plurality_pin_gen.c, using bitmap fonts and image files."""
    text = (EDITOR_UI / "plurality_pin_gen.c").read_text()
    fonts = make_fonts(text)

    def to_bitmap(m):
        ttf, indent, var, size = m.group(1), m.group(2), m.group(3), int(m.group(4))
        symbol = fonts[(ttf, size)]
        value = f"(lv_font_t *)&{symbol}" if symbol else "NULL"
        return f"\n{indent}{var} = {value};  /* {ttf} at {size} px */"

    text, n_fonts = FONT_CREATE.subn(to_bitmap, text)
    externs = "".join(f"extern const lv_font_t {s};\n" for s in sorted(set(fonts.values()) - {None}))
    missing = []

    def to_path(m):
        var, name = m.group(1), m.group(2)
        if name not in files:
            missing.append(name)
            return m.group(0)
        return f"{var} = assets_image({files[name]});  /* {name} */"

    text, n = re.subn(r"(image_(\w+)) = &image_\2_data;", to_path, text)
    if missing:
        sys.exit(f"no image data for: {', '.join(missing)}")
    note = ("/* Copied by tools/sync_ui.py with two changes:\n"
            " *  - fonts are pre-rendered bitmaps (ui/fonts) instead of TTF files\n"
            " *  - images come from the assets partition (assets_image(N))\n"
            " *    instead of built-in C arrays */\n\n")
    # The bitmap font declarations and assets.h go after the includes
    first_include_end = text.index("\n", text.index("#include")) + 1
    text = (text[:first_include_end] + '#include "assets.h"\n\n' + externs
            + text[first_include_end:])
    (UI_DST / "plurality_pin_gen.c").write_text(note + text)
    print(f"init:   {n_fonts} fonts use bitmaps, {n} images load from the assets partition")


def main():
    if not EDITOR_UI.is_dir():
        sys.exit(f"Editor project not found at {EDITOR_UI}")
    if not FONT_CONV.exists():
        sys.exit("Font converter missing. Install it with:\n"
                 f"    cd {FONT_CONV.parent.parent.parent} && npm ci --cache /tmp/npm-cache")
    copy_code()
    patch_init(copy_assets())


if __name__ == "__main__":
    main()
