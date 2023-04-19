#!/bin/bash

#if [[ $# -ne 1 ]]; then
#    echo "Usage: $0 <file.c>"
#    exit 1
#fi

file="$1"

if [[ ! -f "$file" ]]; then
    echo "Error: $file does not exist or is not a file"
    exit 1
fi

gcc_output=$(gcc -Wall -Wextra "$file" 2>&1)
num_errors=$(echo "$gcc_output" | grep -c 'error')
num_warnings=$(echo "$gcc_output" | grep -c 'warning')

echo "Errors: $num_errors"
echo "Warnings: $num_warnings"
