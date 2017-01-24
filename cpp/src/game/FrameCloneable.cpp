#include "FrameCloneable.hpp"

#include <string.h>
#include <assert.h>
#include <misc/Debug.hpp>

void FrameCloneable::cloneMembers(std::map<FrameCloneable*, FrameCloneable*>* map)
{
	assert(hasToBeCloned() < 2);
	std::vector<FrameCloneable**> clonePointers = getClonePointers();
	assert(clonePointers.size() < 20);
	for (unsigned int i = 0; i < clonePointers.size(); i++)
	{
		assert((long) clonePointers[i] > 4000);
		assert((long) *clonePointers[i] > 4000);

		assert((*clonePointers[i])->hasToBeCloned() < 2);

		if (not (*clonePointers[i])->hasToBeCloned()) {
			continue;
		}

		if (map->find(*clonePointers[i]) != map->end())
		{
			*clonePointers[i] = (*map)[*clonePointers[i]];
		}
		else
		{
			const unsigned int size = (*clonePointers[i])->getMemSize();
			assert(size > 7);
			assert(size < 400);
			FrameCloneable* c = (FrameCloneable*) ::operator new(size);
			memcpy(c, (char*) *clonePointers[i], size);
			(*map)[*clonePointers[i]] = c;
			assert(memcmp(*clonePointers[i], c, size) == 0);
			*clonePointers[i] = c;
			assert(c == (*clonePointers[i]));
			c->cloneMembers(map);
		}
		assert(((*map)[*clonePointers[i]])->getMemSize() == (*clonePointers[i])->getMemSize());
	}
}
