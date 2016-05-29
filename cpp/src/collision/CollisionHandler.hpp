#ifndef __COLLISIONHANDLER_CLASS__
#define __COLLISIONHANDLER_CLASS__

class CollisionEvent;

class CollisionHandler
{
	public:
		static void handleCollisionEvent(CollisionEvent*);
};

#include "CollisionEvent.hpp"

#endif
