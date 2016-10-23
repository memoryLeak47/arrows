#include "LobbyPlayer.hpp"

#include <misc/Global.hpp>
#include <core/Main.hpp>
#include <misc/compress/CompressBuffer.hpp>

#include <network/packets/LockPacket.hpp>
#include <network/packets/TeamPacket.hpp>
#include <network/packets/LoginPacket.hpp>
#include <network/packets/AvatarPacket.hpp>
#include <network/packets/SkillPacket.hpp>
#include <network/packets/ItemPacket.hpp>

LobbyPlayer::LobbyPlayer(LobbyPlayer* player)
{
	ip = new sf::IpAddress(*player->getIP());
	lockPacket = new LockPacket(*player->lockPacket);
	teamPacket = new TeamPacket(*player->teamPacket);
	loginPacket = new LoginPacket(*player->loginPacket);
	avatarPacket = new AvatarPacket(*player->avatarPacket);
	skillPacket = new SkillPacket(*player->skillPacket);
	itemPacket = new ItemPacket(*player->itemPacket);
}

LobbyPlayer::LobbyPlayer(const LobbyPlayer& player)
{
	Debug::error("DONT USE LobbyPlayer::LobbyPlayer(const LobbyPlayer&); USE THE POINTER STUFF");
}

LobbyPlayer::LobbyPlayer(LoginPacket* login, sf::IpAddress* ipArg)
{
	ip = new sf::IpAddress(*ipArg);
	lockPacket = new LockPacket(false);
	teamPacket = new TeamPacket((char)0);
	itemPacket = new ItemPacket();
	avatarPacket = new AvatarPacket();
	skillPacket = new SkillPacket();
	loginPacket = new LoginPacket(*login);
}

LobbyPlayer::LobbyPlayer(LoginPacket* login)
{
	ip = new sf::IpAddress(sf::IpAddress::getLocalAddress());
	lockPacket = new LockPacket(false);
	teamPacket = new TeamPacket((char)0);
	itemPacket = new ItemPacket();
	avatarPacket = new AvatarPacket();
	skillPacket = new SkillPacket();
	loginPacket = new LoginPacket(*login);
}

LobbyPlayer::LobbyPlayer(CompressBuffer* buffer)
{
	ip = NULL;
	lockPacket = static_cast<LockPacket*>(buffer->cutByCompressID(LOCK_PACKET_CID));
	teamPacket = static_cast<TeamPacket*>(buffer->cutByCompressID(TEAM_PACKET_CID));
	loginPacket = static_cast<LoginPacket*>(buffer->cutByCompressID(LOGIN_PACKET_CID));
	avatarPacket = static_cast<AvatarPacket*>(buffer->cutByCompressID(AVATAR_PACKET_CID));
	skillPacket = static_cast<SkillPacket*>(buffer->cutByCompressID(SKILL_PACKET_CID));
	itemPacket = static_cast<ItemPacket*>(buffer->cutByCompressID(ITEM_PACKET_CID));
}

LobbyPlayer::~LobbyPlayer()
{
	deleteAndNULL(lockPacket);
	deleteAndNULL(teamPacket);
	deleteAndNULL(loginPacket);
	deleteAndNULL(avatarPacket);
	deleteAndNULL(skillPacket);
	deleteAndNULL(itemPacket);
	deleteAndNULL(ip);
}

sf::IpAddress* LobbyPlayer::getIP() const
{
	return ip;
}

CompressID LobbyPlayer::getCompressID() const
{
	return LOBBY_PLAYER_CID;
}

LockPacket* LobbyPlayer::getLockPacket() const
{
	return lockPacket;
}

TeamPacket* LobbyPlayer::getTeamPacket() const
{
	return teamPacket;
}

LoginPacket* LobbyPlayer::getLoginPacket() const
{
	return loginPacket;
}

AvatarPacket* LobbyPlayer::getAvatarPacket() const
{
	return avatarPacket;
}

SkillPacket* LobbyPlayer::getSkillPacket() const
{
	return skillPacket;
}

ItemPacket* LobbyPlayer::getItemPacket() const
{
	return itemPacket;
}

void LobbyPlayer::applyLockPacket(LockPacket* packet)
{
	if (lockPacket != NULL)
	{
		deleteAndNULL(lockPacket);
	}
	lockPacket = new LockPacket(*packet);
}

void LobbyPlayer::applyTeamPacket(TeamPacket* packet)
{
	if (teamPacket != NULL)
	{
		deleteAndNULL(teamPacket);
	}
	teamPacket = new TeamPacket(*packet);
}

void LobbyPlayer::applyLoginPacket(LoginPacket* packet)
{
	if (loginPacket != NULL)
	{
		deleteAndNULL(loginPacket);
	}
	loginPacket = new LoginPacket(*packet);
}

void LobbyPlayer::applyAvatarPacket(AvatarPacket* packet)
{
	if (avatarPacket != NULL)
	{
		deleteAndNULL(avatarPacket);
	}
	avatarPacket = new AvatarPacket(*packet);
}

void LobbyPlayer::applySkillPacket(SkillPacket* packet)
{
	if (skillPacket != NULL)
	{
		deleteAndNULL(skillPacket);
	}
	skillPacket = new SkillPacket(*packet);
}

void LobbyPlayer::applyItemPacket(ItemPacket* packet)
{
	if (itemPacket != NULL)
	{
		deleteAndNULL(itemPacket);
	}
	itemPacket = new ItemPacket(*packet);
}

std::string LobbyPlayer::getCompressString() const
{
	std::string s;
	s += getLockPacket()->getCompressString();
	s += getTeamPacket()->getCompressString();
	s += getLoginPacket()->getCompressString();
	s += getAvatarPacket()->getCompressString();
	s += getSkillPacket()->getCompressString();
	s += getItemPacket()->getCompressString();
	return s;
}
