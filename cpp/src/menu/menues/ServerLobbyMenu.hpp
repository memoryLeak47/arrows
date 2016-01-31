#ifndef __SERVERLOBBYMENU_CLASS__
#define __SERVERLOBBYMENU_CLASS__

#include "LobbyMenu.hpp"

class ServerLobbyMenu : public LobbyMenu
{
	public:
		void handlePacket(Packet*, const sf::IpAddress&) override;
		virtual void lockPressed() override;
		virtual void disconnectPressed() override;
};

#endif
