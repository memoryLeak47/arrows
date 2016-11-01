#include "Entity.hpp"

#include <misc/Global.hpp>
#include <core/Screen.hpp>

#include "EntityGivethrough.hpp"
#include <collision/CollisionTester.hpp>
#include <collision/PhysicsHandler.hpp>
#include <collision/Shape.hpp>
#include <math/pixel/PixelRect.hpp>
#include <math/game/GameRect.hpp>
#include <view/View.hpp>

Entity::Entity(const EntityGivethrough& gt)
	: shape(gt.shape), position(gt.position), size(gt.size), speed(gt.speed), rotation(gt.rotation), spin(gt.spin)
{}

Entity::~Entity()
{
	delete shape;
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
		//Debug::warn("Entity::tick(): dashCounter == 1: TODO");
	}
}

void Entity::move(float time)
{
	if (!isStatic())
	{
		position += getSpeed() * time;
		// TODO rotation, spin
	}
}

void Entity::setSpeed(const GameVector& speed_arg)
{
	if (speed != speed_arg)
	{
		speed = speed_arg;
		setChanged(true);
	}
}

void Entity::setPosition(const GameVector& position_arg)
{
	if (position != position_arg)
	{
		position = position_arg;
		setChanged(true);
	}
	// TODO reload collision partners
}

void Entity::setRotation(float rotation_arg)
{
	rotation = rotation_arg;
	setChanged(true);
}

void Entity::setSpin(float spin_arg)
{
	spin = spin_arg;
	setChanged(true);
}

void Entity::push(const GameVector& how)
{
	addSpeed(how/getMass());
}

void Entity::addPosition(const GameVector& how)
{
	setPosition(position + how);
}

void Entity::addSpeed(const GameVector& how)
{
	setSpeed(how + getSpeed());
}


CollisionType Entity::getCollisionType() const
{
	return CollisionType{0, SOLID};
}

const GameVector& Entity::getPosition() const
{
	return position;
}

const GameVector& Entity::getSize() const
{
	return size;
}

const GameVector& Entity::getSpeed() const
{
	return speed;
}

float Entity::getRotation() const
{
	return rotation;
}

float Entity::getSpin() const
{
	return spin;
}

void Entity::optGravity()
{
	addSpeed(GameVector(0.f, 0.02f));
}

void Entity::optDrag()
{
	push(getSpeed() * -0.01f);
}

Sponge Entity::getSponge() const
{
	return Sponge{0, 0.f};
}

float Entity::getSpongeBetween(Entity* e1, Entity* e2)
{
	Sponge s1 = e1->getSponge();
	Sponge s2 = e2->getSponge();
	if (s1.priority > s2.priority)
	{
		return s1.value;
	}
	else
	{
		return s2.value;
	}
}

bool Entity::areCollisionPartners(Entity* e1, Entity* e2)
{
       return e1->hasCollisionPartner(e2) or e2->hasCollisionPartner(e1);
}

bool Entity::areWrapperPartners(Entity* e1, Entity* e2)
{
       return e1->hasWrapperPartner(e2) or e2->hasWrapperPartner(e1);
}

CollisionTypeID Entity::getCollisionTypeIDBetween(Entity* e1, Entity* e2)
{
	CollisionType t1 = e1->getCollisionType();
	CollisionType t2 = e2->getCollisionType();
	if (t1.priority > t2.priority)
	{
		return t1.id;
	}
	return t2.id;
}

void Entity::render(const View& v) const
{
	basicRender(v);
}

void Entity::basicRender(const View& v) const
{
	Screen::drawTexture(getTexture(), getRenderRect(v), getRotation());
}

PixelRect Entity::getRenderRect(const View& v) const
{
	GameRect r = getRenderGameRect();
	r = GameRect(r.getPosition() - r.getSize()/2, r.getSize());
	return v.gameRectToPixelRect(r);
}

void Entity::dash(const GameVector& targetPosition, float duration)
{
	setSpeed((targetPosition - getPosition())/duration);
	dashCounter = duration;
}

bool Entity::couldDashTo(const GameVector&) const
{
	Debug::warn("Entity::couldDashTo(): TODO");
	return true;
}

void Entity::flash(const GameVector& target)
{
	setPosition(target);
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

// for Shape
bool Entity::isCollidingPoint(const GameVector& point) const
{
	return shape->isCollidingPoint(point);
}

float Entity::getLeftest() const
{
	return shape->getLeftest();
}

float Entity::getRightest() const
{
	return shape->getRightest();
}

float Entity::getToppest() const
{
	return shape->getToppest();
}

float Entity::getBottest() const
{
	return shape->getBottest();
}

void Entity::reactToCollision_solid(const float massshare, const GameVector& otherSpeed, const GameVector& collisionPoint, float sponge)
{
	if (not isStatic())
	{
		shape->reactToCollision_solid(massshare, otherSpeed, collisionPoint, sponge);
	}
}

void Entity::reactToCollision_sticky(const float massshare, const GameVector& otherSpeed, const GameVector& collisionPoint)
{
	if (not isStatic())
	{
		shape->reactToCollision_sticky(massshare, otherSpeed, collisionPoint);
	}
}

GameRect Entity::getWrapper(float time) const
{
	return shape->getWrapper(time);
}

GameRect Entity::getRenderGameRect() const
{
	return shape->getRenderGameRect();
}

GameVector Entity::getSpeedAt(const GameVector& here) const
{
	return shape->getSpeedAt(here);
}
