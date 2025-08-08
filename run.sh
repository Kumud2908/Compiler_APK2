#!/bin/bash
set -e  # stop if make fails
make
for file in test/*.c; do
    echo "Running on $file"
    ./lexer "$file"
    echo
done
