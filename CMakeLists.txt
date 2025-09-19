cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)  
include(pico_extras_import.cmake)  
project(my_pico C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(my_pico main.cpp)
target_link_libraries(my_pico pico_stdlib hardware_pwm hardware_clocks hardware_sleep hardware_rosc)

# pico_enable_stdio_usb(my_pico 1)
# pico_enable_stdio_uart(my_pico 1)

pico_add_extra_outputs(my_pico)
