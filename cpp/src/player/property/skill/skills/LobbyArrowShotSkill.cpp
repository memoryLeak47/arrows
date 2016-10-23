#include "LobbyArrowShotSkill.hpp"

#include <player/property/avatar/AvatarID.hpp>
#include <player/property/skill/SkillID.hpp>

char LobbyArrowShotSkill::getID() const
{
	return ARROWSHOTSKILL_SID;
}

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
