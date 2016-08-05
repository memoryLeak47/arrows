#include "CollisionDetector.hpp"

#include "../misc/Debug.hpp"
#include "../tile/map/GameTileMap.hpp"

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
	float a = ((posX1 - sizeX1/2.f) - (posX2 + sizeX2/2.f)) / -speedX;
	if (a >= 0.f && a <= timeLeft)
	{
		floats.push_back(a);
		bools.push_back(true);
	}
	a = ((posX2 - sizeX2/2.f) - (posX1 + sizeX1/2.f)) / speedX;
	if (a >= 0.f && a <= timeLeft)
	{
		floats.push_back(a);
		bools.push_back(true);
	}

	// y
	a = ((posY1 - sizeY1/2.f) - (posY2 + sizeY2/2.f)) / -speedY;
	if (a >= 0.f && a <= timeLeft)
	{
		floats.push_back(a);
		bools.push_back(false);
	}
	a = ((posY2 - sizeY2/2.f) - (posY1 + sizeY1/2.f)) / speedY;
	if (a >= 0.f && a <= timeLeft)
	{
		floats.push_back(a);
		bools.push_back(false);
	}

	return std::pair<std::vector<float>, std::vector<bool>>(floats, bools);
}

void CollisionDetector::addCollisionsBetweenEvenRects(Entity* e1, Entity* e2, std::vector<CollisionEvent*>* events, float timeLeft)
{
	Debug::funcOn("addCollisionsBetweenEvenRects(): " + e2->toString() + " AND " + e1->toString());
	const RectBody* b1 = dynamic_cast<const RectBody*>(e1->getBody());
	const RectBody* b2 = dynamic_cast<const RectBody*>(e2->getBody());

	const float posX1 = b1->getPosition().getX();
	const float posY1 = b1->getPosition().getY();
	const float sizeX1 = b1->getSize().getX();
	const float sizeY1 = b1->getSize().getY();

	// speed subtraction
	const float speedX = b1->getSpeed().getX() - b2->getSpeed().getX();
	const float speedY = b1->getSpeed().getY() - b2->getSpeed().getY();

	const float posX2 = b2->getPosition().getX();
	const float posY2 = b2->getPosition().getY();
	const float sizeX2 = b2->getSize().getX();
	const float sizeY2 = b2->getSize().getY();

	switch (Entity::getCollisionTypeBetween(e1, e2))
	{
		case CollisionType::SOLID:
		{
			// getestet
			CollisionStatus xCol, yCol;
			const float right1 = (posX1 + sizeX1/2.f);
			const float right2 = (posX2 + sizeX2/2.f);

			const float left1 = (posX1 - sizeX1/2.f);
			const float left2 = (posX2 - sizeX2/2.f);

			const float bot1 = (posY1 + sizeY1/2.f);
			const float bot2 = (posY2 + sizeY2/2.f);

			const float top1 = (posY1 - sizeY1/2.f);
			const float top2 = (posY2 - sizeY2/2.f);

			if ((right1 > left2) && (right2 > left1)) // Wenn die Entities sich auf der xAchse schneiden
			{
				xCol = CollisionStatus::IN;
			}
			else if ((right1 == left2) || (right2 == left1)) // Wenn die Entities sich auf der xAchse berühren
			{
				xCol = CollisionStatus::BORDER;
			}
			else // sonst OUT
			{
				xCol = CollisionStatus::OUT;
			}

			if ((bot1 > top2) && (bot2 > top1))
			{
				yCol = CollisionStatus::IN;
			}
			else if ((bot1 == top2) || (bot2 == top1))
			{
				yCol = CollisionStatus::BORDER;
			}
			else
			{
				yCol = CollisionStatus::OUT;
			}

			CollisionStatus oldStatus = std::max(xCol, yCol);

			if ((oldStatus < CollisionStatus::OUT) && not Entity::areCollisionPartners(e1, e2))
			{
				CollisionEvent* ev = new CollisionEvent(e1, e2, timeLeft, oldStatus);
				events->push_back(ev);
			}

			std::pair<std::vector<float>, std::vector<bool>> pair = getPair(posX1, posY1, sizeX1, sizeY1, speedX, speedY, posX2, posY2, sizeX2, sizeY2, timeLeft);
			std::vector<float> floats = pair.first;
			std::vector<bool> bools = pair.second;

			while (floats.size() > 0)
			{
				int index = getNextIndex(floats);
				float time = floats[index];

				if (bools[index])
				{
					if (xCol == CollisionStatus::IN)
					{
						xCol = CollisionStatus::OUT;
					}
					else if (xCol == CollisionStatus::OUT)
					{
						xCol = CollisionStatus::IN;
					}
					else
					{
						// linke entity schneller:
						if (speedX == 0) Debug::error("CollisionDetector::addCollisionsBetweenEvenRects(): logical issue here (x)");
						if ((speedX > 0) == (posX1 < posX2))
						{
							xCol = CollisionStatus::IN;
						}
						else
						{
							xCol = CollisionStatus::OUT;
						}
					}
					// xCol = (CollisionStatus)(2 - (int) xCol);
				}
				else
				{
					if (yCol == CollisionStatus::IN)
					{
						yCol = CollisionStatus::OUT;
					}
					else if (yCol == CollisionStatus::OUT)
					{
						yCol = CollisionStatus::IN;
					}
					else
					{
						// obere entity schneller:
						if (speedY == 0) Debug::error("CollisionDetector::addCollisionsBetweenEvenRects(): logical issue here (y)");
						if ((speedY > 0) == (posY1 < posY2))
						{
							yCol = CollisionStatus::IN;
						}
						else
						{
							yCol = CollisionStatus::OUT;
						}
					}
					// yCol = (CollisionStatus)(2 - (int) yCol);
				}

				floats.erase(floats.begin() + index);
				bools.erase(bools.begin() + index);

				if ((oldStatus != std::max(xCol, yCol)) && not Entity::areCollisionPartners(e1, e2))
				{
					oldStatus = std::max(xCol, yCol);
					CollisionEvent* ev = new CollisionEvent(e1, e2, timeLeft-time, oldStatus);
					events->push_back(ev);
				}
			}
			break;
		}
		case CollisionType::IGNORE:
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
	Debug::funcOff("addCollisionBetween(): " + e2->toString());
}
