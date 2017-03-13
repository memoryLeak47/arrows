#!/usr/bin/python3 -B

import sys
import glob
import string

sys.path.append(sys.path[0] + "/pybase")
from std import *
from walk import *

assert(len(sys.argv) == 2)
dir = sys.argv[1].strip("/") + "/"

def get_src_files():
	pattern = dir + "/**/*.*pp"
	return glob.glob(pattern, recursive=True)

class Structure:
	def __init__(self, name, file, index, superstructures, files):
		self.name = name
		self.file = file
		self.index = index
		self.superstructures = superstructures

		index_end = index

		filestr = files.filedict[file]

		parens = 1
		while True:
			left_find = filestr.find("{", index_end+1)
			right_find = filestr.find("}", index_end+1)
			if left_find == -1 and right_find == -1:
				die("shit")
			elif right_find != -1 and ((right_find < left_find) or left_find == -1):
				index_end = right_find
				parens -= 1
			else:
				index_end = left_find
				parens += 1

			if parens == 0:
				break

		self.end_index = index_end

	def get_member_markers(self, files):
		x = dict() # markername => list of (begin, end)
		for markername in files.markerdict[self.file].keys():
			l = files.markerdict[self.file][markername]
			for (begin, end) in l:
				if begin > self.index and end < self.end_index:
					if markername not in x.keys():
						x[markername] = list()
					x[markername].append((begin, end))
		return x

class Files:
	def __init__(self):
		self.filedict = dict() # filename => content of file
		self.markerdict = dict() # filename => (markername => (list of (index_begin, index_end)))
		self.structuredict = dict() # typename => Structure
		self.init_filedict()
		self.init_markerdict()
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

	def init_markerdict(self):
		for filename in self.filenames():
			self.markerdict[filename] = dict()

			filestr = self.filedict[filename]
			while True:
				index1 = filestr.find("$$")

				# $$a$$ abc $!a$$
				# 1   2     3  4

				if index1 == -1:
					break
				index2 = filestr.find("$$", index1+2)
				if index2 == -1:
					die("index2 invalid")
				markername = filestr[index1+2:index2]
				index3 = filestr.find("$!" + markername + "$$", index2)
				index4 = index3 + len(markername) + 2

				if markername not in self.markerdict[filename].keys():
					self.markerdict[filename][markername] = list()

				self.markerdict[filename][markername].append((index2+2, index3))

				filestr = filestr[:index1] + "/*" + filestr[index1+2:]
				filestr = filestr[:index2] + "*/" + filestr[index2+2:]
				filestr = filestr[:index3] + "/*" + filestr[index3+2:]
				filestr = filestr[:index4] + "*/" + filestr[index4+2:]
				self.filedict[filename] = filestr


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
							s = Structure(typename, file, index, supertypes, self)
							self.structuredict[typename] = s
							break
						elif filestr[index] == ",":
							continue
						else:
							die("should not happen2")
					continue
				elif filestr[index] == "{":
					s = Structure(typename, file, index, list(), self)
					self.structuredict[typename] = s
					continue
				else:
					continue

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

def insert_into_file(filename, content, index, files):
	filestr = files.filedict[filename]
	files.filedict[filename] = filestr[:index+1] + content + filestr[index+1:]

	items = files.markerdict[filename].items()
	files.markerdict[filename] = dict()
	for markername, marker_list in items:
		for marker in marker_list:
			l, r = marker
			if l > index:
				l += len(content)
				r += len(content)
			elif r > index:
				die("insert_into_file: left side of marker is not affected by insertion, right side of marker is affected by insertion")
			if markername in files.markerdict[filename]:
				files.markerdict[filename][markername].append((l, r))
			else:
				files.markerdict[filename][markername] = [(l, r)]


def add_to_class_def(classname, content, files):
	s = files.structuredict[classname]
	if s.file == E or s.index == E:
		return E
	insert_into_file(s.file, content, s.index, files)

def get_marker_content(marker, filename, files):
	(l, r) = marker
	filestr = files.filedict[filename]
	return filestr[l:r]

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
