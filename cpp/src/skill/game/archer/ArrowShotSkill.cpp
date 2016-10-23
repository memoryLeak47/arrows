#include "ArrowShotSkill.hpp"

#include <misc/Debug.hpp>

ArrowShotSkill::ArrowShotSkill(Mob* owner_arg)
	: TriggerSkill(owner_arg)
{}

void ArrowShotSkill::onTrigger()
{
	Debug::screen("ARROWWWW");
}
