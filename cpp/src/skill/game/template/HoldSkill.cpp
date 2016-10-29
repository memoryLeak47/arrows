#include "HoldSkill.hpp"

HoldSkill::HoldSkill(SkillGivethrough&& gt)
	: Skill(gt)
{}

void HoldSkill::tick()
{
	if (isEnabled())
	{
		setCharge(getCharge() - getReduction());
	}
	else
	{
		setCharge(getCharge() + getRecharge());
	}
}

float HoldSkill::getReduction()
{
	return 3.f; // default value; shoud be overwritten
}
