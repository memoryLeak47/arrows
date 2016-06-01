#ifndef __COLLISIONDETECTOR_CLASS__
#define __COLLISIONDETECTOR_CLASS__

#include <vector>

class CollisionEvent;
class Entity;

class CollisionDetector
{
	public:
		static void addCollisionsBetween(Entity*, Entity*, std::vector<CollisionEvent*>*, float timeLeft);
	private:
		static void addCollisionsBetweenEvenRects(Entity*, Entity*, std::vector<CollisionEvent*>*, float timeLeft);
};

#include "CollisionEvent.hpp"
#include "../entity/Entity.hpp"

#endif
