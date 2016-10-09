#include "GameInterface.hpp"

#include <core/Main.hpp>
#include <misc/Global.hpp>
#include <player/GamePlayer.hpp>
#include <collision/CollisionDetector.hpp>
#include <collision/CollisionTester.hpp>
#include <collision/PhysicsHandler.hpp>

#include <entity/TestKiste.hpp>

static const int LOOP_LIMIT = 30;
static const float FREQ = 0.2f;

GameInterface::GameInterface(LobbyTileMap* map, const std::vector<LobbyPlayer*>& lobbyPlayers)
{
	tileMap = new GameTileMap(map);
	for (unsigned int i = 0; i < lobbyPlayers.size(); i++)
	{
		players.push_back(Avatar::get(lobbyPlayers[i]->getAvatarUserPacket()->getAvatarID())->createGamePlayer(getGameTileMap()->teamToSpawnPosition(lobbyPlayers[i]->getTeamUserPacket()->getTeam()), lobbyPlayers[i]));
	}

	idlers.push_back(new TestKiste(GameVector(7.5f, 4.5f)));
	idlers.push_back(new TestKiste(GameVector(7.5f, 3.5f)));
}

GameInterface::~GameInterface()
{
	delete tileMap;
	deleteAndClearVector(players);
	deleteAndClearVector(idlers);
	deleteAndClearVector(mobs);
	deleteAndClearVector(tiles);
	//deleteAndClearVector(bullets);
}

void GameInterface::tick()
{
	Debug::tickConsole();
	Menu::tick();
	NetworkInterface::handleAllPackets();
	controlLocalPlayer();
	tickEntities();
	tickPhysics();
}

int GameInterface::ipToID(sf::IpAddress* ip) const
{
	if (ip == NULL)
	{
		Debug::error("GameInterface::ipToID(): ip == NULL");
	}

	for (unsigned int i = 0; i < players.size(); i++)
	{
		if (players[i]->getIP() == NULL)
		{
			Debug::error("GameInterface::ipToID(): ip of player(" + Converter::intToString(i) + ") is NULL");
		}

		if (players[i] == getLocalPlayer())
			continue;

		if (*players[i]->getIP() == *ip)
		{
			return i;
		}
	}
	Debug::error("GameInterface::ipToID(): failed");
	return -1;
}

void GameInterface::controlLocalPlayer()
{
	if (getLocalPlayer()->updateActions())
	{
		updateOtherGamers();
	}
}

void GameInterface::tickEntities()
{
	controlLocalPlayer();
	for (unsigned int i = 0; i < getDynamicEntityAmount(); i++)
	{
		Entity* entity = getDynamicEntity(i);
		entity->tick();
		entity->setChanged(true); // wichtig für tickPhysics()
	}
	// TODO tick tiles?
}

void GameInterface::tickPhysics()
{
	Debug::funcOn("GameInterface::tickPhysics()");

	int c = 0;
	int checkCounter = 1;
	float timeLeft = global::GAME_FRAME_TIME;
	std::vector<CollisionEvent*> events;

	updateChanged(&events, timeLeft);

	while (true)
	{
		enum Id {CHECK, END, EVENT};
		struct TimeStruct
		{
			static TimeStruct getFirst(TimeStruct t1, TimeStruct t2, TimeStruct t3)
			{
				if (t1.time >= t2.time && t1.time >= t3.time) return t1; /* XXX not sure about this */
				if (t2.time >= t3.time && t2.time >= t1.time) return t2;
				return t3;
			}
			Id id;
			float time; /* until frame ends */
		};

		float eventTime = -1.f;
		if (events.size() > 0)
		{
			eventTime = events[0]->getTimeUntilFrameEnds();
		}

		// suche ersten Zeitpunkt, um dann zu ihm zu gehen
		TimeStruct first = TimeStruct::getFirst({CHECK, global::GAME_FRAME_TIME-(checkCounter*FREQ)}, {END, 0}, {EVENT, eventTime});
		moveAllEntities(timeLeft - first.time); // bewege die Entities um die Zeitänderung
		timeLeft = first.time;
		switch (first.id)
		{
			case CHECK:
				checkCounter++;
				for (unsigned int i = 0; i < getDynamicEntityAmount(); ++i)
				{
					getDynamicEntity(i)->checkWrapperPartners();
				}
				updateChanged(&events, timeLeft);
				break;
			case END:
				Debug::funcOff("GameInterface::tickPhysics()");
				return;
			case EVENT:
				if (events.size() == 0)
				{
					Debug::error("GameInterface::tickPhysics(): events.size() == 0");
					return;
				}
				// add Wrapper Partners
				if (Entity::areWrapperPartners(events[0]->getEntity1(), events[0]->getEntity2()))
				{
					Debug::warn("collision detected between wrapper partners:\n\t" + events[0]->getEntity1()->toString() + "\n\t" + events[0]->getEntity2()->toString());
				}
				else
				{
					events[0]->getEntity1()->addWrapperPartner(events[0]->getEntity2());
					events[0]->getEntity2()->addWrapperPartner(events[0]->getEntity1());
				}

				events[0]->getEntity1()->setChanged(true);
				events[0]->getEntity2()->setChanged(true);

				removeEventsBetween(events[0]->getEntity1(), events[0]->getEntity2(), &events);
		}

		if (c++ > LOOP_LIMIT)
		{
			Debug::error("GameInterface::tickPhysics(): infinite loop");
			break;
		}
	}
}

