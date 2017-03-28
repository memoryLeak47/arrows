#ifndef __FRAMEHISTORY_CLASS__
#define __FRAMEHISTORY_CLASS__

/*
	FrameHistory::frameCounter gives the number of add()ed Frames in this History

	frameIndex == 0 refers to the first frame
	FrameIndex X refers to the Frame ticked when frameCounter was X, for X > 0
*/

#include "Frame.hpp"

#include <vector>

constexpr unsigned int FRAME_HISTORY_SIZE = 200;

class FrameHistory
{
	class FrameWrapper
	{
		public:
			FrameWrapper(const Frame*);
			~FrameWrapper();
			bool isEmpty() const;
			const Frame* get() const;
			void incReferenceCount();
			bool del();
		private:
			unsigned int referenceCount;
			const Frame* frame;
	};

	public:
		FrameHistory();
		~FrameHistory();
		void add(const Frame*);
		const Frame* getFrameSince(const unsigned int offset) const;
		const Frame* getNewestFrame() const;

		// the frame pointed by branchPoint will not be copied
		FrameHistory* branch(const unsigned int branchPoint) const;

		// will delete Frames, beginning by the frame pointed to by branchPoint up to the newest frame
		void merge(FrameHistory* sourceHistory, const unsigned int branchPoint);

		unsigned int getFrameCounter() const;
	private:
		// increases the wrappers referenceCount
		void addWrapper(FrameWrapper*);

		// converts frameIndex to slot-index
		unsigned int frameIndexToSlotIndex(const unsigned int) const;

		// correct invalid slot-indexes
		unsigned int toIndex(unsigned int) const;

		// points to the slot, where the newest Frame is
		unsigned int getNewestFrameSlot() const;

		// getFrame pointed by c
		const Frame* getFrame(const unsigned int c) const;

		// deletes all Frames in this History
		void deleteAll();

		FrameWrapper* history[FRAME_HISTORY_SIZE];

		// points to the history-slot which is going to be overwritten by next add-Function
		unsigned int addTargetSlot;

		// if history is empty this will be 0
		// the number of added frames
		unsigned int frameCounter;
};

#endif
