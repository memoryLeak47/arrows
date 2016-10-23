#include "LobbyArrowShotSkill.hpp"

#include <avatar/AvatarID.hpp>

std::string LobbyArrowShotSkill::getDescription() const
{
	return "shoots an arrow";
}

char LobbyArrowShotSkill::getAvatarID() const
{
	return ARCHER_AID;
}

TextureID LobbyArrowShotSkill::getIconTextureID() const
{
	return ARROWSHOTSKILL_ICON_GID;
}
