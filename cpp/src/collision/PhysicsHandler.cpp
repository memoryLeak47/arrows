#include "PhysicsHandler.hpp"

// MultiCollisions sind noch nicht mit eingerechnet

void PhysicsHandler::handlePhysics(Entity* e1, Entity* e2, std::vector<GameVector> collisionPoints, const GameVector& escapeVec1, const GameVector& escapeVec2)
{
	GameVector s1 = e1->getBody()->getSpeed();
	GameVector s2 = e2->getBody()->getSpeed();
	float m1 = e1->getMass();
	float m2 = e2->getMass();
	float ms1, ms2;

	if (m1 == INFINITY)
	{
		ms1 = 1.f;
		ms2 = 0.f;
	}
	else if (m2 == INFINITY)
	{
		ms1 = 0.f;
		ms2 = 1.f;
	}
	else
	{
		ms1 = m1/(m1+m2);
		ms2 = 1.f - ms1;
	}

	GameVector res1 = (s2 - s1).getProjectionOn(escapeVec1) * ms2;
	GameVector res2 = (s1 - s2).getProjectionOn(escapeVec2) * ms1;

	e1->addSpeed(res1);
	e2->addSpeed(res2);
}
