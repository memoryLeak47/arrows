#include "PlayerController.hpp"

PlayerController::PlayerController(CompressBuffer *b)
	: Controller(b)
{}

CompressID PlayerController::getCompressID() const
{
	return PLAYER_CONTROLLER_CID;
}
