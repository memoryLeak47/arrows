#ifndef __PLAYERCONTROLLER_CLASS__
#define __PLAYERCONTROLLER_CLASS__

class CompressBuffer;

#include "Controller.hpp"
#include <misc/compress/CompressID.hpp>

class PlayerController : public Controller
{
	public:
		PlayerController() = default;
		PlayerController(CompressBuffer*); // => Controller(CompressBuffer*)
		virtual ~PlayerController() {}

		CREATE_GETMEMSIZE(PlayerController)

		// compress
		CompressID getCompressID() const override;
		/* std::string Controller::getCompressString() const */

	friend class GameInterface;
};

#endif
