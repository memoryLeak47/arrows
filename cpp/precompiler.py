#!/usr/bin/python3 -B

import sys
import glob

def die(msg):
	print("ERROR: " + msg)
	sys.exit(1)

assert(len(sys.argv) == 2)
dir = sys.argv[1].strip("/") + "/"

def get_src_files():
	pattern = dir + "/**/*.*pp"
	return glob.glob(pattern, recursive=True)

class Files:
	def __init__(self):
		self.filedict = dict()
		for file in get_src_files():
			with open(file, "r") as f:
				lines = ""
				try:
					lines = "\n".join(f.readlines())
				except:
					print("Files::__init__(): Could not read file: '" + file + "'")
			self.filedict[file.replace(dir, "").strip("/")] = lines

	def writeback(self):
		for file in get_src_files():
			lines = ""
			with open(file, "r") as f:
				try:
					lines = "\n".join(f.readlines())
				except:
					print("Files::writeback(): Could not read file: '" + file + "'")
			if lines != self.filedict[file.replace(dir, "").strip("/")]:
				with open(file, "w") as wf:
					try:
						wf.writelines(self.filedict[file.replace(dir, "").strip("/")].split("\n"))
					except:
						print("Files::writeback(): Could not write to file: '" + file + "'")

	def __getitem__(self, filename):
		return self.filedict[filename]

	def filenames(self):
		return self.filedict.keys()

def walk_blank(filestr, index): # => (blank, index)
	# allowes blank == ""
	blank=""
	while filestr[index] in [" ", "\n", "\t"]:
		blank.append(filestr[index])
		index += 1
	return blank, index

def walk_simple_typename(filestr, index): # => (typename, index)
	if filestr[index] in "0123456789":
		return "ERROR", "ERROR"

	typename = ""
	while filestr[index] in (strings.alphabet + strings.Alphabet + "_0123456789"):
		typename.append(filestr[index])
		index += 1

	if typename == "":
		return "ERROR", "ERROR"

	return typename, index

def walk_spaced_typename(filestr, index): # => (typename, index)
	typename, index = walk_simple_typename(filestr, index)
	if typename == "ERROR" or index == "ERROR":
		return "ERROR", "ERROR"

	if filestr[index:].startswith("::"):
		index += 2

		typename2, index2 = walk_simple_typename(filestr, index)
		if typename2 == "ERROR" or index2 == "ERROR":
			return "ERROR", "ERROR"

		return typename + "::" + typename2, index2
	return typename, index

def walk_typename(filestr, index): # => (typename, index)
	typename, index = walk_spaced_typename(filestr, index)
	if typename == "ERROR" or index == "ERROR":
		return "ERROR"

	if filestr[index] != "<":
		return typename, index

	index += 1
	typenames = list()
	while True:
		typename_tmp, index = walk_typename(filestr, index)
		if typename_tmp == "ERROR" or index == "ERROR":
			return "ERROR", "ERROR"
		typenames.append(typename_tmp)
		index = walk_blank(filestr, index)
		if filestr[index] == ",":
			index = walk_blank(filestr, index+1)
		elif filestr[index] == ">":
			break
		else:
			die("invalid character in walk_typename template list: '" + filestr[index] + "'")
	return typename + "<" + ",".join(typenames) + ">", index

def walk_modifier(filestr, index):  # => (modifier, index)
	if filestr[index].startswith("public"):
		return "public", index + 6
	elif filestr[index].startswith("protected"):
		return "protected", index + 9
	elif filestr[index].startswith("private"):
		return "private", index + 7
	else:
		return "ERROR", "ERROR"

def find_class_def(classname, files):
	for file in files.filenames():
		filestr = files[file]
		index = -1 # because of index+1
		while True:
			index = filestr.find("class", index+1)
			if index == -1:
				break
			else:
				blank, index = walk_blank(filestr, index)
				if blank == "":
					continue
				typename, index = walk_typename(filestr, index)
				if typename != classname:
					continue
				assert(index != "ERROR")
				# TODO

def main():
	files = Files()
	# TODO
	files.writeback()

main()
