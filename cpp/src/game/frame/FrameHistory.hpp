#ifndef __FRAMEHISTORY_CLASS__
#define __FRAMEHISTORY_CLASS__

#include "Frame.hpp"

#include <vector>

class FrameHistory
{
	public:
		FrameHistory();
		~FrameHistory();
		void add(Frame*);
		Frame* getFrameSince(const unsigned int offset) const;

		// the frame pointed by branchPoint will not be copied
		FrameHistory* branch(int branchPoint) const;

		// will delete Frames, beginning by the frame pointed to by branchPoint up to the newest frame
		void merge(int branchPoint, FrameHistory* sourceHistory);

		// does not delete anything
		void clear();

		int getFrameCounter() const;
	private:
		// converts frameCounter to slot-index
		int frameCounterToIndex(const int c) const;

		// correct invalid slot-indexes to valid valid slot-indexes
		unsigned int toIndex(int) const;

		// points to the slot, where the newest Frame is
		int getNewestFrameSlot() const;

		// getFrame pointed by c
		Frame* getFrame(const int c) const;

		Frame** history;
		const unsigned int size;

		// points to the history-slot which is going to be overwritten by next add-Function
		unsigned int addTargetSlot;

		// the frameCounter of the newest Entry
		// if history is empty this will be -1
		int frameCounter;
};

#endif
