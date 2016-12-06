#ifndef __CALENDAR_CLASS__
#define __CALENDAR_CLASS__

#include <vector>

#include <controller/Actions.hpp>

class Calendar
{
	public:
		struct Entry
		{
			int frame;
			char playerID;
			Actions actions;
		};

		Calendar();
		void addEntry(int frame, char playerID, Actions actions);
		std::vector<Entry> cutEntries(int frame);
	private:
		std::vector<Entry> entries;
};

#endif
