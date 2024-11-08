import re

def merge_single_letters(arr):
	result = []
	i = 0
	while i < len(arr):
		# If the current element has length 1 or less, we merge with subsequent small elements
		if len(arr[i]) <= 1:
			# Collect all small elements into a buffer
			buffer = arr[i]
			while i + 1 < len(arr) and len(arr[i + 1]) <= 1:
				buffer += arr[i + 1]
				i += 1
			
			#to handle special cases like clGetPlatformIDs
			if (len(buffer) == 1):
				if (i + 1 < len(arr)):
					result.append(buffer + arr[i + 1])
					i += 1
				else:
					if result:
						result[-1] += buffer
					else:
						result.append(buffer)
			else:
				result.append(buffer)
		else:
			result.append(arr[i])
		i += 1
	return result

class ClFunction:

	types_mapping_args = {
		"cl_char": "S8",
		"cl_short": "S16",
		"cl_int": "S32",
		"cl_long": "S64",
		"ssize_t": "S64",
		"cl_uchar": "U8",
		"cl_ushort": "U16",
		"cl_half": "U16",
		"cl_uint": "U32",
		"cl_ulong": "U64",
		"size_t": "U64",
		"cl_float": "F32",
		"cl_double": "F64",
		"cl_bool": "bool",
	}
	special_types_mapping_args = {
		repr(["const", "char", "*"]): "const_string"
	}
	def map_function_arg_type(type:list[str]) -> list[str]:
		new_type = []
		for t in type[:-1]:
			new_type.append(ClFunction.types_mapping_args.get(t, t))
		new_type.append(type[-1])
		return new_type
	def map_ret_arg_type(type:list[str]) -> list[str]:
		return ClFunction.map_function_arg_type(type + [""])[:-1]

	def split_args(args: str) -> list[list[str]]:

		if (args == "void"):
			return [[""]]

		matches = re.findall(r"(void\s+\(CL_CALLBACK(?:[\s]+)?\*(?:[\s]+)?(.+?(?=\)))\)\(([\s\S\r]+?(?=\)))\),)", args)
		if (len(matches) != 0 and len(matches[0]) != 0):
			matches = matches[0]
			matches:list[str]
			func_args = matches[2].split()
			buffer = matches[1].strip() + " " #func ptr name
			buffer += "; "
			for a in func_args:
				if (a.startswith("*")):
					buffer += "* " + a.removeprefix("*") + " "
				elif (a.endswith("*")):
					buffer += a.removesuffix("*") + " * "
				elif (a.endswith(",")):
					buffer += a.removesuffix(",") + " ; "
				else:
					buffer += a + " "
			buffer += ", "
			args = args.replace(matches[0], buffer)

		splitted = args.split(',')
		buffer = []
		i = 0
		while i < len(splitted):
			keywords = splitted[i].split()
			out_keywords = []
			for k in keywords:
				if (k.endswith("]")):
					out_keywords.append(k.split("[")[0])
					out_keywords.append("[" + k.split("[")[1])
				else:
					out_keywords.append(k)
			buffer.append(out_keywords)
			i += 1

		return buffer

	def return_err_ptr(self) -> bool:
		return self.args[-1][-1] == "errcode_ret"

	def join_args(self) -> str:
		buffer = ""

		working_args = self.args
		if (self.args[0][0] == "" and len(self.args) >= 1):
			working_args = working_args[1:]
		if (self.return_err_ptr()):
			working_args = working_args[:-1]

		for i, a in enumerate(working_args):
			if (";" in a):
				buffer += f"void (*{a[0]})({', '.join([c.strip() for c in ' '.join([b.strip() for b in a[1:]]).split(';')[1:]])})"
			else:
				for j, p in enumerate(a):
					buffer += p
					if (p != "*" and j != len(a) - 1):
						buffer += " "
			if (i != len(working_args) - 1):
				buffer += ", "
		return buffer
	
	def join_args_names(self):
		try:
			buffer = ""

			working_args = self.args[:]
			if (self.return_err_ptr()):
				working_args[-1] = ["&_err"]

			for i, a in enumerate(working_args):
				if (";" in a):
					buffer += a[0]
				elif ("[" in ' '.join(a)):
					buffer += a[-2]
				else:
					buffer += a[-1]
				if (i != len(working_args) - 1):
					buffer += ", "
			return buffer
		except:
			return ""

	def __init__(self, f_str:str):
		parsed = re.findall(r"extern\s+(?:[A-Z0-9_]+\s+)+(.+?)\s+CL_API_CALL\n(.+?(?=\())([\s\S]*?\)) CL_API_SUFFIX__VERSION_([0-9])_([0-9])", f_str)
		parsed = parsed[0]
		parsed:list[str]

		self.original_str = f_str

		self.return_type = ' '.join(ClFunction.map_ret_arg_type(parsed[0].strip().split(' ')))
		self.name = parsed[1].strip()

		args_lst = ClFunction.split_args(parsed[2].removeprefix("(").removesuffix(")"))
		self.args = [ClFunction.map_function_arg_type(a) for a in args_lst]

		self.version_major = int(parsed[3])
		self.version_minor = int(parsed[4])

		self.is_err_return_in_arg = self.args[-1] == "S32 * errcode_ret"

		name_split:list[str]
		name_split = [s.lower() for s in re.findall(r"[A-Z][^A-Z]*", self.name)]
		name_formatted = merge_single_letters(name_split)
		self.clfw_name = f"clfw_{'_'.join(name_formatted)}"

	def get_include_name(self) -> str:
		return f"_CLFW_CALL_{self.name.upper()}"

	def get_prototype(self) -> str:
		if (self.name == "clSVMAlloc" or self.name == "clGetExtensionFunctionAddressForPlatform" or self.name == "clGetExtensionFunctionAddress"):
			return_err_ptr = True
		else:
			return_err_ptr = self.return_err_ptr()

		buf = ""

		if (return_err_ptr):
			buf += f"{self.return_type} ({self.clfw_name})(CLFW_DEBUG_ARGS({self.join_args()}))"
		else:
			buf += f"bool ({self.clfw_name})(CLFW_DEBUG_ARGS({self.join_args()}))"
		return buf

	def get_implementation(self) -> str:
		if (self.name == "clSVMAlloc" or self.name == "clGetExtensionFunctionAddressForPlatform" or self.name == "clGetExtensionFunctionAddress"):
			return f"""\tS32 _err;
	void *_ret;

	_ret = {self.name}({self.join_args_names()});
	if (UNLIKELY(_ret == NULL))
		_err = CL_OUT_OF_HOST_MEMORY;
	else
		_err = 0;
	clfw_last_error = _err;
	clfw_last_call = {self.get_include_name()};
	if (_err != 0) clfw_error("%s(%d): %s(%d)\\n", clfw_func_calls[{self.get_include_name()}], {self.get_include_name()}, clfw_get_error_title(_err), _err);
	return _ret;
"""
		return_err_ptr = self.return_err_ptr()

		buf = ""
		#variables
		if (self.return_type != "void"):
			buf += "\t" + "S32 _err;\n"
			if (return_err_ptr):
				buf += "\t" + f"{self.return_type} _ret;\n"
			buf += "\n"

		#call
		if (self.return_type == "void"):
			buf += "\t" + f"{self.name}({self.join_args_names()});"
		elif (return_err_ptr):
			buf += "\t" + f"_ret = {self.name}({self.join_args_names()});\n"
		else:
			buf += "\t" + f"_err = {self.name}({self.join_args_names()});\n"

		#errors
		if (self.return_type != "void"):
			buf += "\t" + "clfw_last_error = _err;\n"
		else:
			buf += "\t" + "clfw_last_error = 0;\n"
		buf += "\t" + f"clfw_last_call = {self.get_include_name()};\n"
		if (self.return_type != "void"):
			buf += "\t" + f"if (_err != 0) clfw_error(\"%s(%d): %s(%d)\\n\", clfw_func_calls[{self.get_include_name()}], {self.get_include_name()}, clfw_get_error_title(_err), _err);\n"

		#return
		if (self.return_type != "void"):
			if (return_err_ptr):
				buf += "\t" + "return _ret;"
			else:
				buf += "\t" + "return _err == 0;"
		else:
			buf += "\t" + "return TRUE;"
		return buf

