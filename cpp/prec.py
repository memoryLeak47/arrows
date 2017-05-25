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

# <Sub>Message::applyTo(...) { ... }
message_subclasses = get_subclasses("Message", files)
for message_subclass in message_subclasses:
	hpp_string = "\n\tpublic:\n\t\tvirtual void applyTo(MessageListener* l);\n\tprivate:\n"
	add_to_class_def(message_subclass, hpp_string, files)

	s = files.structuredict[message_subclass]

	cpp = s.file.replace(".hpp", ".cpp")
	cpp_string = "\nvoid " + message_subclass + "::applyTo(MessageListener* l) { l->applyMessage(*this); }"
	add_to_file(cpp, cpp_string, files)


# frame cloneables stuff
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
	add_to_class_def(subclass, "\n\tpublic:\n\t\t" + subclass + "(const " + subclass + "&) = default;\n\tprivate:\n", files)

	# add clone()
	if not is_surrounded_by_markername(s.index, s.file, "abstract", files):
		add_to_class_def(subclass, "\n\tpublic:\n\t\tFrameCloneable* clone(std::map<FrameCloneable*, FrameCloneable*>*) const override;\n\tprivate:\n", files)
		string = "\n" + \
			"FrameCloneable* " + subclass + "::clone(std::map<FrameCloneable*, FrameCloneable*>* map) const\n" + \
			"{\n" + \
			"\t" + subclass + " *c = new " + subclass + "(*this);\n" + \
			"\t(*map)[const_cast<FrameCloneable*>(static_cast<const FrameCloneable*>(this))] = c;\n" + \
			"\tc->cloneMembers(map);\n" + \
			"\treturn c;\n" + \
			"}\n"
		add_to_file(cpp, string, files)

	# add cloneMembers()
	add_to_class_def(subclass, "\n\tprotected:\n\t\tvoid cloneMembers(std::map<FrameCloneable*, FrameCloneable*>*);\n\tprivate:\n", files)
	string = "\nvoid " + subclass + "::cloneMembers(std::map<FrameCloneable*, FrameCloneable*>* map)\n{\n"
	for supername in s.superstructures:
		superstructure = files.structuredict[supername]
		if superstructure.name in frame_cloneables:
			string += "\t" + superstructure.name + "::cloneMembers(map);\n"
	l = s.get_member_markers(files)
	if "clone" in l:
		for marker in l["clone"]:
			content = get_marker_content(marker, s.file, files).strip()
			string += "\tif (" + content + " != nullptr)\n" + \
				"\t{\n" + \
				"\t\tif (map->find(" + content + ") == map->end())\n" + \
				"\t\t{\n" + \
				"\t\t\t" + content + "->clone(map);\n" + \
				"\t\t}\n" + \
				"\t\t" + content + " = static_cast<decltype(" + content + ")>((*map)[" + content + "]);\n" + \
				"\t}\n"
	if "clone_list" in l:
		for marker in l["clone_list"]:
			content = get_marker_content(marker, s.file, files).strip()
			string += "\tfor (unsigned int i = 0; i < " + content + ".size(); i++)\n" + \
				"\t{\n" + \
				"\t\tif (" + content + "[i] != nullptr)\n" + \
				"\t\t{\n" + \
				"\t\t\tif (map->find(" + content + "[i]) == map->end())\n" + \
				"\t\t\t{\n" \
				"\t\t\t\t" + content + "[i]->clone(map);\n" + \
				"\t\t\t}\n" \
				"\t\t\t" + content + "[i] = static_cast<decltype(" + content + ")::value_type>((*map)[" + content + "[i]]);\n" + \
				"\t\t}\n" + \
				"\t}\n"

	string += "}\n"
	add_to_file(cpp, string, files)

#
files.writeback()
