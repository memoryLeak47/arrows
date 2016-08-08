#include "Bullet.hpp"

Bullet::Bullet(Body* body)
	: Entity(body)
{}

EntityType Bullet::getEntityType() const
{
	return EntityType::BULLET;
}
