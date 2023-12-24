cmake_minimum_required(VERSION 3.12)

# Pull in SDK (must be before project)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(PicoWOL)
set(PICO_BOARD pico_w)

pico_sdk_init()

file(GLOB ALL_FILES
    "src/wol/wol.c"
)

add_executable(${PROJECT_NAME} src/main.c ${ALL_FILES})

include_directories(src/wol src)

include_directories(
    $ENV{PICO_SDK_PATH}/lib/lwip/contrib/ports/freertos/include/
)

set(PICO_SDK_TOOLS
    pico_stdlib 
    pico_cyw43_arch_lwip_poll
)

target_link_libraries(${PROJECT_NAME} ${PICO_SDK_TOOLS})


# enable usb output, disable uart output
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)

# generate UF2 files for pico
pico_add_extra_outputs(${PROJECT_NAME})