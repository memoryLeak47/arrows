#include "FrameCloneable.hpp"

#include <string.h>

void FrameCloneable::cloneMembers(std::map<FrameCloneable*, FrameCloneable*>* map)
{
	std::vector<FrameCloneable**> clonePointers = getClonePointers();
	for (unsigned int i = 0; i < clonePointers.size(); i++)
	{
		if (not (*clonePointers[i])->hasToBeCloned())
			continue;

		if (map->find(*clonePointers[i]) != map->end())
		{
			*clonePointers[i] = (*map)[*clonePointers[i]];
		}
		else
		{
			const unsigned int size = (*clonePointers[i])->getMemSize();
			FrameCloneable* c = (FrameCloneable*) ::operator new(size);
			memcpy(c, *clonePointers[i], size);
			(*map)[*clonePointers[i]] = c;
			(*clonePointers[i])->cloneMembers(map);
		}
	}
}
