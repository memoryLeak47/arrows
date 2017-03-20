#include "FrameHistory.hpp"

#include <misc/Debug.hpp>

unsigned int modulo(int n, const unsigned int m)
{
	n %= m;
	while (n < 0)
		n += m;
	return n;
}

FrameHistory::FrameHistory(const unsigned int size_arg)
	: size(size_arg), counter(0)
{
	history = (Frame**) ::operator new(size*sizeof(Frame*));
	for (unsigned int i = 0; i < size; i++)
	{
		history[i] = nullptr;
	}
}

FrameHistory::~FrameHistory()
{
	for (unsigned int i = 0; i < size; i++)
	{
		if (history[i] != nullptr)
		{
			delete history[i];
		}
	}
	delete history;
}

void FrameHistory::add(Frame* f)
{
	Frame* item = history[counter];
	if (item != nullptr)
	{
		delete item;
	}
	history[counter] = f;
	counter++;
	counter %= size;
}

Frame* FrameHistory::getFrameSince(const unsigned int since) const
{
	if (size < since)
	{
		Debug::warn("FrameHistory::getFrameSince(): size < since");
		return nullptr;
	}
	const unsigned int index = modulo((counter-1)-since, size);
	return history[index];
}
