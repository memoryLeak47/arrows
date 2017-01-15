#include "Calendar.hpp"

#include <iostream>

#include <misc/Debug.hpp>

Calendar::Calendar()
{}

void Calendar::addEntry(int frame, char playerID, Actions actions)
{
	entries.push_back(Calendar::Entry{frame, playerID, actions});
}

std::vector<Calendar::Entry> Calendar::getEntries(int frame) const
{
	std::vector<Calendar::Entry> tmp;
	for (auto i = entries.begin(); i != entries.end(); i++)
	{
		if ((*i).frame == frame)
		{
			tmp.push_back(*i);
		}
	}
	return tmp;
}

void Calendar::printString() const
{
	std::cout << "entries.size()=" << entries.size() << std::endl;
	for (unsigned int i = 0; i < entries.size(); i++)
	{
		std::cout << "" << i << ": frame=" << entries[i].frame << " playerID=" << (int)entries[i].playerID << " actions=" << (int)entries[i].actions << std::endl;
	}
}
