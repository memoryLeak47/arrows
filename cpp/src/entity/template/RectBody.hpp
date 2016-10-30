#include <math/game/GameRect.hpp>
#include <cmath>

GameRect Classname::getWrapper(float timeLeft) const
{
	float deltaX = getSpeed().x * timeLeft;
	float deltaY = getSpeed().y * timeLeft;

	float sizeX = getSize().x + std::abs(deltaX);
	float sizeY = getSize().y + std::abs(deltaY);
	float posX = getPosition().x + deltaX/2 - sizeX/2;
	float posY = getPosition().y + deltaY/2 - sizeY/2;

	return GameRect(GameVector(posX, posY), GameVector(sizeX, sizeY));
}

bool Classname::isCollidingPoint(const GameVector& point) const
{
	if ((point.x >= getLeftest()) && (point.x <= getRightest()))
	{
		if ((point.y >= getToppest()) && (point.y <= getBottest()))
		{
			return true;
		}
	}
	return false;
}

GameRect Classname::getRenderGameRect() const
{
	return GameRect(getPosition(), getSize());
}

float Classname::getLeftest() const
{
	return getPosition().x - getSize().x/2.f;
}

float Classname::getRightest() const
{
	return getPosition().x + getSize().x/2.f;
}

float Classname::getToppest() const
{
	return getPosition().y - getSize().y/2.f;
}

float Classname::getBottest() const
{
	return getPosition().y + getSize().y/2.f;
}

GameVector Classname::getSpeedAt(const GameVector& where) const // where is a map-coordinate
{
	return getSpeed();
}

void Classname::setSpeedAt(const GameVector& how, const GameVector& where) // where is a map-coordinate
{
	speed = how;
}
