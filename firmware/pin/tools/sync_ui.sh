#!/bin/sh
# Copy the LVGL Editor's generated C files into the firmware.
# Run this after pressing Ctrl+B in the Editor:
#   sh tools/sync_ui.sh
#
# Only the files the firmware currently uses are copied. When a new screen is
# added to the firmware, add it (and any components it uses) to the lists below.

set -e
cd "$(dirname "$0")/.."

SRC=../../test_project/ui
DST=main/ui

SCREENS="watch"
COMPONENTS="base/container base/column base/row base/label"

for s in $SCREENS; do
    mkdir -p "$DST/screens"
    cp "$SRC/screens/${s}_gen.c" "$SRC/screens/${s}_gen.h" "$DST/screens/"
done

for c in $COMPONENTS; do
    name=$(basename "$c")
    mkdir -p "$DST/components/$c"
    cp "$SRC/components/$c/${name}_gen.c" "$SRC/components/$c/${name}_gen.h" "$DST/components/$c/"
done

echo "Copied screens: $SCREENS"
echo "Copied components: $COMPONENTS"
