#include "PhysicsHandler.hpp"

#include <misc/Global.hpp>
#include <math/game/GameVector.hpp>
#include <entity/Entity.hpp>

void PhysicsHandler::handlePhysics(Entity* e1, Entity* e2, const GameVector& collisionPoint)
{
	Debug::funcOn("PhysicsHandler::handlePhysics(" + e1->toString() + ", " + e2->toString() + ")");

	float ms1 = 0.f;

	if (e1->isStatic())
	{
		if (e2->isStatic())
		{
			Debug::warn("PhysicsHandler::handlePhysics(): e1 and e2 are static");
			return;
		}
		else
		{
			ms1 = 1.f;
		}
	}
	else
	{
		if (not e2->isStatic())
		{
			ms1 = e1->getMass() / (e1->getMass() + e2->getMass());
		}
	}

	switch (Entity::getCollisionTypeIDBetween(e1, e2))
	{
		case CollisionTypeID::SOLID:
		{
			GameVector v1 = e1->getSpeedAt(collisionPoint);
			float sponge = Entity::getSpongeBetween(e1, e2);
			e1->reactToCollision_solid(ms1, e2->getSpeedAt(collisionPoint), collisionPoint, sponge);
			e2->reactToCollision_solid(1.f - ms1, v1, collisionPoint, sponge);
			break;
		}
		case CollisionTypeID::STICKY:
		{
			GameVector v1 = e1->getSpeedAt(collisionPoint);
			e1->reactToCollision_sticky(ms1, e2->getSpeedAt(collisionPoint), collisionPoint);
			e2->reactToCollision_sticky(1.f - ms1, v1, collisionPoint);
			break;
		}
		case CollisionTypeID::IGNORE:
			break;
		default:
		{
			Debug::error("unknown CollisionTypeID");
		}
	}

	Debug::funcOff("PhysicsHandler::handlePhysics(" + e1->toString() + ", " + e2->toString() + ")");
}
