#ifndef __CLIENTLOBBYMENU_CLASS__
#define __CLIENTLOBBYMENU_CLASS__

#include "LobbyMenu.h"

#include <string>

class ClientLobbyMenu : public LobbyMenu
{
	public:
		ClientLobbyMenu(const std::string&);
		void handlePacket(Packet*, const sf::IpAddress&);
};

#endif
