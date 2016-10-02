#include "GameInterface.hpp"

#include <core/Main.hpp>
#include <misc/Global.hpp>
#include <player/GamePlayer.hpp>
#include <collision/CollisionDetector.hpp>
#include <collision/CollisionTester.hpp>
#include <collision/PhysicsHandler.hpp>

#include <entity/TestKiste.hpp>

const float EXIT_CHECK_BORDER_ADDITION = 0.03f;
const int LOOP_LIMIT = 30;

GameInterface::GameInterface(LobbyTileMap* map, const std::vector<LobbyPlayer*>& lobbyPlayers)
{
	tileMap = new GameTileMap(map);
	for (unsigned int i = 0; i < lobbyPlayers.size(); i++)
	{
		Debug::warn("GameInterface::GameInterface(): players in mobs?");
		mobs.push_back(Avatar::get(lobbyPlayers[i]->getAvatarUserPacket()->getAvatarID())->createGamePlayer(getGameTileMap()->teamToSpawnPosition(lobbyPlayers[i]->getTeamUserPacket()->getTeam()), lobbyPlayers[i]));
	}

	mobs.push_back(new TestKiste(GameVector(9.f, 2.5f)));
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
		entity->setChanged(true); // wichtig für tickPhysics()
	}
	// TODO tick tiles?
}

void GameInterface::tickPhysics()
{
	Debug::funcOn("GameInterface::tickPhysics()");

	int c = 0;
	float timeLeft = global::GAME_FRAME_TIME;
	std::vector<CollisionEvent*> events;

	updateChanged(&events, timeLeft);

	while (events.size() > 0)
	{
		CollisionEvent* event = cutFirstEvent(&events); // Returnt die Collision, die als nächstes ausgeführt werden muss.
		moveAllEntities(timeLeft - event->getTimeUntilFrameEnds());     // bewegt alle Entities bis zu der Situation, in der die nächste
						// remember rotation is updated too
		timeLeft = event->getTimeUntilFrameEnds();

		// add Partners
		if (Entity::areCollisionPartners(event->getEntity1(), event->getEntity2()))
		{
			Debug::warn("collision detected between collision partners");
		}
		else
		{
			event->getEntity1()->addCollisionPartner(event->getEntity2());
			event->getEntity2()->addCollisionPartner(event->getEntity1());
		}

		event->getEntity1()->setChanged(true);
		event->getEntity2()->setChanged(true);

		updateChanged(&events, timeLeft);

		c++;

		// TODO call Enter Event
		delete event;

		if (c > LOOP_LIMIT)
		{
			Debug::error("GameInterface::tickPhysics(): infinite loop");
			break;
		}
	}
	moveAllEntities(timeLeft); // move to End of Frame
	Debug::funcOff("GameInterface::tickPhysics()");
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
		if (time < 0) Debug::warn("GameInterface::moveAllEntities(" + Converter::floatToString(time) + "): arg is negative");
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
	if (e1->isStatic() && e2->isStatic())
	{
		Debug::warn("GameInterface::update(): e1->isStatic && e2->isStatic()");
		return;
	}

	if (Entity::areCollisionPartners(e1, e2))
	{
		if (!CollisionTester::areColliding(e1, e2, EXIT_CHECK_BORDER_ADDITION)) // prüfen, ob sie noch CollisionPartner sein sollten
		{
			// TODO call Exit-Event
			e1->removeCollisionPartner(e2);
			e2->removeCollisionPartner(e1);
			addEventsBetween(e1, e2, events, timeLeft);
		}
		else
		{
			// TODO glitch check
			PhysicsHandler::handlePhysics(e1, e2);
		}
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
		if (((events->at(i)->getEntity1() == e1) && (events->at(i)->getEntity2() == e2)) || ((events->at(i)->getEntity1() == e2) && (events->at(i)->getEntity2() == e1)))
		{
			events->erase(events->begin() + i);
		}
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
