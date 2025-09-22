#include <cstring>
#include <filesystem>
#include <iostream>
#include <parse.hpp>
#include <print>
#include <string>

void printHelp(std::string_view program_name)
{
    std::print("VHDL 2008 Parser\n\n"
               "Usage: {} [OPTIONS]\n\n"
               "Options:\n"
               "  -h, --help           Show this help message\n"
               "  -i, --input <file>   Input VHDL file to parse\n"
               "\nExample:\n"
               "  {} -i example/hello.vhd\n",
               program_name,
               program_name);
}

auto main(int argc, char *argv[]) -> int
{
    std::string hdl_file_name;
    const std::span<char *> args(argv, argc);

    for (auto it = args.begin() + 1; it != args.end(); ++it) {
        std::string_view arg = *it;

        if (arg == "-h" || arg == "--help") {
            printHelp(args[0]);
            return 0;
        }
        if (arg == "-i" || arg == "--input") {
            if (++it != args.end()) {
                hdl_file_name = *it;
            } else {
                std::print(std::cerr, "Error: {} requires a filename argument\n", arg);
                printHelp(args[0]);
                return 1;
            }
        } else if (arg.starts_with('-')) {
            std::print(std::cerr, "Error: Unknown option {}\n", arg);
            printHelp(args[0]);
            return 1;
        } else {
            if (hdl_file_name.empty()) {
                hdl_file_name = arg;
            } else {
                std::print(std::cerr, "Error: Multiple input files specified\n");
                printHelp(args[0]);
                return 1;
            }
        }
    }

    if (hdl_file_name.empty()) {
        std::print(std::cerr, "Error: No input file specified\n");
        printHelp(args[0]);
        return 1;
    }

    std::filesystem::path hdl_file_path(hdl_file_name);

    if (std::filesystem::is_regular_file(hdl_file_path)) {
        std::print("Parsing VHDL file: {}\n", hdl_file_path.string());
        parseVhdl2008(hdl_file_path);
    } else {
        std::print(std::cerr,
                   "Error: {} does not exist or is not a file; please specify a file.\n",
                   hdl_file_path.string());
        return 1;
    }

    return 0;
}
