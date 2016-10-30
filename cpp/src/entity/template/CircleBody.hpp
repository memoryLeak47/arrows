#include <math/game/GameRect.hpp>
#include <cmath>

GameRect Classname::getWrapper(float timeLeft) const
{
	float deltaX = getSpeed().x * timeLeft;
	float deltaY = getSpeed().y * timeLeft;

	float diagonal = 2 * getSize().x; // getSize().x == radius
	float sizeX = diagonal + std::abs(deltaX);
	float sizeY = diagonal + std::abs(deltaY);
	float posX = getPosition().x + deltaX/2 - sizeX/2;
	float posY = getPosition().y + deltaY/2 - sizeY/2;

	return GameRect(GameVector(posX, posY), GameVector(sizeX, sizeY));
}

bool Classname::isCollidingPoint(const GameVector&) const
{
	Debug::warn(std::string(__PRETTY_FUNCTION__) + " TODO");
	return false;
}

GameRect Classname::getRenderGameRect() const
{
	return GameRect(getPosition(), getSize() * 2);
}

float Classname::getLeftest() const
{
	Debug::warn("<CircleBody>::getLeftest(): TODO");
	return 0.f;
}

float Classname::getRightest() const
{
	Debug::warn("<CircleBody>::getRightest(): TODO");
	return 0.f;
}

float Classname::getToppest() const
{
	Debug::warn("<CircleBody>::getToppest() TODO");
	return 0.f;
}

float Classname::getBottest() const
{
	Debug::warn("<CircleBody>::getBottest(): TODO");
	return 0.f;
}
