#ifndef __CLIENTLOBBYMENU_CLASS__
#define __CLIENTLOBBYMENU_CLASS__

#include <string>

#include "LobbyMenu.hpp"

class ClientLobbyMenu : public LobbyMenu
{
	public:
		ClientLobbyMenu(const std::string&);
		virtual void handlePacket(Packet*, const sf::IpAddress&) override;
		virtual LobbyPlayer* getLocalPlayer() const override;
		virtual void lockPressed() override;
		virtual void disconnectPressed() override;
		virtual void teamPressed(Team*) override;
		void sendToServer(Packet*);
		virtual void handleLoginUserPacket(LoginUserPacket*, int) override;
		virtual void handleLobbyPlayersPacket(LobbyPlayersPacket*, int) override;
	private:
		LobbyPlayer* localPlayer;
		sf::IpAddress serverIP;
};

#endif
