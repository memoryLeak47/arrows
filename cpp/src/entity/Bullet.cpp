#include "Bullet.hpp"

#include <entity/Mob.hpp>

Bullet::Bullet(const EntityGivethrough& gt, Mob* o)
	: Idler(gt), owner(o)
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
