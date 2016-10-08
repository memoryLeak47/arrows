#ifndef __PLAYERCONTROLLER_CLASS__
#define __PLAYERCONTROLLER_CLASS__

#include "Controller.hpp"

class PlayerController : public Controller
{
	public:
	private:
		virtual bool updateActions() override;
	friend class GameInterface;
};

#include <game/GameInterface.hpp>

#endif
