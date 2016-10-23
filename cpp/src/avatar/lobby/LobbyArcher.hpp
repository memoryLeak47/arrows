#ifndef __LOBBYARCHER_CLASS__
#define __LOBBYARCHER_CLASS__

class GamePlayer;
class GameVector;
class LobbyPlayer;

#include <avatar/LobbyAvatar.hpp>
#include <graphics/TextureID.hpp>
#include <string>

class LobbyArcher : public LobbyAvatar
{
	public:
		virtual TextureID getIconTextureID() const override;
		char getID() const override;
		std::string getDescription() const;
};

#endif
