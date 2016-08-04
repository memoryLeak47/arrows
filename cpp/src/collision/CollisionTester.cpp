#include "CollisionTester.hpp"

bool CollisionTester::isColliding(Entity* e1, Entity* e2)
{
	if (e1->getBody()->getBodyType() == BodyType::RECT)
	{
		if (dynamic_cast<const RectBody*>(e1->getBody())->isEven())
		{
			// e1 unrot rect
			if (e2->getBody()->getBodyType() == BodyType::RECT)
			{
				if (dynamic_cast<const RectBody*>(e2->getBody())->isEven())
				{
					// e2 unrot Rects
					return isCollidingEvenRects(dynamic_cast<const RectBody*>(e1->getBody()), dynamic_cast<const RectBody*>(e2->getBody()));
				}
			}
		}
		else
		{
			// e1 Rotated Rect
		}
	}
	else
	{
		// e1 Circle
	}
	Debug::error("CollisionTester::isColliding(): unhandled Entity Combination");
	return false;
}

bool CollisionTester::isCollidingEvenRects(const RectBody* b1, const RectBody* b2)
{
	if ((b1->getLeft() < b2->getRight()) && (b1->getRight() > b2->getLeft()))
	{
		if ((b1->getTop() < b2->getBot()) && (b1->getBot() > b2->getTop()))
		{
			return true;
		}
	}
	return false;
}
