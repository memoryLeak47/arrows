#include "Entity.hpp"

#include "../core/Main.hpp"
#include "../core/Screen.hpp"
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

void Entity::addCollisionPartner(Entity* e)
{
	collisionPartners.push_back(e);
}

void Entity::removeCollisionPartner(Entity* e)
{
	// TODO
	// collisionPartners.erase(e);
}

std::vector<Entity*> Entity::getCollisionPartners()
{
	return collisionPartners;
}

Body* Entity::getBody() const
{
	return body;
}

bool Entity::hasChanged() const
{
	return changed;
}

void Entity::setChanged(bool b)
{
	changed = b;
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
