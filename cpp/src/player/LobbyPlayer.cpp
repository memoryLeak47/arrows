#include "LobbyPlayer.h"

#include "../misc/Debug.h"

sf::IpAddress LobbyPlayer::getIP() const
{
	Debug::warnIf(ip == NULL, "LobbyPlayer::getIP(): ip == NULL");
	return ip;
}
