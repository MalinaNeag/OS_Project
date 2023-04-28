#!/bin/bash

file="$1"

if [[ ! -f "$file" ]]; then
    echo "Error: $file does not exist or is not a file"
    exit 1
fi

echo -e "\n------------------------------------\n"
echo "The provided argument is a C file. In addition, it will be compiled:"

gcc_output=$(gcc -Wall -Wextra "$file" 2>&1)
num_errors=$(echo "$gcc_output" | grep -c 'error')
num_warnings=$(echo "$gcc_output" | grep -c 'warning')

echo "Errors: $num_errors"
echo "Warnings: $num_warnings"

