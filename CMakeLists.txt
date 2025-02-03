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
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(Aula-27-01-Tarefa-1-1 C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(Aula-27-01-Tarefa-1-1 Aula-27-01-Tarefa-1-1.c 
    lib/ws2812.c
)

pico_set_program_name(Aula-27-01-Tarefa-1-1 "Aula-27-01-Tarefa-1-1")
pico_set_program_version(Aula-27-01-Tarefa-1-1 "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(Aula-27-01-Tarefa-1-1 1)
pico_enable_stdio_usb(Aula-27-01-Tarefa-1-1 1)

#Converte o .pio para .h
pico_generate_pio_header(Aula-27-01-Tarefa-1-1 ${CMAKE_CURRENT_LIST_DIR}/ws2818b.pio)

target_sources(Aula-27-01-Tarefa-1-1 PRIVATE Aula-27-01-Tarefa-1-1.c)

# Add the standard library to the build
target_link_libraries(Aula-27-01-Tarefa-1-1
        pico_stdlib
        pico_bootrom
        hardware_pio
        hardware_gpio
        hardware_irq
        hardware_adc
        pico_bootrom)

# Add the standard include files to the build
target_include_directories(Aula-27-01-Tarefa-1-1 PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        Aula-27-01-Tarefa-1-1 PRIVATE ${CMAKE_CURRENT_LIST_DIR}/lib
)

# Add any user requested libraries
target_link_libraries(Aula-27-01-Tarefa-1-1 
        
        )

pico_add_extra_outputs(Aula-27-01-Tarefa-1-1)

