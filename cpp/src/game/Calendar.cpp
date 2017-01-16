#include "Calendar.hpp"

#include <iostream>

#include <misc/Debug.hpp>

Calendar::Calendar()
{}

void Calendar::addEntry(int frame, char playerID, Actions actions)
{
	unsigned int index = 0;
	while (index < entries.size() && frame < entries[index].frame)
	{
		index++;
	}

	entries.insert(entries.begin() + index, Calendar::Entry{frame, playerID, actions});
}

std::vector<Calendar::Entry> Calendar::getEntries(int frame) const
{
	std::vector<Calendar::Entry> tmp;
	unsigned int index = 0;
	while (frame < entries[index].frame)
	{
		index++;
	}
	while (frame == entries[index].frame)
	{
		tmp.push_back(entries[index++]);
	}
	return tmp;
}
