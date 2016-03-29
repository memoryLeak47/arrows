#include "Collision.hpp"
	
Collision::Collision(Entity* e, const GameVector& v)
	: collisionPoint(v)
{
	entity = e;
}
