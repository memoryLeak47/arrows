#ifndef __PHYSICSHANDLER_CLASS__
#define __PHYSICSHANDLER_CLASS__

#include <vector>

class Entity;
class GameVector;

class PhysicsHandler
{
	public:
		static void handlePhysics(Entity* e1, Entity* e2);
		static GameVector getEscapeVector(Entity* e, const std::vector<GameVector>& collisionPoints);
		static std::vector<GameVector> getCollisionPoints(Entity* e1, Entity* e2);
};

#include "../entity/Entity.hpp"
#include "../math/game/GameVector.hpp"

#endif
