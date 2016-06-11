#include "CollisionDetector.hpp"

#include "../misc/Debug.hpp"

void CollisionDetector::addCollisionsBetween(Entity* e1, Entity* e2, std::vector<CollisionEvent*>* events, float timeLeft)
{
	if (e1->getBody()->getBodyType() == BodyType::RECT && e2->getBody()->getBodyType() == BodyType::RECT)
	{
		if (dynamic_cast<RectBody*>(e1->getBody())->isEven() && dynamic_cast<RectBody*>(e2->getBody())->isEven())
		{
			addCollisionsBetweenEvenRects(e1, e2, events, timeLeft);
		}
		else
		{
			Debug::warn("CollisionDetector::addCollisionsBetween: TODO");
		}
	}
	else
	{
		Debug::warn("CollisionDetector::addCollisionsBetween: TODO");
	}
}


// private function
int getNextIndex(const std::vector<float>& floats)
{
	int spot = 0;
	for (unsigned int i = 1; i < floats.size(); i++)
	{
		if (floats[i] < floats[spot])
		{
			spot = i;
		}
	}
	return spot;
}

void CollisionDetector::addCollisionsBetweenEvenRects(Entity* e1, Entity* e2, std::vector<CollisionEvent*>* events, float timeLeft)
{
	float posX1 = dynamic_cast<RectBody*>(e1->getBody())->getPosition().getX();
	float posY1 = dynamic_cast<RectBody*>(e1->getBody())->getPosition().getY();
	float sizeX1 = dynamic_cast<RectBody*>(e1->getBody())->getSize().getX();
	float sizeY1 = dynamic_cast<RectBody*>(e1->getBody())->getSize().getY();

	// speed subtraction
	float speedX = dynamic_cast<RectBody*>(e1->getBody())->getSpeed().getX() - dynamic_cast<RectBody*>(e2->getBody())->getSpeed().getX();
	float speedY = dynamic_cast<RectBody*>(e1->getBody())->getSpeed().getY() - dynamic_cast<RectBody*>(e2->getBody())->getSpeed().getY();

	float posX2 = dynamic_cast<RectBody*>(e2->getBody())->getPosition().getX();
	float posY2 = dynamic_cast<RectBody*>(e2->getBody())->getPosition().getY();
	float sizeX2 = dynamic_cast<RectBody*>(e2->getBody())->getSize().getX();
	float sizeY2 = dynamic_cast<RectBody*>(e2->getBody())->getSize().getY();

	std::vector<float> floats;
	std::vector<bool> bools;

	// x
	float a = ((posX1 + sizeX1/2.f) - (posX2 - sizeX2/2.f))/speedX;
	if (a >= 0 && a <= timeLeft)
	{
		floats.push_back(a);
		bools.push_back(true);
	}
	a = (-(posX1 + sizeX1/2.f) + (posX2 - sizeX2/2.f))/speedX;
	if (a >= 0 && a <= timeLeft)
	{
		floats.push_back(a);
		bools.push_back(true);
	}
	a = ((posX2 + sizeX2/2.f) - (posX1 - sizeX1/2.f))/speedX;
	if (a >= 0 && a <= timeLeft)
	{
		floats.push_back(a);
		bools.push_back(true);
	}
	a = (-(posX2 + sizeX2/2.f) + (posX1 - sizeX1/2.f))/speedX;
	if (a >= 0 && a <= timeLeft)
	{
		floats.push_back(a);
		bools.push_back(true);
	}

	// y
	a = ((posY1 + sizeY1/2.f) - (posY2 - sizeY2/2.f))/speedY;
	if (a >= 0 && a <= timeLeft)
	{
		floats.push_back(a);
		bools.push_back(false);
	}
	a = (-(posY1 + sizeY1/2.f) + (posY2 - sizeY2/2.f))/speedY;
	if (a >= 0 && a <= timeLeft)
	{
		floats.push_back(a);
		bools.push_back(false);
	}
	a = ((posY2 + sizeY2/2.f) - (posY1 - sizeY1/2.f))/speedY;
	if (a >= 0 && a <= timeLeft)
	{
		floats.push_back(a);
		bools.push_back(false);
	}
	a = (-(posY2 + sizeY2/2.f) + (posY1 - sizeY1/2.f))/speedY;
	if (a >= 0 && a <= timeLeft)
	{
		floats.push_back(a);
		bools.push_back(false);
	}

	bool xCol = ((posX1 + sizeX1/2.f) > (posX2 - sizeX2/2.f)) && ((posX2 + sizeX2/2.f) > (posX1 - sizeX1/2.f));
	bool yCol = ((posY1 + sizeY1/2.f) > (posY2 - sizeY2/2.f)) && ((posY2 + sizeY2/2.f) > (posY1 - sizeY1/2.f));

	if (xCol && yCol)
	{
		if (floats.size() > 0)
		{
			events->push_back(new CollisionEvent(e1, e2, floats[getNextIndex(floats)], false));
		}
	}
	else
	{
		float time = 0;
		while (floats.size() > 0)
		{
			int index = getNextIndex(floats);
			time = floats[index];
			if (bools[index])
			{
				xCol = !xCol;
			}
			else
			{
				yCol = !yCol;
			}

			floats.erase(floats.begin() + index);
			bools.erase(bools.begin() + index);
			if (xCol && yCol)
			{
				events->push_back(new CollisionEvent(e1, e2, timeLeft-time, true));
				if (floats.size() > 0)
				{
					events->push_back(new CollisionEvent(e1, e2, timeLeft-floats[getNextIndex(floats)], false));
				}
				return;
			}
		}
	}
}
