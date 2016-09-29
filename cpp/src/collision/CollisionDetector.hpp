/*
	in = non-superficial collision / IN einander / eg. unrotated rects: 1.y == 2.y && 1.x == 2.x
	border = superficial collision / AN einander / eg. unrotated rects: 1.y == 2.y && 1.right == 2.left
	out = entfernt von einander

	two entities always have a collisionstatus = in / border / out

	CollisionDetector adds CollisionEvent on collision-status-change
*/

#ifndef __COLLISIONDETECTOR_CLASS__
#define __COLLISIONDETECTOR_CLASS__

#include <vector>

class CollisionEvent;
class Entity;

enum CollisionStatus {IN, BORDER, OUT};

class CollisionDetector
{
	public:
		static void addCollisionsBetween(Entity*, Entity*, std::vector<CollisionEvent*>*, float timeLeft);
	private:
		static void addCollisionsBetweenEvenRects(Entity*, Entity*, std::vector<CollisionEvent*>*, float timeLeft);
};

#include "CollisionEvent.hpp"
#include <entity/Entity.hpp>

#endif
