#include "LobbySkill.hpp"

#include <misc/Global.hpp>
#include <core/Main.hpp>
#include <skill/lobby/archer/LobbyArrowShotSkill.hpp>
#include <skill/lobby/archer/LobbyArrowSalveSkill.hpp>
#include <skill/game/archer/ArrowShotSkill.hpp>
#include <skill/game/archer/ArrowSalveSkill.hpp>
#include "SkillID.hpp"

std::vector<LobbySkill*> LobbySkill::skills;

void LobbySkill::init()
{
	#define X(sid, lobbyname, gamename) skills.push_back(new lobbyname());
	#define Y(sid, lobbyname, gamename) skills.push_back(new lobbyname());
	#include "SkillID.list"
	#undef X
	#undef Y

	for (unsigned int i = 0; i < skills.size(); i++)
	{
		skills[i]->setID(i);
	}
}

void LobbySkill::uninit()
{
	deleteAndClearVector(skills);
}

LobbySkill* LobbySkill::get(int id)
{
	if (id < 0 || id >= getAmount()) Debug::warn("LobbySkill::get(): id(" + Converter::intToString(id) + ") out of range");
	return skills[id];
}

int LobbySkill::getAmount()
{
	return skills.size();
}

const std::vector<LobbySkill*> LobbySkill::getAllLobbySkillsByAvatarID(char avatarID)
{
	std::vector<LobbySkill*> tmp;
	for (unsigned int i = 0; i < skills.size(); i++)
	{
		if (skills[i]->getAvatarID() == avatarID)
		{
			tmp.push_back(skills[i]);
		}
	}
	return tmp;
}

char LobbySkill::getID() const
{
	return id;
}

Skill* LobbySkill::createGameSkill(Mob* owner) const
{
	switch (getID())
	{
		#define X(sid, lobbyname, gamename) case SkillIDs::sid: return new gamename(SkillGivethrough {owner, this});
		#define Y(sid, lobbyname, gamename) case SkillIDs::sid: return new gamename(SkillGivethrough {owner, this});
		#include "SkillID.list"
		#undef X
		#undef Y
		default:
		{
			Debug::error("LobbySkill::createGameSkill(): nothing found here");
			return nullptr;
		}
	}
}

void LobbySkill::setID(char id_arg)
{
	id = id_arg;
}
