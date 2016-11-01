#include "RotatedRectShape.hpp"

#include <entity/Entity.hpp>
#include <math/game/GameRect.hpp>
#include <misc/Debug.hpp>
#include <cmath>

CompressID RotatedRectShape::getCompressID() const
{
	return ROTATED_RECT_SHAPE_CID;
}

GameRect RotatedRectShape::getWrapper(float timeLeft) const
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

bool RotatedRectShape::isCollidingPoint(const GameVector& point) const
{
	Debug::warn("RotatedRectShape::isCollidingPoint(): TODO");
	GameVector rotatedPoint = point; // TODO rotation here
	if ((rotatedPoint.x >= entity->getLeftest()) && (rotatedPoint.x <= entity->getRightest()))
	{
		if ((rotatedPoint.y >= entity->getToppest()) && (rotatedPoint.y <= entity->getBottest()))
		{
			return true;
		}
	}
	return false;
}

GameRect RotatedRectShape::getRenderGameRect() const
{
	return GameRect(entity->getPosition(), entity->getSize()); // XXX correct?
}

float RotatedRectShape::getLeftest() const
{
	Debug::warn("RotatedRectShape::getLeftest(): TODO");
	return 0;
}

float RotatedRectShape::getRightest() const
{
	Debug::warn("RotatedRectShape::getRightest(): TODO");
	return 0;
}

float RotatedRectShape::getToppest() const
{
	Debug::warn("RotatedRectShape::getToppest(): TODO");
	return 0;
}

float RotatedRectShape::getBottest() const
{
	Debug::warn("RotatedRectShape::getBottest(): TODO");
	return 0;
}

GameVector RotatedRectShape::getSpeedAt(const GameVector& where) const // where is a map-coordinate
{
	Debug::warn("RotatedRectShape::getSpeedAt(): TODO");
	return entity->getSpeed();
}

void RotatedRectShape::reactToCollision(const float massshare, const GameVector& otherSpeed, const GameVector& collisionPoint, float sponge)
{
	Debug::warn("RotatedRectShape::reactToCollision(): TODO");
}
