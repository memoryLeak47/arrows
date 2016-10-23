#ifndef __TRIGGERSKILL_CLASS__
#define __TRIGGERSKILL_CLASS__

#include <skill/Skill.hpp>

class TriggerSkill : public Skill
{
	public:
		virtual void onEnabled() override;
	protected:
		virtual void onTrigger();
};

#endif
