#include "GameInterface.hpp"

#include "../core/Main.hpp"
#include "../misc/Global.hpp"
#include "../player/GamePlayer.hpp"
#include "../collision/CollisionDetector.hpp"
#include "../collision/PhysicsHandler.hpp"

#include "../entity/TestKiste.hpp"

GameInterface::GameInterface(LobbyTileMap* map, const std::vector<LobbyPlayer*>& lobbyPlayers)
{
	tileMap = new GameTileMap(map);
	for (unsigned int i = 0; i < lobbyPlayers.size(); i++)
	{
		Debug::warn("GameInterface::GameInterface(): players in mobs?");
		mobs.push_back(Avatar::get(lobbyPlayers[i]->getAvatarUserPacket()->getAvatarID())->createGamePlayer(getGameTileMap()->teamToSpawnPosition(lobbyPlayers[i]->getTeamUserPacket()->getTeam()), lobbyPlayers[i]));
	}

	mobs.push_back(new TestKiste(GameVector(9.f, 1.5f)));
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
	Debug::tickConsole();
	NetworkingMenu::tick();
	tickEntities();
	removeOutdatedCollisionPartners();
	checkGlitch();
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
	{
		view.setEntity(getLocalPlayer()); // TODO NOT NICE OF YOU ..
		view.changeFocus();
	}
}

void GameInterface::tickEntities()
{
	controlLocalPlayer();
	for (unsigned int i = 0; i < getDynamicEntityAmount(); i++)
	{
		Entity* entity = getDynamicEntity(i);
		entity->tick();
		/* // Security system
		for (Entity* partner : entity->getCollisionPartners())
		{
			entity->addSpeed((entity->getBody()->getPosition() - partner->getBody()->getPosition()) * 0.001f);
		}
		*/
		entity->setChanged(true);
	}
	// TODO tick tiles?
}

void GameInterface::tickPhysics()
{
	int c = 0;
	Debug::funcOn("GameInterface::tickPhysics()");
	float timeLeft = global::GAME_FRAME_TIME;
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


		if (not Entity::areCollisionPartners(event->getEntity1(), event->getEntity2()))
		{
			event->getEntity1()->addCollisionPartner(event->getEntity2());
			event->getEntity2()->addCollisionPartner(event->getEntity1());
		}
		PhysicsHandler::handlePhysics(event->getEntity1(), event->getEntity2());
		c++;
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
		if (c > 100)
		{
			Debug::error("GameInterface::tickPhysics(): infinite loop");
			break;
		}
	}
	moveAllEntities(timeLeft);
	Debug::funcOff("GameInterface::tickPhysics()");
}

CollisionEvent* GameInterface::cutFirstEvent(std::vector<CollisionEvent*>* events)
{
	int bigIndex = 0;
	for (unsigned int i = 1; i < events->size(); i++)
	{
		if (events->at(bigIndex)->getTimeUntilFrameEnds() < events->at(i)->getTimeUntilFrameEnds())
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
	Debug::func("GameInterface::updateEventsFrom(" + entity->toString() + ")");
	for (unsigned int i = 0; i < events->size(); i++)
	{
		CollisionEvent* e = events->at(i);
		if (e->getEntity1() == entity || e->getEntity2() == entity)
		{
			events->erase(events->begin() + i);
			deleteAndNULL(e);
			i--;
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

void GameInterface::removeOutdatedCollisionPartners()
{
	for (unsigned int i = 0; i < getDynamicEntityAmount(); i++)
	{
		getDynamicEntity(i)->removeOutdatedCollisionPartners();
	}
}

void GameInterface::checkGlitch()
{
	for (unsigned int i = 0; i < getDynamicEntityAmount(); i++)
	{
		getDynamicEntity(i)->checkGlitch();
	}
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
	Debug::renderConsole();
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
