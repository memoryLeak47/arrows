#include "FrameHistory.hpp"

#include <misc/Global.hpp>

FrameHistory::FrameHistory()
	: size(global::FRAME_HISTORY_SIZE), addTargetSlot(0), frameCounter(-1)
{
	history = (Frame**) ::operator new(size*sizeof(Frame*));
	for (unsigned int i = 0; i < size; i++)
	{
		history[i] = nullptr;
	}
}

FrameHistory::~FrameHistory()
{
	deleteAll();
	delete history;
}

void FrameHistory::add(Frame* f)
{
	if (history[addTargetSlot] != nullptr)
	{
		deleteAndNullptr(history[addTargetSlot]);
	}
	history[addTargetSlot] = f;
	addTargetSlot = toIndex(addTargetSlot + 1);
	frameCounter++;
}

Frame* FrameHistory::getFrameSince(const unsigned int since) const
{
	if (size < since)
	{
		Debug::warn("FrameHistory::getFrameSince(): size < since: size = " + Converter::intToString(size) + "; since = " + Converter::intToString(since));
		return nullptr;
	}
	const unsigned int index = toIndex(getNewestFrameSlot() - since);
	return history[index];
}

FrameHistory* FrameHistory::branch(int branchPoint) const
{
	FrameHistory *result = new FrameHistory();

	int end = frameCounterToIndex(branchPoint);
	for (int i = addTargetSlot; i != end; i = toIndex(i + 1))
	{
		Frame* f = history[i];
		if (f != nullptr)
			result->add(f->clone());
	}

	result->frameCounter = branchPoint-1;
	return result;
}

// will delete Frames, beginning by the frame pointed to by branchPoint up to the newest frame
void FrameHistory::merge(FrameHistory* sourceHistory)
{
	deleteAll();

	for (unsigned int i = 0; i < sourceHistory->size; i++)
	{
		history[i] = sourceHistory->history[i];
	}
	this->frameCounter = sourceHistory->frameCounter;
}

void FrameHistory::clear()
{
	for (unsigned int i = 0; i < size; i++)
	{
		history[i] = nullptr;
	}
	addTargetSlot = 0;
	frameCounter = -1;
}

int FrameHistory::getFrameCounter() const
{
	return frameCounter;
}

int FrameHistory::frameCounterToIndex(const int c) const
{
	const int targetDif = frameCounter - c;
	if (targetDif < 0)
	{
		Debug::error("FrameHistory::frameCounterToIndex(): targetDif < 0: frameCounter=" + Converter::intToString(frameCounter) + ", c=" + Converter::intToString(c));
	}
	if (targetDif > (int) size)
	{
		Debug::error("FrameHistory::frameCounterToIndex(): targetDif > size: frameCounter=" + Converter::intToString(frameCounter) + ", c=" + Converter::intToString(c));
	}
	return toIndex(getNewestFrameSlot() - targetDif);
}

unsigned int FrameHistory::toIndex(int n) const
{
	while (n < 0)
		n += size;
	while (n >= (int) size)
		n -= size;
	return n;
}

int FrameHistory::getNewestFrameSlot() const
{
	return toIndex(addTargetSlot-1);
}

Frame* FrameHistory::getFrame(const int c) const
{
	return history[frameCounterToIndex(c)];
}

void FrameHistory::deleteAll()
{
	for (unsigned int i = 0; i < size; i++)
	{
		if (history[i] != nullptr)
		{
			delete history[i];
			history[i] = nullptr;
		}
	}
}
