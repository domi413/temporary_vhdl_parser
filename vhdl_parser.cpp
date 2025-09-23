#include "peglib.h"

#include <filesystem>
#include <fstream>
#include <print>
#include <string>

auto readFile(const std::filesystem::path &file_path) -> std::string
{
    std::ifstream file(file_path);
    if (!file) {
        std::println(std::cerr, "Error: Could not open file: {}", file_path.string());
        return "";
    }
    return std::string{ std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>() };
}

auto main() -> int
{
    std::filesystem::path hdl_file_path = "example/hello.vhd";
    const std::filesystem::path grammar_path = "grammar/vhdl2008.peg";

    // Read grammar file
    const auto grammar_content = readFile(grammar_path);
    if (grammar_content.empty()) {
        std::println(
          std::cerr, "Error: Could not load grammar file from {}", grammar_path.string());
        return 1;
    }

    // Create parser
    peg::parser vhdl_parser{ grammar_content };
    if (!vhdl_parser) {
        std::println(std::cerr, "Error: Failed to create parser from grammar");
        return 1;
    }

    // Enable AST generation and packrat parsing
    vhdl_parser.enable_ast();
    vhdl_parser.enable_packrat_parsing();

    // Setup error logging
    vhdl_parser.set_logger([](std::size_t line, std::size_t col, const std::string &msg) {
        std::println(std::cerr, "Parse error at {}:{}: {}", line, col, msg);
    });

    // Read VHDL file
    const auto vhdl_content = readFile(hdl_file_path);
    if (vhdl_content.empty()) {
        std::println(std::cerr, "Error: Could not read VHDL file {}", hdl_file_path.string());
        return 1;
    }

    // Parse and output AST
    std::shared_ptr<peg::Ast> ast;
    if (const bool parse_success = vhdl_parser.parse(vhdl_content, ast); parse_success && ast) {
        std::println("{}", peg::ast_to_s(ast));
        return 0;
    }

    std::println(std::cerr, "Parse failed!");
    return 1;
}
