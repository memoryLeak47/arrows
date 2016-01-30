#ifndef __CLIENTLOBBYMENU_CLASS__
#define __CLIENTLOBBYMENU_CLASS__

#include <string>

#include "LobbyMenu.h"

class ClientLobbyMenu : public LobbyMenu
{
	public:
		ClientLobbyMenu(const std::string&);
		void handlePacket(Packet*, const sf::IpAddress&) override;
};

#endif
