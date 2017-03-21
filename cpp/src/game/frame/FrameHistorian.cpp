#include "FrameHistorian.hpp"

#include <misc/Global.hpp>

FrameHistorian::FrameHistorian()
	: newestMainThreadFrameCounter(0), backtrackHistory(nullptr), oldestChangePoint(-1), branchPoint(-1), thread(nullptr)
{}

void FrameHistorian::addCalendarEntry(int frame, char playerID, Actions actions)
{
	calendar.addEntry(frame, playerID, actions);
	if ((oldestChangePoint == -1 || oldestChangePoint > frame) && (!isBacktracking() || getBacktrackFrameCounter() >= frame))
	{
		oldestChangePoint = frame;
	}
}

std::vector<Calendar::Entry> FrameHistorian::getCalendarEntries(int frame) const
{
	return calendar.getEntries(frame);
}

void FrameHistorian::backtrack(FrameHistory *mainHistory)
{
	if (oldestChangePoint == -1 || branchPoint != -1)
	{
		return;
	}

	if (thread != nullptr)
	{
		Debug::error("FrameHistorian::backtrack(): thread is not nullptr");
	}

	if (backtrackHistory != nullptr)
	{
		Debug::error("FrameHistorian::backtrack(): backtrackHistory is not nullptr");
	}

	branchPoint = oldestChangePoint;
	oldestChangePoint = -1;
	backtrackHistory = mainHistory->branch(branchPoint);
	thread = new std::thread(&FrameHistorian::run, this);
}

int FrameHistorian::getBacktrackFrameCounter() const
{
	if (backtrackHistory == nullptr)
	{
		Debug::error("FrameHistorian::getBacktrackFrameCounter(): backtrackHistory is nullptr");
	}

	return backtrackHistory->getFrameCounter();
}

void FrameHistorian::updateIfReady(Frame& mainFrame, FrameHistory* mainFrameHistory)
{
	std::lock_guard<std::mutex> lock(mutex);
	if (readyForMerge())
	{
		thread->join();
		deleteAndNullptr(thread); 
		updateHistory(mainFrameHistory);
		mainFrame = *(mainFrameHistory->getFrameSince(0)->clone());
		backtrack(mainFrameHistory);
	}
	setNewestMainThreadFrameCounter(mainFrameHistory->getFrameCounter() + 1);
}

void FrameHistorian::run()
{
	Frame mainFrame = *(backtrackHistory->getFrameSince(0)->clone());
	while (!readyForMerge())
	{
		mainFrame.applyEntries(calendar.getEntries(getBacktrackFrameCounter()));
		mainFrame.tick();
		addHistoryEntry(mainFrame.clone());
	}
}

void FrameHistorian::updateHistory(FrameHistory* mainFrameHistory)
{
	mainFrameHistory->merge(branchPoint, backtrackHistory);
	backtrackHistory->clear();
	deleteAndNullptr(backtrackHistory);
}

bool FrameHistorian::isBacktracking() const
{
	return branchPoint != -1;
}

bool FrameHistorian::readyForMerge() const
{
	if (!isBacktracking())
	{
		return false;
	}
	return getBacktrackFrameCounter() == newestMainThreadFrameCounter;
}

void FrameHistorian::addHistoryEntry(Frame* f)
{
	std::lock_guard<std::mutex> lock(mutex);
	backtrackHistory->add(f);
}

void FrameHistorian::setNewestMainThreadFrameCounter(int frame)
{
	newestMainThreadFrameCounter = frame;
}
