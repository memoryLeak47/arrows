#include "ArrowShotSkill.hpp"

extern const char ARCHER_AID;
extern const char ARROWSHOTSKILL_SID;

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

Skill* ArrowShotSkill::clone() const
{
	return new ArrowShotSkill();
}
