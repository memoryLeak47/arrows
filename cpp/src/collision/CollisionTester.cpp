#include "CollisionTester.hpp"

bool CollisionTester::areColliding(Entity* e1, Entity* e2, float borderAddition)
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
					return areCollidingEvenRects(dynamic_cast<const RectBody*>(e1->getBody()), dynamic_cast<const RectBody*>(e2->getBody()), borderAddition);
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

bool CollisionTester::areCollidingEvenRects(const RectBody* b1, const RectBody* b2, float borderAddition)
{
	if ((b1->getLeft() <= b2->getRight() + borderAddition) && (b1->getRight() + borderAddition >= b2->getLeft()))
	{
		if ((b1->getTop() <= b2->getBot() + borderAddition) && (b1->getBot() + borderAddition >= b2->getTop()))
		{
			return true;
		}
	}
	return false;
}
