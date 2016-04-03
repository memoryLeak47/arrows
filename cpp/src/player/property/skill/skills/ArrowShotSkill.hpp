#ifndef __ARROWSHOTSKILL_CLASS__
#define __ARROWSHOTSKILL_CLASS__

#include "../Skill.hpp"

class ArrowShotSkill : public Skill
{
	public:
		char getID() const override;
		std::string getDescription() const override;
		char getAvatarID() const override;
		GraphicsID getIconGraphicsID() const override;
		Skill* clone() const override;
};

#endif
