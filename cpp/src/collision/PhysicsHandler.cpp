#include "PhysicsHandler.hpp"

// MultiCollisions sind noch nicht mit eingerechnet

void PhysicsHandler::handlePhysics(Entity* e1, Entity* e2, std::vector<GameVector> collisionPoints, const GameVector& escapeVec1, const GameVector& escapeVec2)
{
	Debug::funcOn("PhysicsHandler::handlePhysics(" + e1->toString() + ", " + e2->toString() + ")");

	// init

	GameVector v1 = e1->getBody()->getSpeed();
	GameVector v2 = e2->getBody()->getSpeed();
	GameVector v(0.f,0.f);
	float m1 = e1->getMass();
	float m2 = e2->getMass();

	float drag = 0.01f;

	if (e1->isStatic())
	{
		v.apply(v1);
	}
	else if (e2->isStatic())
	{
		v.apply(v2);
	}
	else
	{
		v = (v1 * m1) + (v2 * m2) / (m1 + m2);
	}

	// simple deglitch

	if (v1 != GameVector(0, 0))
	{
		e1->addPosition(v1.getNormalized() * -global::BORDER_SIZE);
	}

	if (v2 != GameVector(0, 0))
	{
		e2->addPosition(v2.getNormalized() * -global::BORDER_SIZE);
	}

	// physics

	GameVector v1res(v1.getProjectionOn(escapeVec1.getOrthogonal())*(1-drag) + v.getProjectionOn(escapeVec1));
	GameVector v2res(v2.getProjectionOn(escapeVec2.getOrthogonal())*(1-drag) + v.getProjectionOn(escapeVec2));

	e1->setSpeed(v1res);
	e2->setSpeed(v2res);

	/* // This is a working older version
		// mass-share (ms1, ms2) definition has been removed.

		GameVector res1 = (v2 - v1).getProjectionOn(escapeVec1) * ms2;
		GameVector res2 = (v1 - v2).getProjectionOn(escapeVec2) * ms1;

		e1->addSpeed(res1);
		e2->addSpeed(res2);
	*/

	Debug::funcOff("PhysicsHandler::handlePhysics(" + e1->toString() + ", " + e2->toString() + ")");
}
