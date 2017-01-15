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

ClientGameInterface::ClientGameInterface(LobbyTileMap* map, const std::vector<LobbyPlayer*>& players, int playerID, sf::IpAddress* ip, long int unixTime_arg)
	: GameInterface(map, players, unixTime_arg), localPlayerID(playerID)
{
	serverIP = new sf::IpAddress(*ip);
}

ClientGameInterface::~ClientGameInterface()
{
	delete serverIP;
}

void ClientGameInterface::handlePacket(Packet* packet, sf::IpAddress* ipAddress)
{
	switch (packet->getCompressID())
	{
		case PACKET_WITH_ID_CID:
		{
			PacketWithID* pwid = packet->unwrap<PacketWithID>();
			switch (pwid->getPacket()->getCompressID())
			{
				case CHANGE_ACTIONS_PACKET_CID:
				{
					ChangeActionsPacket* cap = packet->unwrap<ChangeActionsPacket>();
					calendar.addEntry(cap->getFrameNumber(), pwid->getID(), cap->getActions());
					// TODO maybe call backtracking thread
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

void ClientGameInterface::tick()
{
	if (startTime > global::unix_millis())
	{
		return;
	}
	GameInterface::tick();

	handleAllPackets();

	applyCalendar();

	mainFrame.tickEntities();
	mainFrame.tickPhysics();

	Actions a = calcActions();
	if (serverActionsStatus != a)
	{
		serverActionsStatus = a;
		ChangeActionsPacket packet(a, frameCounter);
		send(&packet, serverIP);
	}
}

GamePlayer* ClientGameInterface::getLocalPlayer() const
{
	return mainFrame.players[localPlayerID];
}
