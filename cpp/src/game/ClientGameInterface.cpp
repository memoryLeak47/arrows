#include "ClientGameInterface.hpp"

#include "../misc/Debug.hpp"

ClientGameInterface::ClientGameInterface(LobbyTileMap* map, const std::vector<LobbyPlayer*>& players, int localPlayerID, sf::IpAddress* ip)
	: GameInterface(map, players), localPlayerID(localPlayerID)
{
	serverIP = new sf::IpAddress(*ip);
}

ClientGameInterface::~ClientGameInterface()
{
	delete serverIP;
}

void ClientGameInterface::handlePacket(Packet*, sf::IpAddress*)
{
	Debug::warn("ClientGameInterface::handlePacket(): TODO");
}
