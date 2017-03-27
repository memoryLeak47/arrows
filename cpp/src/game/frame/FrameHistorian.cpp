#include "FrameHistorian.hpp"

#include <misc/Global.hpp>

FrameHistorian::FrameHistorian()
	: newestMainThreadFrameCounter(1), backtrackHistory(nullptr), oldestChangePoint(-1), branchPoint(-1), thread(nullptr)
{}

void FrameHistorian::executeCalendarEntry(int frameIndex, char playerID, Actions actions, const FrameHistory* mainHistory)
{
	calendar.addEntry(frameIndex, playerID, actions);

	if (oldestChangePoint != -1 && oldestChangePoint < frameIndex) return;
	if (mainHistory->getFrameCounter() <= frameIndex) return;
	if (backtrackHistory != nullptr && getBacktrackFrameCounter() <= frameIndex) return;

	oldestChangePoint = frameIndex;
	backtrack(mainHistory);
}

std::vector<Calendar::Entry> FrameHistorian::getCalendarEntries(int frameIndex) const
{
	return calendar.getEntries(frameIndex);
}

int FrameHistorian::getBacktrackFrameCounter()
{
	if (backtrackHistory == nullptr)
	{
		Debug::error("FrameHistorian::getBacktrackFrameCounter(): backtrackHistory is nullptr");
	}

	return backtrackHistory->getFrameCounter();
}

void FrameHistorian::updateIfReady(Frame** mainFrame, FrameHistory* mainFrameHistory)
{
	std::lock_guard<std::mutex> lock(mutex);
	if (readyForMerge())
	{
		thread->join();
		deleteAndNullptr(thread); 

		mainFrameHistory->merge(backtrackHistory);
		backtrackHistory->clear();
		deleteAndNullptr(backtrackHistory);

		delete *mainFrame;
		*mainFrame = mainFrameHistory->getNewestFrame()->clone();

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
		frame->applyEntries(calendar.getEntries(getBacktrackFrameCounter()));
		frame->tick();
		addHistoryEntry(frame->clone());
	}
	delete frame;
}

bool FrameHistorian::readyForMerge()
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

void FrameHistorian::backtrack(const FrameHistory *mainHistory)
{
	if (backtrackHistory != nullptr) return;
	if (oldestChangePoint == -1) return;

	branchPoint = oldestChangePoint;
	oldestChangePoint = -1;
	backtrackHistory = mainHistory->branch(branchPoint);
	thread = new std::thread(&FrameHistorian::run, this);
}
