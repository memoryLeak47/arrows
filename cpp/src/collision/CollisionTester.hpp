#ifndef __COLLISIONTESTER_CLASS__
#define __COLLISIONTESTER_CLASS__

class Entity;
class RectBody;

class CollisionTester
{
	public:
		static bool areColliding(Entity*, Entity*, float borderAddition=0);
		static bool areWrapperColliding(Entity*, Entity*);
};

#include <entity/Entity.hpp>
#include "RectBody.hpp"

#endif
