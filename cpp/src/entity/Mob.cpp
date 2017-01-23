#include "Mob.hpp"

#include <misc/Global.hpp>
#include <controller/Controller.hpp>
#include <misc/compress/CompressBuffer.hpp>

Mob::Mob(const EntityGivethrough& gt, Controller* controller)
	: ImpactfulDynamicEntity(gt), controller(controller)
{}

Mob::Mob(CompressBuffer* buffer)
	: ImpactfulDynamicEntity(buffer), controller(buffer->cutCompressable<Controller>())
{}

Mob::~Mob()
{
	delete controller;
}

std::vector<FrameCloneable**> Mob::getClonePointers() const
{
	std::vector<FrameCloneable**> tmp = ImpactfulDynamicEntity::getClonePointers();
	tmp.push_back((FrameCloneable**) &controller);
	return tmp;
}

std::string Mob::getCompressString() const
{
	return ImpactfulDynamicEntity::getCompressString() + getController()->compress();
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
	setSpeed(GameVector(getSpeed().x, getSpeed().y - 0.04f));
}

float Mob::getMass() const
{
	return 10.f;
}

float Mob::getMaxXSpeed() const
{
	return 0.3f;
}

void Mob::optSetSkillEnabled(int, bool)
{}

Controller* Mob::getController() const
{
	return controller;
}

void Mob::applyActions()
{
	if (getController() == nullptr)
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

	optSetSkillEnabled(0, getAction(getController()->getActions(), SKILL0));
	optSetSkillEnabled(1, getAction(getController()->getActions(), SKILL1));
	optSetSkillEnabled(2, getAction(getController()->getActions(), SKILL2));
	optSetSkillEnabled(3, getAction(getController()->getActions(), SKILL3));
}
