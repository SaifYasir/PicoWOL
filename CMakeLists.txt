cmake_minimum_required(VERSION 3.12)

# Pull in SDK (must be before project)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
#include($ENV{PICO_SDK_PATH}\\external\\pico_extras_import_optional.cmake)

project(PicoWOL)
set(PICO_BOARD pico_w)

pico_sdk_init()

add_executable(${PROJECT_NAME} main.c)

target_link_libraries(${PROJECT_NAME} pico_stdlib pico_cyw43_arch_none)

# enable usb output, disable uart output
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)

# generate UF2 files for pico
pico_add_extra_outputs(${PROJECT_NAME})