#include "Skill.hpp"

#include <misc/Global.hpp>
#include <core/Main.hpp>
#include "skills/ArrowShotSkill.hpp"

std::vector<Skill*> Skill::skills;

void Skill::init()
{
	#define X(sid, lobbyname, gamename) skills.push_back(new lobbyname());
	#define Y(sid, lobbyname, gamename) skills.push_back(new lobbyname());
	#include "SkillID.list"
	#undef X
	#undef Y
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
