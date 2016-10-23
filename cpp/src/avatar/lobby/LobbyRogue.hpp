#ifndef __LOBBYROGUE_CLASS__
#define __LOBBYROGUE_CLASS__

#include <avatar/LobbyAvatar.hpp>
#include <graphics/TextureID.hpp>
#include <string>

class LobbyRogue : public LobbyAvatar
{
	public:
		virtual TextureID getIconTextureID() const override;
		std::string getDescription() const;
};

#endif
