#include "Bullet.hpp"

Bullet::Bullet(Body* body, Mob* o)
	: Idler(body), owner(o)
{}

Bullet::Bullet(CompressBuffer* buffer)
	: Idler(buffer)
{}

EntityType Bullet::getEntityType() const
{
	return EntityType::BULLET;
}

Mob* Bullet::getOwner() const
{
	return owner;
}
