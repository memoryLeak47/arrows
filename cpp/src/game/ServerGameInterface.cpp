#include "ServerGameInterface.hpp"

#include <misc/Global.hpp>
#include <network/packets/ChangeActionsPacket.hpp>
#include <network/packets/ChangeActionsResponsePacket.hpp>
#include <player/GamePlayer.hpp>

constexpr int ACTIONS_FRAME_OFFSET = 2;

ServerGameInterface::ServerGameInterface(LobbyTileMap* map, const std::vector<LobbyPlayer*>& players, long int startTime_arg)
	: GameInterface(map, players, startTime_arg)
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

			calendar.addEntry(frameCounter + ACTIONS_FRAME_OFFSET, id, changePacket->getActions());

			ChangeActionsResponsePacket *carp = new ChangeActionsResponsePacket(frameCounter + ACTIONS_FRAME_OFFSET, id, changePacket->getActions());
			for (unsigned int i = 1; i < mainFrame.players.size(); i++)
			{
				send(carp, mainFrame.players[i]->getIP());
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
	if (startTime > global::unix_millis())
	{
		return;
	}
	GameInterface::tick();

	Actions a = calcActions();
	if (getLocalPlayer()->getActions() != a)
	{
		calendar.addEntry(frameCounter + ACTIONS_FRAME_OFFSET, 0, a);
		ChangeActionsResponsePacket* p = new ChangeActionsResponsePacket(frameCounter + ACTIONS_FRAME_OFFSET, 0, a);

		for (unsigned int i = 1; i < mainFrame.players.size(); i++)
		{
			send(p, mainFrame.players[i]->getIP());
		}
		delete p;
	}
	handleAllPackets();

	applyCalendar();

	mainFrame.tickEntities();
	mainFrame.tickPhysics();
}

GamePlayer* ServerGameInterface::getLocalPlayer() const
{
	return mainFrame.players[0];
}
