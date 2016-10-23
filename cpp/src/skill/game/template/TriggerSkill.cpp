#include "TriggerSkill.hpp"

TriggerSkill::TriggerSkill(Mob* owner_arg)
	: Skill(owner_arg)
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
