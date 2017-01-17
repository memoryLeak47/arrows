/*
	in = non-superficial collision / IN einander / eg. unrotated rects: 1.y == 2.y && 1.x == 2.x
	border = superficial collision / AN einander / eg. unrotated rects: 1.y == 2.y && 1.right == 2.left
	out = entfernt von einander

	two entities always have a collisionstatus = in / border / out

	CollisionDetector adds CollisionEvent on collision-status-change
*/

#ifndef __COLLISIONDETECTOR_CLASS__
#define __COLLISIONDETECTOR_CLASS__

enum CollisionStatus {IN, BORDER, OUT};

class Entity;
class CollisionEvent;

#include <deque>

class CollisionDetector
{
	public:
		static void addCollisionsBetween(Entity*, Entity*, std::deque<CollisionEvent*>*, float timeLeft);
};

#endif
