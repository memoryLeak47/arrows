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
	// should be an ActionsUpdatePacket
	switch (packet->getCID())
	{
		case ACTIONS_UPDATE_PACKET_CID:
		{
			ActionsUpdatePacket* actionsPacket = dynamic_cast<ActionsUpdatePacket*>(packet);
			players[ipToID(ipAddress)]->setActions(actionsPacket->getActions());
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
	Packet* packet = new ActionsUpdatePacket(getLocalPlayer()->getActions());
	send(packet, serverIP);
	delete packet;
}
