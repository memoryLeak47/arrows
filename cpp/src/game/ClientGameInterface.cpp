#include "ClientGameInterface.hpp"

#include <collision/CollisionTester.hpp>
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
		default:
		{
			Debug::error("ClientGameInterface::handlePacket(): unknown Packet with CID=" + Converter::intToString((int) packet->getCID()));
		}
	}
}

void ClientGameInterface::tick()
{
	GameInterface::tick();
	Actions a = calcActions();
	if (serverActionsStatus != a)
	{
		serverActionsStatus = a;
		ActionsUpdateUserPacket packet(a);
		send(&packet, serverIP);
	}
}

GamePlayer* ClientGameInterface::getLocalPlayer() const
{
	return players[localPlayerID];
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

	for (unsigned int i = 0; i < players.size(); i++)
	{
		players[i]->wrapperPartners.clear(); // only players clear list, because other entities' lists are new
		players[i]->collisionPartners.clear();
	}

	unsigned int amount = getDynamicEntityAmount();
	for (unsigned int i = 0; i < amount; i++)
	{
		DynamicEntity* e1 = getDynamicEntity(i);

		const std::vector<Tile*> tiles = getGameTileMap()->getIntersectionTiles(e1->getBody()->getWrapper(0.f));
		for (unsigned int j = 0; j < tiles.size(); j++)
		{
			if (e1->getCollisionPriority(tiles[j]) + tiles[j]->getCollisionPriority(e1) <= 0) continue;
			if (CollisionTester::areWrapperColliding(e1, tiles[j]))
			{
				e1->addWrapperPartner(tiles[j]);
				if (CollisionTester::areColliding(e1, tiles[j]))
				{
					e1->addCollisionPartner(tiles[j]);
				}
			}
		}
		
		for (unsigned int j = i+1; j < amount; j++)
		{
			DynamicEntity* e2 = getDynamicEntity(j);
			if (e1->getCollisionPriority(e2) + e2->getCollisionPriority(e1) <= 0) continue;
			if (CollisionTester::areWrapperColliding(e1, e2))
			{
				e1->addWrapperPartner(e2);
				e2->addWrapperPartner(e1);
				if (CollisionTester::areColliding(e1, e2))
				{
					e1->addCollisionPartner(e2);
					e2->addCollisionPartner(e1);
				}
			}
		}
	}
}
