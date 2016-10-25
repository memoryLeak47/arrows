#include "RectBody.hpp"

#include <misc/Global.hpp>
#include <misc/compress/CompressBuffer.hpp>
#include <cmath>
#include <algorithm>

static const float RANGE = 0.08f;
static const float SPONGE = 0.f;

RectBody::RectBody(const GameVector& pos, const GameVector& size, const GameVector& speed)
	: position(pos), size(size), speed(speed)
{}

RectBody::RectBody(CompressBuffer* buffer)
{
	GameVector* p = (GameVector*) buffer->cutByCompressID(GAME_VECTOR_CID);
	GameVector* s = (GameVector*) buffer->cutByCompressID(GAME_VECTOR_CID);
	GameVector* sp = (GameVector*) buffer->cutByCompressID(GAME_VECTOR_CID);

	position = *p;
	size = *s;
	speed = *sp;

	delete p;
	delete s;
	delete sp;
}

CompressID RectBody::getCompressID() const
{
	return RECT_BODY_CID;
}

std::string RectBody::getCompressString() const
{
	return position.getCompressString() + size.getCompressString() + speed.getCompressString();
}

BodyType RectBody::getBodyType() const
{
	return RECT;
}

GameRect RectBody::getWrapper(float timeLeft) const
{
	float deltaX = speed.x * timeLeft;
	float deltaY = speed.y * timeLeft;

	float sizeX = size.x + std::abs(deltaX);
	float sizeY = size.y + std::abs(deltaY);
	float posX = getPosition().x + deltaX/2 - sizeX/2;
	float posY = getPosition().y + deltaY/2 - sizeY/2;

	return GameRect(GameVector(posX, posY), GameVector(sizeX, sizeY));
}

bool RectBody::isCollidingPoint(const GameVector& point) const
{
	if ((point.x >= getLeft()) && (point.x <= getRight()))
	{
		if ((point.y >= getTop()) && (point.y <= getBot()))
		{
			return true;
		}
	}
	return false;
}

void RectBody::setPosition(const GameVector& pos)
{
	position = pos;
}

const GameVector& RectBody::getPosition() const
{
	return position;
}

const GameVector RectBody::getSize() const
{
	return size;
}

void RectBody::setSpeed(const GameVector& s)
{
	speed = s;
}

const GameVector& RectBody::getSpeed() const
{
	return speed;
}

void RectBody::setRotation(float f)
{
	Debug::warn("RectBody::setRotation(): RectBody has no rotation");
}

float RectBody::getRotation() const
{
	// Debug::warn("RectBody::getRotation(): RectBody has no rotation");
	return 0.f;
}

void RectBody::setSpin(float f)
{
	Debug::warn("RectBody::setSpin(): RectBody has no spin");
}

float RectBody::getSpin() const
{
	Debug::warn("RectBody::getSpin(): RectBody has no spin");
	return 0.f;
}

GameRect RectBody::getRenderGameRect() const
{
	return GameRect(position, size);
}

float RectBody::getLeft() const
{
	return getPosition().x - getSize().x/2.f;
}

float RectBody::getRight() const
{
	return getPosition().x + getSize().x/2.f;
}

float RectBody::getTop() const
{
	return getPosition().y - getSize().y/2.f;
}

float RectBody::getBot() const
{
	return getPosition().y + getSize().y/2.f;
}

std::string RectBody::toString() const
{
	return "rect: left=" + Converter::floatToString(getLeft()) + " top=" + Converter::floatToString(getTop()) + " right=" + Converter::floatToString(getRight()) + " bot=" + Converter::floatToString(getBot()) + " speed=" + getSpeed().toString();
}

void RectBody::setSpeedAt(const GameVector& how, const GameVector& where) // where is a map-coordinate
{
	setSpeed(how);
}

GameVector RectBody::getSpeedAt(const GameVector& where) const // where is a map-coordinate
{
	return getSpeed();
}

void RectBody::reactToCollision(const float mass1, const float mass2, const GameVector& otherSpeed, const GameVector& collisionPoint)
{
	enum Pos { MIN, MID, MAX };

	Pos x, y;
	// set x
	if (collisionPoint.x > getLeft() + RANGE)
	{
		if ((collisionPoint.x < getRight() - RANGE))
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
	if (collisionPoint.y > getTop() + RANGE)
	{
		if ((collisionPoint.y < getBot() - RANGE))
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

	const float massshare = mass1 / (mass1 + mass2);

	GameVector v_sum(speed*massshare + otherSpeed*(1-massshare));
	GameVector sponge_sum(0.f, 0.f);
	if (mass2 != INFINITY)
	{
		sponge_sum = GameVector(v_sum + (otherSpeed - speed)/2 * (1-massshare));
	}

	float sponge = 2.f;

	GameVector speedSum = v_sum * (1.f - sponge) + sponge_sum * sponge;

	if ((x == MID) && (y == MID)) // Wenn der CollisionPoint in der Mitte der Entity liegt
	{
		// Move Out
		if (collisionPoint.x < position.x)
		{
			// Move Right
			position.x += collisionPoint.x - getLeft();
			speed.x = std::max(2*SPONGE + otherSpeed.x, speed.x);
		}
		else
		{
			// Move Left
			position.x += collisionPoint.x - getRight();
			speed.x = std::min(-2*SPONGE + otherSpeed.x, speed.x);
		}

		if (collisionPoint.y < position.y)
		{
			// Move Down
			position.y += collisionPoint.y - getTop();
			speed.y = std::max(2*SPONGE + otherSpeed.y, speed.y);
		}
		else
		{
			// Move Up
			position.y += collisionPoint.y - getBot();
			speed.y = std::min(-2*SPONGE + otherSpeed.y, speed.y);
		}
	}
	else if (x == MID) // Wenn nur x in der Mitte liegt
	{
		if (y == MIN)
		{
			// Move Down
			position.y += collisionPoint.y - getTop();
			speed.y = std::max(SPONGE + speedSum.y, speed.y);
		}
		else
		{
			// Move Up
			position.y += collisionPoint.y - getBot();
			speed.y = std::min(-SPONGE + speedSum.y, speed.y);
		}
	}
	else if (y == MID)
	{
		if (x == MIN)
		{
			// Move Right
			position.x += collisionPoint.x - getLeft();
			speed.x = std::max(SPONGE + speedSum.x, speed.x);
		}
		else
		{
			// Move Left
			position.x += collisionPoint.x - getRight();
			speed.x = std::min(-SPONGE + speedSum.x, speed.x);
		}
	}
}

void RectBody::apply(const Body* b)
{
	position = b->getPosition();
	size = b->getSize();
	speed = b->getSpeed();
}
