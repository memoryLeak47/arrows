#ifndef __FRAMECLONEABLE_CLASS__
#define __FRAMECLONEABLE_CLASS__

#include <vector>
#include <map>

class FrameCloneable
{
	public:
		virtual FrameCloneable* clone(std::map<FrameCloneable*, FrameCloneable*>*) const = 0;
	friend class Frame;
};

#endif
