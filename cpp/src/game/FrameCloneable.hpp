#ifndef __FRAMECLONEABLE_CLASS__
#define __FRAMECLONEABLE_CLASS__

#include <vector>
#include <map>

class FrameCloneable
{
	protected:
		virtual std::vector<FrameCloneable**> getClonePointers() const = 0;
		virtual unsigned int getMemSize() const = 0;
		virtual bool hasToBeCloned() const = 0;
	private:
		void cloneMembers(std::map<FrameCloneable*, FrameCloneable*>*);
	friend class Frame;
};

#define CREATE_GETMEMSIZE(classname) unsigned int getMemSize() const { return sizeof(classname); }

#endif
