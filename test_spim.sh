#!/bin/bash

# =========================================================================================
# SPIM SIMULATOR TEST RUNNER
# Compiles C/C++ to MIPS and executes in SPIM simulator
# Date: November 24, 2025
# =========================================================================================
# Usage:
#   ./test_spim.sh                          - Interactive: select file to test
#   ./test_spim.sh <file.c>                 - Test specific file
#   ./test_spim.sh output.s                 - Run existing MIPS assembly
#   ./test_spim.sh --all                    - Test all files (with timeout)
#   ./test_spim.sh <file.c> --debug         - Show SPIM debug info
# =========================================================================================

# Configuration
EXECUTABLE="./compiler"
TEST_DIR="test_passed"
TIMEOUT=5
DEBUG=false
RUN_ALL=false
INPUT_FILE=""

# Parse arguments
for arg in "$@"; do
    case $arg in
        --debug)
            DEBUG=true
            ;;
        --all)
            RUN_ALL=true
            ;;
        -*)
            echo "Unknown option: $arg"
            exit 1
            ;;
        *)
            INPUT_FILE="$arg"
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

# Check if SPIM is installed
if ! command -v spim &> /dev/null; then
    echo -e "${RED}ERROR: SPIM simulator not found!${NC}"
    echo "Install with: sudo apt-get install spim"
    exit 1
fi

# =========================================================================================
# Function: Compile and Run in SPIM
# =========================================================================================
compile_and_run() {
    local source_file=$1
    local filename=$(basename "$source_file")
    local test_name="${filename%.*}"
    
    echo -e "${CYAN}==========================================${NC}"
    echo -e "${YELLOW}Testing: $filename${NC}"
    echo -e "${CYAN}==========================================${NC}"
    
    # Compile the source file
    echo -e "${BLUE}[1/2] Compiling...${NC}"
    "$EXECUTABLE" "$source_file" 2>&1 | grep -E "(PARSING|SEMANTIC|COMPILATION)"
    
    if [ ${PIPESTATUS[0]} -ne 0 ]; then
        echo -e "${RED}✗ Compilation failed${NC}"
        echo ""
        return 1
    fi
    
    if [ ! -f "output.s" ]; then
        echo -e "${RED}✗ No MIPS assembly generated${NC}"
        echo ""
        return 1
    fi
    
    echo -e "${GREEN}✓ Compilation successful${NC}"
    echo ""
    
    # Run in SPIM
    echo -e "${BLUE}[2/2] Executing in SPIM...${NC}"
    echo -e "${CYAN}========================================${NC}"
    
    if [ $DEBUG = true ]; then
        # Show full SPIM output
        timeout $TIMEOUT spim -file output.s
    else
        # Filter out SPIM header noise
        timeout $TIMEOUT spim -file output.s 2>&1 | \
            grep -v "SPIM Version" | \
            grep -v "Copyright" | \
            grep -v "All Rights Reserved" | \
            grep -v "See the file" | \
            grep -v "Loaded:" | \
            grep -v "^$"
    fi
    
    local exit_code=$?
    echo -e "${CYAN}========================================${NC}"
    
    if [ $exit_code -eq 0 ]; then
        echo -e "${GREEN}✓ Execution completed successfully${NC}"
        return 0
    elif [ $exit_code -eq 124 ]; then
        echo -e "${YELLOW}⚠ Execution timed out (${TIMEOUT}s)${NC}"
        return 2
    else
        echo -e "${RED}✗ Execution failed (exit code: $exit_code)${NC}"
        return 1
    fi
    
    echo ""
}

# =========================================================================================
# Function: Run existing MIPS assembly
# =========================================================================================
run_mips() {
    local mips_file=$1
    
    echo -e "${CYAN}==========================================${NC}"
    echo -e "${YELLOW}Running MIPS Assembly: $mips_file${NC}"
    echo -e "${CYAN}==========================================${NC}"
    
    if [ ! -f "$mips_file" ]; then
        echo -e "${RED}ERROR: File not found: $mips_file${NC}"
        exit 1
    fi
    
    echo -e "${BLUE}Executing in SPIM...${NC}"
    echo -e "${CYAN}========================================${NC}"
    
    if [ $DEBUG = true ]; then
        timeout $TIMEOUT spim -file "$mips_file"
    else
        timeout $TIMEOUT spim -file "$mips_file" 2>&1 | \
            grep -v "SPIM Version" | \
            grep -v "Copyright" | \
            grep -v "All Rights Reserved" | \
            grep -v "See the file" | \
            grep -v "Loaded:" | \
            grep -v "^$"
    fi
    
    echo -e "${CYAN}========================================${NC}"
    echo ""
}

