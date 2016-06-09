#include "Mob.hpp"

#include "../misc/Debug.hpp"

Mob::Mob(Body* body)
	: Entity(body)
{
	getBody()->setSpeed(GameVector(-0.03f, 0.03f)); // TODO remove
	Debug::warn("Mob::Mob(): remove setSpeed");
}

EntityType Mob::getEntityType()
{
	return ENTITYTYPE_MOB;
}
