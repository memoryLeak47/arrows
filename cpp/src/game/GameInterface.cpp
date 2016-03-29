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
}
