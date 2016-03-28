#include "ServerGameInterface.hpp"

#include "../misc/Debug.hpp"

ServerGameInterface::ServerGameInterface(LobbyTileMap* map, const std::vector<LobbyPlayer*>& players)
	: GameInterface(map)
{
	for (int i = 0; i < players.size(); i++)
	{
		Debug::warn("ServerGameInterface::ServerGameInterface(): add player HERE, TODO");
	}
}

void ServerGameInterface::handlePacket(Packet*, const sf::IpAddress&)
{
	Debug::warn("ServerGameInterface::handlePacket(): TODO");
}
