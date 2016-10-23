#include "ServerGameInterface.hpp"

#include <misc/Global.hpp>
#include <network/packets/ActionsUpdatePacket.hpp>
#include <network/packets/GameUpdatePacket.hpp>
#include <player/GamePlayer.hpp>

static const int MAX_UPDATE_COUNTER = 30;

ServerGameInterface::ServerGameInterface(LobbyTileMap* map, const std::vector<LobbyPlayer*>& players)
	: GameInterface(map, players), updateCounter(MAX_UPDATE_COUNTER)
{}

ServerGameInterface::~ServerGameInterface()
{}

void ServerGameInterface::handlePacket(Packet* packet, sf::IpAddress* ip)
{
	switch (packet->getCompressID())
	{
		case ACTIONS_UPDATE_PACKET_CID:
		{
			ActionsUpdatePacket* actionsPacket = dynamic_cast<ActionsUpdatePacket*>(packet);
			int id = ipToID(ip);
			players[id]->setActions(actionsPacket->getActions());
			updateCounter = 0;
			break;
		}
		default:
		{
			Debug::error("ServerGameInterface::handlePacket(): unknown Packet with CompressID=" + Converter::intToString((int) packet->getCompressID()));
		}
	}
	delete packet;
}

void ServerGameInterface::tick()
{
	GameInterface::tick();
	Actions a = calcActions();
	if (getLocalPlayer()->getActions() != a)
	{
		getLocalPlayer()->setActions(a);
		updateCounter = 0;
	}

	if (updateCounter-- <= 0)
	{
		updateClients();
	}
}

GamePlayer* ServerGameInterface::getLocalPlayer() const
{
	return players[0];
}

void ServerGameInterface::updateClients()
{
	updateCounter = MAX_UPDATE_COUNTER;
	GameUpdatePacket packet(players, mobs, idlers);
	for (unsigned int i = 1 /* player ignores itself ... sad */; i < players.size(); ++i)
	{
		send(&packet, players[i]->getIP());
	}
}

