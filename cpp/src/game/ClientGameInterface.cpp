#include "ClientGameInterface.hpp"

#include "../misc/Debug.hpp"

ClientGameInterface::ClientGameInterface(LobbyTileMap* map, const std::vector<LobbyPlayer*>& players, int localPlayerID, sf::IpAddress* ip)
	: GameInterface(map), localPlayerID(localPlayerID)
{
	serverIP = new sf::IpAddress(*ip);
	for (int i = 0; i < players.size(); i++)
	{
		Debug::warn("ClientGameInterface::ClientGameInterface: add Player HERE, TODO");
	}
}

ClientGameInterface::~ClientGameInterface()
{
	delete serverIP;
}

void ClientGameInterface::handlePacket(Packet*, sf::IpAddress*)
{
	Debug::warn("ClientGameInterface::handlePacket(): TODO");
}
