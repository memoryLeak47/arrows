#ifndef __LOBBYARROWSHOTSKILL_CLASS__
#define __LOBBYARROWSHOTSKILL_CLASS__

#include <player/property/skill/Skill.hpp>
#include <string>
#include <graphics/TextureID.hpp>

class LobbyArrowShotSkill : public Skill
{
	public:
		char getID() const override;
		std::string getDescription() const override;
		char getAvatarID() const override;
		TextureID getIconTextureID() const override;
		Skill* clone() const override;
};

#endif
