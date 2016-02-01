#include "ClientLobbyMenu.hpp"

#include "../../misc/Debug.hpp"
#include "../../core/Main.hpp"

ClientLobbyMenu::ClientLobbyMenu(const std::string& ip) : serverIP(ip)
{}

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
