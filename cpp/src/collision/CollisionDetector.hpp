/*
	glitch         = non-superficial collision / IN einander / eg. unrotated rects: 1.y == 2.y && 1.x == 2.x
	border-collide = superficial collision / AN einander / eg. unrotated rects: 1.y == 2.y && 1.right == 2.left

	Requirements:
		adds enterEvent on border-collide: if the entities would glitch into each other
		adds exitEvent on border-collide: if the entities will move away from each other
		adds nothing on border-collide: if the entities don't move away / to each other
*/

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
