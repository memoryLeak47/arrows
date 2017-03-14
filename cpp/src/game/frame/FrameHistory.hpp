#ifndef __FRAMEHISTORY_CLASS__
#define __FRAMEHISTORY_CLASS__

#include "Frame.hpp"

#include <vector>

class FrameHistory
{
	public:
		FrameHistory(const unsigned int size);
		~FrameHistory();
		void add(Frame*);
		Frame* getFrameSince(const unsigned int offset) const;
	private:
		Frame** history;
		const unsigned int size;
		unsigned int counter;
};

#endif
