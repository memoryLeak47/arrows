#include "CollisionDetector.hpp"

#include "../misc/Debug.hpp"

GameVector CollisionDetector::getCollisionPoint(Body* a, Body* b)
{
	if (!checkWrapper(a, b))
	{
		return GameVector(-1, -1);
	}
	if (a->getBodyType() == RECT)
	{
		if (b->getBodyType() == RECT)
			return rectCollision(dynamic_cast<RectBody*>(a), dynamic_cast<RectBody*>(b));
		else
			return rectCircleCollision(dynamic_cast<RectBody*>(a), dynamic_cast<CircleBody*>(b));
	}
	else
	{
		if (b->getBodyType() == RECT)
			return rectCircleCollision(dynamic_cast<RectBody*>(b), dynamic_cast<CircleBody*>(a));
		else 
			return circleCollision(dynamic_cast<CircleBody*>(a), dynamic_cast<CircleBody*>(b));
	}
}

GameVector CollisionDetector::rectCollision(RectBody* a, RectBody* b)
{
	Debug::warn("CollisionDetector: TODO");
	return GameVector(-1, -1);
}

GameVector CollisionDetector::rectCircleCollision(RectBody* a, CircleBody* b)
{
	Debug::warn("CollisionDetector: TODO");
	return GameVector(-1, -1);
}

GameVector CollisionDetector::circleCollision(CircleBody* a, CircleBody* b)
{
	Debug::warn("CollisionDetector: TODO");
	return GameVector(-1, -1);
}

bool CollisionDetector::unrotatedRectCollision(RectBody* a, RectBody* b)
{
	return     (a->getPosition().getX() <= b->getPosition().getX() + b->getSize().getX())
		&& (a->getPosition().getY() <= b->getPosition().getY() + b->getSize().getY())
		&& (b->getPosition().getX() <= a->getPosition().getX() + a->getSize().getX())
		&& (b->getPosition().getY() <= a->getPosition().getY() + a->getSize().getY());
}

bool CollisionDetector::checkWrapper(Body* a, Body* b)
{
	RectBody* wa = a->getWrapper();
	RectBody* wb = b->getWrapper();
	bool result = unrotatedRectCollision(wa, wb);
	delete wa;
	delete wb;
	return result;
}
