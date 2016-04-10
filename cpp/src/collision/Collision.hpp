#ifndef __COLLISION_CLASS__
#define __COLLISION_CLASS__

#include "../math/game/GameVector.hpp"

#include "CollisionLine.hpp"

class Entity;

class Collision
{
	public:
		Collision(Entity*, const CollisionLine&);
		virtual ~Collision() {}
		Entity* getEntity() const;
	private:
		Entity* entity;
		CollisionLine line;
};

#include "../entity/Entity.hpp"

#endif
