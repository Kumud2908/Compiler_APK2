#!/bin/bash

# Comprehensive Test Script - Detailed Version
# Date: November 24, 2025

echo "==========================================="
echo "COMPREHENSIVE COMPILER TEST SUITE"
echo "==========================================="
echo ""

TEST_DIR="test_passed"
PASSED=0
FAILED=0
TOTAL=0

test_file() {
    local file=$1
    local filename=$(basename "$file")
    
    echo "========================================="
    echo "TEST: $filename"
    echo "========================================="
    
    TOTAL=$((TOTAL + 1))
    
    # Compile and capture result
    ./compiler "$file" > /tmp/test_output.txt 2>&1
    
    # Check for semantic errors
    ERRORS=$(grep "Found.*semantic error" /tmp/test_output.txt)
    SUCCESS=$(grep "COMPILATION SUCCESSFUL" /tmp/test_output.txt)
    
    if [[ ! -z "$SUCCESS" ]]; then
        echo "✓ COMPILATION: SUCCESS"
        ERROR_COUNT=$(echo "$ERRORS" | grep -oE '[0-9]+' | head -1)
        if [[ -z "$ERROR_COUNT" || "$ERROR_COUNT" == "0" ]]; then
            echo "✓ SEMANTIC ERRORS: 0"
            echo "✓ STATUS: PASSED"
            PASSED=$((PASSED + 1))
        else
            echo "✗ SEMANTIC ERRORS: $ERROR_COUNT"
            echo "✗ STATUS: FAILED"
            FAILED=$((FAILED + 1))
            grep "SEMANTIC ERROR" /tmp/test_output.txt | head -3
        fi
    else
        echo "✗ COMPILATION: FAILED"
        echo "✗ STATUS: FAILED"
        FAILED=$((FAILED + 1))
        grep "SEMANTIC ERROR\|SYNTAX ERROR" /tmp/test_output.txt | head -3
    fi
    
    echo ""
}

# Run tests
for file in $TEST_DIR/*.cpp $TEST_DIR/*.c; do
    if [[ -f "$file" ]]; then
        test_file "$file"
    fi
done

echo "==========================================="
echo "FINAL SUMMARY"
echo "==========================================="
echo "Total Tests:     $TOTAL"
echo "Passed:          $PASSED"
echo "Failed:          $FAILED"
echo "Success Rate:    $(( (PASSED * 100) / TOTAL ))%"
echo "==========================================="
