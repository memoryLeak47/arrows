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

void Body::applyImpact(const Impact& impact)
{
	Debug::test("applyImpact(" + impact.getSpeed().toString() + ")");
	if (rotateable)
	{
		// TODO
	}
	else
	{
		setSpeed(getSpeed() + (impact.getSpeed() * impact.getStrength()));
	}
}
