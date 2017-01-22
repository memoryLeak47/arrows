#ifndef __CONTROLLER_CLASS__
#define __CONTROLLER_CLASS__

class CompressBuffer;

#include <misc/compress/Compressable.hpp>
#include <game/FrameCloneable.hpp>
#include <string>
#include "Actions.hpp"

class Controller : public Compressable, FrameCloneable
{
	public:
		Controller() = default;
		Controller(CompressBuffer*); // cuts actions
		virtual ~Controller() {}

		virtual bool hasToBeCloned() const override;
		virtual std::vector<FrameCloneable**> getClonePointers() const override;

		// compress
		std::string getCompressString() const override; // puts actions

		// getter
		Actions getActions() const;
	private:
		// setter
		void setActions(const Actions); // used in GamePlayer::setActions()

		Actions actions;

	friend class GameInterface;
	friend class GamePlayer;
};

#endif
