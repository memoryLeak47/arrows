#include "CollisionTester.hpp"

#include <math/game/GameRect.hpp>

const float STEPSIZE = 0.05f; // Schrittweite bei der CollisionPoint suche

bool CollisionTester::areColliding(Entity* e1, Entity* e2, GameVector* p)
{
	GameRect intersectionRect = GameRect::getIntersectionRect(e1->getBody()->getWrapper(0), e2->getBody()->getWrapper(0));

	 // nicht wundern. Stimmt so ;)
	float left = intersectionRect.getRight(); // mit Wert initialisieren, der definitiv weiter rechts liegt, als der gesuchte wert
	float right = intersectionRect.getLeft(); // mit Wert initialisieren, der definitiv weiter links liegt, als der gesuchte wert
	float top = intersectionRect.getBot(); // mit Wert initialisieren, der definitiv weiter unten liegt, als der gesuchte wert
	float bot = intersectionRect.getTop(); // mit Wert initialisieren, der definitiv weiter oben liegt, als der gesuchte wert

	bool found = false;

	GameVector point(intersectionRect.getLeft(), intersectionRect.getTop());

	// IntersectionRect wird schrittweise durchlaufen und nach CollisionPoints durchsucht.
	while (point.y <= intersectionRect.getBot())
	{
		while (point.x <= intersectionRect.getRight())
		{
			if (e1->getBody()->isCollidingPoint(point) && e2->getBody()->isCollidingPoint(point))
			{
				// left usw. updaten
				if (point.x < left)
					left = point.x;
				if (point.x > right)
					right = point.x;
				if (point.y < bot)
					bot = point.y;
				if (point.y > top)
					left = point.y;

				found = true;
			}
			point.x += STEPSIZE;
		}
		point.x = intersectionRect.getLeft();
		point.y += STEPSIZE;
	}

	if (found) // Wenn ein Punkt gefunden, an dem die Entities kollidieren
	{
		if (p != NULL) // Wenn Punkt zurück gegeben werden soll
		{
			(*p).x = ((left+right)/2.f);
			(*p).y = ((top+bot)/2.f);
		}
		return true;
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
