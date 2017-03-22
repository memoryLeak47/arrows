#include "ClientGameInterface.hpp"

#include <misc/Global.hpp>
#include <collision/CollisionTester.hpp>
#include <player/GamePlayer.hpp>
#include <entity/Idler.hpp>
#include <entity/Tile.hpp>
#include <tilemap/GameTileMap.hpp>
#include <math/game/GameRect.hpp>
#include <network/packets/ChangeActionsPacket.hpp>
#include <network/packets/PacketWithID.hpp>

ClientGameInterface::ClientGameInterface(LobbyTileMap* map, const std::vector<LobbyPlayer*>& players, int playerID, const sf::IpAddress& ip, long int unixTime_arg)
	: GameInterface(map, players, unixTime_arg), localPlayerID(playerID)
{
	serverIP = ip;
}

ClientGameInterface::~ClientGameInterface()
{}

void ClientGameInterface::handlePacket(Packet* packet, const sf::IpAddress& ipAddress)
{
	if (ipAddress != serverIP) {
		Debug::warn("received packet, not coming from server");
		delete packet;
		return;
	}

	switch (packet->getCompressID())
	{
		case CompressIDs::PACKET_WITH_ID:
		{
			PacketWithID* pwid = packet->unwrap<PacketWithID>();
			switch (pwid->getPacket()->getCompressID())
			{
				case CompressIDs::CHANGE_ACTIONS_PACKET:
				{
					ChangeActionsPacket* cap = pwid->getPacket()->unwrap<ChangeActionsPacket>();
					addCalendarEntry(cap->getFrameNumber(), pwid->getID(), cap->getActions());
					backtrack();
					delete cap;
					break;
				}
				default:
				{
					Debug::error("ClientGameInterface::handlePacket(): unknown Packet (in PacketWithID) with CompressID=" + Converter::intToString((int) pwid->getPacket()->getCompressID()));
				}
			}
			break;
		}
		default:
		{
			Debug::error("ClientGameInterface::handlePacket(): unknown Packet with CompressID=" + Converter::intToString((int) packet->getCompressID()));
		}
	}
	delete packet;
}

void ClientGameInterface::subTick()
{
	handleAllPackets();

	Actions a = calcActions();
	if (serverActionsStatus != a)
	{
		// Send
		serverActionsStatus = a;
		ChangeActionsPacket packet(a, getFrameCounter());
		send(&packet, serverIP);
		// add to Calendar
		addCalendarEntry(getFrameCounter(), localPlayerID, a);
	}

	applyCalendar();

	mainFrame->tick();
}

GamePlayer* ClientGameInterface::getLocalPlayer() const
{
	return mainFrame->players[localPlayerID];
}
