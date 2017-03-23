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

void ServerGameInterface::handlePacket(Packet* packet, const sf::IpAddress& ip)
{
	switch (packet->getCompressID())
	{
		case CompressIDs::CHANGE_ACTIONS_PACKET:
		{
			ChangeActionsPacket* cap = packet->unwrap<ChangeActionsPacket>();
			int id = ipToID(ip);

			addForeignCalendarEntry(cap->getFrameNumber(), id, cap->getActions());

			PacketWithID pwid(cap, id);
			for (unsigned int i = 1; i < mainFrame->players.size(); i++)
			{
				if ((int) i != id)
				{
					send(&pwid, mainFrame->players[i]->getIP());
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

void ServerGameInterface::subTick()
{
	Actions a = calcActions();
	if (getLocalPlayer()->getActions() != a)
	{
		addOwnCalendarEntry(getFrameCounter(), a);
		ChangeActionsPacket* p = new ChangeActionsPacket(a, getFrameCounter());
		PacketWithID pwid(p, 0);

		for (unsigned int i = 1; i < mainFrame->players.size(); i++)
		{
			send(&pwid, mainFrame->players[i]->getIP());
		}
		delete p;
	}
	handleAllPackets();

	applyCalendar();

	mainFrame->tick();
}

unsigned int ServerGameInterface::getLocalPlayerID() const
{
	return 0;
}
