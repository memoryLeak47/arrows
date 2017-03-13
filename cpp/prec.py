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
	add_to_class_def(subclass.name, "public: " + subclass.name + "(const" + subclass.name + "&) = default; private: ")
	add_to_class_def(subclass.name, "public: FrameCloneable* clone(std::map<FrameCloneable*, FrameCloneable*>*); private: ")
	add_to_class_def(subclass.name, "private: void cloneMembers(std::map<FrameCloneable*, FrameCloneable*>*); private: ")
	cpp = subclass.name.replace(".hpp", ".cpp")
	string = "FrameCloneable* " + subclass.name + "::clone(std::map<FrameCloneable*, FrameCloneable*>* map) const { " + subclass.name + " *c = new " + subclass.name + "(*this); c->cloneMembers(map); return c; }"
	add_to_file(cpp, string, files)

	string = "void " + subclass.name + "::cloneMembers(std::map<FrameCloneable*, FrameCloneable*>* map) {"
	l = subclass.get_member_markers()

	for marker in l["pointer_clone"]:
		content = marker.?
		string += "if (map->find(" + content + ") == map->end()) { map[" + content + "] = " + content + ".clone(); } " + content + " = map[" + content + "]; "
	for marker in l["pointer_list_clone"]:
		content = marker.?
		string += "for (unsigned int i = 0; i < " + content ".size(); i++) { if (map->find(" + content + "[i]) == map->end()) { map[" + content + "[i]] = " + content + "[i].clone(); } " + content + "[i] = map[" + content + "[i]]; }"

	string += "}"
	add_to_file(cpp, string, files)
		
# 
files.writeback()
