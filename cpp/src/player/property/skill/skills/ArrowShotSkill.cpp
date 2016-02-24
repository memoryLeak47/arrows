#include "ArrowShotSkill.hpp"

extern const char ARCHER_AID;
extern const char ARROWSHOTSKILL_SID;
extern TextureID ARROWSHOTSKILL_ICON;

char ArrowShotSkill::getID() const
{

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
	return ARROWSHOTSKILL_ICON;
}

Skill* ArrowShotSkill::clone() const
{
	return new ArrowShotSkill();
}
