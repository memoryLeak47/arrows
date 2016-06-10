#include "Mob.hpp"

#include "../misc/Debug.hpp"

Mob::Mob(Body* body)
	: Entity(body)
{}

EntityType Mob::getEntityType()
{
	return ENTITYTYPE_MOB;
}

void Mob::actionGoLeft()
{
	getBody()->setSpeed(getBody()->getSpeed() - GameVector(0.003f, 0.f));
}

void Mob::actionGoRight()
{
	getBody()->setSpeed(getBody()->getSpeed() + GameVector(0.003f, 0.f));
}

void Mob::actionJump()
{
	getBody()->setSpeed(GameVector(getBody()->getSpeed().getX(), -0.1f));
}