# =========================================================================================
# Function: Interactive file selection
# =========================================================================================
interactive_select() {
    echo -e "${BLUE}Available test files:${NC}"
    echo ""
    
    shopt -s nullglob
    files=($TEST_DIR/*.cpp $TEST_DIR/*.c)
    
    if [ ${#files[@]} -eq 0 ]; then
        echo -e "${RED}No test files found in '$TEST_DIR/'${NC}"
        exit 1
    fi
    
    # Display files with numbers
    for i in "${!files[@]}"; do
        printf "%3d) %s\n" $((i+1)) "$(basename "${files[$i]}")"
    done
    
    echo ""
    echo -e "${YELLOW}Enter file number (or 'q' to quit):${NC} "
    read -r choice
    
    if [[ "$choice" == "q" || "$choice" == "Q" ]]; then
        echo "Exiting..."
        exit 0
    fi
    
    if [[ "$choice" =~ ^[0-9]+$ ]] && [ "$choice" -ge 1 ] && [ "$choice" -le "${#files[@]}" ]; then
        selected_file="${files[$((choice-1))]}"
        echo ""
        compile_and_run "$selected_file"
    else
        echo -e "${RED}Invalid selection!${NC}"
        exit 1
    fi
}

# =========================================================================================
# Function: Test all files
# =========================================================================================
test_all_files() {
    echo -e "${BLUE}==========================================${NC}"
    echo -e "${BLUE}  SPIM TEST SUITE - ALL FILES${NC}"
    echo -e "${BLUE}==========================================${NC}"
    echo ""
    
    local total=0
    local passed=0
    local failed=0
    local timeout_count=0
    
    shopt -s nullglob
    files=($TEST_DIR/*.cpp $TEST_DIR/*.c)
    
    for file in "${files[@]}"; do
        total=$((total + 1))
        compile_and_run "$file"
        result=$?
        
        if [ $result -eq 0 ]; then
            passed=$((passed + 1))
        elif [ $result -eq 2 ]; then
            timeout_count=$((timeout_count + 1))
        else
            failed=$((failed + 1))
        fi
        
        echo ""
    done
    
    # Summary
    echo -e "${BLUE}==========================================${NC}"
    echo -e "${BLUE}         SPIM TEST SUMMARY${NC}"
    echo -e "${BLUE}==========================================${NC}"
    echo -e "Total:       ${CYAN}$total${NC}"
    echo -e "Passed:      ${GREEN}$passed${NC}"
    echo -e "Failed:      ${RED}$failed${NC}"
    echo -e "Timeouts:    ${YELLOW}$timeout_count${NC}"
    echo -e "${BLUE}==========================================${NC}"
}

# =========================================================================================
# Main Execution
# =========================================================================================

echo -e "${BLUE}==========================================${NC}"
echo -e "${BLUE}      SPIM SIMULATOR TEST RUNNER${NC}"
echo -e "${BLUE}==========================================${NC}"
echo ""

# Determine what to run
if [ $RUN_ALL = true ]; then
    # Test all files
    test_all_files
elif [ -n "$INPUT_FILE" ]; then
    # Check file type
    if [[ "$INPUT_FILE" == *.s ]]; then
        # Run existing MIPS assembly
        run_mips "$INPUT_FILE"
    elif [[ "$INPUT_FILE" == *.c || "$INPUT_FILE" == *.cpp ]]; then
        # Compile and run source file
        compile_and_run "$INPUT_FILE"
    else
        echo -e "${RED}ERROR: Unsupported file type${NC}"
        echo "Supported: .c, .cpp, .s"
        exit 1
    fi
else
    # Interactive mode
    interactive_select
fi

echo -e "${GREEN}Done.${NC}"
