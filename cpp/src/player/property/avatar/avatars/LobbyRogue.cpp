#include "LobbyRogue.hpp"

#include <player/property/avatar/AvatarID.hpp>

TextureID LobbyRogue::getIconTextureID() const
{
	return ROGUE_ICON_GID;
}

char LobbyRogue::getID() const
{
	return ROGUE_AID;
}

std::string LobbyRogue::getDescription() const
{
	return "?";
}
