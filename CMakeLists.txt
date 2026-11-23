cmake_minimum_required(VERSION 3.22)

#
# This file is generated only once,
# and is not re-generated if converter is called multiple times.
#
# User is free to modify the file as much as necessary
#

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)


# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME Head_control_board_750)

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

# Enable CMake support for ASM and C languages
enable_language(C ASM)

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME})

# Add STM32CubeMX generated sources
add_subdirectory(cmake/stm32cubemx)

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths
)

#方法一：添加相应的文件夹为指定路径
file(GLOB GlobalControl_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/user/GlobalControl/*.c)
file(GLOB MotorControl_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/user/MotorControl/*.c)
file(GLOB UsartControl_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/user/UsartControl/*.c)


# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user sources here
    ${GlobalControl_SOURCES}
    ${MotorControl_SOURCES}
    ${UsartControl_SOURCES}
)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined include paths
    user/GlobalControl
    user/MotorControl
    user/UsartControl
)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined symbols
)

# Remove wrong libob.a library dependency when using cpp files
list(REMOVE_ITEM CMAKE_C_IMPLICIT_LINK_LIBRARIES ob)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx

    # Add user defined libraries
)

# DMA 接收缓冲区：将 .dma_buffer 输出段固定到 D2 SRAM 起始（0x30000000，
# DMA1/DMA2 本域直达）。dma_buffer.ld 为用户自有片段脚本，经 -T 与
# CubeMX 生成的 STM32H750XX_FLASH.ld 叠加，主脚本保持不动；本文件仅
# 首次生成，CubeMX 重新生成代码不会覆盖此配置。
target_link_options(${CMAKE_PROJECT_NAME} PRIVATE
    -T ${CMAKE_SOURCE_DIR}/dma_buffer.ld
    -u _printf_float
)

#Generate HEX and BIN files after build
add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex
    $<TARGET_FILE:${CMAKE_PROJECT_NAME}>
    ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}.hex
    COMMENT "Generating HEX file"
)

add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary
    $<TARGET_FILE:${CMAKE_PROJECT_NAME}>
    ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}.bin
    COMMENT "Generating BIN file"
)
