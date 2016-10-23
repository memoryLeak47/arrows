#include "Avatar.hpp"

#include <misc/Global.hpp>
#include <core/Main.hpp>
#include "avatars/Archer.hpp"
#include "avatars/Rogue.hpp"
#include <player/game/ArcherGamePlayer.hpp>
#include <player/game/RogueGamePlayer.hpp>
#include "avatars/Rogue.hpp"
#include "AvatarID.hpp"

std::vector<Avatar*> Avatar::avatars;

void Avatar::init()
{
	#define X(aid, lobbyname, gamename) avatars.push_back(new lobbyname());
	#define Y(aid, lobbyname, gamename) avatars.push_back(new lobbyname());
	#include "AvatarID.list"
	#undef X
	#undef Y
}

void Avatar::uninit()
{
	deleteAndClearVector(avatars);
}

Avatar* Avatar::get(int id)
{
	if (id < 0 || id >= getAmount()) Debug::warn("Avatar::get(): id(" + Converter::intToString(id) + ") out of range");
	return avatars[id];
}

int Avatar::getAmount()
{
	return avatars.size();
}

const std::vector<Avatar*> Avatar::getAllAvatars()
{
	return avatars;
}

int Avatar::getMassStat() const
{
	return 20;
}

float Avatar::getHealthStat() const
{
	return 20;
}

GamePlayer* Avatar::createGamePlayer(const GameVector& vec, const LobbyPlayer* player) const
{
	switch (getID())
	{
		#define X(aid, lobbyname, gamename) case aid: return new gamename(vec, player);
		#define Y(aid, lobbyname, gamename) case aid: return new gamename(vec, player);
		#include "AvatarID.list"
		#undef X
		#undef Y
		default:
		{
			Debug::error("Avatar::createGamePlayer() has no result");
			return nullptr;
		}
	}
}
