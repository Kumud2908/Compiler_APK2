#!/bin/bash

# =========================
# C/C++ Syntax Analyzer Test Runner
# =========================

# Default executable
EXECUTABLE="./compiler"

# Use provided executable name if given
if [ $# -eq 1 ]; then
    EXECUTABLE="$1"
fi

# Check if executable exists
if [ ! -f "$EXECUTABLE" ]; then
    echo "ERROR: Executable '$EXECUTABLE' not found!"
    echo "Please build the project first using 'make'"
    exit 1
fi

# Check if test directory exists
if [ ! -d "test_passed" ]; then
    echo "ERROR: Test directory not found! Creating sample tests..."
    make test-setup
fi

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

# Counters
total_tests=0
passed_tests=0
failed_tests=0

# Function to run a single test
run_test() {
    local test_file="$1"
    local test_name=$(basename "$test_file" .c)
    echo -e "${YELLOW}Running test: $test_name${NC}"
    echo "Input file: $test_file"
    echo "----------------------------------------"
    
    echo -e "${BLUE}Test file content:${NC}"
    cat "$test_file"
    echo "----------------------------------------"
    
    echo -e "${BLUE}Syntax Analyzer Output:${NC}"
    "$EXECUTABLE" "$test_file"
    exit_code=$?
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

# Function for error tests
run_error_test() {
    local test_file="$1"
    local test_name=$(basename "$test_file" .c)
    echo -e "${YELLOW}Running error test: $test_name${NC}"
    echo "Input file: $test_file"
    echo "----------------------------------------"
    
    echo -e "${BLUE}Test file content:${NC}"
    cat "$test_file"
    echo "----------------------------------------"
    
    echo -e "${BLUE}Syntax Analyzer Output:${NC}"
    "$EXECUTABLE" "$test_file"
    exit_code=$?
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

# Get all .c files safely
mapfile -t test_files < <(find test -maxdepth 1 -name "*.c" | sort -V)

if [ ${#test_files[@]} -eq 0 ]; then
    echo -e "${RED}No test files found!${NC}"
    exit 1
fi

echo -e "${BLUE}Found test files:${NC}"
for file in "${test_files[@]}"; do
    echo "  - $(basename "$file")"
done
echo

# Run tests
for test_file in "${test_files[@]}"; do
    filename=$(basename "$test_file")
    if [[ "$filename" =~ ^[Ee]rror ]]; then
        run_error_test "$test_file"
    else
        run_test "$test_file"
    fi
done


# Summary
echo -e "${BLUE}========================================${NC}"
echo -e "${BLUE}           TEST SUMMARY                 ${NC}"
echo -e "${BLUE}========================================${NC}"
echo "Total tests run: $total_tests"
echo -e "Passed: ${GREEN}$passed_tests${NC}"
echo -e "Failed: ${RED}$failed_tests${NC}"

if [ $failed_tests -eq 0 ]; then
    echo -e "${GREEN}All tests passed!${NC}"
    exit 0
else
    echo -e "${RED}Some tests failed!${NC}"
    exit 1
fi
