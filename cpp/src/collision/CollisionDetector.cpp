#include "CollisionDetector.hpp"

#include <misc/Global.hpp>
#include <tilemap/GameTileMap.hpp>
#include "CollisionEvent.hpp"
#include <entity/Entity.hpp>
#include <collision/Body.hpp>
#include <math/game/GameRect.hpp>

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

void addEvent(std::vector<CollisionEvent*>* events, CollisionEvent* event)
{
	for (unsigned int i = 0; i < events->size(); i++)
	{
		if (events->at(i)->getTimeUntilFrameEnds() <= event->getTimeUntilFrameEnds())
		{
			events->insert(events->begin()+i, event);
			return;
		}
	}
	events->push_back(event);
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

void CollisionDetector::addCollisionsBetween(Entity* e1, Entity* e2, std::vector<CollisionEvent*>* events, float timeLeft)
{
	if (Entity::areWrapperPartners(e1, e2))
	{
		Debug::warn(std::string(__PRETTY_FUNCTION__) + ": between collision partners");
	}

	const Body* b1 = e1->getBody();
	const Body* b2 = e2->getBody();

	const GameRect wrapper1 = b1->getWrapper(0.f); // TODO make getWrapper more beautiful
	const GameRect wrapper2 = b2->getWrapper(0.f);

	const float posX1 = b1->getPosition().x;
	const float posY1 = b1->getPosition().y;
	const float sizeX1 = wrapper1.getSize().x;
	const float sizeY1 = wrapper1.getSize().y;

	const float posX2 = b2->getPosition().x;
	const float posY2 = b2->getPosition().y;
	const float sizeX2 = wrapper2.getSize().x;
	const float sizeY2 = wrapper2.getSize().y;

	// speed subtraction
	const float speedX = b1->getSpeed().x - b2->getSpeed().x;
	const float speedY = b1->getSpeed().y - b2->getSpeed().y;

	// getestet
	CollisionStatus xCol, yCol;
	const float right1 = wrapper1.getRight();
	const float right2 = wrapper2.getRight();

	const float left1 = wrapper1.getLeft();
	const float left2 = wrapper2.getLeft();

	const float bot1 = wrapper1.getBot();
	const float bot2 = wrapper2.getBot();

	const float top1 = wrapper1.getTop();
	const float top2 = wrapper2.getTop();

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

	if (oldStatus < CollisionStatus::OUT)
	{
		CollisionEvent* ev = new CollisionEvent(e1, e2, timeLeft);
		addEvent(events, ev);
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
		}

		floats.erase(floats.begin() + index);
		bools.erase(bools.begin() + index);

		if (oldStatus != std::max(xCol, yCol))
		{
			oldStatus = std::max(xCol, yCol);
			CollisionEvent* ev = new CollisionEvent(e1, e2, timeLeft-time);
			addEvent(events, ev);
		}
	}
}
