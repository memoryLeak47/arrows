#include "Body.hpp"

#include "../misc/Debug.hpp"

#include <math.h>

Body::Body(bool isRot)
	: rotateable(isRot)
{}

void Body::move(float time)
{
	setPosition(getPosition() + (getSpeed() * time));
	// setRotation(getRotation() + (2 * std::pi * getSpin() * time)); // TODO correct?
	// TODO rotation
}

GameVector Body::getSpeedAt(const GameVector& where) const
{
	if (where == getPosition())
	{
		return getSpeed();
	}
	else
	{
		return ((where - getPosition()) * getSpin() * 2 * ((float)M_PI)) + getSpeed();
	}
}
