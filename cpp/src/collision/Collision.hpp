#ifndef __COLLISION_CLASS__
#define __COLLISION_CLASS__

#include "../math/game/GameVector.hpp"

class Entity;

class Collision
{
	public:
		Collision(Entity*, const GameVector&);
		virtual ~Collision() {}
		Entity* getEntity() const;
	private:
		Entity* entity;
		GameVector collisionPoint;
};

#include "../entity/Entity.hpp"

#endif
