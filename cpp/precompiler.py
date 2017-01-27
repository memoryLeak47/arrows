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

class Structure:
	def __init__(self, name, file, index, superstructures, members):
		self.name = name
		self.file = file
		self.index = index
		self.superstructures = superstructures
		self.members = members

class Files:
	def __init__(self):
		self.filedict = dict()
		self.structures = list()
		self.init_filedict()
		self.init_structures()

	def init_filedict(self):
		for file in get_src_files():
			with open(file, "r") as f:
				lines = ""
				try:
					lines = "".join(f.readlines())
				except:
					die("Files::__init__(): Could not read file: '" + file + "'")
			self.filedict[file.replace(dir, "").strip("/")] = lines

	def init_structures(self):
		for file in self.filenames():
			filestr = self.filedict[file]
			index = -1
			while True:
				index = filestr.find("class", index+1)
				if index == -1:
					break
				index += 5
				blank, index = walk_blank(filestr, index)
				if blank == "":
					continue
				typename, index_tmp = walk_typename(filestr, index)
				if index_tmp == E or typename == E:
					die("should not happen")
					continue
				index = index_tmp
				_, index = walk_blank(filestr, index)
				if filestr[index] == ":":
					supertypes = list()
					while True:
						_, index = walk_blank(filestr, index+1)
						_, index_tmp = walk_modifier(filestr, index)
						if index_tmp != E:
							index = index_tmp
						_, index = walk_blank(filestr, index)
						supertypename, index_tmp = walk_typename(filestr, index)
						if supertypename == E or index_tmp == E:
							die("supertypename or index_tmp contain an error value, should not happen")
							break
						index = index_tmp
						supertypes.append(supertypename)
						_, index = walk_blank(filestr, index)
						if filestr[index] == "{":
							s = Structure(typename, file, index, supertypes, list())
							self.add_members_to_structure(s)
							self.structures.append(s)
							break
						elif filestr[index] == ",":
							continue
						else:
							die("should not happen2")
					continue
				elif filestr[index] == "{":
					s = Structure(typename, file, index, list(), list())
					self.add_members_to_structure(s)
					self.structures.append(s)
					continue
				else:
					continue

	def add_members_to_structure(self, structure):
		pass

	def writeback(self):
		for file in get_src_files():
			lines = ""
			with open(file, "r") as f:
				try:
					lines = "".join(f.readlines())
				except:
					die("Files::writeback(): Could not read file: '" + file + "'")
			if lines != self.filedict[file.replace(dir, "").strip("/")]:
				with open(file, "w") as wf:
					try:
						wf.write(self.filedict[file.replace(dir, "").strip("/")])
					except:
						die("Files::writeback(): Could not write to file: '" + file + "'")

	def __getitem__(self, filename):
		return self.filedict[filename]

	def filenames(self):
		return self.filedict.keys()

def walk_blank(filestr, index): # => (blank, index)
	# allowes blank == ""
	start_index = index
	blank=""
	while True:
		if filestr[index] in [" ", "\n", "\t"]:
			blank += filestr[index]
			index += 1
		elif filestr[index:].startswith("/*"):
			index = walk_to(filestr, "*/", index)
			if index == E:
				return filestr[start_index:], len(filestr)-1
			index += 2
		elif filestr[index:].startswith("//"):
			index = walk_to(filestr, "\n", index)
			if index == E:
				return filestr[start_index:], len(filestr)-1
			index += 1
		else:
			break

		if index >= len(filestr):
			return E, E
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
	if filestr[index:].startswith("public"):
		return "public", index + 6
	elif filestr[index:].startswith("protected"):
		return "protected", index + 9
	elif filestr[index:].startswith("private"):
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

def add_to_class_def(classname, content, files):
	file, index = find_class_def(classname, files)
	if file == E or index == E:
		return E
	files.filedict[file] = files[file][:index+1] + content + files[file][index+1:]

def add_to_file(file, content, files):
	files.filedict[file] += content

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
				typename, index_tmp = walk_typename(filestr, index)
				if index_tmp == E:
					continue
				else:
					index = index_tmp

				if typename != classname:
					continue

				_, index = walk_blank(filestr, index)
				if filestr[index] == ";":
					continue
				index = walk_to("{", filestr, index)
				if index == E:
					continue
				return file, index
	return E, E

def get_direct_subclasses(classname, files):
	l = list()
	for file in files.filenames():
		filestr = files[file]
		index = -1
		while True:
			index = filestr.find("class", index+1)
			if index == -1:
				break
			else:
				index += 5
				blank, index = walk_blank(filestr, index)
				if blank == "":
					continue
				sub_typename, index = walk_typename(filestr, index)
				if sub_typename == E or index == E:
					continue
				_, index = walk_blank(filestr, index)
				if filestr[index] != ":":
					continue
				index += 1
				while True:
					_, index = walk_blank(filestr, index)
					_, index_tmp = walk_modifier(filestr, index)
					if index_tmp != E:
						index = index_tmp
					_, index = walk_blank(filestr, index)

					typename, index_tmp = walk_typename(filestr, index)

					if typename == classname:
						l.append(sub_typename)
						break

					if index_tmp != E:
						index = index_tmp
					_, index = walk_blank(filestr, index)

					if filestr[index] != ",":
						break
					else:
						index += 1
				continue # with finding class definitions in this file
	return l

def get_subclasses(classname, files):
	l = get_direct_subclasses(classname, files)
	for subclass in l:
		for subby in get_direct_subclasses(subclass, files):
			if subby not in l:
				l.append(subby)
	return l

def main():
	files = Files()

	"""
	add_to_class_def("FrameCloneable", "public: virtual std::string to_string() const = 0; private:", files)
	for subcloneable in get_subclasses("FrameCloneable", files):
		add_to_class_def(subcloneable, "public: virtual std::string to_string() const override; private:", files)
		file, _ = find_class_def(subcloneable, files)
		if file == E:
			die("Could not load " + subcloneable)
		add_to_file(file.replace(".hpp", ".cpp"), "std::string " + subcloneable + "::to_string() const { return \"" + subcloneable + "\"; }", files)
	"""

	files.writeback()

main()
