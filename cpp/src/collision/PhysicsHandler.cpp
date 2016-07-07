#include "PhysicsHandler.hpp"

#include "../misc/Global.hpp"

// MultiCollisions sind noch nicht mit eingerechnet

void PhysicsHandler::handlePhysics(Entity* e1, Entity* e2, std::vector<GameVector> collisionPoints, const std::vector<GameVector>& escapeVec1, const std::vector<GameVector>& escapeVec2)
{
	Debug::test("stop");
	e1->stop();
	e1->setPosition(e1->getBody()->getPosition() + (e2->getBody()->getPosition() - e1->getBody()->getPosition()) * -0.01f);
	e2->stop();
}
