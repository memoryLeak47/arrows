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
	Debug::funcOn("GameInterface::tick");
	NetworkingMenu::tick();
	tickEntities();
	tickPhysics();
	Debug::funcOff("GameInterface::tick");
}

void GameInterface::controlLocalPlayer()
{
	Debug::func("GameInterface::controlLocalPlayer");
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
	{
		view.setEntity(getLocalPlayer()); // TODO NOT NICE OF YOU ..
		view.changeFocus();
	}
}

void GameInterface::tickEntities()
{
	Debug::funcOn("GameInterface::tickEntities");
	controlLocalPlayer();
	for (unsigned int i = 0; i < getDynamicEntityAmount(); i++)
	{
		Entity* entity = getDynamicEntity(i);
		entity->tick();
		entity->setChanged(true);
	}
	// TODO tick tiles?
	Debug::funcOff("GameInterface::tickEntities");
}

void GameInterface::tickPhysics()
{
	Debug::funcOn("GameInterface::tickPhysics");
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
		CollisionHandler::handleCollisionEvent(event);
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
	Debug::funcOff("GameInterface::tickPhysics");
}

CollisionEvent* GameInterface::cutFirstEvent(std::vector<CollisionEvent*>* events)
{
	int bigIndex = 0;
	for (unsigned int i = 1; i < events->size(); i++)
	{
		if (events->at(bigIndex)->getTimeUntilFrameEnds() > events->at(i)->getTimeUntilFrameEnds())
		{
			bigIndex = i;
		}
	}
	CollisionEvent* ret = events->at(bigIndex);
	events->erase(events->begin() + bigIndex);
	return ret;
}

void GameInterface::updateEventsFrom(Entity* entity, std::vector<CollisionEvent*>* events, float timeLeft)
{
	for (unsigned int i = 0; i < events->size(); i++)
	{
		if (events->at(i)->getEntity1() == entity || events->at(i)->getEntity2() == entity)
		{
			CollisionEvent* e = events->at(i);
			events->erase(events->begin() + i);
			deleteAndNULL(e);
		}
	}
	addEventsFrom(entity, events, timeLeft);
}

void GameInterface::addEventsFrom(Entity* entity, std::vector<CollisionEvent*>* events, float timeLeft)
{
	Debug::funcOn("GameInterface::addEventsFrom " + entity->toString());
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
	Debug::funcOff("GameInterface::addEventsFrom " + entity->toString());
}

void GameInterface::moveAllEntities(float time)
{
	Debug::func("GameInterface::moveAllEntities(" + Converter::floatToString(time) + ")");
	if (time == 0)
	{
		return;
	}

	for (unsigned int i = 0; i < getDynamicEntityAmount(); i++)
	{
		getDynamicEntity(i)->move(time);
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
