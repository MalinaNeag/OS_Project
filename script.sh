#!/bin/bash

file="$1"

if [[ ! -f "$file" ]]; then
    echo "Error: $file does not exist or is not a file"
    exit 1
fi

if [[ ${file: -2} != ".c" ]]; then
    echo "Error: $file is not a C file"
    exit 1
fi

output=$(gcc -o /dev/null -Wall -Wextra -pedantic-errors "$file" 2>&1)
errors=$(echo "$output" | grep -c "error:")
warnings=$(echo "$output" | grep -c "warning:")

echo "$errors $warnings"

exit 0