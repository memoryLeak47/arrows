#ifndef __TRIGGERSKILL_CLASS__
#define __TRIGGERSKILL_CLASS__

class Mob;

#include <skill/Skill.hpp>

class TriggerSkill : public Skill
{
	public:
		TriggerSkill(Mob*);
		virtual void onEnabled() override;
		virtual void tick() override;
	protected:
		virtual void onTrigger();
};

#endif
