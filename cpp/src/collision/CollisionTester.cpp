#include "CollisionTester.hpp"

bool CollisionTester::areColliding(Entity* e1, Entity* e2, float borderAddition)
{
	// TODO
	Debug::warn("CollisionTester::areColliding(): TODO");
	return false;
}

bool CollisionTester::areWrapperColliding(Entity* e1, Entity* e2)
{
	const GameRect r1 = e1->getBody()->getWrapper(0);
	const GameRect r2 = e2->getBody()->getWrapper(0);

	if ((r1.getLeft() <= r2.getRight()) && (r1.getRight() >= r2.getLeft()))
	{
		if ((r1.getTop() <= r2.getBot()) && (r1.getBot() >= r2.getTop()))
		{
			return true;
		}
	}
	return false;
}
