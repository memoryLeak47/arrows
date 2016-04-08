#include "CollisionDetector.hpp"

#include "../misc/Debug.hpp"

CollisionLine CollisionDetector::getCollisionLine(Body* a, Body* b)
{
	if (!a->getWrapper().collidesWith(b->getWrapper()))
	{
		return CollisionLine(GameVector(-1, -1), GameVector(-1, -1));
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

CollisionLine CollisionDetector::rectCollision(RectBody* a, RectBody* b)
{
	Debug::warn("CollisionDetector: TODO");
	return CollisionLine(GameVector(-1, -1), GameVector(-1, -1));
}

CollisionLine CollisionDetector::rectCircleCollision(RectBody* a, CircleBody* b)
{
	Debug::warn("CollisionDetector: TODO");
	return CollisionLine(GameVector(-1, -1), GameVector(-1, -1));
}

CollisionLine CollisionDetector::circleCollision(CircleBody* a, CircleBody* b)
{
	Debug::warn("CollisionDetector: TODO");
	return CollisionLine(GameVector(-1, -1), GameVector(-1, -1));
}
