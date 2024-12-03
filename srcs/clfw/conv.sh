#!/bin/bash

# Check if the input file is provided
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <input_shader_file>"
    exit 1
fi

input_file="$1"

# Extract the filename without the extension, for variable naming
filename=$(basename -- "$input_file" | sed -e 's/\./_/g')
output_file="$(dirname -- "$input_file")/$filename""_sources.c"
variable_name="${filename%.*}_source"

# Create or overwrite the output file
echo "// Auto-generated file. Do not edit manually." > "$output_file"
echo -e "\n#include \"libft/std.h\"\n" >> "$output_file"
echo -n "const const_string $variable_name =" >> "$output_file"

# Read the input file and convert it to a valid C string
while IFS= read -r line; do
    # Escape backslashes and double quotes
    escaped_line=$(echo "$line" | sed -e 's/\\/\\\\/g' -e 's/"/\\"/g')
    
    # Append the escaped line to the output file
    echo -en "\n\t\"$escaped_line\\\\n\"" >> "$output_file"
done < "$input_file"

# End the C string variable properly
echo ";" >> "$output_file"
