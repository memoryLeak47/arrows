#ifndef __ARROWSHOTSKILL_CLASS__
#define __ARROWSHOTSKILL_CLASS__

#include <player/property/skill/Skill.hpp>
#include <string>
#include <graphics/TextureID.hpp>

class ArrowShotSkill : public Skill
{
	public:
		char getID() const override;
		std::string getDescription() const override;
		char getAvatarID() const override;
		TextureID getIconTextureID() const override;
		Skill* clone() const override;
};

#endif
