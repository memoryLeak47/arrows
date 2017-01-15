#include "ServerGameInterface.hpp"

#include <misc/Global.hpp>
#include <network/packets/ChangeActionsPacket.hpp>
#include <network/packets/PacketWithID.hpp>
#include <player/GamePlayer.hpp>

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
			ChangeActionsPacket* cap = packet->unwrap<ChangeActionsPacket>();
			int id = ipToID(ip);

			calendar.addEntry(cap->getFrameNumber(), id, cap->getActions());
			// TODO maybe call backtracking thread

			PacketWithID pwid(cap, id);
			for (unsigned int i = 1; i < mainFrame.players.size(); i++)
			{
				send(&pwid, mainFrame.players[i]->getIP());
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
		calendar.addEntry(frameCounter, 0, a);
		ChangeActionsPacket* p = new ChangeActionsPacket(frameCounter, a);
		PacketWithID pwid(p, 0);

		for (unsigned int i = 1; i < mainFrame.players.size(); i++)
		{
			send(&pwid, mainFrame.players[i]->getIP());
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
