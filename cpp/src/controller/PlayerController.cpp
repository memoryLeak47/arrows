#include "PlayerController.hpp"

PlayerController::PlayerController(CompressBuffer*) {}

CID PlayerController::getCID() const
{
	return PLAYER_CONTROLLER_CID;
}

std::string PlayerController::getCompressString() const
{
	return "";
}

bool PlayerController::updateActions()
{
	bool changed = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) != getAction(GO_LEFT))
	{
		setAction(GO_LEFT, not getAction(GO_LEFT));
		changed = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) != getAction(GO_RIGHT))
	{
		setAction(GO_RIGHT, not getAction(GO_RIGHT));
		changed = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) != getAction(JUMP))
	{
		setAction(JUMP, not getAction(JUMP));
		changed = true;
	}

	return changed;
}
