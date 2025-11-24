#!/bin/bash

# =========================================================================================
# COMPREHENSIVE COMPILER TEST SUITE
# Combined test runner for all C/C++ compiler tests
# Date: November 24, 2025
# =========================================================================================
# Usage:
#   ./test_comprehensive.sh                  - Run all tests in test_passed/
#   ./test_comprehensive.sh <file.c>        - Test a specific file
#   ./test_comprehensive.sh --detailed      - Show detailed error messages
#   ./test_comprehensive.sh --quick         - Quick test (no SPIM execution)
# =========================================================================================

# Configuration
EXECUTABLE="./compiler"
TEST_DIR="test_passed"
OUTPUT_DIR="outputs"
DETAILED=false
QUICK=false
SPECIFIC_FILE=""

# Parse arguments
for arg in "$@"; do
    case $arg in
        --detailed)
            DETAILED=true
            ;;
        --quick)
            QUICK=true
            ;;
        -*)
            echo "Unknown option: $arg"
            exit 1
            ;;
        *)
            if [ -f "$arg" ]; then
                SPECIFIC_FILE="$arg"
            fi
            ;;
    esac
done

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
NC='\033[0m'

# Counters
TOTAL=0
PASSED=0
FAILED=0

# Create output directory
mkdir -p "$OUTPUT_DIR"

# Check if compiler exists
if [ ! -f "$EXECUTABLE" ]; then
    echo -e "${RED}ERROR: Compiler executable not found!${NC}"
    echo "Please build the project first: make clean && make"
    exit 1
fi

# =========================================================================================
# Test Function
# =========================================================================================
test_file() {
    local file=$1
    local filename=$(basename "$file")
    local test_name="${filename%.*}"
    
    echo -e "${CYAN}==========================================${NC}"
    echo -e "${YELLOW}TEST: $filename${NC}"
    echo -e "${CYAN}==========================================${NC}"
    
    TOTAL=$((TOTAL + 1))
    
    # Compile and capture output
    "$EXECUTABLE" "$file" > "$OUTPUT_DIR/${test_name}_console.txt" 2>&1
    local compile_result=$?
    
    # Extract error information
    local semantic_errors=$(grep "Found.*semantic error" "$OUTPUT_DIR/${test_name}_console.txt" | grep -oE '[0-9]+' | head -1)
    local compilation_status=$(grep "COMPILATION" "$OUTPUT_DIR/${test_name}_console.txt")
    
    # Default to 0 if no errors found
    if [[ -z "$semantic_errors" ]]; then
        semantic_errors=0
    fi
    
    # Display results
    if [[ "$compilation_status" == *"SUCCESSFUL"* ]]; then
        echo -e "${GREEN}✓ COMPILATION: SUCCESS${NC}"
        echo -e "${GREEN}✓ SEMANTIC ERRORS: $semantic_errors${NC}"
        echo -e "${GREEN}✓ STATUS: PASSED${NC}"
        PASSED=$((PASSED + 1))
        
        # Show generated files
        if [ $DETAILED = true ]; then
            echo -e "${BLUE}Generated files:${NC}"
            echo "  - output.tac (Three-Address Code)"
            echo "  - output.s (MIPS Assembly)"
            echo "  - ast.dot (Abstract Syntax Tree)"
        fi
        
    else
        echo -e "${RED}✗ COMPILATION: FAILED${NC}"
        echo -e "${RED}✗ SEMANTIC ERRORS: $semantic_errors${NC}"
        echo -e "${RED}✗ STATUS: FAILED${NC}"
        FAILED=$((FAILED + 1))
        
        # Show error details if detailed mode
        if [ $DETAILED = true ]; then
            echo -e "${RED}Error details:${NC}"
            grep "SEMANTIC ERROR\|SYNTAX ERROR" "$OUTPUT_DIR/${test_name}_console.txt" | head -5
        else
            echo -e "${YELLOW}(Use --detailed to see error messages)${NC}"
        fi
    fi
    
    echo ""
}

# =========================================================================================
# Main Execution
# =========================================================================================

echo -e "${BLUE}==========================================${NC}"
echo -e "${BLUE}  COMPREHENSIVE COMPILER TEST SUITE${NC}"
echo -e "${BLUE}==========================================${NC}"
echo ""
echo -e "Compiler: ${CYAN}$EXECUTABLE${NC}"
echo -e "Test Directory: ${CYAN}$TEST_DIR${NC}"
echo -e "Output Directory: ${CYAN}$OUTPUT_DIR${NC}"
echo -e "Mode: ${CYAN}$([ $DETAILED = true ] && echo 'Detailed' || echo 'Standard')${NC}"
echo ""

# Test specific file or all files
if [ -n "$SPECIFIC_FILE" ]; then
    echo -e "${YELLOW}Testing specific file: $SPECIFIC_FILE${NC}"
    echo ""
    test_file "$SPECIFIC_FILE"
else
    echo -e "${YELLOW}Testing all files in $TEST_DIR/${NC}"
    echo ""
    
    # Collect all test files
    shopt -s nullglob
    test_files=($TEST_DIR/*.cpp $TEST_DIR/*.c)
    
    if [ ${#test_files[@]} -eq 0 ]; then
        echo -e "${RED}No test files found in '$TEST_DIR/' directory!${NC}"
        exit 1
    fi
    
    # Sort files
    IFS=$'\n' test_files=($(sort <<<"${test_files[*]}"))
    unset IFS
    
    # Run all tests
    for file in "${test_files[@]}"; do
        test_file "$file"
    done
fi

# =========================================================================================
# Summary
# =========================================================================================

echo -e "${BLUE}==========================================${NC}"
echo -e "${BLUE}         FINAL SUMMARY${NC}"
echo -e "${BLUE}==========================================${NC}"
echo -e "Total Tests:     ${CYAN}$TOTAL${NC}"
echo -e "Passed:          ${GREEN}$PASSED${NC}"
echo -e "Failed:          ${RED}$FAILED${NC}"

if [ $TOTAL -gt 0 ]; then
    SUCCESS_RATE=$(( (PASSED * 100) / TOTAL ))
    echo -e "Success Rate:    ${CYAN}$SUCCESS_RATE%${NC}"
fi

echo -e "${BLUE}==========================================${NC}"
echo ""

# Output directory info
echo -e "Console outputs saved to: ${CYAN}$OUTPUT_DIR/${NC}"
echo ""

# Final status
if [ $FAILED -eq 0 ]; then
    echo -e "${GREEN}🎉 All tests passed!${NC}"
    exit 0
else
    echo -e "${RED}❌ Some tests failed. Review errors above.${NC}"
    echo -e "${YELLOW}Tip: Use --detailed flag for more information${NC}"
    exit 1
fi
