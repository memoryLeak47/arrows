#include "LobbyPlayer.hpp"

#include "../misc/Debug.hpp"

sf::IpAddress LobbyPlayer::getIP() const
{
	Debug::warnIf(ip == NULL, "LobbyPlayer::getIP(): ip == NULL");
	return ip;
}
