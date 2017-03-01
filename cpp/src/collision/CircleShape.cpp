#include "CircleShape.hpp"

#include <entity/Entity.hpp>
#include <math/game/GameRect.hpp>
#include <misc/Debug.hpp>
#include <cmath>

CompressID CircleShape::getCompressID() const
{
	return CompressIDs::CIRCLE_SHAPE;
}

GameRect CircleShape::getWrapper(float timeLeft) const
{
	float deltaX = entity->getSpeed().x * timeLeft;
	float deltaY = entity->getSpeed().y * timeLeft;

	float diagonal = 2 * entity->getSize().getMagnitude();
	float sizeX = diagonal + std::abs(deltaX);
	float sizeY = diagonal + std::abs(deltaY);
	float posX = entity->getPosition().x + deltaX/2 - sizeX/2;
	float posY = entity->getPosition().y + deltaY/2 - sizeY/2;
	return GameRect(GameVector(posX, posY), GameVector(sizeX, sizeY));
}

bool CircleShape::isCollidingPoint(const GameVector& point) const
{
	return (point - entity->getPosition()).getMagnitude() < entity->getSize().x; // size == radius
}

GameRect CircleShape::getRenderGameRect() const
{
	return GameRect(entity->getPosition(), entity->getSize()); // XXX correct?
}

float CircleShape::getLeftest() const
{
	return entity->getPosition().x - entity->getSize().x/2;
}

float CircleShape::getRightest() const
{
	return entity->getPosition().x + entity->getSize().x/2;
}

float CircleShape::getToppest() const
{
	return entity->getPosition().y - entity->getSize().y/2;
}

float CircleShape::getBottest() const
{
	return entity->getPosition().y + entity->getSize().y/2;
}

GameVector CircleShape::getSpeedAt(const GameVector& where) const // where is a map-coordinate
{
	Debug::warn("CircleShape::getSpeedAt(): TODO");
	return entity->getSpeed();
}

void CircleShape::reactToCollision_solid(const float massshare, const GameVector& otherSpeed, const GameVector& collisionPoint, float sponge)
{
	Debug::warn("CircleShape::reactToCollision_solid(): TODO");
}
