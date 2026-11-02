file(GLOB_RECURSE UI_SRCS ui/*.c)

idf_component_register(
    SRCS "main.c" "display.c" "nav.c" "assets.c" "brightness.c" "status.c" "wifi.c" "store.c" "web.c" "fronter.c" "textpic.c" "photos.c" "connect.c" "settings.c" "storage_info.c" "button.c" "boot.c" "pksync.c" "auth.c" "power.c" "timezones.c" "zone.c" ${UI_SRCS}
    INCLUDE_DIRS "."
    EMBED_FILES "../dashboard/index.html"
                "../dashboard/fonts/PlaywriteUSTrad-Regular.ttf"
                "../dashboard/fonts/Inter-Medium.ttf" "../dashboard/fonts/Inter-SemiBold.ttf" "../dashboard/fonts/Inter-Bold.ttf"
                "../dashboard/fonts/IBMPlexMono-Regular.ttf" "../dashboard/fonts/IBMPlexMono-Medium.ttf" "../dashboard/fonts/IBMPlexMono-SemiBold.ttf"
)

# The Editor's generated headers include "lvgl.h" (not "lvgl/lvgl.h") only when this is set
target_compile_definitions(${COMPONENT_LIB} PRIVATE LV_LVGL_H_INCLUDE_SIMPLE)
