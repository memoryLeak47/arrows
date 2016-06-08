#include "GameTileMap.hpp"

#include "../../core/Main.hpp"
#include "../../core/Screen.hpp"
#include "../../misc/Converter.hpp"
#include "../../misc/Debug.hpp"

#include "../../entity/tiles/SpawnTeamTile.hpp"
#include "../../graphics/GraphicsManager.hpp"

GameTileMap::GameTileMap(LobbyTileMap* lobbyMap)
{
	loadFromLobbyTileMap(lobbyMap);
	staticImage.create(getWidth()*TILESIZE, getHeight()*TILESIZE);
	updateFullImage();
}

void GameTileMap::loadFromLobbyTileMap(LobbyTileMap* lobbyMap)
{
	spawnPositions.clear();
	for (unsigned int i = 0; i < Team::getAmount(); i++)
	{
		spawnPositions.push_back(GameVector(0,0));
	}

	for (unsigned int x = 0; x < lobbyMap->getInts().size(); x++)
	{
		tiles.push_back(std::vector<Tile*>());
		for (unsigned int y = 0; y < lobbyMap->getInts()[0].size(); y++)
		{
			tiles.back().push_back(Tile::createByColorID(lobbyMap->getInts()[x][y], GameVector(x, y)));
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
	int right = std::min(getWidth(), ((int)gameRect.getRight()) + 1);
	int top = std::max(0, ((int)gameRect.getTop()));
	int bot = std::min(getHeight(), ((int)gameRect.getBot()) + 1);

	std::vector<Tile*> intersectionTiles;

	for (int x = left; x <= right; x++)
	{
		for (int y = top; y <= bot; y++)
		{
			intersectionTiles.push_back(tiles[x][y]);
		}
	}
	return intersectionTiles;
}

void GameTileMap::updateFullImage()
{
	Debug::warnIf(getHeight() < 0, "GameTileMap::updateFullImage(): getHeight == " + Converter::intToString(getHeight()));
	Debug::warnIf(getWidth() < 0, "GameTileMap::updateFullImage(): getWidth == " + Converter::intToString(getWidth()));
	for (int x = 0; x < getWidth(); x++)
	{
		for (int y = 0; y < getHeight(); y++)
		{
			Debug::errorIf(tiles[x][y] == NULL, "GameTileMap::updateFullImage(): tiles[" + Converter::intToString(x) + "][" + Converter::intToString(y) + "] == NULL");
			tiles[x][y]->renderToImage(staticImage, x*TILESIZE, y*TILESIZE);
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

void GameTileMap::render(const View& v) const
{
	PixelRect r = v.gameRectToPixelRect(GameRect(0,0, getWidth(), getHeight())); // correct
	// r = map in pixels
	int x = r.getPosition().getX();
	int y = r.getPosition().getY();
	int realX = std::max(0, x);
	int realY = std::max(0, y);
	int w = Screen::getSize().getX() - std::max(0, x) + std::min(0, x + r.getSize().getX() - Screen::getSize().getX());
	int h = Screen::getSize().getY() - std::max(0, y) + std::min(0, y + r.getSize().getY() - Screen::getSize().getY());

	if (w <= 0 || h <= 0 || realX < 0 || realY < 0 || realX+w > Screen::getSize().getX() || realY+h > Screen::getSize().getY())
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
