#include "LobbyArrowSalveSkill.hpp"

#include <avatar/AvatarID.hpp>

std::string LobbyArrowSalveSkill::getDescription() const
{
	return "shoots an arrow";
}

char LobbyArrowSalveSkill::getAvatarID() const
{
	return ARCHER_AID;
}

TextureID LobbyArrowSalveSkill::getIconTextureID() const
{
	return ARROWSALVESKILL_ICON_GID;
}
