#include "TriggerSkill.hpp"

void TriggerSkill::onEnabled()
{
	if (getCharge() >= MAX_CHARGE)
	{
		setCharge(0.f);
		onTrigger();
	}
}

void TriggerSkill::onTrigger() {}
