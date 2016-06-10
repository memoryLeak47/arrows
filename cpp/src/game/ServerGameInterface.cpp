#include "ServerGameInterface.hpp"

#include "../misc/Debug.hpp"

ServerGameInterface::ServerGameInterface(LobbyTileMap* map, const std::vector<LobbyPlayer*>& players)
	: GameInterface(map, players)
{}

ServerGameInterface::~ServerGameInterface()
{}

void ServerGameInterface::handlePacket(Packet*, sf::IpAddress*)
{
	Debug::warn("ServerGameInterface::handlePacket(): TODO");
}

GamePlayer* ServerGameInterface::getLocalPlayer() const
{
	return dynamic_cast<GamePlayer*>(mobs[0]);
}
