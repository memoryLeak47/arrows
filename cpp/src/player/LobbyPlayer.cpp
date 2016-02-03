#include "LobbyPlayer.hpp"

#include "../misc/Debug.hpp"

LobbyPlayer::LobbyPlayer(LoginUserPacket* login, const sf::IpAddress& ip)
{
	this->ip = ip;
	lockPacket = new LockUserPacket(false);
	teamPacket = new TeamUserPacket(0);
	loginPacket = login;
	// TODO create avatar/skill/item-userpacket
}

LobbyPlayer::LobbyPlayer(LoginUserPacket* login)
{
	lockPacket = new LockUserPacket(false);
	teamPacket = new TeamUserPacket(0);
	loginPacket = new LoginUserPacket(*login);
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
