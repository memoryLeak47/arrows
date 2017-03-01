#include "LobbyArrowShotSkill.hpp"

#include <avatar/AvatarID.hpp>

std::string LobbyArrowShotSkill::getDescription() const
{
	return "shoots an arrow";
}

char LobbyArrowShotSkill::getAvatarID() const
{
	return AvatarIDs::ARCHER;
}

TextureID LobbyArrowShotSkill::getIconTextureID() const
{
	return GraphicsIDs::ARROWSHOTSKILL_ICON;
}
