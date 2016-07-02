#ifndef __PHYSICSHANDLER_CLASS__
#define __PHYSICSHANDLER_CLASS__

#include <vector>

class Entity;
class GameVector;

class PhysicsHandler
{
	public:
		static void handlePhysics(Entity* e1, Entity* e2, std::vector<GameVector> collisionPoints, const std::vector<GameVector>& escapeVec1, const std::vector<GameVector>& escapeVec2);
};

#include "../entity/Entity.hpp"
#include "../math/game/GameVector.hpp"

#endif
