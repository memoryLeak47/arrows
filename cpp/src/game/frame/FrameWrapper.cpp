#include "FrameHistory.hpp"

#include <misc/Debug.hpp>

FrameHistory::FrameWrapper::FrameWrapper(const Frame* f)
	: referenceCount(1), frame(f)
{}

FrameHistory::FrameWrapper::~FrameWrapper()
{
	if (!isEmpty())
	{
		Debug::warn("FrameWrapper::~FrameWrapper(): is still used");
	}
}

bool FrameHistory::FrameWrapper::isEmpty() const
{
	return (referenceCount == 0);
}

const Frame* FrameHistory::FrameWrapper::get() const
{
	return frame;
}

void FrameHistory::FrameWrapper::incReferenceCount()
{
	referenceCount++;
}

bool FrameHistory::FrameWrapper::del()
{
	referenceCount--;

	if (referenceCount == 0)
	{
		delete frame;
		frame = nullptr;
		return true;
	}
	return false;
}
