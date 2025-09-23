.PHONY: all clean run debug lint format check-format build

SOURCES_CPP = $(shell find . -name "*.cpp" -o -name "*.hpp" | grep -v build/)
SOURCES_CMake = $(shell find . -name "CMakeLists.txt" | grep -v build/)
LINT_COMMON_FLAGS = -p build/
LINT_TIDY_FLAGS = --warnings-as-errors='*'

all: clean build

build:
	@echo "Configuring and building with Ninja..."
	@cmake -B build -DCMAKE_BUILD_TYPE=Release -GNinja
	@cmake --build build

debug:
	@echo "Configuring and building in debug mode..."
	@cmake -B build -DCMAKE_BUILD_TYPE=Debug -GNinja
	@cmake --build build

clean:
	@echo "Removing build directory..."
	@rm -rf build/

run: build
	@echo "Running the VHDL parser..."
	@if [ -f "example/hello.vhd" ]; then \
		./build/vhdl_parser example/hello.vhd; \
	else \
		echo "No example file found."; \
	fi

test: build
	@echo "Testing with example file..."
	@if [ -f "example/hello.vhd" ]; then \
		./build/vhdl_parser example/hello.vhd; \
	else \
		echo "No example file found."; \
	fi

help: build
	@echo "VHDL Parser - Usage: ./build/vhdl_parser [input_file]"
	@echo "Default input file: example/hello.vhd"

check-format:
	@echo "Checking code formatting..."
	@if command -v clang-format >/dev/null 2>&1; then \
		if clang-format --dry-run --Werror $(SOURCES_CPP) 2>/dev/null; then \
			echo "✓ All files are properly formatted"; \
		else \
			echo "⚠ Some files need formatting. Run 'make format' to fix."; \
		fi; \
	else \
		echo "clang-format not found, skipping format check"; \
	fi

format:
	@echo "Formatting code..."
	@if command -v clang-format >/dev/null 2>&1; then \
		clang-format -i $(SOURCES_CPP); \
		echo "✓ Code formatting complete"; \
	else \
		echo "clang-format not found, skipping formatting"; \
	fi

lint: build
	@echo "Running clang-tidy..."
	@clang-tidy $(LINT_COMMON_FLAGS) $(LINT_TIDY_FLAGS) $(SOURCES_CPP)
	@echo "✓ Linting complete"

install: build
	@echo "Installing VHDL parser..."
	@cd build && ninja install


fix: build
	@echo "Auto-fixing clang-tidy issues..."
	@clang-tidy --fix $(LINT_COMMON_FLAGS) $(SOURCES_CPP)
	@echo "✓ Auto-fixes applied"
