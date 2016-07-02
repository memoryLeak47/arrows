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
	applyImpact(Impact(GameVector(-getMaxXSpeed(), 0.f), 0.03f, body->getPosition()));
}

void Mob::actionGoRight()
{
	applyImpact(Impact(GameVector(getMaxXSpeed(), 0.f), 0.03f, body->getPosition()));
}

void Mob::actionJump()
{
	body->setSpeed(GameVector(body->getSpeed().getX(), -0.1f));
}
