#ifndef __LOBBYPLAYER_CLASS__
#define __LOBBYPLAYER_CLASS__

#include <SFML/Network.hpp>

class LobbyPlayer
{
	public:
		sf::IpAddress getIP() const;
	private:
		sf::IpAddress ip;
};

#endif
