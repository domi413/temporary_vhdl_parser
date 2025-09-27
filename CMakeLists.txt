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
# Conan Integration
# ==================================================================

# Include Conan-generated toolchain and dependencies
find_file(CONAN_TOOLCHAIN conan_toolchain.cmake PATHS ${CMAKE_BINARY_DIR} NO_DEFAULT_PATH)
if(CONAN_TOOLCHAIN)
    include(${CONAN_TOOLCHAIN})
endif()

# ==================================================================
# Dependencies
# ==================================================================

find_package(spdlog REQUIRED)
find_package(Catch2 REQUIRED)
find_package(CLI11 REQUIRED)
find_package(peglib REQUIRED)

# ==================================================================
# Main Executable
# ==================================================================

add_executable(vhdl_parser parser/vhdl_parser.cpp)

target_link_libraries(
    vhdl_parser
    PRIVATE
        spdlog::spdlog
        CLI11::CLI11
        peglib
)

# ==================================================================
# Compiler Flags
# ==================================================================

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
