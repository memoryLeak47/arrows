#include "Skill.hpp"

#include <skill/LobbySkill.hpp>

Skill::Skill(const SkillGivethrough& gt)
	: owner(gt.owner), enabled(false), charge(0.f), description(gt.lobbySkill->getDescription()), iconTextureID(gt.lobbySkill->getIconTextureID())
{}

void Skill::setEnabled(bool b)
{
	if (enabled != b)
	{
		if (b)
		{
			onEnabled();
		}
		else
		{
			onDisabled();
		}
	}
	enabled = b;
}

void Skill::tick() {}

bool Skill::isEnabled() const
{
	return enabled;
}

float Skill::getCharge() const
{
	return charge;
}

float Skill::getRecharge() const
{
	return 1.f; // default value. Should be overwritten
}

void Skill::setCharge(float charge_arg)
{
	if (charge_arg >= MAX_CHARGE)
	{
		charge = MAX_CHARGE;
	}
	else if (charge_arg <= 0.f)
	{
		charge = 0.f;
	}
	else
	{
		charge = charge_arg;
	}
}

void Skill::onEnabled() {}
void Skill::onDisabled() {}
