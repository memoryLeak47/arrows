#include "Skill.hpp"

#include "../../../core/Main.hpp"
#include "../../../misc/Converter.hpp"
#include "../../../misc/Debug.hpp"
#include "skills/ArrowShotSkill.hpp"

extern const char ARROWSHOTSKILL_SID = 0;

std::vector<Skill*> Skill::skills;

void Skill::init()
{
	skills.push_back(new ArrowShotSkill());
}

void Skill::uninit()
{
	deleteAndClearVector(skills);
}

Skill* Skill::get(int id)
{
	if (id < 0 || id >= getAmount()) Debug::warn("Skill::get(): id(" + Converter::intToString(id) + ") out of range");
	return skills[id];
}

int Skill::getAmount()
{
	return skills.size();
}

const std::vector<Skill*> Skill::getAllSkillsByAvatarID(char avatarID)
{
	std::vector<Skill*> tmp;
	for (unsigned int i = 0; i < skills.size(); i++)
	{
		if (skills[i]->getAvatarID() == avatarID)
		{
			tmp.push_back(skills[i]);
		}
	}
	return tmp;
}
