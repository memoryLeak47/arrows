#include "LobbyArcher.hpp"

#include <avatar/AvatarID.hpp>

TextureID LobbyArcher::getIconTextureID() const
{
	return ARCHER_ICON_GID;
}

char LobbyArcher::getID() const
{
	return ARCHER_AID;
}

std::string LobbyArcher::getDescription() const
{
	return "legolas; enough said";
}
