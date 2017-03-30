#include "FrameHistorian.hpp"

#include <misc/Global.hpp>

FrameHistorian::FrameHistorian()
	: newestMainThreadFrameCounter(1), backtrackHistory(nullptr), oldestChangePoint(-1), branchPoint(-1), thread(nullptr)
{}

void FrameHistorian::executeCalendarEntry(const int frameIndex, const char playerID, const Actions actions, const FrameHistory* mainHistory)
{
	calendarMutex.lock();
	calendar.addEntry(frameIndex, playerID, actions);
	calendarMutex.unlock();

	if (oldestChangePoint != -1 && oldestChangePoint < (int) frameIndex) return;
	if (mainHistory->getFrameCounter() <= frameIndex) return;
	if (backtrackHistory != nullptr && getBacktrackFrameCounter() <= frameIndex) return;

	oldestChangePoint = frameIndex;
	backtrack(mainHistory);
}

std::vector<Calendar::Entry> FrameHistorian::getCalendarEntries(const int frameIndex)
{
	std::lock_guard<std::mutex> lock(calendarMutex);
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

		mainFrameHistory->merge(backtrackHistory, branchPoint);
		deleteAndNullptr(backtrackHistory);

		delete *mainFrame;
		*mainFrame = mainFrameHistory->getNewestFrame()->clone();

		backtrack(mainFrameHistory);
	}
	setNewestMainThreadFrameCounter(mainFrameHistory->getFrameCounter() + 1);
}

void FrameHistorian::run()
{
	const Frame *src = backtrackHistory->getNewestFrame();
	Frame *frame = src->clone();
	while (!readyForMerge())
	{
		frame->applyEntries(getCalendarEntries(getBacktrackFrameCounter()));
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

void FrameHistorian::setNewestMainThreadFrameCounter(const int frame)
{
	newestMainThreadFrameCounter = frame;
}

void FrameHistorian::backtrack(const FrameHistory *mainHistory)
{
	if (backtrackHistory != nullptr) return;
	if (oldestChangePoint == -1) return;

	Debug::note("backtracking " + Converter::intToString(mainHistory->getFrameCounter() - oldestChangePoint) + " frames");

	branchPoint = oldestChangePoint;
	oldestChangePoint = -1;
	backtrackHistory = mainHistory->branch(branchPoint);
	thread = new std::thread(&FrameHistorian::run, this);
}