with open("../../../../3rdparty/OpenCL/include/CL/cl.h", "r") as f:
    header = f.read()

#PARSING
all_functions_str = re.findall(r"extern\s+CL_API_ENTRY[\r\s\S]*?;", header)

ClFunction(all_functions_str[10])

functions:list[ClFunction]
functions = [ClFunction(r) for r in all_functions_str]

#OUTPUT
with open("clfw_wrapper_generated.c", "w+") as f:

	f.write("/*\n")
	f.write("Auto generated OpenCL wrapper from 'auto_gen_wrapper.py'\n")
	f.write("*/\n\n")
	f.write("#include \"clfw_wrapper_generated.h\"\n")

	f.write("\n")
	f.write("#pragma GCC diagnostics push\n")
	f.write("#pragma GCC diagnostic ignored \"-Wdeprecated-declarations\"\n")

	f.write("\n")
	f.writelines([
		"#ifdef CLFW_DEBUG\n",
		"\n",
		"#undef clfw_error\n",
		"#undef clfw_warn\n",
		"#undef clfw_info\n",
		"#undef clfw_debug\n",
		"\n",
		"#define clfw_error(...) (log_error)(_file, _line, clfw_tag, __VA_ARGS__)\n",
		"#define clfw_warn(...) (log_warn)(_file, _line, clfw_tag, __VA_ARGS__)\n",
		"#define clfw_info(...) (log_info)(_file, _line, clfw_tag, __VA_ARGS__)\n",
		"#define clfw_debug(...) (log_debug)(_file, _line, clfw_tag, __VA_ARGS__)\n",
		"#endif\n",
	])

	f.write("\n")
	#f.write("#ifndef CLFW_DEBUG\n")
	for func in functions:
		f.write(func.get_prototype() + "\n{\n" + func.get_implementation() + "\n}\n")
		f.write("\n")
	#f.write("#else\n")
	#for func in functions:
	#	func_debug = ClFunction(func.original_str)
	#	implementation = func_debug.get_implementation()
	#	func_debug.args += [["const_string", "_file"], ["U32", "_line"]]
	#	f.write(func_debug.get_prototype() + "\n{\n" + implementation + "\n}\n")
	#	f.write("\n")
	#f.write("#endif\n")

	f.write("\n")
	f.write("#pragma GCC diagnostics pop\n")

