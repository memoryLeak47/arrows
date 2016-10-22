#ifndef __PHYSICSHANDLER_CLASS__
#define __PHYSICSHANDLER_CLASS__

class Entity;
class GameVector;

#include <vector>

class PhysicsHandler
{
	public:
		static void handlePhysics(Entity* e1, Entity* e2, const GameVector& collisionPoint);
		static GameVector getEscapeVector(Entity* e, const std::vector<GameVector>& collisionPoints);
		static std::vector<GameVector> getCollisionPoints(Entity* e1, Entity* e2);
};

#endif
