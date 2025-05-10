# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 1.5.1)
set(toolchainVersion 13_2_Rel1)
set(picotoolVersion 2.0.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(iot_rosa_dos_ventos C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# set main code path
file(GLOB_RECURSE MAIN "src/iot_rosa_dos_ventos.c")
# set path to utility files
file(GLOB_RECURSE UTILS "src/utils/**/*.c")
# set path to includes
file(GLOB_RECURSE LIB "lib/ssd1306/*.c")
# set path to connection files
file(GLOB_RECURSE CONNECTION_FILES "src/connection/*.c")

# Add executable. Default name is the project name, version 0.1

add_executable(iot_rosa_dos_ventos 
        ${MAIN}
        ${UTILS}
        ${LIB}
        ${CONNECTION_FILES}
)

pico_set_program_name(iot_rosa_dos_ventos "iot_rosa_dos_ventos")
pico_set_program_version(iot_rosa_dos_ventos "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(iot_rosa_dos_ventos 0)
pico_enable_stdio_usb(iot_rosa_dos_ventos 1)

# Add the standard library to the build
target_link_libraries(iot_rosa_dos_ventos
        pico_stdlib
        hardware_adc
        hardware_gpio
        hardware_i2c
        pico_cyw43_arch_lwip_threadsafe_background
        )

# Add the standard include files to the build
target_include_directories(iot_rosa_dos_ventos PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/src
        ${CMAKE_CURRENT_LIST_DIR}/src/utils
        ${CMAKE_CURRENT_LIST_DIR}/src/utils/joystick
        ${CMAKE_CURRENT_LIST_DIR}/src/utils/displayOLED
        ${CMAKE_CURRENT_LIST_DIR}/src/utils/wifi
        ${CMAKE_CURRENT_LIST_DIR}/src/connection
        ${CMAKE_CURRENT_LIST_DIR}/lib
        ${CMAKE_CURRENT_LIST_DIR}/lib/ssd1306
)

# Add any user requested libraries

pico_add_extra_outputs(iot_rosa_dos_ventos)
