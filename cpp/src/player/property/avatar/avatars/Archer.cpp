#include "Archer.hpp"

#include <player/game/ArcherGamePlayer.hpp>
#include <player/property/avatar/AvatarID.hpp>

TextureID Archer::getIconTextureID() const
{
	return ARCHER_ICON_GID;
}

char Archer::getID() const
{
	return ARCHER_AID;
}

std::string Archer::getDescription() const
{
	return "legolas; enough said";
}
