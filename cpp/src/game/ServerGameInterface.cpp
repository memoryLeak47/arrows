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
			if (cap->getFrameNumber() <= frameCounter)
			{
				Debug::warn("ServerGameInterface::handlePacket(): should backtrack " + Converter::intToString(std::abs(cap->getFrameNumber() - frameCounter)) + " frames now");
			}

			PacketWithID pwid(cap, id);
			for (unsigned int i = 1; i < mainFrame.players.size(); i++)
			{
				if ((int) i != id)
				{
					send(&pwid, mainFrame.players[i]->getIP());
				}
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
		ChangeActionsPacket* p = new ChangeActionsPacket(a, frameCounter);
		PacketWithID pwid(p, 0);

		for (unsigned int i = 1; i < mainFrame.players.size(); i++)
		{
			send(&pwid, mainFrame.players[i]->getIP());
		}
		delete p;
	}
	handleAllPackets();

	applyCalendar();

	mainFrame.tick();
}

GamePlayer* ServerGameInterface::getLocalPlayer() const
{
	return mainFrame.players[0];
}
