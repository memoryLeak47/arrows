#ifndef __COLLISIONTESTER_CLASS__
#define __COLLISIONTESTER_CLASS__

class Entity;
class RectBody;

class CollisionTester
{
	public:
		static bool isColliding(Entity*, Entity*);
	private:
		static bool isCollidingEvenRects(const RectBody*, const RectBody*);
};

#include "../entity/Entity.hpp"
#include "RectBody.hpp"

#endif
