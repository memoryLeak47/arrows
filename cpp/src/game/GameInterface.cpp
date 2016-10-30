#include "GameInterface.hpp"

#include <core/Main.hpp>
#include <misc/Global.hpp>
#include <player/GamePlayer.hpp>
#include <player/LobbyPlayer.hpp>
#include <collision/CollisionDetector.hpp>
#include <collision/CollisionTester.hpp>
#include <collision/PhysicsHandler.hpp>
#include <avatar/LobbyAvatar.hpp>
#include <tilemap/GameTileMap.hpp>
#include <collision/CollisionEvent.hpp>
#include <entity/Tile.hpp>
#include <math/game/GameRect.hpp>

#include <network/packets/TeamPacket.hpp>
#include <network/packets/LoginPacket.hpp>
#include <network/packets/AvatarPacket.hpp>
#include <network/packets/SkillPacket.hpp>
#include <network/packets/ItemPacket.hpp>

#include <entity/TestKiste.hpp>

static const int LOOP_LIMIT = 30;
static const float FREQ = 0.2f;

GameInterface::GameInterface(LobbyTileMap* map, const std::vector<LobbyPlayer*>& lobbyPlayers)
	: restrictedGameInterface(this)
{
	Debug::note("------------ [ GAME ON ] ------------");
	tileMap = new GameTileMap(map);
	for (unsigned int i = 0; i < lobbyPlayers.size(); i++)
	{
		players.push_back(LobbyAvatar::get(lobbyPlayers[i]->getAvatarPacket()->getAvatarID())->createGamePlayer(
			getGameTileMap()->teamToSpawnPosition(lobbyPlayers[i]->getTeamPacket()->getTeam()), lobbyPlayers[i], &restrictedGameInterface));
	}

	//idlers.push_back(new TestKiste(GameVector(7.5f, 4.5f)));
	//idlers.push_back(new TestKiste(GameVector(7.5f, 3.5f)));
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
	struct X {
		X(GameInterface* gi)
		{
			gi->view.setEntity(gi->getLocalPlayer());
			gi->view.changeFocus();
		}
	};
	static X x(this);

	Debug::tickConsole();
	Menu::tick();
	NetworkInterface::handleAllPackets();
	tickEntities();
	tickPhysics();
}

int GameInterface::ipToID(sf::IpAddress* ip) const
{
	if (ip == nullptr)
	{
		Debug::error("GameInterface::ipToID(): ip == nullptr");
	}

	for (unsigned int i = 0; i < players.size(); i++)
	{
		if (players[i]->getIP() == nullptr)
		{
			Debug::error("GameInterface::ipToID(): ip of player(" + Converter::intToString(i) + ") is nullptr");
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

void GameInterface::tickEntities()
{
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
				if (t1.time >= t2.time && t1.time >= t3.time) return t1;
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
		return nullptr;
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
			std::vector<Tile*> intersectionTiles = getGameTileMap()->getIntersectionTiles(e1->getWrapper(timeLeft));
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

Actions GameInterface::calcActions() const
{
	Actions actions;
	// movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		setAction(&actions, GO_LEFT, true);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		setAction(&actions, GO_RIGHT, true);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		setAction(&actions, JUMP, true);
	}

	// skills
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		setAction(&actions, SKILL0, true);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		setAction(&actions, SKILL1, true);
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		setAction(&actions, SKILL2, true);
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
	{
		setAction(&actions, SKILL3, true);
	}
	return actions;
}

const View& GameInterface::getView() const
{
	return view;
}

DynamicEntity* GameInterface::getDynamicEntity(unsigned int id)
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
				// and then cosmetics
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
	Debug::error("GameInterface::getImpactfulDynamic(" + Converter::intToString(id) + "): id kinda out of range");
	return nullptr;
}

unsigned int GameInterface::getDynamicEntityAmount()
{
	return mobs.size() + /* bullets.size() +*/ players.size() + idlers.size() /*+ cosmetics.size() */;
}
