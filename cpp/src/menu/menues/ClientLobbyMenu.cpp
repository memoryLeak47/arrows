#include "ClientLobbyMenu.hpp"

ClientLobbyMenu::ClientLobbyMenu(const std::string& ip)
{
}

void ClientLobbyMenu::handlePacket(Packet* packet, const sf::IpAddress& ip)
{
	handlePacketByID(packet, 0);
}

void ClientLobbyMenu::lockPressed() {}
void ClientLobbyMenu::disconnectPressed() {}
