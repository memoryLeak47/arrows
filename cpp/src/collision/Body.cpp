#include "Body.hpp"

#include "../misc/Debug.hpp"

Body::Body(bool isRot)
	: rotateable(isRot)
{}

void Body::move(float time)
{
	setPosition(getPosition() + (getSpeed() * time));
	// setRotation(getRotation() + (2 * std::pi * getSpin() * time)); // TODO correct?
	// TODO rotation
}


const GameVector Body::getSpeedAt(const GameVector&) const
{
	Debug::warn("Body::getSpeedAt(): Not accurate, when rotating");
	return GameVector(getSpeed());
}

void Body::applyImpact(const Impact& impact)
{
	if (rotateable)
	{
		// TODO
	}
	else
	{
		setSpeed(getSpeed() + (impact.getSpeed() * impact.getStrength()));
	}
}
