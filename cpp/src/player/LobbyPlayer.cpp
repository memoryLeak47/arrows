#include "LobbyPlayer.hpp"

#include "../misc/Debug.hpp"

LobbyPlayer::LobbyPlayer(LoginUserPacket* login, const sf::IpAddress& ip)
{
	this->ip = ip;
	lockPacket = new LockUserPacket(false);
	teamPacket = new TeamUserPacket(0);
	itemPacket = new ItemUserPacket();
	avatarPacket = new AvatarUserPacket();
	loginPacket = login;
	// TODO create avatar/skill/item-userpacket
}

LobbyPlayer::LobbyPlayer(LoginUserPacket* login)
{
	lockPacket = new LockUserPacket(false);
	teamPacket = new TeamUserPacket(0);
	itemPacket = new ItemUserPacket();
	loginPacket = new LoginUserPacket(*login);
	avatarPacket = new AvatarUserPacket();
}

sf::IpAddress LobbyPlayer::getIP() const
{
	Debug::warnIf(ip == NULL, "LobbyPlayer::getIP(): ip == NULL");
	return ip;
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