CollisionEvent* GameInterface::cutFirstEvent(std::vector<CollisionEvent*>* events)
{
	if (events->empty())
	{
		Debug::error("GameInterface::cutFirstEvent(): no more events");
		return NULL;
	}

	auto big = events->begin();
	for (auto i = events->begin()+1; i != events->end(); i++)
	{
		if ((*big)->getTimeUntilFrameEnds() < (*i)->getTimeUntilFrameEnds())
		{
			big = i;
		}
	}
	CollisionEvent* ret = *big;
	events->erase(big);
	return ret;
}

void GameInterface::moveAllEntities(float time)
{
	Debug::func("GameInterface::moveAllEntities(" + Converter::floatToString(time) + ")");
	if (time <= 0)
	{
		if (time < 0) Debug::error("GameInterface::moveAllEntities(" + Converter::floatToString(time) + "): arg is negative");
		return;
	}

	for (unsigned int i = 0; i < getDynamicEntityAmount(); i++)
	{
		getDynamicEntity(i)->move(time);
	}
}

void GameInterface::updateChanged(std::vector<CollisionEvent*>* events, float timeLeft)
{
	if (timeLeft < 0)
	{
		Debug::error("GameInterface::updateChanged(..., " + Converter::floatToString(timeLeft) + "): timeLeft is negative");
		return;
	}

	for (unsigned int i = 0; i < getDynamicEntityAmount(); i++)
	{
		Entity* e1 = getDynamicEntity(i);
		for (unsigned int j = i+1; j < getDynamicEntityAmount(); j++)
		{
			Entity* e2 = getDynamicEntity(j);
			if (Entity::areWrapperPartners(e1, e2)) continue;
			if (e1->hasChanged() || e2->hasChanged())
			{
				update(e1, e2, events, timeLeft);
			}
		}
		if (e1->hasChanged())
		{
			std::vector<Tile*> intersectionTiles = getGameTileMap()->getIntersectionTiles(e1->getBody()->getWrapper(timeLeft));
			for (auto iter = intersectionTiles.begin(); iter != intersectionTiles.end(); ++iter)
			{
				if (Entity::areWrapperPartners(e1, *iter)) continue;
				update(e1, *iter, events, timeLeft);
			}
		}
	}

	for (unsigned int i = 0; i < getDynamicEntityAmount(); i++)
	{
		getDynamicEntity(i)->setChanged(false);
	}
}

void GameInterface::update(Entity* e1, Entity* e2, std::vector<CollisionEvent*>* events, float timeLeft)
{
	if (Entity::areWrapperPartners(e1, e2))
	{
		Debug::warn(std::string(__PRETTY_FUNCTION__) + " called for Wrapper partners:\n\t" + e1->toString() + "\n\t" + e2->toString());
	}
	else
	{
		removeEventsBetween(e1, e2, events);
		addEventsBetween(e1, e2, events, timeLeft);
	}
}

void GameInterface::addEventsBetween(Entity* e1, Entity* e2, std::vector<CollisionEvent*>* events, float timeLeft)
{
	if (e1->getCollisionPriority(e2) + e2->getCollisionPriority(e1) > 0)
	{
		CollisionDetector::addCollisionsBetween(e1, e2, events, timeLeft);
	}
}

void GameInterface::removeEventsBetween(Entity* e1, Entity* e2, std::vector<CollisionEvent*>* events)
{
	for (unsigned int i = 0; i < events->size(); i++)
	{
		Entity* f1 = events->at(i)->getEntity1();
		Entity* f2 = events->at(i)->getEntity2();
		if ((f1 == e1 and f2 == e2) or (f1 == e2 and f2 == e1))
		{
			CollisionEvent* event = events->at(i);
			events->erase(events->begin() + i--);
			delete event;
		}
	}
}

void GameInterface::render() const
{
	renderMap();
	renderBars();
	renderEntities();
	Menu::render();
	Debug::renderConsole();
}

void GameInterface::renderMap() const
{
	getGameTileMap()->render(getView());
}

void GameInterface::renderBars() const
{
	for (unsigned int i = 0; i < players.size(); i++)
	{
		players[i]->renderBar(getView());
	}

	for (unsigned int i = 0; i < mobs.size(); i++)
	{
		mobs[i]->renderBar(getView());
	}
}

void GameInterface::renderEntities() const
{
	for (unsigned int i = 0; i < players.size(); i++)
	{
		players[i]->render(getView());
	}
	for (unsigned int i = 0; i < idlers.size(); i++)
	{
		idlers[i]->render(getView());
	}
	for (unsigned int i = 0; i < mobs.size(); i++)
	{
		mobs[i]->render(getView());
	}
	/*
	for (unsigned int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->render(getView());
	}
	*/
}

GameTileMap* GameInterface::getGameTileMap() const
{
	return tileMap;
}

const View& GameInterface::getView() const
{
	return view;
}

Entity* GameInterface::getDynamicEntity(unsigned int id)
{
	if (id >= players.size())
	{
		id -= players.size();
		if (id >= mobs.size())
		{
			id -= mobs.size();
			if (id >= idlers.size())
			{
				// id -= idlers.size();
				// return bullets[id];
			}
			else
			{
				return idlers[id];
			}
		}
		else
		{
			return mobs[id];
		}
	}
	else
	{
		return players[id];
	}
	Debug::error("GameInterface::getDynamicEntity(" + Converter::intToString(id) + "): id kinda out of range");
	return NULL;
}

unsigned int GameInterface::getDynamicEntityAmount()
{
	return mobs.size() + /*bullets.size() +*/ players.size() + idlers.size();
}
