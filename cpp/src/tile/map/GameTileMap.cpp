#include "GameTileMap.hpp"

#include "../../core/Main.hpp"
#include "../../core/Screen.hpp"
#include "../../misc/Converter.hpp"
#include "../../misc/Debug.hpp"

#include "../../graphics/TextureManager.hpp"

GameTileMap::GameTileMap(LobbyTileMap* lobbyMap)
{
	loadFromLobbyTileMap(lobbyMap);
	staticImage.create(getWidth()*TILESIZE, getHeight()*TILESIZE);
	updateFullImage();
}

void GameTileMap::loadFromLobbyTileMap(LobbyTileMap* lobbyMap)
{
	for (unsigned int x = 0; x < lobbyMap->getInts().size(); x++)
	{
		tiles.push_back(std::vector<Tile*>());
		for (unsigned int y = 0; y < lobbyMap->getInts()[0].size(); y++)
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

void GameTileMap::updateFullImage()
{
	Debug::warnIf(getHeight() < 0, "GameTileMap::updateFullTexture(): getHeight == " + Converter::intToString(getHeight()));
	Debug::warnIf(getWidth() < 0, "GameTileMap::updateFullTexture(): getWidth == " + Converter::intToString(getWidth()));
	for (int x = 0; x < getWidth(); x++)
	{
		for (int y = 0; y < getHeight(); y++)
		{
			Debug::errorIf(tiles[x][y] == NULL, "GameTileMap::updateFullTexture(): tiles[" + Converter::intToString(x) + "][" + Converter::intToString(y) + "] == NULL");
			TextureID tileTextureID = tiles[x][y]->getTextureID();
			staticImage.copy(TextureManager::getTexture(tileTextureID)->copyToImage(), x*TILESIZE, y*TILESIZE);
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
	Debug::warn("GameTileMap::render(): TODO unfinished");
	sf::Texture t;
	PixelRect r = v.gameRectToPixelRect(v.getVisionRect());
	t.loadFromImage(staticImage, sf::IntRect(r.getPosition().getX(), r.getPosition().getY(), r.getSize().getX(), r.getSize().getY()));
	Screen::drawTexture(&t, PixelRect(0, 0, Screen::getSize().getX(), Screen::getSize().getY()));
}
