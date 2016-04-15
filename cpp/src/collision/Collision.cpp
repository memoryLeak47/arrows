#include "Collision.hpp"
	
Collision::Collision(Entity* e, const CollisionLine& line)
	: line(line)
{
	entity = e;
}

Entity* Collision::getEntity() const
{
	return entity;
}
