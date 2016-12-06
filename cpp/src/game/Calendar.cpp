#include "Calendar.hpp"

Calendar::Calendar()
{}

void Calendar::addEntry(int frame, char playerID, Actions actions)
{
	entries.push_back(Calendar::Entry{frame, playerID, actions});
}

std::vector<Calendar::Entry> Calendar::cutEntries(int frame)
{
	std::vector<Calendar::Entry> tmp;
	auto i = entries.begin();
	while (i != entries.end())
	{
		if ((*i).frame == frame)
		{
			tmp.push_back(*i);
			i = entries.erase(i);
		}
		else
		{
			i++;
		}

	}
	return tmp;
}
