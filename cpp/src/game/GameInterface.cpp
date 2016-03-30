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

	for (unsigned int i = 0; i < mobs.size(); i++)
	{
		mobs[i]->calculateCollisions(mobs, tiles, bullets);
	}
	for (unsigned int i = 0; i < tiles.size(); i++)
	{
		tiles[i]->calculateCollisions(mobs, tiles, bullets);
	}
	for (unsigned int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->calculateCollisions(mobs, tiles, bullets);
	}

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
