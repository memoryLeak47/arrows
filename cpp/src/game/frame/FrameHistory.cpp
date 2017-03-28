#include "FrameHistory.hpp"

#include <misc/Global.hpp>

FrameHistory::FrameHistory()
	: addTargetSlot(0), frameCounter(0)
{
	for (int i = 0; i < FRAME_HISTORY_SIZE; i++)
	{
		history[i] = nullptr;
	}
}

FrameHistory::~FrameHistory()
{
	deleteAll();
}

void FrameHistory::add(const Frame* f)
{
	if (history[addTargetSlot] != nullptr)
	{
		if (history[addTargetSlot]->del())
		{
			delete history[addTargetSlot];
			history[addTargetSlot] = nullptr;
		}
	}
	history[addTargetSlot] = new FrameWrapper(f);
	addTargetSlot = toIndex(addTargetSlot + 1);
	frameCounter++;
}

const Frame* FrameHistory::getFrameSince(const int since) const
{
	if (FRAME_HISTORY_SIZE < since)
	{
		Debug::warn("FrameHistory::getFrameSince(): FRAME_HISTORY_SIZE < since: FRAME_HISTORY_SIZE = " + Converter::intToString(FRAME_HISTORY_SIZE) + "; since = " + Converter::intToString(since));
		return nullptr;
	}
	const int index = toIndex(getNewestFrameSlot() - since);
	return history[index]->get();
}

const Frame* FrameHistory::getNewestFrame() const
{
	FrameWrapper* w = history[getNewestFrameSlot()];
	if (w == nullptr)
	{
		Debug::error("FrameHistory::getNewestFrame(): no frame yet (should not happen)");
	}
	return w->get();
}

FrameHistory* FrameHistory::branch(const int branchPoint) const
{
	if (branchPoint < 1)
	{
		Debug::error("FrameHistory::branch(): branchPoint < 1");
	}
	FrameHistory *result = new FrameHistory();

	const int end = frameIndexToSlotIndex(branchPoint);
	for (int i = addTargetSlot; i != end; i = toIndex(i + 1))
	{
		FrameWrapper* w = history[i];
		if (w != nullptr)
		{
			result->addWrapper(w);
		}
	}

	result->frameCounter = branchPoint;
	return result;
}

// will delete Frames, beginning by the frame pointed to by branchPoint up to the newest frame
void FrameHistory::merge(FrameHistory* sourceHistory, const int branchPoint)
{
	if (sourceHistory->getFrameCounter() != getFrameCounter())
	{
		Debug::error("FrameHistory::merge(): different frameCounters");
	}
	int ownSlot = 0;
	int sourceSlot = 0;
	for (int fIndex = branchPoint; fIndex < getFrameCounter(); fIndex++)
	{
		ownSlot = frameIndexToSlotIndex(fIndex);
		sourceSlot = sourceHistory->frameIndexToSlotIndex(fIndex);
		if (sourceHistory->history[sourceSlot] == nullptr)
		{
			Debug::error("FrameHistory::merge(): sourceHistory->history[sourceSlot] == nullptr");
		}
		if (history[ownSlot]->del())
		{
			delete history[ownSlot];
		}
		history[ownSlot] = sourceHistory->history[sourceSlot];
		sourceHistory->history[sourceSlot]->incReferenceCount();
	}
	if (toIndex(sourceSlot + 1) != sourceHistory->addTargetSlot)
	{
		Debug::warn("FrameHistory::merge(): (sourceSlot + 1) != sourceHistory->addTargetSlot()");
	}
}

int FrameHistory::getFrameCounter() const
{
	return frameCounter;
}

void FrameHistory::addWrapper(FrameWrapper* w)
{
	if (history[addTargetSlot] != nullptr)
	{
		if (history[addTargetSlot]->del())
		{
			delete history[addTargetSlot];
			history[addTargetSlot] = nullptr;
		}
	}
	history[addTargetSlot] = w;
	addTargetSlot = toIndex(addTargetSlot + 1);
	frameCounter++;
	w->incReferenceCount();
}

int FrameHistory::frameIndexToSlotIndex(const int frameIndex) const
{
	if (frameIndex >= getFrameCounter())
	{
		Debug::error("FrameHistory::frameIndexToSlotIndex(): frameIndex(" + Converter::intToString(frameIndex) + ") too high, frameCounter(" + Converter::intToString(getFrameCounter()) + ")");
	}
	if (frameIndex < (getFrameCounter() - FRAME_HISTORY_SIZE))
	{
		Debug::error("FrameHistory::frameIndexToSlotIndex(): frameIndex(" + Converter::intToString(frameIndex) + ") too small, frameCounter(" + Converter::intToString(getFrameCounter()) + ")");
	}
	return toIndex(getNewestFrameSlot() - frameCounter + frameIndex);
}

int FrameHistory::toIndex(int n) const
{
	while (n < 0)
		n += FRAME_HISTORY_SIZE;
	while (n >= FRAME_HISTORY_SIZE)
		n -= FRAME_HISTORY_SIZE;
	return n;
}

int FrameHistory::getNewestFrameSlot() const
{
	return toIndex(addTargetSlot-1);
}

const Frame* FrameHistory::getFrame(const int c) const
{
	return history[frameIndexToSlotIndex(c)]->get();
}

void FrameHistory::deleteAll()
{
	for (int i = 0; i < FRAME_HISTORY_SIZE; i++)
	{
		if (history[i] != nullptr)
		{
			if (history[i]->del())
			{
				delete history[i];
				history[i] = nullptr;
			}
		}
	}
}
