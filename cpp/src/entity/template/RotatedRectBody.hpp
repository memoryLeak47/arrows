#include <math/game/GameRect.hpp>
#include <cmath>

GameRect Classname::getWrapper(float timeLeft) const
{
	float deltaX = getSpeed().x * timeLeft;
	float deltaY = getSpeed().y * timeLeft;

	float diagonal = 2 * getSize().getMagnitude();
	float sizeX = diagonal + std::abs(deltaX);
	float sizeY = diagonal + std::abs(deltaY);
	float posX = getPosition().x + deltaX/2 - sizeX/2;
	float posY = getPosition().y + deltaY/2 - sizeY/2;

	return GameRect(GameVector(posX, posY), GameVector(sizeX, sizeY));
}

bool Classname::isCollidingPoint(const GameVector& point) const
{
	Debug::warn("<RotatedRectBody>::isCollidingPoint(): TODO");
	return false;
}

GameRect Classname::getRenderGameRect() const
{
	Debug::warn("<RotatedRectBody>::getRenderGameRect(): TODO");
	return GameRect(getPosition(), getSize());
}

float Classname::getLeftest() const
{
	Debug::warn("<RotatedRectBody>::getLeftest(): TODO");
	return 0.f;
}

float Classname::getRightest() const
{
	Debug::warn("<RotatedRectBody>::getRightest(): TODO");
	return 0.f;
}

float Classname::getToppest() const
{
	Debug::warn("<RotatedRectBody>::getToppest(): TODO");
	return 0.f;
}

float Classname::getBottest() const
{
	Debug::warn("<RotatedRectBody>::getBottest(): TODO");
	return 0.f;
}

GameVector Classname::getSpeedAt(const GameVector& where) const // where is a map-coordinate
{
	return Body::getSpeedAt(where);
}
