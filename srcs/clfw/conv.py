import sys
import os.path

if (len(sys.argv) < 1):
    print(f"usage: {sys.argv[0]} <input_cl_file>")

input_file=sys.argv[1]

# Extract the filename without the extension, for variable naming
filename = os.path.basename(input_file).replace(".", "_")
output_dir = f"{os.path.dirname(input_file)}/generated_sources"
if (not os.path.exists(output_dir)):
		os.mkdir(output_dir)
output_file = f"{output_dir}/{filename}_sources.c"
variable_name = f"{filename}_source"

# Create or overwrite the output file
with open(output_file, "w+") as out:
	out.write("// Auto-generated file. Do not edit manually.\n\n")
	out.write("#include \"libft/std.h\"\n\n")
	out.write(f"const_string {variable_name} =")

	# Read the input file and convert it to a valid C string
	with open(input_file, "r") as f:
		for line in f.readlines():
			line = line.replace("\\", "\\\\").replace("\"", "\\\"").rstrip("\n")
			out.write("\n\t")
			out.write(f"\"")
			out.write(f"{line}")
			out.write("\\n\"")
	out.write(";\n")
