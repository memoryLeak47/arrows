#!/usr/bin/python3 -B

import sys
import glob

assert(len(sys.argv) == 2)
dir = sys.argv[1]

def get_path_by_classname(classname):
	pattern = dir + "/**/*.*pp"
	files = glob.glob(pattern, recursive=True)
	for filename in files:
		file = open(filename)
		lines = "".join(file.readlines())
		if lines.find("class " + classname) != -1:
			file.close()
			return filename
		file.close()
	print("Could not find class '" + classname + "'")
	sys.exit(1)

def get_subclasses(classname):
	pass

def get_recursive_subclasses(classname):
	pass

def add_to_hpp(classname, content):
	path = get_path_by_classname(classname)
	file = open(path, "r")
	lines = "".join(file.readlines())
	file.close()
	spot = lines.find("class " + classname)
	if spot == -1:
		print("Could not add '" + content + "' to hpp from '" + classname + "'")
	else:
		while lines[spot-1] != "{":
			spot += 1
		lines = lines[:spot] + content + lines[spot:]
		file = open(path, "w")
		file.writelines(lines)

def add_to_cpp(classname, content):
	file = open(get_path_by_classname(classname) + ".cpp", "a")
	file.write(content)
	file.close()

def main():
	pass
	# add_to_hpp("FrameCloneable", "public: int testvar;")

main()
