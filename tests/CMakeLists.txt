cmake_minimum_required(VERSION 3.12)

add_executable(test_app pico_i_am_tests.c)

target_include_directories(test_app PRIVATE ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(test_app
    dbg_helperz
    pico_stdlib
)

# enable usb output, disable uart output
pico_enable_stdio_usb(test_app 1)
pico_enable_stdio_uart(test_app 0)

# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(test_app)