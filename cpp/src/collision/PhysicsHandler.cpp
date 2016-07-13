#include "PhysicsHandler.hpp"

// MultiCollisions sind noch nicht mit eingerechnet

void PhysicsHandler::handlePhysics(Entity* e1, Entity* e2, std::vector<GameVector> collisionPoints, const GameVector& escapeVec1, const GameVector& escapeVec2)
{
	e1->stop();
	e2->stop();
}
