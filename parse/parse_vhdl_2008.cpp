#include "peglib.h"

#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <string>

inline auto readFile(const std::filesystem::path &file_path, std::vector<char> &buffer) -> bool
{
    std::ifstream ifs(file_path, std::ios::in | std::ios::binary);
    if (ifs.fail()) {
        return false;
    }

    buffer.resize(static_cast<unsigned int>(ifs.seekg(0, std::ios::end).tellg()));
    if (!buffer.empty()) {
        ifs.seekg(0, std::ios::beg)
          .read(buffer.data(), static_cast<std::streamsize>(buffer.size()));
    }
    return true;
}

auto parseVhdl2008(const std::filesystem::path &hdl_file_path) -> int
{
    std::filesystem::path grammar_path
      = std::filesystem::current_path() / "grammar" / "vhdl2008.peg";
    std::ifstream grammar_file(grammar_path);
    std::string grammar_content((std::istreambuf_iterator<char>(grammar_file)),
                                std::istreambuf_iterator<char>());

    if (grammar_content.empty()) {
        std::println(
          std::cerr, "Error: Could not load grammar file from {}", grammar_path.string());
        return 1;
    }

    peg::parser parser(grammar_content);

    std::vector<char> file_contents;
    if (!readFile(hdl_file_path, file_contents)) {
        std::print(std::cerr, "Error: Could not open file {}\n", hdl_file_path.string());
        return -1;
    }

    //  parser.set_verbose_trace(true);

    // Create a way to show error messages
    parser.set_logger([](size_t line, size_t col, const std::string &msg) {
        std::println(std::cerr, "{}:{}: {}", line, col, msg);
    });

    // Enable packrat parsing for performance; it's too slow otherwise
    parser.enable_packrat_parsing();

    parser.enable_ast();
    std::shared_ptr<peg::Ast> ast;

    // Parse
    parser.parse_n(file_contents.data(), file_contents.size(), ast);

    if (ast) {
        // ast = parser.optimize_ast(ast, false);
        std::cout << peg::ast_to_s(ast);
    }

    return 0;
}
