cmake_minimum_required(VERSION 3.12)

# Pull in SDK (must be before project)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(PicoWOL)
set(PICO_BOARD pico_w)
set(PICO_DEOPTIMIZED_DEBUG 1)

pico_sdk_init()

file(GLOB_RECURSE ALL_FILES
    "src/**/*.c"
)

add_executable(${PROJECT_NAME} src/main.c ${ALL_FILES})

# Include directories for LWIP
include_directories(
    $ENV{PICO_SDK_PATH}/lib/lwip/contrib/ports/freertos/include/
)

include_directories(
    src/wol 
    src/wifi
    src
)

set(PICO_SDK_TOOLS
    pico_stdlib 
    pico_cyw43_arch_lwip_poll
    hardware_i2c
)

target_link_libraries(${PROJECT_NAME} ${PICO_SDK_TOOLS})


# enable uart output, disable usb output
pico_enable_stdio_usb(${PROJECT_NAME} 0)
pico_enable_stdio_uart(${PROJECT_NAME} 1)

# generate UF2 files for pico
pico_add_extra_outputs(${PROJECT_NAME})