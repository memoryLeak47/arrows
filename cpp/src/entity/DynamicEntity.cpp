#include "DynamicEntity.hpp"

#include <misc/Global.hpp>
#include <collision/CollisionTester.hpp>
#include <collision/PhysicsHandler.hpp>
#include <entity/EntityGivethrough.hpp>
#include <math/game/GameVector.hpp>
#include <game/message/messages/DestroyMessage.hpp>

DynamicEntity::DynamicEntity(const EntityGivethrough& gt)
	: Entity(gt), changed(true), speed(gt.speed)
{}

void DynamicEntity::tick()
{
	Entity::tick();
	lifetime++;
}

bool DynamicEntity::hasChanged() const
{
	return changed;
}

void DynamicEntity::setChanged(bool b)
{
	changed = b;
}

void DynamicEntity::checkWrapperPartners()
{
	for (unsigned int i = 0; i < wrapperPartners.size(); ++i)
	{
		Entity* p = wrapperPartners[i];
		if (CollisionTester::areWrapperColliding(this, p))
		{
			GameVector collisionPoint(0,0);
			if (CollisionTester::areColliding(this, p, &collisionPoint))
			{
				if (not Entity::areCollisionPartners(this, p))
				{
					addCollisionPartner(p);
					p->addCollisionPartner(this);
					// TODO throw enter event
				}
				PhysicsHandler::handlePhysics(this, p, collisionPoint);

				this->setChanged(true);
				p->setChanged(true);
			}
			else
			{
				if (Entity::areCollisionPartners(this, p))
				{
					removeCollisionPartner(p);
					p->removeCollisionPartner(this);
					// TODO throw exit event
				}
			}
		}
		else
		{
			removeWrapperPartner(p);
			p->removeWrapperPartner(this);
		}
	}
}

const GameVector& DynamicEntity::getSpeed() const
{
	return speed;
}

void DynamicEntity::setSpeed(const GameVector& speed_arg)
{
	if (speed != speed_arg)
	{
		speed = speed_arg;
		setChanged(true);
	}
}

void DynamicEntity::addCollisionPartner(Entity* e)
{
	if (e == this)
	{
		Debug::error("DynamicEntity::addCollisionPartner(): entity wanted to add itself: " + e->toString());
	}

	if (! memberOf(e, collisionPartners))
	{
		collisionPartners.push_back(e);
	}
	else
	{
		Debug::warn("DynamicEntity::addCollisionPartner(): entity is already in collisionPartners");
	}
}

void DynamicEntity::addWrapperPartner(Entity* e)
{
	if (e == this)
	{
		Debug::error("DynamicEntity::addWrapperPartner(): entity wanted to add itself: " + e->toString());
	}

	if (! memberOf(e, wrapperPartners))
	{
		wrapperPartners.push_back(e);
	}
	else
	{
		Debug::warn("DynamicEntity::addWrapperPartner(): entity is already in wrapperPartners");
	}
}

void DynamicEntity::removeCollisionPartner(Entity* e)
{
	if (e == this)
	{
		Debug::error("DynamicEntity::removeCollisionPartner(): entity wanted to remove itself: " + e->toString());
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
		Debug::error("DynamicEntity::removeCollisionPartner(): e=" + e->toString() + " was not found in " + toString() + ".collisionPartners");
	}
}


void DynamicEntity::removeWrapperPartner(Entity* e)
{
	if (e == this)
	{
		Debug::error("DynamicEntity::removeWrapper Partner(): entity wanted to remove itself: " + e->toString());
	}
	bool found = false;
	for (auto it = wrapperPartners.begin(); it != wrapperPartners.end(); ++it)
	{
		if (*it == e)
		{
			found = true;
			wrapperPartners.erase(it);
			break;
		}
	}

	if (not found)
	{
		Debug::error("DynamicEntity::removeWrapperPartner(): e=" + e->toString() + " was not found in " + toString() + ".wrapperPartners");
	}
}

const std::vector<Entity*>& DynamicEntity::getCollisionPartners() const
{
       return collisionPartners;
}

const std::vector<Entity*>& DynamicEntity::getWrapperPartners() const
{
       return wrapperPartners;
}

bool DynamicEntity::hasCollisionPartner(Entity* e) const
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

bool DynamicEntity::hasWrapperPartner(Entity* e) const
{
	for (unsigned int i = 0; i < wrapperPartners.size(); i++)
	{
		if (e == wrapperPartners[i])
		{
			return true;
		}
	}
	return false;
}

void DynamicEntity::broadcastMessage(Message* m)
{
	// TODO broadcast to the effects
}

void DynamicEntity::pollSubMessages()
{
	// TODO poll from effects
}

void DynamicEntity::applyMessage(const DestroyMessage& m)
{
	for (unsigned int i = 0; i < wrapperPartners.size(); i++)
	{
		if (m.getEntity() == wrapperPartners[i])
		{
			wrapperPartners.erase(wrapperPartners.begin() + i--);
		}
	}
	for (unsigned int i = 0; i < collisionPartners.size(); i++)
	{
		if (m.getEntity() == collisionPartners[i])
		{
			collisionPartners.erase(collisionPartners.begin() + i--);
		}
	}
}

void DynamicEntity::destroy()
{
	addMessage(new DestroyMessage(this));
}

int DynamicEntity::getLifetime() const
{
	return lifetime;
}
