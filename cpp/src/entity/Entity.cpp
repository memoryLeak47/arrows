#include "Entity.hpp"

#include "../core/Main.hpp"
#include "../core/Screen.hpp"
#include "../misc/Debug.hpp"
#include "../collision/CollisionDetector.hpp"
#include "../collision/CollisionLine.hpp"

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

void Entity::calculateCollisions(const std::vector<Mob*>& mobs, GameTileMap* tileMap, const std::vector<Bullet*>& bullets)
{
	if (isCollidingMobs())
	{
		for (unsigned int i = 0; i < mobs.size(); i++)
		{
			if (this == mobs[i])
				continue;
			CollisionLine line(CollisionDetector::getCollisionLine(getBody(), mobs[i]->getBody()));
			if (line.isValid())
			{
				applyCollision(new Collision(mobs[i], line)); // added die Collision nur, wenn noch keine Collision mit der Entity vorhanden ist
			}
		}
	}

	// TODO Annäherung hinzufügen
	if (isCollidingTiles())
	{
		std::vector<Tile*> tiles(tileMap->getIntersectionTiles(getBody()->getWrapper()));

		for (unsigned int i = 0; i < tiles.size(); i++)
		{
			if (this == tiles[i])
				continue;
			CollisionLine line(CollisionDetector::getCollisionLine(getBody(), tiles[i]->getBody()));
			if (line.isValid())
			{
				applyCollision(new Collision(tiles[i], line));
			}
		}
	}

	if (isCollidingBullets())
	{
		for (unsigned int i = 0; i < bullets.size(); i++)
		{
			if (this == bullets[i])
				continue;
			CollisionLine line(CollisionDetector::getCollisionLine(getBody(), bullets[i]->getBody()));
			if (line.isValid())
			{
				applyCollision(new Collision(bullets[i], line));
			}
		}
	}
}

void Entity::applyCollision(Collision* c)
{
	for (unsigned int i = 0; i < getCollisions().size(); i++)
	{
		if (getCollisions()[i]->getEntity() == c->getEntity())
		{
			delete c;
			return;
		}
	}
	getCollisions().push_back(c);
}

void Entity::applyForces()
{
	Debug::warn("Entity::applyForces(): TODO");
	// TODO apply...
}

Body* Entity::getBody() const
{
	return body;
}

void Entity::render(const View& v) const
{
	basicRender(v);
}

void Entity::basicRender(const View& v) const
{
	Screen::drawTexture(getTexture(), getRenderRect(v), getBody()->getRotation());
}

PixelRect Entity::getRenderRect(const View& v) const
{
	GameRect r = getBody()->getRenderGameRect();
	r = GameRect(r.getPosition() - r.getSize()/2, r.getSize());
	return v.gameRectToPixelRect(r);
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

void Entity::resetCollisionSystem()
{
	deleteAndClearVector(collisions);
	deleteAndClearVector(forces);
}

std::vector<Collision*>& Entity::getCollisions()
{
	return collisions;
}

std::vector<Force*>& Entity::getForces()
{
	return forces;
}
