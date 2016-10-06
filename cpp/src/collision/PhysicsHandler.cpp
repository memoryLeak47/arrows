#include "PhysicsHandler.hpp"

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
	GameVector v1 = e1->getBody()->getSpeedAt(collisionPoint);

	e1->reactToCollision(ms1, e2->getBody()->getSpeedAt(collisionPoint), collisionPoint);
	e2->reactToCollision(1.f - ms1, v1, collisionPoint);

	Debug::funcOff("PhysicsHandler::handlePhysics(" + e1->toString() + ", " + e2->toString() + ")");
}
