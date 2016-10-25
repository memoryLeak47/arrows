#include "Skill.hpp"

#include <skill/LobbySkill.hpp>

Skill::Skill(Mob* owner_arg, const LobbySkill* skill)
	: owner(owner_arg), enabled(false), charge(0.f), description(skill->getDescription()), iconTextureID(skill->getIconTextureID())
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
