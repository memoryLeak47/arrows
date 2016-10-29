#include "ArrowShotSkill.hpp"

#include <misc/Debug.hpp>

ArrowShotSkill::ArrowShotSkill(const SkillGivethrough& gt)
	: TriggerSkill(gt)
{}

void ArrowShotSkill::onTrigger()
{
	Debug::screen("ARROWWWW");
}
