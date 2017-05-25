#include "RectShape.hpp"

#include <entity/Entity.hpp>
#include <math/game/GameRect.hpp>
#include <cmath>

CompressID RectShape::getCompressID() const
{
	return CompressIDs::RECT_SHAPE;
}

GameRect RectShape::getWrapper(float timeLeft) const
{
	float deltaX = entity->getSpeed().x * timeLeft;
	float deltaY = entity->getSpeed().y * timeLeft;

	float sizeX = entity->getSize().x + std::abs(deltaX);
	float sizeY = entity->getSize().y + std::abs(deltaY);
	float posX = entity->getPosition().x + deltaX/2 - sizeX/2;
	float posY = entity->getPosition().y + deltaY/2 - sizeY/2;

	return GameRect(GameVector(posX, posY), GameVector(sizeX, sizeY));
}

bool RectShape::isCollidingPoint(const GameVector& point) const
{
	if ((point.x >= entity->getLeftest()) && (point.x <= entity->getRightest()))
	{
		if ((point.y >= entity->getToppest()) && (point.y <= entity->getBottest()))
		{
			return true;
		}
	}
	return false;
}

GameRect RectShape::getRenderGameRect() const
{
	return GameRect(entity->getPosition(), entity->getSize());
}

float RectShape::getLeftest() const
{
	return entity->getPosition().x - entity->getSize().x/2.f;
}

float RectShape::getRightest() const
{
	return entity->getPosition().x + entity->getSize().x/2.f;
}

float RectShape::getToppest() const
{
	return entity->getPosition().y - entity->getSize().y/2.f;
}

float RectShape::getBottest() const
{
	return entity->getPosition().y + entity->getSize().y/2.f;
}

GameVector RectShape::getSpeedAt(const GameVector& where) const // where is a map-coordinate
{
	return entity->getSpeed();
}

void RectShape::reactToCollision_solid(const float massshare, const GameVector& otherSpeed, const GameVector& collisionPoint, float sponge)
{
	constexpr float RANGE = 0.08f;
	constexpr float SPONGE = 0.f;

	enum Pos { MIN, MID, MAX };

	Pos x, y;
	// set x
	if (collisionPoint.x > entity->getLeftest() + RANGE)
	{
		if ((collisionPoint.x < entity->getRightest() - RANGE))
		{
			x = MID;
		}
		else
		{
			x = MAX;
		}
	}
	else
	{
		x = MIN;
	}

	// set y
	if (collisionPoint.y > entity->getToppest() + RANGE)
	{
		if ((collisionPoint.y < entity->getBottest() - RANGE))
		{
			y = MID;
		}
		else
		{
			y = MAX;
		}
	}
	else
	{
		y = MIN;
	}

	// react
	GameVector v_sum(entity->getSpeed()*massshare + otherSpeed*(1-massshare));
	GameVector sponge_sum = GameVector(v_sum + (otherSpeed - entity->getSpeed()) * (1-massshare));
	GameVector speedSum = v_sum * (1.f - sponge) + sponge_sum * sponge;

	GameVector tmp_speed = entity->getSpeed();

	if ((x == MID) && (y == MID)) // Wenn der CollisionPoint in der Mitte der Entity liegt
	{
		// Move Out
		if (collisionPoint.x < entity->getPosition().x)
		{
			// Move Right
			entity->position.x += collisionPoint.x - entity->getLeftest();
			tmp_speed.x = std::max(2*SPONGE + speedSum.x, entity->getSpeed().x);
		}
		else
		{
			// Move Left
			entity->position.x += collisionPoint.x - entity->getRightest();
			tmp_speed.x = std::min(-2*SPONGE + speedSum.x, entity->getSpeed().x);
		}

		if (collisionPoint.y < entity->getPosition().y)
		{
			// Move Down
			entity->position.y += collisionPoint.y - entity->getToppest();
			tmp_speed.y = std::max(2*SPONGE + speedSum.y, entity->getSpeed().y);
		}
		else
		{
			// Move Up
			entity->position.y += collisionPoint.y - entity->getBottest();
			tmp_speed.y = std::min(-2*SPONGE + speedSum.y, entity->getSpeed().y);
		}
	}
	else if (x == MID) // Wenn nur x in der Mitte liegt
	{
		if (y == MIN) // top-collision
		{
			// Move Down
			entity->position.y += collisionPoint.y - entity->getToppest();
			tmp_speed.y = std::max(SPONGE + speedSum.y, tmp_speed.y);
		}
		else // bot-collision
		{
			// Move Up
			entity->position.y += collisionPoint.y - entity->getBottest();
			tmp_speed.y = std::min(-SPONGE + speedSum.y, tmp_speed.y);
		}
	}
	else if (y == MID)
	{
		if (x == MIN) // left-collision
		{
			// Move Right
			entity->position.x += collisionPoint.x - entity->getLeftest();
			tmp_speed.x = std::max(SPONGE + speedSum.x, tmp_speed.x);
		}
		else // right-collision
		{
			// Move Left
			entity->position.x += collisionPoint.x - entity->getRightest();
			tmp_speed.x = std::min(-SPONGE + speedSum.x, tmp_speed.x);
		}
	}

	entity->setSpeed(tmp_speed);
}
