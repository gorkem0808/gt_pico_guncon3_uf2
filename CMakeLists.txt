cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(gt_pico_guncon3 C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(gt_pico_guncon3
    src/main.c
    src/usb_descriptors.c
    src/guncon3_packet.c
)

target_include_directories(gt_pico_guncon3 PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src
)

target_link_libraries(gt_pico_guncon3 PRIVATE
    pico_stdlib
    hardware_adc
    tinyusb_device
    tinyusb_board
)

# Seri port kapalı. Pico sadece USB Vendor/GunCon3 cihazı gibi görünsün.
pico_enable_stdio_usb(gt_pico_guncon3 0)
pico_enable_stdio_uart(gt_pico_guncon3 0)

pico_add_extra_outputs(gt_pico_guncon3)
