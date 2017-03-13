#!/usr/bin/python3 -B

import sys
import glob
import string

sys.path.append(sys.path[0] + "/pybase")
from std import *
from walk import *
from main import *

assert(len(sys.argv) == 2)
dir = sys.argv[1].strip("/") + "/"

files = Files()
# add code here

for subclass in get_subclasses("FrameCloneable", files):
	s = files.structuredict[subclass]
	cpp = s.file.replace(".hpp", ".cpp")

	# add copy-constructor
	add_to_class_def(subclass, "public: " + subclass + "(const " + subclass + "&) = default; private: ", files)

	# add clone()
	if not is_surrounded_by_markername(s.index, s.file, "abstract", files):
		add_to_class_def(subclass, "public: FrameCloneable* clone(std::map<FrameCloneable*, FrameCloneable*>*) const override; private: ", files)
		string = "FrameCloneable* " + subclass + "::clone(std::map<FrameCloneable*, FrameCloneable*>* map) const { " + subclass + " *c = new " + subclass + "(*this); c->cloneMembers(map); return c; }"
		add_to_file(cpp, string, files)

	# add cloneMembers()
	add_to_class_def(subclass, "private: void cloneMembers(std::map<FrameCloneable*, FrameCloneable*>*); private: ", files)
	string = "void " + subclass + "::cloneMembers(std::map<FrameCloneable*, FrameCloneable*>* map) {"
	l = s.get_member_markers(files)
	if "pointer_clone" in l:
		for marker in l["pointer_clone"]:
			content = get_marker_content(marker, s.file, files)
			string += "if (map->find(" + content + ") == map->end()) { map[" + content + "] = " + content + "->clone(); } " + content + " = map[" + content + "]; "
	if "pointer_list_clone" in l:
		for marker in l["pointer_list_clone"]:
			content = get_marker_content(marker, s.file, files)
			string += "for (unsigned int i = 0; i < " + content + ".size(); i++) { if (map->find(" + content + "[i]) == map->end()) { map[" + content + "[i]] = " + content + "[i]->clone(); } " + content + "[i] = map[" + content + "[i]]; }"

	string += "}"
	add_to_file(cpp, string, files)
		
# 
files.writeback()
