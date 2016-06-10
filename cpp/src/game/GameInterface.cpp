#include "GameInterface.hpp"

#include "../core/Main.hpp"
#include "../misc/Converter.hpp"
#include "../misc/Debug.hpp"
#include "../player/GamePlayer.hpp"
#include "../collision/CollisionHandler.hpp"
#include "../collision/CollisionDetector.hpp"

GameInterface::GameInterface(LobbyTileMap* map, const std::vector<LobbyPlayer*>& lobbyPlayers)
{
	tileMap = new GameTileMap(map);
	for (unsigned int i = 0; i < lobbyPlayers.size(); i++)
	{
		Debug::warn("GameInterface::GameInterface(): players in mobs?");
		mobs.push_back(Avatar::get(lobbyPlayers[i]->getAvatarUserPacket()->getAvatarID())->createGamePlayer(getGameTileMap()->teamToSpawnPosition(lobbyPlayers[i]->getTeamUserPacket()->getTeam()), lobbyPlayers[i]));
	}
}

GameInterface::~GameInterface()
{
	delete tileMap;
	deleteAndClearVector(mobs);
	deleteAndClearVector(tiles);
	deleteAndClearVector(bullets);
}

void GameInterface::tick()
{
	NetworkingMenu::tick();
	tickEntities();
	tickPhysics();
}

void GameInterface::controlLocalPlayer()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		getLocalPlayer()->actionGoLeft();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		getLocalPlayer()->actionGoRight();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		getLocalPlayer()->actionJump();
	}
}

void GameInterface::tickEntities()
{
	controlLocalPlayer();
	for (unsigned int i = 0; i < getDynamicEntityAmount(); i++)
	{
		Entity* entity = getDynamicEntity(i);
		entity->tick();
		entity->setChanged(true);
	}
	// TODO tick tiles?
}

void GameInterface::tickPhysics()
{
	float timeLeft = GAME_FRAME_TIME;
	std::vector<CollisionEvent*> events; // Es gäbe auch die Möglichkeit diesen vector global zu machen & länger als nur GAME_FRAME_TIME vorauszuber

	// fügt alle CollisionEvents in die TickPhysics-Liste
	for (unsigned int i = 0; i < getDynamicEntityAmount(); i++)
	{
		Entity* entity = getDynamicEntity(i);
		addEventsFrom(entity, &events, timeLeft);
		entity->setChanged(false);
	}

	while (events.size() > 0)
	{
		CollisionEvent* event = cutFirstEvent(&events); // Returnt die Collision, die als nächstes ausgeführt werden muss.
		moveAllEntities(timeLeft - event->getTimeUntilFrameEnds());     // bewegt alle Entities bis zu der Situation, in der die nächste
						// remember rotation is updated too
		timeLeft = event->getTimeUntilFrameEnds();

		// CollisionPartner aktualisieren / on/offCollide
		if (event->isEnterEvent()) // Hi
		{
			if (! memberOf(event->getEntity2(), event->getEntity1()->getCollisionPartners())) // you are new
			{
				// Partner :D
				event->getEntity1()->addCollisionPartner(event->getEntity2());
				event->getEntity2()->addCollisionPartner(event->getEntity1());
				event->getEntity1()->onCollide(event->getEntity2());
				event->getEntity2()->onCollide(event->getEntity1());
			}
			CollisionHandler::handleCollisionEvent(event);
		}
		else // Bye
		{
			if (memberOf(event->getEntity2(), event->getEntity1()->getCollisionPartners())) // ma old friend
			{
				// Bye
				event->getEntity1()->removeCollisionPartner(event->getEntity2());
				event->getEntity2()->removeCollisionPartner(event->getEntity1());
				event->getEntity1()->offCollide(event->getEntity2());
				event->getEntity2()->offCollide(event->getEntity1());

			}
			else
			{
				Debug::warn("shit");
			}
		}

		delete event;

		// Falls eine der Entities beschleunigt/umpositioniert wurden, werden die Collisions der Entity neu berechnet
		for (unsigned int i = 0; i < getDynamicEntityAmount(); i++)
		{
			Entity* entity = getDynamicEntity(i);
			if (entity->hasChanged())
			{
				updateEventsFrom(entity, &events, timeLeft);
				entity->setChanged(false);
			}
		}
	}
	moveAllEntities(timeLeft);
}

