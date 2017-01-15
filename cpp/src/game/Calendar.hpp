#ifndef __CALENDAR_CLASS__
#define __CALENDAR_CLASS__

#include <vector>
#include <string>

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
		std::vector<Entry> getEntries(int frame) const;
		void printString() const;
	private:
		std::vector<Entry> entries;
};

#endif
