#!/usr/bin/python3 -B

import sys
import glob
import string

class Error: pass
E=Error()

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
		blank += filestr[index]
		index += 1
	return blank, index

def walk_simple_typename(filestr, index): # => (typename, index)
	if filestr[index] in "0123456789":
		return E, E

	typename = ""
	while filestr[index] in (string.ascii_lowercase + string.ascii_uppercase + "_0123456789"):
		typename += filestr[index]
		index += 1

	if typename == "":
		return E, E

	return typename, index

def walk_spaced_typename(filestr, index): # => (typename, index)
	typename, index = walk_simple_typename(filestr, index)
	if typename == E or index == E:
		return E, E

	if filestr[index:].startswith("::"):
		index += 2

		typename2, index2 = walk_simple_typename(filestr, index)
		if typename2 == E or index2 == E:
			return E, E

		return typename + "::" + typename2, index2
	return typename, index

def walk_typename(filestr, index): # => (typename, index)
	typename, index = walk_spaced_typename(filestr, index)
	if typename == E or index == E:
		return E, E

	if filestr[index] != "<":
		return typename, index

	index += 1
	typenames = list()
	while True:
		typename_tmp, index = walk_typename(filestr, index)
		if typename_tmp == E or index == E:
			return E, E
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
		return E, E

def walk_to(pattern, filestr, index): # => index
	while True:
		if filestr[index:].startswith(pattern):
			return index
		elif filestr[index:].startswith("//"):
			index = filestr.find("\n", index)
		elif filestr[index:].startswith("/*"):
			index = filestr.find("*/", index+2)
		else:
			index += 1
			if index >= len(filestr):
				return E

def find_class_def(classname, files): # (file, index)
	for file in files.filenames():
		filestr = files[file]
		index = -1 # because of index+1
		while True:
			index = filestr.find("class", index+1)
			if index == -1:
				break
			else:
				index += 5
				blank, index = walk_blank(filestr, index)
				if blank == "":
					continue
				typename, index = walk_typename(filestr, index)
				if typename != classname:
					continue
				assert(index != E)
				_, index = walk_blank(filestr, index)
				index = walk_to("{", filestr, index)
				if index == E:
					return E, E
				return file, index
	return E, E

def main():
	files = Files()
	print(find_class_def("Main", files))
	files.writeback()

main()
