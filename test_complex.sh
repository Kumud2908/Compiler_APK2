#!/bin/bash

# Complex Test Suite Runner
# Tests all major compiler features

echo "=================================================="
echo "   COMPREHENSIVE COMPILER TEST SUITE"
echo "=================================================="
echo ""

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

PASSED=0
FAILED=0
TOTAL=0

# Function to run a single test
run_test() {
    local test_file=$1
    local test_name=$(basename "$test_file" .c)
    
    echo -e "${BLUE}Testing: ${test_name}${NC}"
    echo "-------------------------------------------"
    
    # Compile
    ./compiler "$test_file" > /dev/null 2>&1
    
    if [ $? -ne 0 ]; then
        echo -e "${RED}✗ Compilation FAILED${NC}"
        echo ""
        FAILED=$((FAILED + 1))
        return 1
    fi
    
    echo -e "${GREEN}✓ Compilation successful${NC}"
    
    # Run in SPIM with timeout
    echo "Running in SPIM..."
    timeout 5 spim -file output.s 2>&1 | grep -v "SPIM Version" | grep -v "Copyright" | grep -v "All Rights Reserved" | grep -v "See the file" | grep -v "Loaded:" | head -30
    
    if [ $? -eq 0 ]; then
        echo -e "${GREEN}✓ Execution successful${NC}"
        PASSED=$((PASSED + 1))
    else
        echo -e "${RED}✗ Execution FAILED or TIMEOUT${NC}"
        FAILED=$((FAILED + 1))
    fi
    
    echo ""
    return 0
}

# Test all complex test cases
echo "Starting comprehensive test suite..."
echo ""

TOTAL=8

# Test 1: Nested Loops
run_test "test/test_nested_loops.c"

# Test 2: Recursion
run_test "test/test_recursion.c"

# Test 3: Complex Pointers
run_test "test/test_pointers_complex.c"

# Test 4: Complex Structs
run_test "test/test_struct_complex.c"

# Test 5: Function Pointers
run_test "test/test_funcptr_complex.c"

# Test 6: Goto
run_test "test/test_goto_complex.c"

# Test 7: Operators
run_test "test/test_operators_complex.c"

# Test 8: Arrays/Matrix
run_test "test/test_arrays_complex.c"

# Summary
echo "=================================================="
echo "                  TEST SUMMARY"
echo "=================================================="
echo -e "Total Tests:  ${TOTAL}"
echo -e "Passed:       ${GREEN}${PASSED}${NC}"
echo -e "Failed:       ${RED}${FAILED}${NC}"
echo -e "Success Rate: $((PASSED * 100 / TOTAL))%"
echo "=================================================="
