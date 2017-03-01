#include "LobbyArrowSalveSkill.hpp"

#include <avatar/AvatarID.hpp>

std::string LobbyArrowSalveSkill::getDescription() const
{
	return "shoots an arrow";
}

char LobbyArrowSalveSkill::getAvatarID() const
{
	return AvatarIDs::ARCHER;
}

TextureID LobbyArrowSalveSkill::getIconTextureID() const
{
	return GraphicsIDs::ARROWSALVESKILL_ICON;
}
