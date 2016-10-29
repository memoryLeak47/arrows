#ifndef __TOGGLESKILL_CLASS__
#define __TOGGLESKILL_CLASS__

class Mob;

#include <skill/Skill.hpp>

class ToggleSkill : public Skill
{
	public:
		ToggleSkill(const SkillGivethrough&);
		virtual void tick() override;

		bool isToggled() const;
	protected:
		virtual float getReduction();
		virtual void onEnabled() override;
	private:
		bool toggled;
};

#endif
