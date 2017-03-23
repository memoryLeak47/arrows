#include "Calendar.hpp"

#include <iostream>

#include <misc/Debug.hpp>

Calendar::Calendar()
{}

void Calendar::addEntry(int frameIndex, char playerID, Actions actions)
{
	unsigned int index = 0;
	while (index < entries.size() && frameIndex < entries[index].frameIndex)
	{
		index++;
	}

	entries.insert(entries.begin() + index, Calendar::Entry{frameIndex, playerID, actions});
}

std::vector<Calendar::Entry> Calendar::getEntries(int frameIndex) const
{
	std::vector<Calendar::Entry> tmp;
	unsigned int index = 0;
	while (frameIndex < entries[index].frameIndex)
	{
		index++;
	}
	while (frameIndex == entries[index].frameIndex)
	{
		tmp.push_back(entries[index++]);
	}
	return tmp;
}
