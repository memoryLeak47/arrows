#include "Rogue.hpp"

#include <player/property/avatar/AvatarID.hpp>

TextureID Rogue::getIconTextureID() const
{
	return ROGUE_ICON_GID;
}

char Rogue::getID() const
{
	return ROGUE_AID;
}

std::string Rogue::getDescription() const
{
	return "?";
}
