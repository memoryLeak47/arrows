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

void CollisionDetector::addCollisionsBetweenEvenRects(Entity* e1, Entity* e2, std::vector<CollisionEvent*>* events, float timeLeft)
{
	float posX1 = dynamic_cast<RectBody*>(e1->getBody())->getPosition().getX();
	float posY1 = dynamic_cast<RectBody*>(e1->getBody())->getPosition().getY();
	float sizeX1 = dynamic_cast<RectBody*>(e1->getBody())->getSize().getX();
	float sizeY1 = dynamic_cast<RectBody*>(e1->getBody())->getSize().getY();

	// speed subtraction
	float speedX1 = dynamic_cast<RectBody*>(e1->getBody())->getSpeed().getX() - dynamic_cast<RectBody*>(e2->getBody())->getSpeed().getX();
	float speedY1 = dynamic_cast<RectBody*>(e1->getBody())->getSpeed().getY() - dynamic_cast<RectBody*>(e2->getBody())->getSpeed().getY();

	float posX2 = dynamic_cast<RectBody*>(e2->getBody())->getPosition().getX();
	float posY2 = dynamic_cast<RectBody*>(e2->getBody())->getPosition().getY();
	float sizeX2 = dynamic_cast<RectBody*>(e2->getBody())->getSize().getX();
	float sizeY2 = dynamic_cast<RectBody*>(e2->getBody())->getSize().getY();

	float a = ((posX2 + sizeX2/2.f) - (posX1 - sizeX1/2.f))/speedX1;
	float b = ((posY2 + sizeY2/2.f) - (posY1 - sizeY1/2.f))/speedY1;

	float minCT = std::max(a, b);
	float maxCT = std::min(a, b);

	bool alreadyPartners = Entity::areCollisionPartners(e1, e2);

	if (minCT < timeLeft) // Diese Abfrage ( minCT < maxCT ) ist falsch, aber iwas fehlt da noch ...
	{
		if (!alreadyPartners)
		{
			events->push_back(new CollisionEvent(e1, e2, timeLeft-minCT, true));
		}
		events->push_back(new CollisionEvent(e1, e2, timeLeft-maxCT, false));
	}
}
