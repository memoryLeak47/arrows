#ifndef __CALENDAR_CLASS__
#define __CALENDAR_CLASS__

#include <deque>
#include <vector>
#include <string>

#include <controller/Actions.hpp>

class Calendar
{
	public:
		struct Entry
		{
			int frameIndex;
			char playerID;
			Actions actions;
		};

		Calendar();
		void addEntry(int frameIndex, char playerID, Actions actions);
		std::vector<Entry> getEntries(int frameIndex) const;
	private:
		std::deque<Entry> entries;
};

#endif
