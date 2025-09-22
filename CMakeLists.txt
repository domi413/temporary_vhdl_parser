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
# Subdirectories and Libraries
# ==================================================================

add_subdirectory(parse)

# ==================================================================
# Main Executable
# ==================================================================

add_executable(vhdl_parser vhdl_parser.cpp)

target_link_libraries(vhdl_parser PRIVATE parse)

target_include_directories(vhdl_parser PRIVATE parse)

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
