#ifndef __LOBBYARROWSALVESKILL_CLASS__
#define __LOBBYARROWSALVESKILL_CLASS__

#include <skill/LobbySkill.hpp>
#include <string>
#include <graphics/TextureID.hpp>

class LobbyArrowSalveSkill : public LobbySkill
{
	public:
		std::string getDescription() const override;
		char getAvatarID() const override;
		TextureID getIconTextureID() const override;
};

#endif
