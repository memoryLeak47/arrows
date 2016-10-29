#ifndef __SIMPLEARROW_CLASS__
#define __SIMPLEARROW_CLASS__

class Mob;

#include <entity/Bullet.hpp>

class SimpleArrow : public Bullet
{
	public:
		SimpleArrow(const GameVector& pos, const GameVector& speed, Mob* owner);
};

#endif
