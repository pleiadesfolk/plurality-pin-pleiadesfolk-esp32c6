cmake_minimum_required(VERSION 3.16)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(plurality_pin)

# Images (packed by tools/sync_ui.py) are written to the "assets" partition by
# `idf.py flash`. The firmware maps them into memory, see main/assets.c.
esptool_py_flash_to_partition(flash "assets" "${CMAKE_CURRENT_SOURCE_DIR}/assets/images.bin")
