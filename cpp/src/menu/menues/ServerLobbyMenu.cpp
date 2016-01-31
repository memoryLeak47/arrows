#include "ServerLobbyMenu.hpp"

void ServerLobbyMenu::handlePacket(Packet* packet, const sf::IpAddress& ip)
{
	handlePacketByID(packet, ipToID(ip, getPlayers()));
}

void ServerLobbyMenu::lockPressed() {}
void ServerLobbyMenu::disconnectPressed() {}
