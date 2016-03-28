#include "GameInterface.hpp"

GameInterface::GameInterface(LobbyTileMap* map)
{
	tileMap = new GameTileMap(map);
}

void GameInterface::tick()
{
	NetworkingMenu::tick();
}
