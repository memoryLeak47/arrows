#include "FrameHistory.hpp"

#include <misc/Global.hpp>

FrameHistory::FrameHistory()
	: size(global::FRAME_HISTORY_SIZE), addTargetSlot(0), frameCounter(0)
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

Frame* FrameHistory::getNewestFrame() const
{
	Frame* f = history[getNewestFrameSlot()];
	if (f == nullptr)
	{
		Debug::error("FrameHistory::getNewestFrame(): no frame yet (should not happen)");
	}
	return f;
}

FrameHistory* FrameHistory::branch(int branchPoint) const
{
	if (branchPoint < 1)
	{
		Debug::error("FrameHistory::branch(): branchPoint < 1");
	}
	FrameHistory *result = new FrameHistory();

	int end = frameIndexToSlotIndex(branchPoint);
	for (int i = addTargetSlot; i != end; i = toIndex(i + 1))
	{
		Frame* f = history[i];
		if (f != nullptr)
			result->add(f->clone());
	}

	result->frameCounter = branchPoint;
	return result;
}

// will delete Frames, beginning by the frame pointed to by branchPoint up to the newest frame
void FrameHistory::merge(FrameHistory* sourceHistory)
{
	if (this->size != sourceHistory->size)
	{
		Debug::error("FrameHistory::merge(): this->size != sourceHistory->size");
	}
	deleteAll();

	for (unsigned int i = 0; i < sourceHistory->size; i++)
	{
		history[i] = sourceHistory->history[i];
	}
	this->addTargetSlot = sourceHistory->addTargetSlot;
	this->frameCounter = sourceHistory->frameCounter;
}

void FrameHistory::clear()
{
	for (unsigned int i = 0; i < size; i++)
	{
		history[i] = nullptr;
	}
	addTargetSlot = 0;
	frameCounter = 0;
}

int FrameHistory::getFrameCounter() const
{
	return frameCounter;
}

int FrameHistory::frameIndexToSlotIndex(const int frameIndex) const
{
	if (frameIndex >= getFrameCounter())
	{
		Debug::error("FrameHistory::frameIndexToSlotIndex(): frameIndex(" + Converter::intToString(frameIndex) + ") too high, frameCounter(" + Converter::intToString(getFrameCounter()) + ")");
	}
	if (frameIndex < (int) (getFrameCounter() - size))
	{
		Debug::error("FrameHistory::frameIndexToSlotIndex(): frameIndex(" + Converter::intToString(frameIndex) + ") too small, frameCounter(" + Converter::intToString(getFrameCounter()) + ")");
	}
	return toIndex(getNewestFrameSlot() - frameCounter + frameIndex);
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
	return history[frameIndexToSlotIndex(c)];
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
