#ifndef __PLAYERCONTROLLER_CLASS__
#define __PLAYERCONTROLLER_CLASS__

#include "Controller.hpp"

class PlayerController : public Controller
{
	public:
		PlayerController() = default;
		PlayerController(CompressBuffer*); // => Controller(CompressBuffer*)
		virtual ~PlayerController() {}

		// compress
		CID getCID() const override;
		/* std::string Controller::getCompressString() const */

	friend class GameInterface;
};

#endif
