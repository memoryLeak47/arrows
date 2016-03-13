#include "ClientLobbyMenu.hpp"

#include "../../misc/Debug.hpp"
#include "../../core/Main.hpp"

ClientLobbyMenu::ClientLobbyMenu(const std::string& ip) : serverIP(ip)
{
	LoginUserPacket* p = new LoginUserPacket("ml47", 9001);
	sendToServer(p);
	delete p;
}

LobbyPlayer* ClientLobbyMenu::getLocalPlayer() const
{
	return NULL; // TODO
}

void ClientLobbyMenu::handlePacket(Packet* packet, const sf::IpAddress& ip)
{
	if (ip == serverIP)
	{
		handlePacketByID(packet, 0);
	}
	else
	{
		Debug::warn("got ip from strange ip...");
	}
}

void ClientLobbyMenu::lockPressed() {}

void ClientLobbyMenu::disconnectPressed()
{
	Main::getMenuList()->back();
}

void ClientLobbyMenu::teamPressed(Team* team) {}

void ClientLobbyMenu::sendToServer(Packet* p)
{
	send(p, serverIP);
}
