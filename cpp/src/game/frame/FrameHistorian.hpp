#ifndef __FRAMEHISTORIAN_CLASS__
#define __FRAMEHISTORIAN_CLASS__

#include <mutex>
#include <thread>

#include <game/Calendar.hpp>
#include "FrameHistory.hpp"
#include "Frame.hpp"

class FrameHistorian
{
	public:
		FrameHistorian();
		void addCalendarEntry(int frameIndex, char playerID, Actions actions, bool needsBacktrack);
		std::vector<Calendar::Entry> getCalendarEntries(int frameIndex) const;

		// backtracks if backtracking is necessary: (oldestChangePoint != -1)
		void backtrack(FrameHistory *mainHistory);

		// returns backtrackHistories frameCounter
		int getBacktrackFrameCounter() const;

		// updates mainFrame and mainFrameHistory if we recently finished backtracking, reinitializes new backtrack
		void updateIfReady(Frame* mainFrame, FrameHistory* mainFrameHistory);
	private:
		// the functions which is ran in thread
		void run();

		void updateHistory(FrameHistory*);
		bool readyForMerge() const;
		void setNewestMainThreadFrameCounter(int);

		// uses mutex to add history entry
		void addHistoryEntry(Frame*);

		int newestMainThreadFrameCounter;
		Calendar calendar;
		FrameHistory* backtrackHistory;
		int oldestChangePoint;
		int branchPoint;
		std::thread *thread;
		std::mutex mutex;
};

#endif
