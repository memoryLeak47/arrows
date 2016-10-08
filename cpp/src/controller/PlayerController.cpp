#include "PlayerController.hpp"

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

	Debug::warn("PlayerController::updateActions(): TODO skills are missing");

	return changed;
}
