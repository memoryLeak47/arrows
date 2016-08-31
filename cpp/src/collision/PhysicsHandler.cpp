#include "PhysicsHandler.hpp"

#include <map>

// MultiCollisions sind noch nicht mit eingerechnet

// hidden Function
std::vector<Entity*> getCollisionGroup(Entity* e)
{
	std::vector<Entity*> group;
	group.push_back(e);
	unsigned int i = 0;
	while (i < group.size())
	{
		for (Entity* c : group[i]->getCollisionPartners())
		{
			if (!memberOf(c, group))
			{
				group.push_back(c);
			}
		}
		i++;
	}
	return group;
}

std::vector<GameVector> PhysicsHandler::getCollisionPoints(Entity* e1, Entity* e2)
{
	std::vector<GameVector> result;
	if (e1->getBody()->getBodyType() == BodyType::RECT && e2->getBody()->getBodyType() == BodyType::RECT)
	{
		const RectBody *b1 = dynamic_cast<const RectBody*>(e1->getBody());
		const RectBody *b2 = dynamic_cast<const RectBody*>(e2->getBody());
		if (b1->isEven() && b2->isEven())
		{
			float x1 = std::max(b1->getLeft(), b2->getLeft());
			float x2 = std::min(b1->getRight(), b2->getRight());

			float y1 = std::max(b1->getTop(), b2->getTop());
			float y2 = std::min(b1->getBot(), b2->getBot());

			GameVector lefttop(std::min(x1, x2), std::min(y1, y2));
			GameVector rightbot(std::max(x1, x2), std::max(y1, y2));

			result.push_back(lefttop);
			if (lefttop != rightbot)
			{
				result.push_back(rightbot);
			}
		}
	}
	return result;
}

// Ein EscapeVector gibt an, in welche Richtung man sich von einer Entity(e) entfernen kann.
// Ein EscapeVector zeigt von der Entity(e) weg.
GameVector PhysicsHandler::getEscapeVector(Entity* e, const std::vector<GameVector>& collisionPoints)
{
	if (collisionPoints.size() == 2)
	{
		GameVector ab = collisionPoints[1] - collisionPoints[0]; // Vector vom einen zum anderen CollisionPoint
		GameVector am = e->getBody()->getPosition() - collisionPoints[0]; // Vector von a nach Mittelpunkt der Entity
		GameVector result = am.getProjectionOn(ab.getOrthogonal());
		if (result.getMagnitude() == 0) Debug::error("PhysicsHandler::getEscapeVector(): result is zero-vector");
		return result * -1.f;
	}
	else if (collisionPoints.size() == 1) // Der CollisionPunkt muss sich an einer der Ecken der Entity befinden
	{
		if (e->getBody()->getPosition().x < collisionPoints[0].x)
		{
			return GameVector(1.f, 0.f);
		}
		else if (e->getBody()->getPosition().x > collisionPoints[0].x)
		{
			return GameVector(-1.f, 0.f);
		}
		else
		{
			Debug::error("PhysicsHandler::getEscapeVector(): CollisionPoints.size() == 1:\te->getBody()->x == collisionPoints[0]->x");
		}
	}
	Debug::error("PhysicsHandler::getEscapeVector(): collisionPoints.size() = " + Converter::intToString(collisionPoints.size()));
	return GameVector(0.f, 0.f);
}

void PhysicsHandler::handlePhysics(Entity* e1, Entity* e2)
{
	Debug::funcOn("PhysicsHandler::handlePhysics(" + e1->toString() + ", " + e2->toString() + ")");

	std::vector<Entity*> group = getCollisionGroup(e1); // Erstellt eine Liste mit allen CollisionPartnern
	std::map<Entity*, GameVector> cache;

	for (Entity* e : group)
	{
		if (e->isStatic())
			continue;
		GameVector backVec{0.f,0.f};
		GameVector momentum{0.f,0.f};

		for (Entity* c : e->getCollisionPartners())
		{
			std::vector<GameVector> collisionPoints = getCollisionPoints(e, c);
			GameVector escapeVec = getEscapeVector(e, collisionPoints);
			if (GameVector::getScalarProduct(escapeVec, e->getSpeed() - c->getSpeed()) > 0.f)
			{
				std::pair<float, GameVector> pair = c->getBackingAndMomentum(escapeVec, collisionPoints);
				GameVector tmp = escapeVec * std::get<0>(pair);
				if (escapeVec.x == 0) tmp.x = 0;
				if (escapeVec.y == 0) tmp.y = 0;
				backVec += tmp;
				momentum += std::get<1>(pair);
			}
		}
		cache.insert(std::pair<Entity*, GameVector>(e, GameVector(
			(e->getSpeed().x * e->getMass() + momentum.x) / (backVec.x + e->getMass()),
			(e->getSpeed().y * e->getMass() + momentum.y) / (backVec.y + e->getMass())
		)));
	}

	for (auto it = cache.begin(); it != cache.end(); ++it)
	{
		it->first->setSpeed(it->second);
	}

	Debug::funcOff("PhysicsHandler::handlePhysics(" + e1->toString() + ", " + e2->toString() + ")");
}
