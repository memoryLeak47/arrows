#include "Mob.hpp"

#include <misc/Debug.hpp>

Mob::Mob(Body* body, Controller* controller)
	: Entity(body), controller(controller)
{}

Mob::~Mob()
{
	delete controller;
}

std::string Mob::getCompressString() const
{
	return getBody()->compress() + getController()->compress();
}

void Mob::tick()
{
	Entity::tick();
	applyActions();
}

EntityType Mob::getEntityType() const
{
	return EntityType::MOB;
}

void Mob::actionGoLeft()
{
	push(GameVector(-getMaxXSpeed(), 0.f));
}

void Mob::actionGoRight()
{
	push(GameVector(+getMaxXSpeed(), 0.f));
}

void Mob::actionJump()
{
	setSpeed(GameVector(body->getSpeed().x, -0.1f));
}

float Mob::getMass() const
{
	return 10.f;
}

float Mob::getMaxXSpeed() const
{
	return 0.3f;
}

Controller* Mob::getController() const
{
	return controller;
}

void Mob::applyActions()
{
	if (getController() == NULL)
	{
		return;
	}

	if (getController()->getAction(GO_LEFT))
	{
		actionGoLeft();
	}
	if (getController()->getAction(GO_RIGHT))
	{
		actionGoRight();
	}
	if (getController()->getAction(JUMP))
	{
		actionJump();
	}

	if (getController()->getAction(SKILL1)) Debug::warn("Mob::applyActions(): SKILL NOT SUPPORTED");
	if (getController()->getAction(SKILL2)) Debug::warn("Mob::applyActions(): SKILL NOT SUPPORTED");
	if (getController()->getAction(SKILL3)) Debug::warn("Mob::applyActions(): SKILL NOT SUPPORTED");
	if (getController()->getAction(SKILL4)) Debug::warn("Mob::applyActions(): SKILL NOT SUPPORTED");
}
