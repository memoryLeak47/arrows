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
	ip = player->getIP();
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

LobbyPlayer::LobbyPlayer(LoginPacket* login, const sf::IpAddress& ipArg)
{
	ip = ipArg;
	lockPacket = new LockPacket(false);
	teamPacket = new TeamPacket((char)0);
	itemPacket = new ItemPacket();
	avatarPacket = new AvatarPacket();
	skillPacket = new SkillPacket();
	loginPacket = new LoginPacket(*login);
}

LobbyPlayer::LobbyPlayer(LoginPacket* login)
{
	ip = sf::IpAddress::getLocalAddress();
	lockPacket = new LockPacket(false);
	teamPacket = new TeamPacket((char)0);
	itemPacket = new ItemPacket();
	avatarPacket = new AvatarPacket();
	skillPacket = new SkillPacket();
	loginPacket = new LoginPacket(*login);
}

LobbyPlayer::LobbyPlayer(CompressBuffer* buffer)
{
	ip = nullptr;
	lockPacket = static_cast<LockPacket*>(buffer->cutByCompressID(CompressIDs::LOCK_PACKET));
	teamPacket = static_cast<TeamPacket*>(buffer->cutByCompressID(CompressIDs::TEAM_PACKET));
	loginPacket = static_cast<LoginPacket*>(buffer->cutByCompressID(CompressIDs::LOGIN_PACKET));
	avatarPacket = static_cast<AvatarPacket*>(buffer->cutByCompressID(CompressIDs::AVATAR_PACKET));
	skillPacket = static_cast<SkillPacket*>(buffer->cutByCompressID(CompressIDs::SKILL_PACKET));
	itemPacket = static_cast<ItemPacket*>(buffer->cutByCompressID(CompressIDs::ITEM_PACKET));
}

LobbyPlayer::~LobbyPlayer()
{
	deleteAndNullptr(lockPacket);
	deleteAndNullptr(teamPacket);
	deleteAndNullptr(loginPacket);
	deleteAndNullptr(avatarPacket);
	deleteAndNullptr(skillPacket);
	deleteAndNullptr(itemPacket);
}

const sf::IpAddress& LobbyPlayer::getIP() const
{
	return ip;
}

CompressID LobbyPlayer::getCompressID() const
{
	return CompressIDs::LOBBY_PLAYER;
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
	if (lockPacket != nullptr)
	{
		deleteAndNullptr(lockPacket);
	}
	lockPacket = new LockPacket(*packet);
}

void LobbyPlayer::applyTeamPacket(TeamPacket* packet)
{
	if (teamPacket != nullptr)
	{
		deleteAndNullptr(teamPacket);
	}
	teamPacket = new TeamPacket(*packet);
}

void LobbyPlayer::applyLoginPacket(LoginPacket* packet)
{
	if (loginPacket != nullptr)
	{
		deleteAndNullptr(loginPacket);
	}
	loginPacket = new LoginPacket(*packet);
}

void LobbyPlayer::applyAvatarPacket(AvatarPacket* packet)
{
	if (avatarPacket != nullptr)
	{
		deleteAndNullptr(avatarPacket);
	}
	avatarPacket = new AvatarPacket(*packet);
}

void LobbyPlayer::applySkillPacket(SkillPacket* packet)
{
	if (skillPacket != nullptr)
	{
		deleteAndNullptr(skillPacket);
	}
	skillPacket = new SkillPacket(*packet);
}

void LobbyPlayer::applyItemPacket(ItemPacket* packet)
{
	if (itemPacket != nullptr)
	{
		deleteAndNullptr(itemPacket);
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
