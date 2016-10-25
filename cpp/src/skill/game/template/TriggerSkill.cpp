#include "TriggerSkill.hpp"

TriggerSkill::TriggerSkill(Mob* owner_arg, const LobbySkill* lobbySkill)
	: Skill(owner_arg, lobbySkill)
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
