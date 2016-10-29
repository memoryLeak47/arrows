#include "Bullet.hpp"

Bullet::Bullet(Body* body, Mob* o)
	: ImpactfulDynamicEntity(body), owner(o)
{}

EntityType Bullet::getEntityType() const
{
	return EntityType::BULLET;
}

Mob* Bullet::getOwner() const
{
	return owner;
}
