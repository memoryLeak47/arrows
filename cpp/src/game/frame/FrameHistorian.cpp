#include "FrameHistorian.hpp"

#include <misc/Global.hpp>

FrameHistorian::FrameHistorian()
	: newestMainThreadFrameCounter(0), backtrackHistory(nullptr), oldestChangePoint(-1), branchPoint(-1), thread(nullptr)
{}

void FrameHistorian::addCalendarEntry(int frame, char playerID, Actions actions, bool needsBacktrack)
{
	calendar.addEntry(frame, playerID, actions);
	if (needsBacktrack && (oldestChangePoint == -1 || oldestChangePoint > frame) && (backtrackHistory == nullptr || getBacktrackFrameCounter() >= frame))
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

void FrameHistorian::updateIfReady(Frame* mainFrame, FrameHistory* mainFrameHistory)
{
	std::lock_guard<std::mutex> lock(mutex);
	if (readyForMerge())
	{
		thread->join();
		deleteAndNullptr(thread); 
		updateHistory(mainFrameHistory);
		mainFrame = mainFrameHistory->getNewestFrame()->clone();
		backtrack(mainFrameHistory);
	}
	setNewestMainThreadFrameCounter(mainFrameHistory->getFrameCounter() + 1);
}

void FrameHistorian::run()
{
	Frame *src = backtrackHistory->getNewestFrame();
	Frame *frame = src->clone();
	while (!readyForMerge())
	{
		frame->applyEntries(calendar.getEntries(getBacktrackFrameCounter() + 1));
		frame->tick();
		addHistoryEntry(frame->clone());
	}
	delete frame;
}

void FrameHistorian::updateHistory(FrameHistory* mainFrameHistory)
{
	mainFrameHistory->merge(backtrackHistory);
	backtrackHistory->clear();
	deleteAndNullptr(backtrackHistory);
}

bool FrameHistorian::readyForMerge() const
{
	if (backtrackHistory == nullptr)
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
