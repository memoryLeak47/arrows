#include "LobbyAvatar.hpp"

#include <misc/Global.hpp>
#include <core/Main.hpp>
#include <avatar/lobby/LobbyArcher.hpp>
#include <avatar/lobby/LobbyRogue.hpp>
#include <avatar/game/Archer.hpp>
#include <avatar/game/Rogue.hpp>
#include <avatar/AvatarID.hpp>

std::vector<LobbyAvatar*> LobbyAvatar::avatars;

void LobbyAvatar::init()
{
	#define X(aid, lobbyname, gamename) avatars.push_back(new lobbyname());
	#define Y(aid, lobbyname, gamename) avatars.push_back(new lobbyname());
	#include "AvatarID.list"
	#undef X
	#undef Y
}

void LobbyAvatar::uninit()
{
	deleteAndClearVector(avatars);
}

LobbyAvatar* LobbyAvatar::get(int id)
{
	if (id < 0 || id >= getAmount()) Debug::warn("LobbyAvatar::get(): id(" + Converter::intToString(id) + ") out of range");
	return avatars[id];
}

int LobbyAvatar::getAmount()
{
	return avatars.size();
}

const std::vector<LobbyAvatar*> LobbyAvatar::getAllLobbyAvatars()
{
	return avatars;
}

int LobbyAvatar::getMassStat() const
{
	return 20;
}

float LobbyAvatar::getHealthStat() const
{
	return 20;
}

GamePlayer* LobbyAvatar::createGamePlayer(const GameVector& vec, const LobbyPlayer* player) const
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
			Debug::error("LobbyAvatar::createGamePlayer() has no result");
			return nullptr;
		}
	}
}
