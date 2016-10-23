#include "Skill.hpp"

Skill::Skill(Mob* owner_arg)
	: owner(owner_arg), enabled(false), charge(0.f)
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

void Skill::setCharge(float charge_arg)
{
	charge = charge_arg;
}

void Skill::onEnabled() {}
void Skill::onDisabled() {}
