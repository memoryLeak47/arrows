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
		case ACTIONS_UPDATE_USER_PACKET_CID:
		{
			ActionsUpdateUserPacket* actionsPacket = dynamic_cast<ActionsUpdateUserPacket*>(packet);
			int id = ipToID(ip);
			players[id]->setActions(actionsPacket->getActions());
			updateOtherGamersExceptFor(id);
		}
		default:
		{
			Debug::error("ServerGameInterface::handlePacket(): unknown Packet with CID=" + Converter::intToString((int) packet->getCID()));
		}
	}
}

GamePlayer* ServerGameInterface::getLocalPlayer() const
{
	return players[0];
}

void ServerGameInterface::updateOtherGamers()
{
	UserPacketWithID* packet = new UserPacketWithID(new ActionsUpdateUserPacket(getLocalPlayer()->getActions()), 0);
	for (unsigned int i = 1 /* player ignores itself ... sad */; i < players.size(); ++i)
	{
		send(packet, players[i]->getIP());
	}
	delete packet->getPacket();
	delete packet;
}

void ServerGameInterface::updateOtherGamersExceptFor(int id)
{
	UserPacketWithID* packet = new UserPacketWithID(new ActionsUpdateUserPacket(players[id]->getActions()), id);
	for (unsigned int i = 1 /* player ignores itself ... sad */; i < players.size(); ++i)
	{
		if (i != (unsigned int) id)
		{
			send(packet, players[i]->getIP());
		}
	}
	delete packet->getPacket();
	delete packet;
}
