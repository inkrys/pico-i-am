# ioLibrary_Driver
add_library(IOLIBRARY_FILES STATIC)

target_sources(IOLIBRARY_FILES PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/ioLibrary_Driver/src/wizchip_spi.c
        ${CMAKE_CURRENT_LIST_DIR}/ioLibrary_Driver/src/wizchip_gpio_irq.c
        )

if(${BOARD_NAME} STREQUAL W55RP20_EVB_PICO OR ${WIZNET_CHIP} STREQUAL W6300)
pico_generate_pio_header(IOLIBRARY_FILES ${CMAKE_CURRENT_LIST_DIR}/ioLibrary_Driver/src/wizchip_qspi_pio.pio)

target_sources(IOLIBRARY_FILES PUBLIC 
        ${CMAKE_CURRENT_LIST_DIR}/ioLibrary_Driver/src/wizchip_qspi_pio.c
)

target_include_directories(IOLIBRARY_FILES PUBLIC
        ${WIZNET_DIR}/Ethernet
        ${CMAKE_CURRENT_LIST_DIR}/ioLibrary_Driver/inc
        ${CMAKE_CURRENT_LIST_DIR}
)
endif()

target_include_directories(IOLIBRARY_FILES PUBLIC
        ${WIZNET_DIR}/Ethernet
        ${CMAKE_CURRENT_LIST_DIR}/ioLibrary_Driver/inc
        ${CMAKE_CURRENT_LIST_DIR}
        )

target_link_libraries(IOLIBRARY_FILES PUBLIC
        pico_stdlib
        hardware_pio
        hardware_spi
        hardware_dma
        hardware_clocks
        )

# timer
add_library(TIMER_FILES STATIC)

target_sources(TIMER_FILES PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/timer/timer.c
        )

target_include_directories(TIMER_FILES PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/timer
        )

target_link_libraries(TIMER_FILES PRIVATE
        pico_stdlib      
        )


# # board
# add_library(BOARD_FILES STATIC)

# target_sources(BOARD_FILES PUBLIC
#         ${CMAKE_CURRENT_LIST_DIR}/board/can/can.c
#         )

# pico_generate_pio_header(BOARD_FILES ${CMAKE_CURRENT_LIST_DIR}/board/can/can.pio)

# target_include_directories(BOARD_FILES PUBLIC
#         ${CMAKE_CURRENT_LIST_DIR}/board/can
#         )

# target_link_libraries(BOARD_FILES PRIVATE
#         pico_stdlib      
#         cmsis_core
#         hardware_pio
#         hardware_dma
#         )

# port_common
add_library(PORT_COMMON_FILES STATIC)

target_include_directories(PORT_COMMON_FILES PUBLIC
${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(PORT_COMMON_FILES PUBLIC
pico_stdlib
hardware_clocks
hardware_spi
hardware_dma
hardware_pio
)