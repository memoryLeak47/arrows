#ifndef __PLAYERCONTROLLER_CLASS__
#define __PLAYERCONTROLLER_CLASS__

#include "Controller.hpp"

class PlayerController : public Controller
{
	public:
		PlayerController() = default;
		PlayerController(CompressBuffer*);
		virtual ~PlayerController() {}

		// compress
		CID getCID() const override;
	friend class GameInterface;
};

#include <game/GameInterface.hpp>

#endif
