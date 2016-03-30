#include "GameTileMap.hpp"

#include "../../core/Main.hpp"
#include "../../misc/Debug.hpp"

GameTileMap::GameTileMap(LobbyTileMap* lobbyMap)
{
	for (unsigned int y = 0; y < lobbyMap->getInts()[0].size(); y++)
	{
		tiles.push_back(std::vector<Tile*>());
		for (unsigned int x = 0; x < lobbyMap->getInts().size(); x++)
		{
			tiles.back().push_back(Tile::createByColorID(lobbyMap->getInts()[x][y], GameVector(x, y)));
		}
	}
}

GameTileMap::~GameTileMap()
{
	for (unsigned int i = 0; i < tiles.size(); i++)
	{
		deleteAndClearVector(tiles[i]);
	}
}

const std::vector<Tile*> GameTileMap::getIntersectionTiles(const GameRect& gameRect) const
{
	Debug::warn("GameTileMap::createIntersectionTiles(): TODO");
	return std::vector<Tile*>();
}
