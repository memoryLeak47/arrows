#include "ArrowSalveSkill.hpp"

#include <misc/Debug.hpp>
#include <entity/bullets/SimpleArrow.hpp>
#include <entity/Mob.hpp>

ArrowSalveSkill::ArrowSalveSkill(const SkillGivethrough& gt)
	: TriggerSkill(gt)
{}

void ArrowSalveSkill::onTrigger()
{
	Debug::error("wot?");
	constexpr int ARROW_COUNT = 40;
	if (getOwner()->getSpeed().x > 0.f)
	{
		for (int i = 0; i < ARROW_COUNT; i++)
		{
			addBullet(new SimpleArrow(getOwner()->getPosition(), getOwner()->getSpeed() + GameVector(1.4f, 0.f), getOwner()));
		}
	}
	else
	{
		for (int i = 0; i < ARROW_COUNT; i++)
		{
			addBullet(new SimpleArrow(getOwner()->getPosition(), getOwner()->getSpeed() + GameVector(-1.4f, 0.f), getOwner()));
		}
	}
}
