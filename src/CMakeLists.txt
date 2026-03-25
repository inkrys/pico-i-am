cmake_minimum_required(VERSION 3.12)

add_library(pico_i_am STATIC
    pico_i_am.c
)

target_link_libraries(pico_i_am PRIVATE
    pico_stdlib
    hardware_spi
    hardware_dma
    ETHERNET_FILES
    IOLIBRARY_FILES
    MQTT_FILES
    TIMER_FILES
    dbg_helperz	   
)

target_include_directories(pico_i_am PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)