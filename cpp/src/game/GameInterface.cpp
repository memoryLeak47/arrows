#include "GameInterface.hpp"

#include "../core/Main.hpp"
#include "../misc/Debug.hpp"
#include "../player/GamePlayer.hpp"
#include "../collision/CollisionHandler.hpp"

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

void GameInterface::tickEntities()
{
	for (unsigned int i = 0; i < mobs.size(); i++)
	{
		mobs[i]->tick();
	}
	// TODO tick tiles?
	for (unsigned int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->tick();
	}
}

void GameInterface::tickPhysics()
{
	float timeLeft = GAME_FRAME_TIME;
	std::vector<CollisionEvent*> events; // Es gäbe auch die Möglichkeit diesen vector global zu machen & länger als nur GAME_FRAME_TIME vorauszuber

	// fügt alle CollisionEvents in die TickPhysics-Liste
	/*
	// TODO
	for entity in dynamicEntities
	{
		entity->addEventsFrom(entity, &events, timeLeft);
		entity->hasChanged = false;
	}
	*/

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
		/*
		// TODO
		for entity in dynamic-entity:
		{
			if (entity->hasChanged())
			{
				updateEventsFrom(entity, &events, timeLeft);
				entity->setChanged(false);
			}
		}
		*/
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
                        events->erase(events->begin() + i);
                        // TODO delete?
                }
        }
        addEventsFrom(entity, events, timeLeft);
}

void GameInterface::addEventsFrom(Entity* entity, std::vector<CollisionEvent*>* events, float timeLeft)
{
        // alle Entities durchgehen
	/*
	// TODO
        for (e in entities)
        {
                if (priority-check && e != entity)
                {
                        CollisionDetector::addCollisionsBetween(entity, e, timeLeft, events);
                }
        }
	*/
}

void GameInterface::moveAllEntities(float time)
{
	Debug::warn("GameInterface::moveAllEntities: TODO");
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
