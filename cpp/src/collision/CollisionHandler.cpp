#include "CollisionHandler.hpp"

#include "../misc/Converter.hpp"
#include "../misc/Debug.hpp"

void CollisionHandler::handleCollisionEvent(CollisionEvent* ev)
{
	Debug::funcOn("CollisionHandler::handleCollisionEvent: " + ev->toString());
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
	Debug::funcOff("CollisionHandler::handleCollisionEvent: " + ev->toString());
}

void CollisionHandler::handleCollisionEventSolid(CollisionEvent* event)
{
	Entity* entity1 = event->getEntity1();
	Entity* entity2 = event->getEntity2();

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

	GameVector point = (event->getCollisionPoints()[0] + event->getCollisionPoints()[1])/2.f;

	for (unsigned int i = 0; i < event->getCollisionPoints().size(); i++)
	{
		Debug::test("collisionPoint[" + Converter::intToString((int)i) + "] = " + event->getCollisionPoints()[i].toString());
	}
	if (event->getCollisionPoints().size() == 1)
	{
		entity1->applyImpact(Impact(entity2->getBody()->getSpeed(), massShare2, point));
		entity2->applyImpact(Impact(entity1->getBody()->getSpeed(), massShare1, point));
	}
	else if (event->getCollisionPoints().size() == 2)
	{
		GameVector norm(event->getCollisionPoints()[0] - event->getCollisionPoints()[1]);
		norm = norm/norm.getMagnitude();
		norm = GameVector(norm.getY(), -norm.getX());
		Debug::test("norm = " + norm.toString());
		GameVector v1(norm * GameVector::getScalarProduct(norm, entity2->getBody()->getSpeed()));
		GameVector v2(norm * GameVector::getScalarProduct(norm, entity1->getBody()->getSpeed()));
		entity1->applyImpact(Impact(v1, massShare2, point));
		entity2->applyImpact(Impact(v2, massShare1, point));
	}
	else
	{
		Debug::warn("CollisionHandler::handleCollisionEventSolid: so many points!");
	}
}
