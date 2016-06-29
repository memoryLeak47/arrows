/*
	handleCollisionEvent is only called for solid collisions (and maybe slow-collision or something)
	It prevents the glitching of the entities into each other
	It applies a drag
	It pushes the entities away from each other by sponginess
*/

#ifndef __COLLISIONHANDLER_CLASS__
#define __COLLISIONHANDLER_CLASS__

class CollisionEvent;

class CollisionHandler
{
	public:
		static void handleCollisionEvent(CollisionEvent*);
	private:
		static void handleCollisionEventSolid(CollisionEvent*);
};

#include "CollisionEvent.hpp"

#endif
