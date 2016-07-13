#include "PhysicsHandler.hpp"

// MultiCollisions sind noch nicht mit eingerechnet

void PhysicsHandler::handlePhysics(Entity* e1, Entity* e2, std::vector<GameVector> collisionPoints, const GameVector& escapeVec1, const GameVector& escapeVec2)
{
	GameVector s1 = e1->getBody()->getSpeed();
	GameVector s2 = e2->getBody()->getSpeed();
	float m1 = e1->getMass();
	float m2 = e2->getMass();

	GameVector v(0.f, 0.f);
	if (m1 == INFINITY)
	{
		v = s1;
		if (m2 == INFINITY)
		{
			Debug::error("infinite mass collision");
		}
	}
	else if (m2 == INFINITY)
	{
		v = s2;
	}
	else
	{
		v = (e1->getBody()->getSpeed() * e1->getMass() + e2->getBody()->getSpeed() * e2->getMass()) / (e1->getMass() + e2->getMass());
	}

	GameVector res1 = v;
	GameVector res2 = v;

	Debug::test("res1=" + res1.toString() + " res2=" + res2.toString());
	e1->setSpeed(res1);
	e2->setSpeed(res2);
}
