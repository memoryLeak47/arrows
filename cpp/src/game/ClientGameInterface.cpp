#include "ClientGameInterface.hpp"

#include <misc/Debug.hpp>
#include <network/packets/GameUpdatePacket.hpp>

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
		case GAME_UPDATE_PACKET_CID:
		{
			GameUpdatePacket* gamePacket = dynamic_cast<GameUpdatePacket*>(packet);
			applyGameUpdate(gamePacket->getPlayers(), gamePacket->getMobs(), gamePacket->getIdlers());
			break;
		}
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

void ClientGameInterface::applyGameUpdate(const std::vector<GamePlayer*>& players_arg, const std::vector<Mob*>& mobs_arg, const std::vector<Idler*>& idlers_arg)
{
	// players
	if (players.size() != players_arg.size())
	{
		Debug::error("ClientGameInterface::applyGameUpdate(): localPlayerListSize=" + Converter::intToString(players.size()) + " receivedPlayerListSize=" + Converter::intToString(players_arg.size()));
	}

	for (unsigned int i = 0; i < players.size(); i++)
	{
		players[i]->apply(players_arg[i]);
	}

	// mobs
	if (mobs.size() != mobs_arg.size())
	{
		Debug::warn("ClientGameInterface::applyGameUpdate(): localMobListSize=" + Converter::intToString(mobs.size()) + " receivedMobListSize=" + Converter::intToString(mobs_arg.size()));
	}
	deleteAndClearVector(mobs);
	for (unsigned int i = 0; i < mobs_arg.size(); i++)
	{
		mobs.push_back(mobs_arg[i]);
	}

	// idlers
	if (idlers.size() != idlers_arg.size())
	{
		Debug::warn("ClientGameInterface::applyGameUpdate(): localIdlerListSize=" + Converter::intToString(idlers.size()) + " receivedIdlerListSize=" + Converter::intToString(idlers_arg.size()));
	}
	deleteAndClearVector(idlers);
	for (unsigned int i = 0; i < idlers_arg.size(); i++)
	{
		idlers.push_back(idlers_arg[i]);
	}

	for (unsigned int i = 0; i < getDynamicEntityAmount(); i++)
	{
		getDynamicEntity(i)->updatePartners();
	}
}
