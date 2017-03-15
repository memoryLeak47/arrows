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

frame_cloneables = get_subclasses("FrameCloneable", files)
for subclass in frame_cloneables:
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
	add_to_class_def(subclass, "protected: void cloneMembers(std::map<FrameCloneable*, FrameCloneable*>*); private: ", files)
	string = "void " + subclass + "::cloneMembers(std::map<FrameCloneable*, FrameCloneable*>* map) {"
	for supername in s.superstructures:
		superstructure = files.structuredict[supername]
		if superstructure.name in frame_cloneables:
			string += superstructure.name + "::cloneMembers(map);"
	l = s.get_member_markers(files)
	if "clone" in l:
		for marker in l["clone"]:
			content = get_marker_content(marker, s.file, files)
			string += "if (map->find(" + content + ") == map->end()) { (*map)[" + content + "] = " + content + "->clone(map); } " + content + " = (*map)[" + content + "]; "
	if "clone_list" in l:
		for marker in l["clone_list"]:
			content = get_marker_content(marker, s.file, files)
			string += "for (unsigned int i = 0; i < " + content + ".size(); i++) { if (map->find(" + content + "[i]) == map->end()) { (*map)[" + content + "[i]] = " + content + "[i]->clone(map); } " + content + "[i] = (*map)[" + content + "[i]]; }"

	string += "}"
	add_to_file(cpp, string, files)
# 
files.writeback()
