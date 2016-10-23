#include "ArrowShotSkill.hpp"

#include <player/property/avatar/AvatarID.hpp>

extern int ARROWSHOTSKILL_SID;

char ArrowShotSkill::getID() const
{
	return ARROWSHOTSKILL_SID;
}

std::string ArrowShotSkill::getDescription() const
{
	return "shoots an arrow";
}

char ArrowShotSkill::getAvatarID() const
{
	return ARCHER_AID;
}

TextureID ArrowShotSkill::getIconTextureID() const
{
	return ARROWSHOTSKILL_ICON_GID;
}

Skill* ArrowShotSkill::clone() const
{
	return new ArrowShotSkill();
}
