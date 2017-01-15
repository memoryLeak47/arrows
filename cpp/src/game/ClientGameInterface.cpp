#include "ClientGameInterface.hpp"

#include <misc/Global.hpp>
#include <collision/CollisionTester.hpp>
#include <player/GamePlayer.hpp>
#include <entity/Idler.hpp>
#include <entity/Tile.hpp>
#include <tilemap/GameTileMap.hpp>
#include <math/game/GameRect.hpp>
#include <network/packets/ChangeActionsPacket.hpp>
#include <network/packets/ChangeActionsResponsePacket.hpp>

// #include <network/packets/GameUpdatePacket.hpp>

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
		case CHANGE_ACTIONS_RESPONSE_PACKET_CID:
		{
			ChangeActionsResponsePacket* carp = packet->unwrap<ChangeActionsResponsePacket>();
			if (carp->getFrame() < frameCounter)
			{
				Debug::warn("None can change what happened.");
				whatIs(carp->getFrame());
				whatIs(frameCounter);
			}
			else
			{
				calendar.addEntry(carp->getFrame(), carp->getPlayerID(), carp->getActions());
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
		ChangeActionsPacket packet(a);
		send(&packet, serverIP);
	}
}

GamePlayer* ClientGameInterface::getLocalPlayer() const
{
	return mainFrame.players[localPlayerID];
}
