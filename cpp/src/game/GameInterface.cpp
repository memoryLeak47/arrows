#include "GameInterface.hpp"

#include "../core/Main.hpp"
#include "../misc/Debug.hpp"
#include "../player/GamePlayer.hpp"

GameInterface::GameInterface(LobbyTileMap* map, const std::vector<LobbyPlayer*>& lobbyPlayers)
{
	tileMap = new GameTileMap(map);
	for (unsigned int i = 0; i < lobbyPlayers.size(); i++)
	{
		Debug::warn("GameInterface::GameInterface(): TODO: create <Avatar>GamePlayer");
		// mobs.push_back(lobbyPlayers[i]->createGamePlayer());
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
	for (unsigned int i = 0; i < mobs.size(); i++)
	{
		mobs[i]->tick();
	}
	// TODO tick tiles?
	for (unsigned int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->tick();
	}

	// calculate Collisions
	for (unsigned int i = 0; i < mobs.size(); i++)
	{
		mobs[i]->calculateCollisions(mobs, getGameTileMap(), bullets);
	}
	for (unsigned int i = 0; i < tiles.size(); i++)
	{
		tiles[i]->calculateCollisions(mobs, getGameTileMap(), bullets);
	}
	for (unsigned int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->calculateCollisions(mobs, getGameTileMap(), bullets);
	}

	// handle Collisions
	for (unsigned int i = 0; i < mobs.size(); i++)
	{
		mobs[i]->handleCollisions();
	}
	for (unsigned int i = 0; i < tiles.size(); i++)
	{
		tiles[i]->handleCollisions();
	}
	for (unsigned int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->handleCollisions();
	}

	// apply Forces
	for (unsigned int i = 0; i < mobs.size(); i++)
	{
		if (!mobs[i]->isIgnoringForces())
			mobs[i]->applyForces();
		mobs[i]->resetCollisionSystem();
	}
	for (unsigned int i = 0; i < tiles.size(); i++)
	{
		if (!tiles[i]->isIgnoringForces())
			tiles[i]->applyForces();
		tiles[i]->resetCollisionSystem();
	}
	for (unsigned int i = 0; i < bullets.size(); i++)
	{
		if (!bullets[i]->isIgnoringForces())
			bullets[i]->applyForces();
		bullets[i]->resetCollisionSystem();
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
