#include "Entity.hpp"

#include "../core/Main.hpp"
#include "../misc/Debug.hpp"
#include "../collision/CollisionDetector.hpp"

Entity::Entity(Body* bodyArg)
{
	body = bodyArg;
}

Entity::~Entity()
{
	delete body;
}

void Entity::tick()
{
	if (dashCounter > 1)
	{
		dashCounter--;
	}
	else if (dashCounter == 1)
	{
		// if (!collides with tile)
		//       dashCounter = 0;
		Debug::warn("Entity::tick(): dashCounter == 1: TODO");
	}
}

void Entity::calculateCollisions(const std::vector<Mob*>& mobs, const std::vector<Tile*>& tiles, const std::vector<Bullet*>& bullets)
{
	for (unsigned int i = 0; i < mobs.size(); i++)
	{
		if (this == mobs[i])
			continue;
		if (wouldCollide(mobs[i]))
		{
			GameVector spot(CollisionDetector::getCollisionPoint(getBody(), mobs[i]->getBody()));
			if (spot != GameVector(-1, -1))
			{
				collisions.push_back(new Collision(mobs[i], spot));
			}
		}
	}

	// TODO Annäherung hinzufügen
	for (unsigned int i = 0; i < tiles.size(); i++)
	{
		if (this == tiles[i])
			continue;
		if (wouldCollide(tiles[i]))
		{
			GameVector spot(CollisionDetector::getCollisionPoint(getBody(), tiles[i]->getBody()));
			if (spot != GameVector(-1, -1))
			{
				collisions.push_back(new Collision(tiles[i], spot));
			}
		}
	}

	for (unsigned int i = 0; i < bullets.size(); i++)
	{
		if (this == bullets[i])
			continue;
		if (wouldCollide(bullets[i]))
		{
			GameVector spot(CollisionDetector::getCollisionPoint(getBody(), bullets[i]->getBody()));
			if (spot != GameVector(-1, -1))
			{
				collisions.push_back(new Collision(bullets[i], spot));
			}
		}
	}
}

void Entity::applyForces()
{
	Debug::warn("Entity::applyForces(): TODO");
	// TODO apply...
}

bool Entity::wouldCollide(Entity* entity) const
{
	return this->wantsToCollide(entity) || entity->wantsToCollide(this);
}

Body* Entity::getBody() const
{
	return body;
}

void Entity::dash(const GameVector& targetPosition, float duration)
{
	getBody()->setSpeed((targetPosition - getBody()->getPosition())/duration);
	dashCounter = duration;
}

bool Entity::couldDashTo(const GameVector&) const
{
	Debug::warn("Entity::couldDashTo(): TODO");
	return true;
}

void Entity::flash(const GameVector& target)
{
	getBody()->setPosition(target);
}

bool Entity::couldFlashTo(const GameVector&) const
{
	Debug::warn("Entity::couldFlashTo(): TODO");
	return true;
}

bool Entity::isIgnoringForces() const
{
	return dashCounter > 0;
}

void Entity::resetForces()
{
	deleteAndClearVector(forces);
}
