#ifndef __COLLISIONTESTER_CLASS__
#define __COLLISIONTESTER_CLASS__

#include <cstddef>

class Entity;
class GameVector;

class CollisionTester
{
	public:
		static bool areColliding(Entity*, Entity*, float borderAddition=0, GameVector* point = NULL);
		static bool areWrapperColliding(Entity*, Entity*);
};

#include <entity/Entity.hpp>
#include <math/game/GameVector.hpp>

#endif
