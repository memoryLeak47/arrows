#include "CollisionHandler.hpp"

#include "../misc/Converter.hpp"
#include "../misc/Debug.hpp"

void CollisionHandler::handleCollisionEvent(CollisionEvent* ev)
{
	int collisionType = std::max(ev->getEntity1()->getCollisionType(), ev->getEntity2()->getCollisionType());
	switch (collisionType)
	{
		case COLLISIONTYPE_SOLID:
			handleCollisionEventSolid(ev);
			break;
		case COLLISIONTYPE_IGNORE:
			// do nothing, unsuccessfully
			break;
	}
}

void CollisionHandler::handleCollisionEventSolid(CollisionEvent* event)
{
	Entity* entity1 = event->getEntity1();
	Entity* entity2 = event->getEntity2();

	Debug::test("collision: " + entity1->toString() + " vs " + entity2->toString());

	float massShare1; // wieviel Prozent der Gesamtmasse der beiden CollisionPartner nimmt entity1 ein
	float massShare2; // wieviel Prozent der Gesamtmasse der beiden CollisionPartner nimmt entity2 ein

	if (entity1->isStatic())
	{
		massShare1 = 1;
		if (entity2->isStatic())
		{
			Debug::error("CollisionHandler::handleCollisionEventSolid(): static vs static :/ (" + Converter::intToString(entity1->getEntityType()) + " - " + Converter::intToString(entity2->getEntityType()));
		}
	}
	else if (entity2->isStatic())
	{
		massShare1 = 0;
	}
	else
	{
		massShare1 = entity1->getMass() / (entity1->getMass() + entity2->getMass());
	}

	massShare2 = 1-massShare1;
	//GameVector speedDif = entity1->getBody()->getSpeed() - entity2->getBody()->getSpeed();
	entity1->applyImpact(Impact(entity2->getBody()->getSpeed(), massShare2, GameVector(0.f, 0.f)));
	entity2->applyImpact(Impact(entity1->getBody()->getSpeed(), massShare1, GameVector(0.f, 0.f)));
}
