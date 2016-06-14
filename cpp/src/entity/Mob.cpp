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
	body->applyImpact(Impact(GameVector(-getMaxXSpeed(), 0.f), 0.03f, body->getPosition()));
}

void Mob::actionGoRight()
{
	body->applyImpact(Impact(GameVector(getMaxXSpeed(), 0.f), 0.03f, body->getPosition()));
}

void Mob::actionJump()
{
	body->setSpeed(GameVector(body->getSpeed().getX(), -0.1f));
}
