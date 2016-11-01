#include "ArrowShotSkill.hpp"

#include <misc/Debug.hpp>
#include <entity/bullets/SimpleArrow.hpp>
#include <entity/Mob.hpp>

ArrowShotSkill::ArrowShotSkill(const SkillGivethrough& gt)
	: TriggerSkill(gt)
{}

void ArrowShotSkill::onTrigger()
{
	if (getOwner()->getSpeed().x > 0.f)
	{
		addBullet(new SimpleArrow(getOwner()->getPosition(), getOwner()->getSpeed() + GameVector(1.4f, 0.f), getOwner()));
	}
	else
	{
		addBullet(new SimpleArrow(getOwner()->getPosition(), getOwner()->getSpeed() + GameVector(-1.4f, 0.f), getOwner()));
	}
}
