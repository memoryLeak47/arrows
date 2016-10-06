#include "PhysicsHandler.hpp"

#include "CollisionTester.hpp"

#include <map>
#include <cmath>
#include <iostream>

static const float DRAG = 0.f;
static const float SPONGE = 0.0001f;

// hidden Function
std::vector<Entity*> getCollisionGroup(Entity* e)
{
	std::vector<Entity*> group;
	group.push_back(e);
	unsigned int i = 0;
	while (i < group.size())
	{
		for (Entity* c : group[i]->getCollisionPartners())
		{
			if (!memberOf(c, group))
			{
				group.push_back(c);
			}
		}
		i++;
	}
	return group;
}

std::vector<GameVector> PhysicsHandler::getCollisionPoints(Entity* e1, Entity* e2)
{
	std::vector<GameVector> result;
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
GameVector PhysicsHandler::getEscapeVector(Entity* e, const std::vector<GameVector>& collisionPoints)
{
	if (collisionPoints.size() == 2)
	{
		GameVector ab = collisionPoints[1] - collisionPoints[0]; // Vector vom einen zum anderen CollisionPoint
		GameVector am = e->getBody()->getPosition() - collisionPoints[0]; // Vector von a nach Mittelpunkt der Entity
		GameVector result = am.getProjectionOn(ab.getOrthogonal());
		if (result.getMagnitude() == 0) Debug::error("PhysicsHandler::getEscapeVector(): result is zero-vector");
		GameVector v = (result * -1.f).getNormalized();
		/* XXX WORKAROUND XXX works only for even rects TODO */
		if (std::abs(v.x) > std::abs(v.y))
		{
			if (v.x<0)
				return {-1,0};
			return {1,0};
		}
		if (v.y<0)
			return {0,-1};
		return {0,1};
	}
	else if (collisionPoints.size() == 1) // Der CollisionPunkt muss sich an einer der Ecken der Entity befinden
	{
		Debug::error("NOOOOOO");
		if (e->getBody()->getPosition().x < collisionPoints[0].x)
		{
			return GameVector(1.f, 0.f);
		}
		else if (e->getBody()->getPosition().x > collisionPoints[0].x)
		{
			return GameVector(-1.f, 0.f);
		}
		else
		{
			Debug::error("PhysicsHandler::getEscapeVector(): CollisionPoints.size() == 1:\te->getBody()->x == collisionPoints[0]->x");
		}
	}
	Debug::error("PhysicsHandler::getEscapeVector(): collisionPoints.size() = " + Converter::intToString(collisionPoints.size()));
	return GameVector(0.f, 0.f);
}

bool moveToEachOther(Entity* e1, Entity* e2, GameVector esc)
{
	return 0 < GameVector::getScalarProduct(esc, (e1->getBody()->getSpeed() - e2->getBody()->getSpeed()));
}

void applyPhysics(Entity* e1, Entity* e2)
{
	const float m1 = e1->getMass();
	const float m2 = e2->getMass();

	GameVector v_sum(0.f, 0.f);
	if (not (e1->isStatic() or (e2->isStatic())))
	{
		v_sum = ((e1->getBody()->getSpeed()*m1)+(e2->getBody()->getSpeed()*m2)) / (m1+m2);
	}

	const std::vector<GameVector> points = PhysicsHandler::getCollisionPoints(e1, e2);
	const GameVector escVec = PhysicsHandler::getEscapeVector(e1, points);
	const GameVector otto = escVec.getOrthogonal();

	if (not moveToEachOther(e1, e2, escVec)) return;
	e1->setSpeed(e1->getBody()->getSpeed().getProjectionOn(otto)*(1-DRAG) + v_sum.getProjectionOn(escVec) - escVec.withMagnitude(SPONGE));
	e2->setSpeed(e2->getBody()->getSpeed().getProjectionOn(otto)*(1-DRAG) + v_sum.getProjectionOn(escVec) + escVec.withMagnitude(SPONGE));
}

void handleRecursive(Entity* e1)
{
	for (unsigned int i = 0; i < e1->getCollisionPartners().size(); ++i)
	{
		GameVector esc = PhysicsHandler::getEscapeVector(e1, PhysicsHandler::getCollisionPoints(e1, e1->getCollisionPartners()[i]));
		if (moveToEachOther(e1, e1->getCollisionPartners()[i], esc))
		{
			applyPhysics(e1, e1->getCollisionPartners()[i]);
			handleRecursive(e1->getCollisionPartners()[i]);
		}
	}
}

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
	e2->reactToCollision(1.f-ms1, v1, collisionPoint);

	Debug::funcOff("PhysicsHandler::handlePhysics(" + e1->toString() + ", " + e2->toString() + ")");
}
