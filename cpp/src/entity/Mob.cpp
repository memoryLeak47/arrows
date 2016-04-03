#include "Mob.hpp"

#include "../misc/Debug.hpp"

Mob::Mob(Body* body)
	: Entity(body)
{}

void Mob::handleCollisions()
{
	handleCollisionsLikeAMob();
}

void Mob::handleCollisionsLikeAMob()
{
	Debug::warn("Mob::handleCollisionsLikeAMob(): TODO");
}
