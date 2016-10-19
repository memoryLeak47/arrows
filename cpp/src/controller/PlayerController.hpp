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
	private:
		virtual Actions* actionsChanged() override; // schaut ob sich etwas verändert hat, return die neuen actions oder NULL; setzt die neuen actions NICHT
	friend class GameInterface;
};

#include <game/GameInterface.hpp>

#endif
