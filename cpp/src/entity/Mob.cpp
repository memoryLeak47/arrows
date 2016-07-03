#include "Mob.hpp"

#include "../misc/Debug.hpp"

Mob::Mob(Body* body)
	: Entity(body)
{}

EntityType Mob::getEntityType()
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
	body->setSpeed(GameVector(body->getSpeed().getX(), -0.1f));
}
