#include "ArrowShotSkill.hpp"

extern const char ARCHER_AID;
extern const char ARROWSHOTSKILL_SID;
extern TextureID ARROWSHOTSKILL_ICON_TID;

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
	return ARROWSHOTSKILL_ICON_TID;
}

Skill* ArrowShotSkill::clone() const
{
	return new ArrowShotSkill();
}
