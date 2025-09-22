#pragma once
#include <filesystem>

// int parse(std::filesystem::path file_path);
auto parseVhdl2008(const std::filesystem::path &hdl_file_path) -> int;
