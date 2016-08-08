#include "CollisionHandler.hpp"

#include "../misc/Converter.hpp"
#include "../misc/Debug.hpp"
#include "PhysicsHandler.hpp"

void CollisionHandler::handleCollisionEvent(CollisionEvent* ev)
{
	// add partner
	if (not Entity::areCollisionPartners(ev->getEntity1(), ev->getEntity2()))
	{
		ev->getEntity1()->addCollisionPartner(ev->getEntity2());
		ev->getEntity2()->addCollisionPartner(ev->getEntity1());
	}

	// if its solid-collision
	if (Entity::getCollisionTypeBetween(ev->getEntity1(), ev->getEntity2()) == CollisionType::SOLID)
	{
		// Calculate CollisionPoints
		std::vector<GameVector> collisionPoints = getCollisionPoints(ev);

		// Calculate EscapeVectors
		GameVector escapeVector1 = getEscapeVector(ev->getEntity1(), collisionPoints);
		GameVector escapeVector2 = getEscapeVector(ev->getEntity2(), collisionPoints);

		// Handle Physics
		PhysicsHandler::handlePhysics(ev->getEntity1(), ev->getEntity2(), collisionPoints, escapeVector1, escapeVector2);
	}
}

std::vector<GameVector> CollisionHandler::getCollisionPoints(CollisionEvent* event)
{
	std::vector<GameVector> result;
	Entity *e1 = event->getEntity1(), *e2 = event->getEntity2();
	if (e1->getBody()->getBodyType() == BodyType::RECT && e2->getBody()->getBodyType() == BodyType::RECT)
	{
		const RectBody *b1 = dynamic_cast<const RectBody*>(e1->getBody());
		const RectBody *b2 = dynamic_cast<const RectBody*>(e2->getBody());
		if (b1->isEven() && b2->isEven())
		{
			float x1 = std::max(b1->getLeft(), b2->getLeft());
			float x2 = std::min(b1->getRight(), b2->getRight());

			float y1 = std::max(b1->getTop(), b2->getTop());
			float y2 = std::min(b1->getBot(), b2->getBot());

			GameVector lefttop(std::min(x1, x2), std::min(y1, y2));
			GameVector rightbot(std::max(x1, x2), std::max(y1, y2));

			result.push_back(lefttop);
			if (lefttop != rightbot)
			{
				result.push_back(rightbot);
			}
		}
	}
	return result;
}

// Ein EscapeVector gibt an, in welche Richtung man sich von einer Entity(e) entfernen kann.
// Ein EscapeVector zeigt von der Entity(e) weg.
GameVector CollisionHandler::getEscapeVector(Entity* e, const std::vector<GameVector>& collisionPoints)
{
	if (collisionPoints.size() == 2)
	{
		GameVector ab = collisionPoints[1] - collisionPoints[0]; // Vector vom einen zum anderen CollisionPoint
		GameVector am = e->getBody()->getPosition() - collisionPoints[0]; // Vector von a nach Mittelpunkt der Entity
		GameVector result = am.getProjectionOn(ab.getOrthogonal());
		if (result.getMagnitude() == 0) Debug::error("CollisionHandler::getEscapeVector(): result is zero-vector");
		return result;
	}
	else if (collisionPoints.size() == 1) // Der CollisionPunkt muss sich an einer der Ecken der Entity befinden
	{
		if (e->getBody()->getPosition().getX() < collisionPoints[0].getX())
		{
			return GameVector(-1.f, 0.f);
		}
		else if (e->getBody()->getPosition().getX() > collisionPoints[0].getX())
		{
			return GameVector(1.f, 0.f);
		}
		else
		{
			Debug::error("CollisionHandler::getEscapeVector(): CollisionPoints.size() == 1:\te->getBody()->getX() == collisionPoints[0]->getX()");
		}
	}
	Debug::error("CollisionHandler::getEscapeVector(): collisionPoints.size() = " + Converter::intToString(collisionPoints.size()));
	return GameVector(0.f, 0.f);
}
