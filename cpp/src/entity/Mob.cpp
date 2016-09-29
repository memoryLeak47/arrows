#include "Mob.hpp"

#include <misc/Debug.hpp>

Mob::Mob(Body* body)
	: Entity(body)
{}

EntityType Mob::getEntityType() const
{
	return EntityType::MOB;
}

void Mob::actionGoLeft()
{
	push(GameVector(-getMaxXSpeed(), 0.f));
}

void Mob::actionGoRight()
{
	push(GameVector(+getMaxXSpeed(), 0.f));
}

void Mob::actionJump()
{
	setSpeed(GameVector(body->getSpeed().x, -0.1f));
}

float Mob::getMass() const
{
	return 10.f;
}

float Mob::getMaxXSpeed() const
{
	return 0.3f;
}
