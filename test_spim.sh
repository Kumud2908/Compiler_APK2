#!/bin/bash
# Test script to run the generated MIPS code in SPIM

echo "Running operators.cpp in SPIM..."
echo ""

spim -file output.s <<EOF
exit
EOF
