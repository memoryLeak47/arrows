#include "Bullet.hpp"

Bullet::Bullet(const EntityGivethrough& gt, Mob* o)
	: Idler(gt), owner(o)
{}

Bullet::Bullet(CompressBuffer* buffer)
	: Idler(buffer)
{}

std::vector<FrameCloneable**> Bullet::getClonePointers() const
{
	std::vector<FrameCloneable**> tmp = Idler::getClonePointers();
	tmp.push_back((FrameCloneable**) &owner);
	return tmp;
}

EntityType Bullet::getEntityType() const
{
	return EntityType::BULLET;
}

Mob* Bullet::getOwner() const
{
	return owner;
}
