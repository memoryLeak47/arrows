#include "GameInterface.hpp"

#include "../core/Main.hpp"

GameInterface::GameInterface(LobbyTileMap* map, const std::vector<LobbyPlayer*>& lobbyPlayers)
{
	tileMap = new GameTileMap(map);
	for (int i = 0; i < lobbyPlayers.size(); i++)
	{
		players.push_back(new GamePlayer(lobbyPlayers[i]));
	}
}

GameInterface::~GameInterface()
{
	delete tileMap;
	deleteAndClearVector(players);
}

void GameInterface::tick()
{
	NetworkingMenu::tick();
}
