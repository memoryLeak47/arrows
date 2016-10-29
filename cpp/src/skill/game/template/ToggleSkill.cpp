#include "ToggleSkill.hpp"

ToggleSkill::ToggleSkill(const SkillGivethrough& gt)
	: Skill(gt), toggled(false)
{}

void ToggleSkill::tick()
{
	if (isToggled())
	{
		setCharge(getCharge() - getReduction());
	}
	else
	{
		setCharge(getCharge() + getRecharge());
	}
}

bool ToggleSkill::isToggled() const
{
	return toggled;
}

float ToggleSkill::getReduction()
{
	return 3.f; // default value; shoud be overwritten
}

void ToggleSkill::onEnabled()
{
	toggled = not toggled;
}
