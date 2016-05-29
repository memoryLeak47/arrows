#ifndef __COLLISIONDETECTOR_CLASS__
#define __COLLISIONDETECTOR_CLASS__

#include <vector>

class CollisionEvent;
class Entity;

class CollisionDetector
{
	public:
		static void addCollisionsBetween(Entity*, Entity*, float timeLeft, std::vector<CollisionEvent*>*);
};

#include "CollisionEvent.hpp"
#include "../entity/Entity.hpp"

#endif
