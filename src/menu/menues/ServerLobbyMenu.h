#ifndef __SERVERLOBBYMENU_CLASS__
#define __SERVERLOBBYMENU_CLASS__

#include "LobbyMenu.h"

class ServerLobbyMenu : public LobbyMenu
{
	public:
		void handlePacket(Packet*, const sf::IpAddress&) override;
};

#endif
