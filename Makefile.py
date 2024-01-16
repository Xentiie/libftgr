#!python3

import os
import sys
import subprocess
from glob import glob

def _execute(*args):
	print(' '.join(args))
	try:
		process = subprocess.Popen(args, shell=False)
	except FileNotFoundError:
		print(f"Error: '{args[0]}' doesn't exist. Double check args sent to subprocess.Popen.")
		exit(1)
	process.communicate()
	if (process.returncode != 0):
		print(f"Error: {args[0]} exited with code {process.returncode}.")
		exit(1)

def _get_platform():
	is_wsl = os.environ.get("WSLENV", default=None) != None

	is_win = sys.platform == "win32" or is_wsl
	is_linux = (sys.platform == "linux" or sys.platform == "linux2") and not is_wsl
	is_osx = sys.platform == "darwin" and not is_wsl
	return "win32" if (is_win) else "linux" if (is_linux) else "osx" if (is_osx) else None

def _get_target(target):
	if target in globals() and callable(globals()[target]):
		return globals()[target]
	else:
		return None

def _filter_files(srcs, objs):
	srcs_out = []
	objs_out = []
	for s, o in zip(srcs, objs):
		try:
			s_mtime = os.stat(s).st_mtime
		except FileNotFoundError as e:
			print(f"Error: couldn't stat '{e.filename}': not found !")
			continue

		try:
			o_mtime = os.stat(o).st_mtime
		except:
			srcs_out.append(s)
			objs_out.append(o)
			continue

		if (s_mtime > o_mtime):
			srcs_out.append(s)
			objs_out.append(o)
	return srcs_out, objs_out

def _rebuild_lib_needed(name, objs):
	try:
		mtime_lib = os.stat(name).st_mtime
	except FileNotFoundError as e:
		return True
	
	_objs_mtime = []
	for o in objs:
		try:
			_objs_mtime.append(os.stat(o).st_mtime)
		except FileNotFoundError:
			continue
	if (mtime_lib < max(_objs_mtime)):
		return True
	else:
		return False


LIBTOOL=["ar", "-rcs"]
RM=["rm", "-rf"]

INCLUDES=["-I../libft", "-I./"]
LIBRARIES_PATH=[]
LIBRARIES=[]
CFLAGS=["-O3"]

platform = _get_platform()
if (platform == "win32"):
	CC="x86_64-w64-mingw32-gcc"
	CFLAGS += ["-D FT_WIN32"]
	INCLUDES += ["-I./libftwin32"]
	DEP_SRCS_DIR="./libftwin32/srcs"
elif (platform == "linux"):
	CC="gcc"
	CFLAGS += ["-D FT_LINUX"]
	INCLUDES += ["-I./libftx11"]
	DEP_SRCS_DIR="./libftx11/srcs"
elif (platform == "osx"):
	CFLAGS += ["-D FT_OSX"]
	print("Platform not supported")
	exit(1)
else:
	print("Platform not supported")
	exit(1)

NAME="libftgr.a"

SRCS_DIR="./srcs"
SRCS_EXT=".c"

OBJS_DIR="./objs"
OBJS_EXT=".o"

SRCS=glob(f'{SRCS_DIR}/*{SRCS_EXT}') + glob(f'{DEP_SRCS_DIR}/*{SRCS_EXT}')
OBJS=[ f'{OBJS_DIR}/{os.path.split(os.path.abspath(o))[1].replace(SRCS_EXT, OBJS_EXT)}' for o in SRCS ]

def name():
	if (not _rebuild_lib_needed(NAME, OBJS)):
		print(f"Nothing to do for {NAME}")
		return
	_execute(*LIBTOOL, NAME, *OBJS)

def all():

	srcs, objs = _filter_files(SRCS, OBJS)
	if (len(srcs) == 0 or len(objs) == 0):
		print(f"Nothing to do for all")
		name()
		return

	for src, obj in zip(srcs, objs):
		out_dir = os.path.split(os.path.abspath(obj))[0]
		if (not os.path.exists(out_dir)):
			print(f"Ouput directory '${out_dir}' doesn't exists, creating...")
			os.makedirs(out_dir)
		_execute(CC, *CFLAGS, *INCLUDES, *LIBRARIES_PATH, '-c', src,'-o', obj, *LIBRARIES)
	name()

def clean():
	for o in OBJS:
		_execute(*RM, o)

def fclean():
	clean()
	_execute(*RM, NAME)

def re():
	fclean()
	all()


target = None
if (len(sys.argv) == 1):
	target = all
else:
	target = _get_target(sys.argv[1])
	if (target == None):
		print(f"No target: {sys.argv[1]}")
		exit(1)

target()