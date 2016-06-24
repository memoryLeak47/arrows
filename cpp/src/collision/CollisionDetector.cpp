#include "CollisionDetector.hpp"

#include <limits>
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
std::pair<std::vector<float>, std::vector<bool>> getPair(float posX1, float posY1, float sizeX1, float sizeY1, float speedX, float speedY, float posX2, float posY2, float sizeX2, float sizeY2, float timeLeft)
{
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

	return std::pair<std::vector<float>, std::vector<bool>>(floats, bools);
}

// private function
std::vector<GameVector> getCollisionPoints(Entity* e1, Entity* e2, float time) // TODO correct?
{
	std::vector<GameVector> collisionPoints;
	if (e1->getBody()->getLeft() + e1->getBody()->getSpeed().getX() * time == e2->getBody()->getRight() || e1->getBody()->getRight() + e1->getBody()->getSpeed().getX() == e2->getBody()->getLeft())
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

	switch (Entity::getCollisionTypeBetween(e1, e2))
	{
		case COLLISIONTYPE_SOLID:
		{
			bool xCol = ((posX1 + sizeX1/2.f) >= (posX2 - sizeX2/2.f)) && ((posX2 + sizeX2/2.f) >= (posX1 - sizeX1/2.f));
			bool yCol = ((posY1 + sizeY1/2.f) >= (posY2 - sizeY2/2.f)) && ((posY2 + sizeY2/2.f) >= (posY1 - sizeY1/2.f));

			if (xCol && yCol)
			{
				std::pair<std::vector<float>, std::vector<bool>> pair = getPair(posX1, posY1, sizeX1, sizeY1, speedX, speedY, posX2, posY2, sizeX2, sizeY2, std::numeric_limits<int>::infinity());
				std::vector<float> floats = pair.first;
				std::vector<bool> bools = pair.second;

				if (floats.size() > 1)
				{
					CollisionEvent* ev = new CollisionEvent(e1, e2, timeLeft, true, getCollisionPoints(e1, e2, 0));
					Debug::test("ev1: " + ev->toString());
					events->push_back(ev);
				}
				else
				{
					CollisionEvent* ev = new CollisionEvent(e1, e2, timeLeft, false, getCollisionPoints(e1, e2, 0));
					Debug::test("ev2: " + ev->toString());
					events->push_back(ev);
				}
			}
			else
			{
				std::pair<std::vector<float>, std::vector<bool>> pair = getPair(posX1, posY1, sizeX1, sizeY1, speedX, speedY, posX2, posY2, sizeX2, sizeY2, timeLeft);
				std::vector<float> floats = pair.first;
				std::vector<bool> bools = pair.second;
				while (floats.size() > 0)
				{
					int index = getNextIndex(floats);
					float time = floats[index];

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
						CollisionEvent* ev = new CollisionEvent(e1, e2, timeLeft-time, true, getCollisionPoints(e1, e2, time));
						Debug::test("ev3: " + ev->toString());
						events->push_back(ev);
						return;
					}
				}
			}
			break;
		}
		case COLLISIONTYPE_IGNORE:
		{
			Debug::warn("TODO ignore collision");
			break;
		}
		default:
		{
			Debug::error("CollisionDetector::addCollisionsBetweenEvenRects: unknown CollisionType");
			break;
		}
	}
}
