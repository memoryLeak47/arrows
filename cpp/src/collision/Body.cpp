#include "Body.hpp"

Body::Body(bool isRot)
	: rotateable(isRot)
{}

void Body::move(float time)
{
	setPosition(getPosition() + (getSpeed() * time));
	// setRotation(getRotation() + (2 * std::pi * getSpin() * time)); // TODO correct?
	// TODO rotation
}

void Body::applyImpact(const Impact& impact)
{
	if (rotateable)
	{
		// TODO
	}
	else
	{
		GameVector speedDif = impact.getSpeed() - getSpeed();
		setSpeed(getSpeed() + (speedDif * impact.getStrength()));
	}
}
