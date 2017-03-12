#!/usr/bin/python3 -B

import sys
import glob
import string

from std import *

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
