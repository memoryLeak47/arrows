#include "ServerGameInterface.hpp"

#include <misc/Debug.hpp>

ServerGameInterface::ServerGameInterface(LobbyTileMap* map, const std::vector<LobbyPlayer*>& players)
	: GameInterface(map, players)
{}

ServerGameInterface::~ServerGameInterface()
{}

void ServerGameInterface::handlePacket(Packet* packet, sf::IpAddress* ip)
{
	switch (packet->getCID())
	{
		case ACTIONS_UPDATE_PACKET_CID:
		{
			ActionsUpdatePacket* actionsPacket = dynamic_cast<ActionsUpdatePacket*>(packet);
			int id = ipToID(ip);
			players[id]->setActions(actionsPacket->getActions());
			updateOtherGamersExceptFor(id);
		}
		default:
		{
			Debug::error("ServerGameInterface::handlePacket(): whats that?");
		}
	}
}

GamePlayer* ServerGameInterface::getLocalPlayer() const
{
	return players[0];
}

void ServerGameInterface::updateOtherGamers()
{
	Packet* packet = new ActionsUpdatePacket(getLocalPlayer()->getActions());
	for (unsigned int i = 1 /* player ignores itself ... sad */; i < players.size(); ++i)
	{
		send(packet, players[i]->getIP());
	}
	delete packet;
}

void ServerGameInterface::updateOtherGamersExceptFor(int id)
{
	Packet* packet = new ActionsUpdatePacket(players[id]->getActions());
	for (unsigned int i = 1 /* player ignores itself ... sad */; i < players.size(); ++i)
	{
		if (i != (unsigned int) id)
		{
			send(packet, players[i]->getIP());
		}
	}
	delete packet;
}
