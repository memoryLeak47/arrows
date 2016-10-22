#ifndef __CONTROLLER_CLASS__
#define __CONTROLLER_CLASS__

#include <misc/compress/Compressable.hpp>
#include "Actions.hpp"

class CompressBuffer;

class Controller : public Compressable
{
	public:
		Controller() = default;
		Controller(CompressBuffer*); // cuts actions
		virtual ~Controller() {}

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

#include <misc/compress/CompressBuffer.hpp>

#endif
