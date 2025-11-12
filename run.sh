#!/bin/bash

# =========================
# C/C++ Compiler Test Runner
# Compiles C/C++ source to MIPS assembly and optionally runs in SPIM
# =========================

# Usage:
#   ./run.sh                    - Run all tests in test_passed/
#   ./run.sh <file.c>          - Compile and run a specific file
#   ./run.sh <file.c> --no-run - Compile only, don't execute in SPIM

# Default executable
EXECUTABLE="./compiler"

# Check if a specific file was provided
if [ $# -ge 1 ] && [ -f "$1" ]; then
    echo "Compiling $1..."
    $EXECUTABLE "$1"
    
    if [ $? -eq 0 ]; then
        echo -e "\n${GREEN}✓ Compilation successful${NC}"
        echo "Generated files:"
        echo "  - output.tac (Three-Address Code)"
        echo "  - output.s (MIPS Assembly)"
        echo "  - ast.dot (Abstract Syntax Tree)"
        
        # Check if user wants to skip execution
        if [ "$2" != "--no-run" ]; then
            echo -e "\n${BLUE}Running in SPIM simulator...${NC}"
            echo "========================================"
            timeout 5 spim -file output.s
            echo "========================================"
        fi
    else
        echo -e "${RED}✗ Compilation failed${NC}"
        exit 1
    fi
    exit 0
fi

# Use provided executable name if given
if [ $# -eq 1 ]; then
    EXECUTABLE="$1"
fi

# Ensure executable exists
if [ ! -f "$EXECUTABLE" ]; then
    echo "ERROR: Executable '$EXECUTABLE' not found!"
    echo "Please build the project first using 'make'"
    exit 1
fi

# Create outputs directory
mkdir -p outputs

echo "Using compiler executable: $EXECUTABLE"
echo "Console outputs saved to: outputs/"

# =========================
# Colors
# =========================
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

# =========================
# Counters
# =========================
total_tests=0
passed_tests=0
failed_tests=0

# =========================
# Function to get test name from file
# =========================
get_test_name() {
    local test_file="$1"
    # Strip extension (either .c or .cpp)
    echo "$(basename "$test_file" .cpp | sed 's/\.c$//')"
}

# =========================
# Function to run a normal test
# =========================
run_test() {
    local test_file="$1"
    local test_name=$(get_test_name "$test_file")
    echo -e "${YELLOW}Running test: $test_name${NC}"
    echo "Input file: $test_file"
    echo "----------------------------------------"

    echo -e "${BLUE}Test file content:${NC}"
    cat "$test_file"
    echo "----------------------------------------"

    echo -e "${BLUE}Syntax Analyzer Output:${NC}"
    # ✅ Save output to file AND print to console
    "$EXECUTABLE" "$test_file" 2>&1 | tee "outputs/${test_name}_console.txt"
    exit_code=${PIPESTATUS[0]}
    echo "----------------------------------------"

    if [ $exit_code -eq 0 ]; then
        echo -e "${GREEN}✓ PASSED: $test_name${NC}"
        ((passed_tests++))
    else
        echo -e "${RED}✗ FAILED: $test_name (Exit code: $exit_code)${NC}"
        ((failed_tests++))
    fi
    ((total_tests++))
    echo
    echo "========================================"
    echo
}

# =========================
# Function to run error tests
# =========================
run_error_test() {
    local test_file="$1"
    local test_name=$(get_test_name "$test_file")
    echo -e "${YELLOW}Running error test: $test_name${NC}"
    echo "Input file: $test_file"
    echo "----------------------------------------"

    echo -e "${BLUE}Test file content:${NC}"
    cat "$test_file"
    echo "----------------------------------------"

    echo -e "${BLUE}Syntax Analyzer Output:${NC}"
    # ✅ Save output to file AND print to console
    "$EXECUTABLE" "$test_file" 2>&1 | tee "outputs/${test_name}_console.txt"
    exit_code=${PIPESTATUS[0]}
    echo "----------------------------------------"

    if [ $exit_code -ne 0 ]; then
        echo -e "${GREEN}✓ PASSED: $test_name (Correctly detected syntax error)${NC}"
        ((passed_tests++))
    else
        echo -e "${RED}✗ FAILED: $test_name (Should have detected syntax error)${NC}"
        ((failed_tests++))
    fi
    ((total_tests++))
    echo
    echo "========================================"
    echo
}

# =========================
# Collect all test files
# =========================
mapfile -t test_files < <(find test -maxdepth 1 \( -name "*.c" -o -name "*.cpp" \) | sort -V)

if [ ${#test_files[@]} -eq 0 ]; then
    echo -e "${RED}No test files found in 'test/' directory!${NC}"
    exit 1
fi

echo "Found test files:"
for f in "${test_files[@]}"; do
    echo "  - $f"
done
echo
echo "========================================"
echo "Running all tests..."
echo "========================================"

# =========================
# Run all tests
# =========================
for test_file in "${test_files[@]}"; do
    filename=$(basename "$test_file")
    if [[ "$filename" =~ ^[Ee]rror ]]; then
        run_error_test "$test_file"
    else
        run_test "$test_file"
    fi
done

# =========================
# Summary
# =========================
echo -e "${BLUE}========================================${NC}"
echo -e "${BLUE}           TEST SUMMARY                 ${NC}"
echo -e "${BLUE}========================================${NC}"
echo "Total tests run: $total_tests"
echo -e "Passed: ${GREEN}$passed_tests${NC}"
echo -e "Failed: ${RED}$failed_tests${NC}"
echo "Console outputs saved to: outputs/"

if [ $failed_tests -eq 0 ]; then
    echo -e "${GREEN}All tests passed!${NC}"
    exit 0
else
    echo -e "${RED}Some tests failed!${NC}"
    exit 1
fi
