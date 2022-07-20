cmake_minimum_required(VERSION 3.13)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(c3bridge C CXX)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(c3bridge)
add_subdirectory(tiny_editline/src)


target_sources(c3bridge PRIVATE c3bridge.c )
target_link_libraries(c3bridge pico_stdlib hardware_uart tiny_editline)


pico_enable_stdio_usb(c3bridge 1)
pico_enable_stdio_uart(c3bridge 0)
pico_add_extra_outputs(c3bridge)

