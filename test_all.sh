#!/bin/bash

# Comprehensive Test Script for All Test Cases
# Date: November 24, 2025

echo "==========================================="
echo "COMPREHENSIVE COMPILER TEST SUITE"
echo "==========================================="
echo ""

# Colors for output
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

TEST_DIR="test_passed"
TOTAL_TESTS=0
PASSED_TESTS=0
FAILED_TESTS=0
PARTIAL_TESTS=0

# Function to test a single file
test_file() {
    local file=$1
    local filename=$(basename "$file")
    
    echo "----------------------------------------"
    echo "Testing: $filename"
    echo "----------------------------------------"
    
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    
    # Compile the file
    ./compiler "$file" 2>&1 | grep -E "(SEMANTIC|Found|COMPILATION)" > /tmp/compile_result.txt
    
    # Check for semantic errors
    SEMANTIC_ERRORS=$(grep "Found.*semantic error" /tmp/compile_result.txt | grep -oE '[0-9]+' | head -1)
    COMPILATION_STATUS=$(grep "COMPILATION" /tmp/compile_result.txt)
    
    if [[ -z "$SEMANTIC_ERRORS" ]]; then
        SEMANTIC_ERRORS=0
    fi
    
    echo "Semantic Errors: $SEMANTIC_ERRORS"
    
    if [[ $SEMANTIC_ERRORS -eq 0 ]]; then
        if [[ $COMPILATION_STATUS == *"SUCCESSFUL"* ]]; then
            echo -e "${GREEN}✓ PASSED${NC} - Compilation successful"
            PASSED_TESTS=$((PASSED_TESTS + 1))
            
            # Try to run with SPIM (limited output)
            echo "Output preview:"
            timeout 2 spim -file output.s 2>&1 | grep -v "^$" | tail -10
            
        else
            echo -e "${YELLOW}⚠ PARTIAL${NC} - No errors but compilation incomplete"
            PARTIAL_TESTS=$((PARTIAL_TESTS + 1))
        fi
    else
        echo -e "${RED}✗ FAILED${NC} - $SEMANTIC_ERRORS semantic error(s)"
        FAILED_TESTS=$((FAILED_TESTS + 1))
        
        # Show error details
        ./compiler "$file" 2>&1 | grep "SEMANTIC ERROR" | head -5
    fi
    
    echo ""
}

# Test all files in test_passed directory
echo "Starting tests..."
echo ""

for file in $TEST_DIR/*.cpp $TEST_DIR/*.c; do
    if [[ -f "$file" ]]; then
        test_file "$file"
    fi
done

# Summary
echo "==========================================="
echo "TEST SUMMARY"
echo "==========================================="
echo "Total Tests:   $TOTAL_TESTS"
echo -e "${GREEN}Passed:        $PASSED_TESTS${NC}"
echo -e "${YELLOW}Partial:       $PARTIAL_TESTS${NC}"
echo -e "${RED}Failed:        $FAILED_TESTS${NC}"
echo ""

SUCCESS_RATE=$(( (PASSED_TESTS * 100) / TOTAL_TESTS ))
echo "Success Rate:  $SUCCESS_RATE%"
echo "==========================================="

if [[ $FAILED_TESTS -eq 0 ]]; then
    echo -e "${GREEN}All critical tests passed!${NC}"
    exit 0
else
    echo -e "${RED}Some tests failed. Review errors above.${NC}"
    exit 1
fi
