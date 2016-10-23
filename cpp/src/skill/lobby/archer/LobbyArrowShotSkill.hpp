#ifndef __LOBBYARROWSHOTSKILL_CLASS__
#define __LOBBYARROWSHOTSKILL_CLASS__

#include <skill/LobbySkill.hpp>
#include <string>
#include <graphics/TextureID.hpp>

class LobbyArrowShotSkill : public LobbySkill
{
	public:
		std::string getDescription() const override;
		char getAvatarID() const override;
		TextureID getIconTextureID() const override;
};

#endif
