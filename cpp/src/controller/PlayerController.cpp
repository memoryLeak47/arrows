#include "PlayerController.hpp"

PlayerController::PlayerController(CompressBuffer *b)
	: Controller(b)
{}

CID PlayerController::getCID() const
{
	return PLAYER_CONTROLLER_CID;
}
