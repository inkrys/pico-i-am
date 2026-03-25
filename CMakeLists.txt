set(PICO_BOARD pico2 CACHE STRING "Board type")

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.2.0)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.2.0-a4)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================


cmake_minimum_required(VERSION 3.12)

# Set board
# set(BOARD_NAME WIZnet_Ethernet_HAT)
# set(BOARD_NAME W5100S_EVB_PICO)
# set(BOARD_NAME W5500_EVB_PICO)
# set(BOARD_NAME W55RP20_EVB_PICO)
# set(BOARD_NAME W6100_EVB_PICO)
# set(BOARD_NAME W6300_EVB_PICO)
# set(BOARD_NAME W5500_EVB_PICO2)
set(BOARD_NAME W6100_EVB_PICO2)
# set(BOARD_NAME W6300_EVB_PICO2)

# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)
include(pico_extras_import_optional.cmake)

project(pico-i-am C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

if (PICO_SDK_VERSION_STRING VERSION_LESS "2.2.0")
    message(FATAL_ERROR "Raspberry Pi Pico SDK version 2.2.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

# If you want debug output from USB (pass -DPICO_STDIO_USB=1) this ensures you don't lose any debug output while USB is set up
if (NOT DEFINED PICO_STDIO_USB_CONNECT_WAIT_TIMEOUT_MS)
    set(PICO_STDIO_USB_CONNECT_WAIT_TIMEOUT_MS 3000)
endif()

# download CPM.cmake
file(
    DOWNLOAD
    https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.40.8/CPM.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake
    EXPECTED_HASH SHA256=78ba32abdf798bc616bab7c73aac32a17bbd7b06ad9e26a6add69de8f3ae4791
)

include(${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake)

# Add Wiznet library stuff
include(wiznet_iolib.cmake)

# Initialize the SDK
pico_sdk_init()

# Add library folder
add_subdirectory(src)
# Add test folder
add_subdirectory(tests)

CPMAddPackage(
    NAME dbg_helperz
    GIT_REPOSITORY "git@github.com:inkrys/dbg_helperz.git"
    GIT_TAG main
    # DOWNLOAD_ONLY YES
)

add_executable(pico-i-am main.c)

target_link_libraries(pico-i-am PRIVATE
    pico_stdlib
    hardware_spi
    hardware_dma
    ETHERNET_FILES
    IOLIBRARY_FILES
    MQTT_FILES
    TIMER_FILES
    dbg_helperz
    pico_i_am
)

add_compile_options(-Wall
    -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
    -Wno-unused-function # we have some for the docs that aren't called
)
if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-Wno-maybe-uninitialized)
endif()

