#include "TriggerSkill.hpp"

TriggerSkill::TriggerSkill(const SkillGivethrough& gt)
	: Skill(gt)
{}

void TriggerSkill::onEnabled()
{
	if (getCharge() >= MAX_CHARGE)
	{
		setCharge(0.f);
		onTrigger();
	}
}

void TriggerSkill::tick()
{
	setCharge(getCharge() + getRecharge());
}

void TriggerSkill::onTrigger() {}
