# Button/LED daughterboard test. See README.md.
cmake_minimum_required(VERSION 3.16)

# Same board support package and drivers as the pin firmware
set(EXTRA_COMPONENT_DIRS "${CMAKE_CURRENT_LIST_DIR}/../pin/components")

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(daughterboard_test)
