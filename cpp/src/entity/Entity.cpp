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

void Entity::calculateCollisions(const std::vector<Mob*>& mobs, const std::vector<Tile*>& tiles, const std::vector<Bullet*>& bullets)
{
	for (unsigned int i = 0; i < mobs.size(); i++)
	{
		if (this == mobs[i])
			continue;
		if (this->wantsToCollide(mobs[i]) || mobs[i]->wantsToCollide(this))
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
		if (this->wantsToCollide(tiles[i]) || tiles[i]->wantsToCollide(this))
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
		if (this->wantsToCollide(bullets[i]) || bullets[i]->wantsToCollide(this))
		{
			GameVector spot(CollisionDetector::getCollisionPoint(getBody(), bullets[i]->getBody()));
			if (spot != GameVector(-1, -1))
			{
				collisions.push_back(new Collision(bullets[i], spot));
			}
		}
	}
}

void Entity::calculateForces()
{
	// TODO
	Debug::warn("Entity::calculateForces(): TODO");
	deleteAndClearVector(collisions);
}

Body* Entity::getBody() const
{
	return body;
}
