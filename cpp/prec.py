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

frame_cloneables = list()

frame_cloneables_with_tiles = get_subclasses("FrameCloneable", files)
for fc in frame_cloneables_with_tiles:
	s = files.structuredict[fc]
	if "Tile" not in s.superstructures:
		frame_cloneables.append(fc)

for subclass in frame_cloneables:
	s = files.structuredict[subclass]
	cpp = s.file.replace(".hpp", ".cpp")

	# add copy-constructor
	add_to_class_def(subclass, "public:\n" + subclass + "(const " + subclass + "&) = default;\nprivate:\n", files)

	# add clone()
	if not is_surrounded_by_markername(s.index, s.file, "abstract", files):
		add_to_class_def(subclass, "public:\nFrameCloneable* clone(std::map<FrameCloneable*, FrameCloneable*>*) const override;\nprivate:\n", files)
		string = "FrameCloneable* " + subclass + "::clone(std::map<FrameCloneable*, FrameCloneable*>* map) const\n{\n" + subclass + " *c = new " + subclass + "(*this);\n(*map)[const_cast<FrameCloneable*>(static_cast<const FrameCloneable*>(this))] = c;\nc->cloneMembers(map);\nreturn c;\n}\n"
		add_to_file(cpp, string, files)

	# add cloneMembers()
	add_to_class_def(subclass, "protected:\nvoid cloneMembers(std::map<FrameCloneable*, FrameCloneable*>*);\nprivate:\n", files)
	string = "void " + subclass + "::cloneMembers(std::map<FrameCloneable*, FrameCloneable*>* map)\n{\n"
	for supername in s.superstructures:
		superstructure = files.structuredict[supername]
		if superstructure.name in frame_cloneables:
			string += superstructure.name + "::cloneMembers(map);\n"
	l = s.get_member_markers(files)
	if "clone" in l:
		for marker in l["clone"]:
			content = get_marker_content(marker, s.file, files)
			string += "if (map->find(" + content + ") == map->end())\n{\n" + content + "->clone(map);\n}\n" + content + " = static_cast<decltype(" + content + ")>((*map)[" + content + "]);\n"
	if "clone_list" in l:
		for marker in l["clone_list"]:
			content = get_marker_content(marker, s.file, files)
			string += "for (unsigned int i = 0; i < " + content + ".size(); i++)\n{\nif (map->find(" + content + "[i]) == map->end())\n{\n" + content + "[i]->clone(map);\n}\n" + content + "[i] = static_cast<decltype(" + content + ")::value_type>((*map)[" + content + "[i]]);\n}\n"

	string += "}\n"
	add_to_file(cpp, string, files)
# 
files.writeback()
