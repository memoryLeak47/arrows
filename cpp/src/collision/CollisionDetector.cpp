#include "CollisionDetector.hpp"

#include "../misc/Debug.hpp"

void CollisionDetector::addCollisionsBetween(Entity* e1, Entity* e2, std::vector<CollisionEvent*>* events, float timeLeft)
{
	if (e1->getBody()->getBodyType() == BodyType::RECT && e2->getBody()->getBodyType() == BodyType::RECT)
	{
		if (dynamic_cast<const RectBody*>(e1->getBody())->isEven() && dynamic_cast<const RectBody*>(e2->getBody())->isEven())
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

// private function
std::vector<GameVector> getCollisionPoints(Entity* e1, Entity* e2, bool lastColWasX, float time)
{
	std::vector<GameVector> collisionPoints;
	if (lastColWasX)
	{
		collisionPoints.push_back(GameVector(	std::max(e1->getBody()->getLeft() + e1->getBody()->getSpeed().getX() * time, 
								e2->getBody()->getLeft() + e2->getBody()->getSpeed().getX() * time),
							std::max(e1->getBody()->getTop() + e1->getBody()->getSpeed().getY() * time,
								e2->getBody()->getTop() + e2->getBody()->getSpeed().getY() * time)));

		collisionPoints.push_back(GameVector(	std::max(e1->getBody()->getLeft() + e1->getBody()->getSpeed().getX() * time, 
								e2->getBody()->getLeft() + e2->getBody()->getSpeed().getX() * time),
							std::min(e1->getBody()->getBot() + e1->getBody()->getSpeed().getY() * time,
								e2->getBody()->getBot() + e2->getBody()->getSpeed().getY() * time)));
	}
	else
	{
		collisionPoints.push_back(GameVector(	std::max(e1->getBody()->getLeft() + e1->getBody()->getSpeed().getX() * time,
								 e2->getBody()->getLeft() + e2->getBody()->getSpeed().getX() * time),
							std::min(e1->getBody()->getTop() + e1->getBody()->getSpeed().getY() * time,
								 e2->getBody()->getTop() + e2->getBody()->getSpeed().getY() * time)));

		collisionPoints.push_back(GameVector(	std::min(e1->getBody()->getRight() + e1->getBody()->getSpeed().getX() * time,
								 e2->getBody()->getRight() + e2->getBody()->getSpeed().getX() * time),
							std::min(e1->getBody()->getTop() + e1->getBody()->getSpeed().getY() * time,
								 e2->getBody()->getTop() + e2->getBody()->getSpeed().getY() * time)));
	}
	return collisionPoints;
}

void CollisionDetector::addCollisionsBetweenEvenRects(Entity* e1, Entity* e2, std::vector<CollisionEvent*>* events, float timeLeft)
{
	float posX1 = dynamic_cast<const RectBody*>(e1->getBody())->getPosition().getX();
	float posY1 = dynamic_cast<const RectBody*>(e1->getBody())->getPosition().getY();
	float sizeX1 = dynamic_cast<const RectBody*>(e1->getBody())->getSize().getX();
	float sizeY1 = dynamic_cast<const RectBody*>(e1->getBody())->getSize().getY();

	// speed subtraction
	float speedX = dynamic_cast<const RectBody*>(e1->getBody())->getSpeed().getX() - dynamic_cast<const RectBody*>(e2->getBody())->getSpeed().getX();
	float speedY = dynamic_cast<const RectBody*>(e1->getBody())->getSpeed().getY() - dynamic_cast<const RectBody*>(e2->getBody())->getSpeed().getY();

	float posX2 = dynamic_cast<const RectBody*>(e2->getBody())->getPosition().getX();
	float posY2 = dynamic_cast<const RectBody*>(e2->getBody())->getPosition().getY();
	float sizeX2 = dynamic_cast<const RectBody*>(e2->getBody())->getSize().getX();
	float sizeY2 = dynamic_cast<const RectBody*>(e2->getBody())->getSize().getY();

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

	bool xCol = ((posX1 + sizeX1/2.f) >= (posX2 - sizeX2/2.f)) && ((posX2 + sizeX2/2.f) >= (posX1 - sizeX1/2.f));
	bool yCol = ((posY1 + sizeY1/2.f) >= (posY2 - sizeY2/2.f)) && ((posY2 + sizeY2/2.f) >= (posY1 - sizeY1/2.f));

	if (xCol && yCol)
	{
		if (floats.size() > 0)
		{
			CollisionEvent* ev1 = new CollisionEvent(e1, e2, timeLeft-floats[getNextIndex(floats)], COLLISIONEVENTTYPE_EXIT, std::vector<GameVector>());
			Debug::test("ev1: " + ev1->toString());
			events->push_back(ev1);
		}
	}
	else
	{
		bool lastColWasX;
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
			lastColWasX = bools[index];

			floats.erase(floats.begin() + index);
			bools.erase(bools.begin() + index);
			if (xCol && yCol)
			{
				std::vector<GameVector> collisionPoints = getCollisionPoints(e1, e2, lastColWasX, time);

				CollisionEvent* ev2 = new CollisionEvent(e1, e2, timeLeft-time, COLLISIONEVENTTYPE_ENTER, collisionPoints);
				Debug::test("ev2: " + ev2->toString());
				events->push_back(ev2);

				CollisionEvent* ev3 = new CollisionEvent(e1, e2, timeLeft-time, COLLISIONEVENTTYPE_STAY, collisionPoints);
				Debug::test("ev3: " + ev3->toString());
				events->push_back(ev3);
				if (floats.size() > 0)
				{
					CollisionEvent* ev4 = new CollisionEvent(e1, e2, timeLeft-floats[getNextIndex(floats)], COLLISIONEVENTTYPE_EXIT, std::vector<GameVector>());
					Debug::test("ev4: " + ev4->toString());
					events->push_back(ev4);
				}
				return;
			}
		}
	}
}
