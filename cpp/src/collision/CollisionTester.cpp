#include "CollisionTester.hpp"

#include <math/game/GameRect.hpp>

const float STEPSIZE = 0.01f; // Schrittweite bei der CollisionPoint suche

bool CollisionTester::areColliding(Entity* e1, Entity* e2, GameVector* p)
{
	// TODO
	GameRect intersectionRect = GameRect::getIntersectionRect(e1->getBody()->getWrapper(0), e2->getBody()->getWrapper(0));

	GameVector point(intersectionRect.getLeft(), intersectionRect.getTop());
	// IntersectionRect wird schrittweise durchlaufen und nach CollisionPoints durchsucht.
	while (point.y <= intersectionRect.getBot())
	{
		while (point.x <= intersectionRect.getRight())
		{
			if (e1->getBody()->isCollidingPoint(point) && e2->getBody()->isCollidingPoint(point))
			{
				if (p != NULL)
				{
					(*p).x = point.x;
					(*p).y = point.y;
				}
				return true;
			}
			point.x += STEPSIZE;
		}
		point.y += STEPSIZE;
	}

	if (p != NULL)
	{
		(*p).x = -1.f; // Error Value
		(*p).y = -1.f; // Error Value
	}

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
