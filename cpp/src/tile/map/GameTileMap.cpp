#include "GameTileMap.hpp"

#include "../../core/Main.hpp"
#include "../../misc/Converter.hpp"
#include "../../misc/Debug.hpp"

#include "../../graphics/TextureManager.hpp"

GameTileMap::GameTileMap(LobbyTileMap* lobbyMap)
{
	loadFromLobbyTileMap(lobbyMap);
	staticTexture.create(getWidth()*TILESIZE, getHeight()*TILESIZE);
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
	Debug::warnIf(getHeight() < 0, "GameTileMap::updateFullTexture(): getHeight == " + Converter::intToString(getHeight()));
	Debug::warnIf(getWidth() < 0, "GameTileMap::updateFullTexture(): getWidth == " + Converter::intToString(getWidth()));
	for (int y = 0; y < getHeight(); y++)
	{
		for (int x = 0; x < getWidth(); x++)
		{
			Debug::errorIf(tiles[x][y] == NULL, "GameTileMap::updateFullTexture(): tiles[" + Converter::intToString(x) + "][" + Converter::intToString(y) + "] == NULL");
			TextureID tileTextureID = tiles[x][y]->getTextureID();
			staticTexture.update(TextureManager::getTexture(tileTextureID)->copyToImage(), x*TILESIZE, y*TILESIZE);
		}
	}
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

int GameTileMap::getHeight() const
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
