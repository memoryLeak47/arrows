#include "LobbyPlayer.hpp"

#include "../misc/Debug.hpp"

LobbyPlayer::LobbyPlayer(LoginUserPacket* login, const sf::IpAddress& ip)
	: ip(ip)
{
	lockPacket = new LockUserPacket(false);
	teamPacket = new TeamUserPacket((char)0);
	itemPacket = new ItemUserPacket();
	avatarPacket = new AvatarUserPacket();
	skillPacket = new SkillUserPacket();
	loginPacket = login;
}

LobbyPlayer::LobbyPlayer(LoginUserPacket* login)
	: ip(sf::IpAddress::getLocalAddress())
{
	lockPacket = new LockUserPacket(false);
	teamPacket = new TeamUserPacket((char)0);
	itemPacket = new ItemUserPacket();
	avatarPacket = new AvatarUserPacket();
	skillPacket = new SkillUserPacket();
	loginPacket = new LoginUserPacket(*login);
}

LobbyPlayer::LobbyPlayer(CompressBuffer* buffer)
	: ip(sf::IpAddress::getLocalAddress())
{
	lockPacket = static_cast<LockUserPacket*>(buffer->cutByCID(LOCK_USER_PACKET_CID));
	teamPacket = static_cast<TeamUserPacket*>(buffer->cutByCID(TEAM_USER_PACKET_CID));
	itemPacket = static_cast<ItemUserPacket*>(buffer->cutByCID(ITEM_USER_PACKET_CID));
	avatarPacket = static_cast<AvatarUserPacket*>(buffer->cutByCID(AVATAR_USER_PACKET_CID));
	skillPacket = static_cast<SkillUserPacket*>(buffer->cutByCID(SKILL_USER_PACKET_CID));
	loginPacket = static_cast<LoginUserPacket*>(buffer->cutByCID(LOGIN_USER_PACKET_CID));
}

sf::IpAddress LobbyPlayer::getIP() const
{
	return ip;
}

CID LobbyPlayer::getCID() const
{
	return LOBBY_PLAYER_CID;
}

LockUserPacket* LobbyPlayer::getLockUserPacket() const
{
	return lockPacket;
}

TeamUserPacket* LobbyPlayer::getTeamUserPacket() const
{
	return teamPacket;
}

LoginUserPacket* LobbyPlayer::getLoginUserPacket() const
{
	return loginPacket;
}

AvatarUserPacket* LobbyPlayer::getAvatarUserPacket() const
{
	return avatarPacket;
}

SkillUserPacket* LobbyPlayer::getSkillUserPacket() const
{
	return skillPacket;
}

ItemUserPacket* LobbyPlayer::getItemUserPacket() const
{
	return itemPacket;
}

void LobbyPlayer::applyLockUserPacket(LockUserPacket* packet)
{
	if (lockPacket != NULL)
	{
		delete lockPacket;
	}
	lockPacket = packet;
}

void LobbyPlayer::applyTeamUserPacket(TeamUserPacket* packet)
{
	if (teamPacket!= NULL)
	{
		delete teamPacket;
	}
	teamPacket = packet;
}

void LobbyPlayer::applyLoginUserPacket(LoginUserPacket* packet)
{
	if (loginPacket != NULL)
	{
		delete loginPacket;
	}
	loginPacket = packet;
}

void LobbyPlayer::applyAvatarUserPacket(AvatarUserPacket* packet)
{
	if (avatarPacket != NULL)
	{
		delete avatarPacket;
	}
	avatarPacket = packet;
}

void LobbyPlayer::applySkillUserPacket(SkillUserPacket* packet)
{
	if (skillPacket != NULL)
	{
		delete skillPacket;
	}
	skillPacket = packet;
}

void LobbyPlayer::applyItemUserPacket(ItemUserPacket* packet)
{
	if (itemPacket != NULL)
	{
		delete itemPacket;
	}
	itemPacket = packet;
}

std::string LobbyPlayer::toString() const
{
	std::string s;
	s += getLockUserPacket()->toString();
	s += getTeamUserPacket()->toString();
	s += getLoginUserPacket()->toString();
	s += getAvatarUserPacket()->toString();
	s += getSkillUserPacket()->toString();
	s += getItemUserPacket()->toString();
	return s;
}
