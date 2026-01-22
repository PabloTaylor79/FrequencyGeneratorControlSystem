cmake_minimum_required(VERSION 3.15)
project(FrequencyGeneratorFirmware C ASM)

# Compiler and toolchain settings
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

# STM32H743 specific settings
set(MCU_NAME STM32H743ZITx)
set(CPU_TYPE cortex-m7)
set(OPTIMIZATION "-O2")

# Compiler flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mcpu=${CPU_TYPE}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mthumb")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OPTIMIZATION}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ffunction-sections -fdata-sections")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DSTM32H743xx")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DUSE_HAL_DRIVER")

# ASM flags
set(CMAKE_ASM_FLAGS "${CMAKE_C_FLAGS} -x assembler-with-cpp")

# Linker flags
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--gc-sections")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Map=firmware.map")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --specs=nosys.specs")

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

# Source files
set(SOURCES
    src/main.c
    src/max2871.c
    src/hal_uart.c
    src/hal_gpio.c
    src/hal_adc.c
    src/hal_i2c.c
    src/calibration.c
    src/stm32h743_startup.s
)

# Create firmware executable
add_executable(firmware.elf ${SOURCES})

# Link script
set_target_properties(firmware.elf PROPERTIES 
    LINK_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/linker.ld"
)

target_link_options(firmware.elf PRIVATE 
    -T${CMAKE_CURRENT_SOURCE_DIR}/linker.ld
)

# STM32 HAL libraries
target_link_libraries(firmware.elf
    m  # math library
    c
    gcc
)

# Generate hex and bin files
add_custom_command(TARGET firmware.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -Oihex firmware.elf firmware.hex
    COMMAND ${CMAKE_OBJCOPY} -Obinary firmware.elf firmware.bin
    COMMAND ${CMAKE_SIZE} firmware.elf
    COMMENT "Building firmware: firmware.hex, firmware.bin"
)

# Flash target
add_custom_target(flash
    COMMAND st-flash write firmware.bin 0x08000000
    DEPENDS firmware.elf
    COMMENT "Flashing firmware to device..."
)

# Debug target
add_custom_target(debug
    COMMAND gdb-multiarch firmware.elf
    DEPENDS firmware.elf
    COMMENT "Starting GDB debugger..."
)