CollisionEvent* GameInterface::cutFirstEvent(std::vector<CollisionEvent*>* events)
{
	int bigIndex = 0;
	for (unsigned int i = 1; i < events->size(); i++)
	{
		if ((*events)[bigIndex]->getTimeUntilFrameEnds() > (*events)[i]->getTimeUntilFrameEnds() ||
		   ((*events)[bigIndex]->getTimeUntilFrameEnds() == (*events)[i]->getTimeUntilFrameEnds() && ! (*events)[bigIndex]->isEnterEvent() && (*events)[bigIndex]->isEnterEvent() && (*events)[i]->isEnterEvent()))
		{
			bigIndex = i;
		}
	}
	CollisionEvent* ret = (*events)[bigIndex];
	events->erase(events->begin() + bigIndex);
	return ret;
}

void GameInterface::updateEventsFrom(Entity* entity, std::vector<CollisionEvent*>* events, float timeLeft)
{
	for (unsigned int i = 0; i < events->size(); i++)
	{
		if ((*events)[i]->getEntity1() == entity || (*events)[i]->getEntity2() == entity)
		{
			CollisionEvent* e = (*events)[i];
			events->erase(events->begin() + i);
			deleteAndNULL(e);
		}
	}
	addEventsFrom(entity, events, timeLeft);
}

void GameInterface::addEventsFrom(Entity* entity, std::vector<CollisionEvent*>* events, float timeLeft)
{
	if (!entity->hasChanged())
	{
		return;
	}

	// find Collision with dynamic entities
	for (unsigned int i = 0; i < getDynamicEntityAmount(); i++)
	{
		Entity* e = getDynamicEntity(i);
								// >= 0
		if (e->getCollisionPriority(entity) + entity->getCollisionPriority(e) > 0 && e != entity)
		{
			CollisionDetector::addCollisionsBetween(entity, e, events, timeLeft);
		}
	}

	// find Collision with static tiles
	const std::vector<Tile*> collisionTiles = getGameTileMap()->getIntersectionTiles(entity->getBody()->getWrapper(timeLeft));
	for (unsigned int i = 0; i < collisionTiles.size(); i++)
	{
		Tile* t = collisionTiles[i];
		if (t->getCollisionPriority(entity) + entity->getCollisionPriority(t) > 0)
		{
			CollisionDetector::addCollisionsBetween(entity, t, events, timeLeft);
		}
	}
}

void GameInterface::moveAllEntities(float time)
{
	if (time == 0)
	{
		return;
	}

	for (unsigned int i = 0; i < getDynamicEntityAmount(); i++)
	{
		getDynamicEntity(i)->getBody()->move(time);
	}
}

void GameInterface::render() const
{
	renderMap();
	renderBars();
	renderEntities();
	NetworkingMenu::render();
}

void GameInterface::renderMap() const
{
	getGameTileMap()->render(getView());
}

void GameInterface::renderBars() const
{
	for (unsigned int i = 0; i < mobs.size(); i++)
	{
		mobs[i]->renderBar(getView());
	}
}

void GameInterface::renderEntities() const
{
	for (unsigned int i = 0; i < mobs.size(); i++)
	{
		mobs[i]->render(getView());
	}
	for (unsigned int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->render(getView());
	}
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
	if (id >= mobs.size())
	{
		id -= mobs.size();
		if (id >= bullets.size())
		{
			// id -= bullets.size();
			// return dynamictiles[id];
		}
		else
		{
			return bullets[id];
		}
	}
	else
	{
		return mobs[id];
	}
	Debug::error("GameInterface::getDynamicEntity(" + Converter::intToString(id) + "): id kinda out of range");
	return NULL;
}

unsigned int GameInterface::getDynamicEntityAmount()
{
	return mobs.size() + bullets.size();
}
