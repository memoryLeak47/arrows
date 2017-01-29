#!/usr/bin/python3 -B

import sys
import glob
import string

sys.path.append(sys.path[0] + "/prec_py")
from std import *
from walk import *

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
		self.structuredict = dict()
		self.init_filedict()
		self.init_structuredict()

	def init_filedict(self):
		for file in get_src_files():
			with open(file, "r") as f:
				lines = ""
				try:
					lines = "".join(f.readlines())
				except:
					die("Files::__init__(): Could not read file: '" + file + "'")
			self.filedict[file.replace(dir, "").strip("/")] = lines

	def init_structuredict(self):
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
							self.structuredict[typename] = s
							break
						elif filestr[index] == ",":
							continue
						else:
							die("should not happen2")
					continue
				elif filestr[index] == "{":
					s = Structure(typename, file, index, list(), list())
					self.add_members_to_structure(s)
					self.structuredict[typename] = s
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

def add_to_class_def(classname, content, files):
	s = files.structuredict[classname]
	if s.file == E or s.index == E:
		return E
	files.filedict[s.file] = files[s.file][:s.index+1] + content + files[s.file][s.index+1:]

def add_to_file(file, content, files):
	files.filedict[file] += content

def get_direct_subclasses(classname, files):
	l = list()
	for s in files.structuredict.values():
		if classname in s.superstructures:
			l.append(s.name)
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

	add_to_class_def("FrameCloneable", "public: virtual std::string to_string() const = 0; private:", files)
	for subcloneable in get_subclasses("FrameCloneable", files):
		add_to_class_def(subcloneable, "public: virtual std::string to_string() const override; private:", files)
		s = files.structuredict[subcloneable]
		if s.file == E:
			die("Could not load " + subcloneable)
		add_to_file(s.file.replace(".hpp", ".cpp"), "std::string " + subcloneable + "::to_string() const { return \"" + subcloneable + "\"; }", files)

	files.writeback()

main()
