#include "ServerGameInterface.hpp"

#include <misc/Debug.hpp>
#include <network/packets/GameUpdatePacket.hpp>

static const int MAX_UPDATE_COUNTER = 30;

ServerGameInterface::ServerGameInterface(LobbyTileMap* map, const std::vector<LobbyPlayer*>& players)
	: GameInterface(map, players), updateCounter(MAX_UPDATE_COUNTER)
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
			delete actionsPacket;

			updateCounter = 0;

			break;
		}
		default:
			Debug::error("ServerGameInterface::handlePacket(): unknown Packet with CID=" + Converter::intToString((int) packet->getCID()));
	}
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

