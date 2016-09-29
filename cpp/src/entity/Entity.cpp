#include "Entity.hpp"

#include <core/Main.hpp>
#include <core/Screen.hpp>
#include <misc/Debug.hpp>
#include <collision/CollisionDetector.hpp>
#include <collision/CollisionTester.hpp>
#include <collision/PhysicsHandler.hpp>

Entity::Entity(Body* bodyArg)
	: changed(true)
{
	body = bodyArg;
}

Entity::~Entity()
{
	delete body;
}

void Entity::tick()
{
	optGravity();
	optDrag();
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

void Entity::move(float time)
{
	if (!isStatic())
	{
		body->move(time);
	}
}

GameVector Entity::getSpeed() const
{
	return body->getSpeed();
}

void Entity::setSpeed(const GameVector& speed)
{
	if (speed != body->getSpeed())
	{
		body->setSpeed(speed);
		setChanged(true);
	}
}

void Entity::setPosition(const GameVector& position)
{
	if (position != body->getPosition())
	{
		body->setPosition(position);
		setChanged(true);
	}
	// TODO reload collision partners
}

void Entity::setRotation(float rotation)
{
	body->setRotation(rotation);
	setChanged(true);
}

void Entity::setSpin(float spin)
{
	body->setSpin(spin);
	setChanged(true);
}

void Entity::push(const GameVector& how, const GameVector& where)
{
	addSpeedAt(how/getMass(), where);
}

void Entity::push(const GameVector& how)
{
	push(how, body->getPosition());
}

void Entity::addPosition(const GameVector& how)
{
	setPosition(body->getPosition() + how);
}

void Entity::setSpeedAt(const GameVector& how, const GameVector& where)
{
	body->setSpeedAt(how, where);
	setChanged(true);
}

void Entity::addSpeedAt(const GameVector& how, const GameVector& where)
{
	setSpeedAt(body->getSpeedAt(where) + how, where);
	setChanged(true);
}

void Entity::addSpeed(const GameVector& how)
{
	setSpeed(how + body->getSpeed());
}

CollisionType Entity::getCollisionType() const
{
	return CollisionType::SOLID;
}

void Entity::optGravity()
{
	addSpeed(GameVector(0.f, 0.02f));
}

void Entity::optDrag()
{
	push(body->getSpeed() * -0.01f);
}

std::pair<float, GameVector> Entity::getBackingAndMomentum(GameVector escapeVector, const std::vector<GameVector> &points)
{
	float backing = getMass();
	GameVector momentum = getSpeed() * backing;
	for (auto partner : getCollisionPartners())
	{
		if (GameVector::getScalarProduct(escapeVector, getSpeed() - partner->getSpeed()) > 0)
		{
			std::vector<GameVector> collisionPoints = PhysicsHandler::getCollisionPoints(this, partner);
			GameVector escVec = PhysicsHandler::getEscapeVector(this, collisionPoints);

			if (GameVector::getScalarProduct(escapeVector, escVec) > 0)
			{
				std::pair<float, GameVector> pair = partner->getBackingAndMomentum(escapeVector, collisionPoints);

				backing += pair.first;
				momentum += pair.second;
			}
		}
	}
	return std::pair<float, GameVector>(backing, momentum);
}

void Entity::addCollisionPartner(Entity* e)
{
	if (e == this)
	{
		Debug::error("Entity::addCollisionPartner(): entity wanted to add itself: " + e->toString());
	}

	if (! memberOf(e, collisionPartners))
	{
		collisionPartners.push_back(e);
	}
	else
	{
		Debug::warn("Entity::addCollisionPartner(): entity is already in collisionPartners");
	}
}

void Entity::removeCollisionPartner(Entity* e)
{
	if (e == this)
	{
		Debug::error("Entity::removeCollisionPartner(): entity wanted to remove itself: " + e->toString());
	}

	bool found = false;
	for (auto it = collisionPartners.begin(); it != collisionPartners.end(); ++it)
	{
		if (*it == e)
		{
			found = true;
			collisionPartners.erase(it);
			break;
		}
	}

	if (not found)
	{
		Debug::error("Entity::removeCollisionPartner(): e=" + e->toString() + " was not found in " + toString() + ".collisionPartners");
	}
}

std::vector<Entity*> Entity::getCollisionPartners()
{
	return collisionPartners;
}

bool Entity::hasCollisionPartner(Entity* e) const
{
	for (unsigned int i = 0; i < collisionPartners.size(); i++)
	{
		if (e == collisionPartners[i])
		{
			return true;
		}
	}
	return false;
}

bool Entity::areCollisionPartners(Entity* e1, Entity* e2)
{
	return e1->hasCollisionPartner(e2) or e2->hasCollisionPartner(e1);
}

CollisionType Entity::getCollisionTypeBetween(Entity* e1, Entity* e2)
{
	return std::max(e1->getCollisionType(), e2->getCollisionType());
}

const Body* Entity::getBody() const
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
	body->setSpeed((targetPosition - getBody()->getPosition())/duration);
	dashCounter = duration;
}

bool Entity::couldDashTo(const GameVector&) const
{
	Debug::warn("Entity::couldDashTo(): TODO");
	return true;
}

void Entity::flash(const GameVector& target)
{
	body->setPosition(target);
	setChanged(true);
	// clear collisionpartners
	// recalculate collisionpartners
}

bool Entity::couldFlashTo(const GameVector&) const
{
	Debug::warn("Entity::couldFlashTo(): TODO");
	return true;
}

void Entity::stop()
{
	setSpeed(GameVector(0.f, 0.f));
}
