#include "ServerGameInterface.hpp"

#include <misc/Global.hpp>
#include <network/packets/ChangeActionsPacket.hpp>
#include <network/packets/PacketWithID.hpp>
#include <player/GamePlayer.hpp>

ServerGameInterface::ServerGameInterface(LobbyTileMap* map, const std::vector<LobbyPlayer*>& players)
	: GameInterface(map, players)
{}

ServerGameInterface::~ServerGameInterface()
{}

void ServerGameInterface::handlePacket(Packet* packet, sf::IpAddress* ip)
{
	switch (packet->getCompressID())
	{
		case CHANGE_ACTIONS_PACKET_CID:
		{
			ChangeActionsPacket* changePacket = packet->unwrap<ChangeActionsPacket>();
			int id = ipToID(ip);

			// TODO make calendar entry

			PacketWithID* pwi = new PacketWithID(changePacket, id);
			for (unsigned int i = 1; i < players.size(); i++)
			{
				send(pwi, players[i]->getIP());
			}
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
		// TODO make calendar entry
		ChangeActionsPacket* changePacket = new ChangeActionsPacket(a);

		PacketWithID* pwi = new PacketWithID(changePacket, 0);
		for (unsigned int i = 1; i < players.size(); i++)
		{
			send(pwi, players[i]->getIP());
		}
	}
	handleAllPackets();

	// TODO cal

	tickEntities();
	tickPhysics();
}

GamePlayer* ServerGameInterface::getLocalPlayer() const
{
	return players[0];
}
