cmake_minimum_required(VERSION 3.13)

# Always include it
include(pico_sdk_import.cmake)

# Project's name (Replace PICOCASH with your own project's name)
project(PICOCASH)

# SDK Initialization - Mandatory
pico_sdk_init()

# C/C++ project files
add_executable(PICOCASH
    main.c
    keyboard.c
)

# pico_stdlib library. You can add more if they are needed
target_link_libraries(PICOCASH 
    pico_stdlib 
    hardware_timer 
    hardware_gpio 
    hardware_pwm 
    hardware_irq 
    hardware_sync)


target_include_directories(PICOCASH PUBLIC hin/)

# Enable usb output, disable uart output
pico_enable_stdio_usb(PICOCASH 1)
pico_enable_stdio_uart(PICOCASH 0)

# Need to generate UF2 file for upload to RP2040
pico_add_extra_outputs(PICOCASH)