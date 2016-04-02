#include "GameTileMap.hpp"

#include "../../core/Main.hpp"
#include "../../misc/Converter.hpp"
#include "../../misc/Debug.hpp"

GameTileMap::GameTileMap(LobbyTileMap* lobbyMap)
{
	loadFromLobbyTileMap(lobbyMap);
	updateFullTexture();
}

void GameTileMap::loadFromLobbyTileMap(LobbyTileMap* lobbyMap)
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

void GameTileMap::updateFullTexture()
{
	//staticTexture.create(
}

int GameTileMap::getWidth() const
{
	if (tiles.size() > 0)
	{
		return (int) tiles.size();
	}
	else
	{
		Debug::warn("GameTileMap::getWidth(): tiles.size == " + Converter::intToString((int) tiles.size()));
		return -1;
	}
}

int GameTileMap::getHeigth() const
{
	if ((tiles.size() > 0) && (tiles[0].size() > 0))
	{
		return (int) tiles[0].size();
	}
	else
	{
		Debug::warn("GameTileMap::getHeight(): invalid size");
		return -1;
	}
}
