#ifndef __CONTROLLER_CLASS__
#define __CONTROLLER_CLASS__

class CompressBuffer;

#include <misc/compress/Compressable.hpp>
#include <string>
#include "Actions.hpp"

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

#endif
