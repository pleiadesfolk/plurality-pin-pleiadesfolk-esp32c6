file(GLOB_RECURSE UI_SRCS ui/*.c)

idf_component_register(
    SRCS "main.c" "display.c" ${UI_SRCS}
    INCLUDE_DIRS "."
    EMBED_FILES "fonts/IBMPlexMono-Regular.ttf" "fonts/IBMPlexMono-SemiBold.ttf"
)

# The Editor's generated headers include "lvgl.h" (not "lvgl/lvgl.h") only when this is set
target_compile_definitions(${COMPONENT_LIB} PRIVATE LV_LVGL_H_INCLUDE_SIMPLE)
