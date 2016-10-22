#include "GameTileMap.hpp"

#include <misc/Global.hpp>
#include <core/Screen.hpp>
#include <player/property/Team.hpp>
#include <entity/tiles/SpawnTeamTile.hpp>
#include <graphics/GraphicsManager.hpp>
#include <math/game/GameVector.hpp>
#include <math/game/GameRect.hpp>
#include <tile/map/LobbyTileMap.hpp>
#include <math/pixel/PixelVector.hpp>
#include <math/pixel/PixelRect.hpp>
#include <view/View.hpp>

GameTileMap::GameTileMap(LobbyTileMap* lobbyMap)
{
	loadFromLobbyTileMap(lobbyMap);
	staticImage.create(getWidth()*global::TILESIZE, getHeight()*global::TILESIZE);
	updateFullImage();
}

void GameTileMap::loadFromLobbyTileMap(LobbyTileMap* lobbyMap)
{
	spawnPositions.clear();
	for (unsigned int i = 0; i < Team::getAmount(); i++)
	{
		spawnPositions.push_back(GameVector(0,0));
	}

	std::vector<std::vector<int>> ints = lobbyMap->getInts();

	tiles.reserve(ints.size());
	for (unsigned int x = 0; x < ints.size(); x++)
	{
		tiles.push_back(std::vector<Tile*>());
		tiles.back().reserve(ints[0].size());
		for (unsigned int y = 0; y < ints[0].size(); y++)
		{
			tiles.back().push_back(Tile::createByColorID(ints[x][y], GameVector(x + 0.5f, y + 0.5f)));
			if (tiles.back().back()->isSpawnTeamTile())
			{
				spawnPositions[dynamic_cast<SpawnTeamTile*>(tiles.back().back())->getTeam()->getID()] = GameVector(x + 0.5f , y + 0.5f);
			}
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

GameVector GameTileMap::teamToSpawnPosition(Team* team)
{
	return spawnPositions[team->getID()];
}

const std::vector<Tile*> GameTileMap::getIntersectionTiles(const GameRect& gameRect) const
{
	int left = std::max(0, ((int)gameRect.getLeft()));
	int right = std::min((int) getWidth(), ((int)gameRect.getRight()) + 1);
	int top = std::max(0, ((int)gameRect.getTop()));
	int bot = std::min((int) getHeight(), ((int)gameRect.getBot()) + 1);

	std::vector<Tile*> intersectionTiles;

	for (int x = left; x < right; x++)
	{
		for (int y = top; y < bot; y++)
		{
			intersectionTiles.push_back(tiles[x][y]);
		}
	}
	return intersectionTiles;
}

bool GameTileMap::obstacleAt(unsigned int x, unsigned int y) const
{
	if (not isValidIndex(x, y))
	{
		Debug::error("GameTileMap::obstacleAt(" + Converter::intToString((int) x) + ", " + Converter::intToString((int) y) + "): invalid index");
		return false;
	}
	return tiles[x][y]->getCollisionType() == CollisionType::SOLID;

}

bool GameTileMap::isValidIndex(unsigned int x, unsigned int y) const
{
	return (x >= 0) && (y >= 0) && (x < getWidth()) && (y < getHeight());
}

void GameTileMap::updateFullImage()
{
	if (getHeight() < 0) Debug::warn("GameTileMap::updateFullImage(): getHeight == " + Converter::intToString(getHeight()));
	if (getWidth() < 0) Debug::warn("GameTileMap::updateFullImage(): getWidth == " + Converter::intToString(getWidth()));
	for (unsigned int x = 0; x < getWidth(); x++)
	{
		for (unsigned int y = 0; y < getHeight(); y++)
		{
			if (tiles[x][y] == NULL) Debug::error("GameTileMap::updateFullImage(): tiles[" + Converter::intToString((int) x) + "][" + Converter::intToString((int) y) + "] == NULL");
			tiles[x][y]->renderToImage(staticImage, x*global::TILESIZE, y*global::TILESIZE);
		}
	}
}

unsigned int GameTileMap::getWidth() const
{
	if (tiles.size() > 0)
	{
		return tiles.size();
	}
	else
	{
		Debug::warn("GameTileMap::getWidth(): tiles.size == " + Converter::intToString((int) tiles.size()));
		return 0;
	}
}

unsigned int GameTileMap::getHeight() const
{
	if ((tiles.size() > 0) && (tiles[0].size() > 0))
	{
		return tiles[0].size();
	}
	else
	{
		Debug::warn("GameTileMap::getHeight(): invalid size");
		return 0;
	}
}

void GameTileMap::render(const View& v) const
{
	PixelRect r = v.gameRectToPixelRect(GameRect(0,0, getWidth(), getHeight())); // correct
	// r = map in pixels
	int x = r.getPosition().x;
	int y = r.getPosition().y;
	int realX = std::max(0, x);
	int realY = std::max(0, y);
	int w = Screen::getSize().x - std::max(0, x) + std::min(0, x + r.getSize().x - Screen::getSize().x);
	int h = Screen::getSize().y - std::max(0, y) + std::min(0, y + r.getSize().y - Screen::getSize().y);

	if (w <= 0 || h <= 0 || realX < 0 || realY < 0 || realX+w > Screen::getSize().x || realY+h > Screen::getSize().y)
	{
		Debug::warn("GameInterface.renderMap(): outside of raster x: " + Converter::intToString(realX) + ", y: " + Converter::intToString(realY) + ", w: " + Converter::intToString(w) + ", h: " + Converter::intToString(h));
	}
	else
	{
		sf::Texture t;
		t.loadFromImage(staticImage, sf::IntRect(std::max(0,-x), std::max(0, -y), w, h));
		Screen::drawTexture(&t, PixelRect(realX, realY, w, h));
	}
}
