cmake_minimum_required(VERSION 3.16)

# ==================================================================
# Project Definition
# ==================================================================

project(
    vhdl_parser
    VERSION 0.1.0
    DESCRIPTION "A VHDL 2008 parser"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# ==================================================================
# Compiler Flags
# ==================================================================

# ==================================================================
# Dependencies
# ==================================================================

set(CPP_PEGLIB_INCLUDE_DIRS
    "${CMAKE_SOURCE_DIR}/vcpkg_installed/x64-linux/include"
)

# ==================================================================
# Main Executable
# ==================================================================

add_executable(vhdl_parser parser/vhdl_parser.cpp)

target_include_directories(
    vhdl_parser
    SYSTEM
    PRIVATE ${CPP_PEGLIB_INCLUDE_DIRS}
)

target_compile_options(
    vhdl_parser
    PRIVATE
        # Optimization
        -O3
        # Warnings
        -Wall
        -Wcast-align
        -Wdouble-promotion
        -Werror
        -Wextra
        -Wformat=2
        -Wmisleading-indentation
        -Wnon-virtual-dtor
        -Wold-style-cast
        -Woverloaded-virtual
        -Wpedantic
        -Wunused
        # Re-enable warnings for our own code after disabling them globally for peglib
        -Wconversion
        # -Wnull-dereference
        -Wshadow
        -Wsign-conversion
)

# ==================================================================
# Installation
# ==================================================================

install(TARGETS vhdl_parser RUNTIME DESTINATION bin)

# ==================================================================
# Build Info
# ==================================================================

message(STATUS "VHDL Parser:")
message(STATUS "  Version: ${PROJECT_VERSION}")
message(STATUS "  Build: ${CMAKE_BUILD_TYPE}")
message(
    STATUS
    "  Compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}"
)
message(STATUS "  Standard: C++${CMAKE_CXX_STANDARD}")
