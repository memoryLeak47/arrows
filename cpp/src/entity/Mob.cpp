#include "Mob.hpp"

#include <misc/Global.hpp>
#include <controller/Controller.hpp>
#include <collision/Body.hpp>
#include <misc/compress/CompressBuffer.hpp>

Mob::Mob(Body* body, Controller* controller)
	: ImpactfulDynamicEntity(body), controller(controller)
{}

Mob::Mob(CompressBuffer* buffer)
	: ImpactfulDynamicEntity(buffer), controller((Controller*) buffer->cutCompressable())
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
	ImpactfulDynamicEntity::tick();
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

	if (getAction(getController()->getActions(), GO_LEFT))
	{
		actionGoLeft();
	}
	if (getAction(getController()->getActions(), GO_RIGHT))
	{
		actionGoRight();
	}
	if (getAction(getController()->getActions(), JUMP))
	{
		actionJump();
	}

	if (getAction(getController()->getActions(), SKILL1)) Debug::warn("Mob::applyActions(): SKILL NOT SUPPORTED");
	if (getAction(getController()->getActions(), SKILL2)) Debug::warn("Mob::applyActions(): SKILL NOT SUPPORTED");
	if (getAction(getController()->getActions(), SKILL3)) Debug::warn("Mob::applyActions(): SKILL NOT SUPPORTED");
	if (getAction(getController()->getActions(), SKILL4)) Debug::warn("Mob::applyActions(): SKILL NOT SUPPORTED");
}