with open("clfw_wrapper_generated.h", "w+") as f:

	f.write("/*\n")
	f.write("Auto generated OpenCL wrapper from 'auto_gen_wrapper.py'\n")
	f.write("*/\n")

	f.write("\n")
	f.write("#define CL_USE_DEPRECATED_OPENCL_1_0_APIS\n")
	f.write("#define CL_TARGET_OPENCL_VERSION 300\n")
	f.write("#include \"CL/cl.h\"\n")
	f.write("#include \"log/log.h\"\n")
	f.write("#include \"clfw_private.h\"\n")
	f.write("#include \"libft/std.h\"\n")

	f.write("\n")
	f.write("#ifdef CLFW_DEBUG\n")
	f.write("#define CLFW_DEBUG_ARGS(...) __VA_ARGS__ __VA_OPT__(,) const_string _file, S32 _line\n")
	f.write("#else\n")
	f.write("#define CLFW_DEBUG_ARGS(...) __VA_ARGS__\n")
	f.write("#endif\n")

	f.write("\n")
	f.write("#define __clfw_expand(x) x\n")

	i = 1
	f.write("\n")
	for func in functions:
		f.write(f"#define _CLFW_CALL_{func.name.upper()} {i}\n")
		i += 1

	f.write("\n")
	#f.write("#ifndef CLFW_DEBUG\n")
	for func in functions:
		f.write(func.get_prototype() + ";\n")
	#f.write("#else\n")
	#for func in functions:
	#	func_debug = ClFunction(func.original_str)
	#	func_debug.args += [["const_string", "_file"], ["U32", "_line"]]
	#	f.write(func_debug.get_prototype() + ";\n")
	#f.write("#endif\n")

	f.write("\n")
	f.write("#ifdef CLFW_DEBUG\n")
	for func in functions:
		f.write(f"#define {func.clfw_name}({func.join_args_names().removesuffix(', &_err')}) ({func.clfw_name})({func.join_args_names().removesuffix(', &_err')}, __clfw_expand(__FILE__), __clfw_expand(__LINE__))\n")
	f.write("#endif")

with open("clfw_funcs_names_generated.c", "w+") as f:

	f.write("/*\n")
	f.write("Auto generated OpenCL wrapper from 'auto_gen_wrapper.py'\n")
	f.write("*/\n\n")
	f.write("#include \"clfw_private.h\"\n")

	f.write("\n")
	f.write("const_string clfw_func_calls[] = {\n")
	f.write("\t" + "\"VOID\",\n")
	for func in functions:
		f.write("\t" + f"\"{func.name}\",\n")
	f.write("};\n")