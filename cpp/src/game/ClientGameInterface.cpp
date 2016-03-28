#include "ClientGameInterface.hpp"

#include "../misc/Debug.hpp"

ClientGameInterface::ClientGameInterface(LobbyTileMap* map, const std::vector<LobbyPlayer*>& players, int localPlayerID, const sf::IpAddress& ip)
	: GameInterface(map), localPlayerID(localPlayerID), ip(ip)
{
	for (int i = 0; i < players.size(); i++)
	{
		Debug::warn("ClientGameInterface::ClientGameInterface: add Player HERE, TODO");
	}
}

void ClientGameInterface::handlePacket(Packet*, const sf::IpAddress&)
{
	Debug::warn("ClientGameInterface::handlePacket(): TODO");
}
