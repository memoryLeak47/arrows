#ifndef __FRAMEHISTORIAN_CLASS__
#define __FRAMEHISTORIAN_CLASS__

#include <mutex>
#include <thread>
#include <atomic>

#include <game/Calendar.hpp>
#include "FrameHistory.hpp"
#include "Frame.hpp"

class FrameHistorian
{
	public:
		FrameHistorian();

		// adds the calendar entry and backtracks if necessary
		void executeCalendarEntry(const int frameIndex, const char playerID, const Actions actions, const FrameHistory* mainHistory);

		std::vector<Calendar::Entry> getCalendarEntries(const int frameIndex) const;

		// returns backtrackHistories frameCounter
		int getBacktrackFrameCounter();

		// updates mainFrame and mainFrameHistory if we recently finished backtracking, reinitializes new backtrack
		void updateIfReady(Frame** mainFrame, FrameHistory* mainFrameHistory);
	private:
		// the functions which is ran in thread
		void run();

		bool readyForMerge();
		void setNewestMainThreadFrameCounter(const int);

		// backtracks if necessary (eg. oldestChangePoint != -1)
		void backtrack(const FrameHistory *mainHistory);

		// uses mutex to add history entry
		void addHistoryEntry(Frame*);

		int newestMainThreadFrameCounter;
		Calendar calendar;
		FrameHistory* backtrackHistory;
		int oldestChangePoint;
		int branchPoint;
		std::thread *thread;
		std::mutex mutex;
		std::mutex bactrackHistoryMutex;
};

#endif
