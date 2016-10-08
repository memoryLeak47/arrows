#include "ClientGameInterface.hpp"

#include <misc/Debug.hpp>

ClientGameInterface::ClientGameInterface(LobbyTileMap* map, const std::vector<LobbyPlayer*>& players, int playerID, sf::IpAddress* ip)
	: GameInterface(map, players), localPlayerID(playerID)
{
	serverIP = new sf::IpAddress(*ip);
}

ClientGameInterface::~ClientGameInterface()
{
	delete serverIP;
}

void ClientGameInterface::handlePacket(Packet* packet, sf::IpAddress* ipAddress)
{
	// should be an ActionsUpdateUserPacket
	switch (packet->getCID())
	{
		case USER_PACKET_WITH_ID_CID:
		{
			UserPacketWithID* packetWithID = dynamic_cast<UserPacketWithID*>(packet);
			switch (packetWithID->getPacket()->getCID())
			{
				case ACTIONS_UPDATE_USER_PACKET_CID:
				{
					ActionsUpdateUserPacket* actionsPacket = dynamic_cast<ActionsUpdateUserPacket*>(packetWithID->getPacket());
					players[packetWithID->getID()]->setActions(actionsPacket->getActions());
					break;
				}
				default:
				{
					Debug::error("ClientGameInterface::handlePacket(): UserPacketWithID with unknown UserPacket with CID=" + Converter::intToString((int) packetWithID->getPacket()->getCID()));
				}
			}
			break;
		}
		default:
		{
			Debug::error("ClientGameInterface::handlePacket(): unknown Packet with CID=" + Converter::intToString((int) packet->getCID()));
		}
	}
}

GamePlayer* ClientGameInterface::getLocalPlayer() const
{
	return players[localPlayerID];
}

void ClientGameInterface::updateOtherGamers()
{
	Packet* packet = new ActionsUpdateUserPacket(getLocalPlayer()->getActions());
	send(packet, serverIP);
	delete packet;
}
