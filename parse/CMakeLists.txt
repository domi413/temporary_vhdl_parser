# Parse library for VHDL parser

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(parse peglib.h parse_vhdl_2008.cpp parse.hpp)
target_include_directories(parse PUBLIC .)
