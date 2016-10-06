#include "RectBody.hpp"

#include <cmath>
#include <algorithm>

#include <misc/Debug.hpp>

static const float RANGE = 0.1f;
static const float IMPULSE = 0.01f;

RectBody::RectBody(const GameVector& pos, const GameVector& size, const GameVector& speed, bool isRot, float rot, float spin)
	: Body(isRot), position(pos), size(size), speed(speed), rotation(rot), spin(spin)
{}

BodyType RectBody::getBodyType() const
{
	return RECT;
}

GameRect RectBody::getWrapper(float timeLeft) const
{
	if (isEven())
	{
		float deltaX = speed.x * timeLeft;
		float deltaY = speed.y * timeLeft;

		float sizeX = size.x + std::abs(deltaX);
		float sizeY = size.y + std::abs(deltaY);
		float posX = getPosition().x + deltaX/2 - sizeX/2;
		float posY = getPosition().y + deltaY/2 - sizeY/2;

		return GameRect(GameVector(posX, posY), GameVector(sizeX, sizeY));
	}
	else
	{
		float deltaX = speed.x * timeLeft;
		float deltaY = speed.y * timeLeft;

		float diagonal = 2 * getSize().getMagnitude();
		float sizeX = diagonal + std::abs(deltaX);
		float sizeY = diagonal + std::abs(deltaY);
		float posX = getPosition().x + deltaX/2 - sizeX/2;
		float posY = getPosition().y + deltaY/2 - sizeY/2;

		return GameRect(GameVector(posX, posY), GameVector(sizeX, sizeY));
	}
}

bool RectBody::isCollidingPoint(const GameVector& point) const
{
	if (isEven())
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
	// is not Even
	Debug::warn("RectBody::isCollidingPoint(): TODO");
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

const GameVector& RectBody::getSize() const
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
	rotation = f;
}

float RectBody::getRotation() const
{
	return rotation;
}

void RectBody::setSpin(float f)
{
	spin = f;
}

float RectBody::getSpin() const
{
	return spin;
}

GameRect RectBody::getRenderGameRect() const
{
	return GameRect(position, size);
}

bool RectBody::isEven() const
{
	return (getSpin() == 0.f) && (getRotation() == 0.f);
}

float RectBody::getLeft() const
{
	if (isEven())
	{
		return getPosition().x - getSize().x/2.f;
	}
	else
	{
		Debug::warn("RectBody::getLeft(): TODO");
	}
	return 0.f;
}

float RectBody::getRight() const
{
	if (isEven())
	{
		return getPosition().x + getSize().x/2.f;
	}
	else
	{
		Debug::warn("RectBody::getRight(): TODO");
	}
	return 0.f;
}

float RectBody::getTop() const
{
	if (isEven())
	{
		return getPosition().y - getSize().y/2.f;
	}
	else
	{
		Debug::warn("RectBody::getTop(): TODO");
	}
	return 0.f;
}

float RectBody::getBot() const
{
	if (isEven())
	{
		return getPosition().y + getSize().y/2.f;
	}
	else
	{
		Debug::warn("RectBody::getBot(): TODO");
	}
	return 0.f;
}

std::string RectBody::toString() const
{
	if (isEven())
	{
		return "rect: left=" + Converter::floatToString(getLeft()) + " top=" + Converter::floatToString(getTop()) + " right=" + Converter::floatToString(getRight()) + " bot=" + Converter::floatToString(getBot()) + " speed=" + getSpeed().toString();
	}
	else
	{
		return "rotated-rect: pos=" + getPosition().toString() + " size=" + getSize().toString() + " speed=" + getSpeed().toString() + " rotation=" + Converter::floatToStringPrecise(rotation);
	}
}

void RectBody::setSpeedAt(const GameVector& how, const GameVector& where) // where is a map-coordinate
{
	if (isEven() || where == getPosition())
	{
		setSpeed(how);
	}
	else
	{
		Debug::warn("RectBody::setSpeedAt: TODO");
	}
}

GameVector RectBody::getSpeedAt(const GameVector& where) const // where is a map-coordinate
{
	if (isEven())
	{
		return getSpeed();
	}
	else
	{
		return Body::getSpeedAt(where);
	}
}

void RectBody::reactToCollision(float massshare, const GameVector& otherSpeed, const GameVector& collisionPoint)
{
	if (isEven())
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
		if ((x == MID) && (y == MID))
		{
			// Move Out
			if (collisionPoint.x < position.x) // move right
				speed.x = std::max(IMPULSE, speed.x);
			else
				speed.x = std::min(-IMPULSE, speed.x);

			if (collisionPoint.y < position.y)
				speed.y = std::max(IMPULSE, speed.y);
			else
				speed.y = std::min(-IMPULSE, speed.y);
		}
		else if (x == MID)
		{
			if (y == MIN)
			{
				// Move Down
				speed.y = std::max(IMPULSE, speed.y);
			}
			else
			{
				// Move Up
				speed.y = std::min(-IMPULSE, speed.y);
			}
		}
		else if (y == MID)
		{
			if (x == MIN)
			{
				// Move Right
				speed.x = std::max(IMPULSE, speed.x);
			}
			else
			{
				// Move Left
				speed.x = std::min(-IMPULSE, speed.x);
			}
 		}
	}
	else
	{
		Debug::warn("RectBody::reactToCollision(): not Even TODO");
	}
}
