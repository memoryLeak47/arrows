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
	PixelRect r = v.gameRectToPixelRect(GameRect(0,0, getWidth(), getHeight())); // correct
	Debug::test("r = " + r.toString());
	int x = r.getPosition().getX();
	int y = r.getPosition().getY();
	int realX = std::max(0, x);
	int realY = std::max(0, y);
	int w = r.getSize().getX() - std::max(0, x) + std::min(0, x + r.getSize().getX() - Screen::getSize().getX());
	int h = r.getSize().getY() - std::max(0, y) + std::min(0, y + r.getSize().getY() - Screen::getSize().getY());
	// int w = r.getSize().getX() - std::max(0, x) - std::max(0, r.getSize().getX()) - (x + Screen::getSize().getX());
	// int h = r.getSize().getY() - std::max(0, y) - std::max(0, r.getSize().getY()) - (y + Screen::getSize().getY());

	/*
	if (w <= 0 || h <= 0 || realX < 0 || realY < 0 || realX+w > r.getSize().getX() || realY+h > r.getSize().getY())
	{
		Debug::warn("GameInterface.renderMap(): outside of raster x: " + Converter::intToString(realX) + ", y: " + Converter::intToString(realY) + ", w: " + Converter::intToString(w) + ", h: " + Converter::intToString(h));
	}
	else
	{
	*/
		sf::Texture t;
		t.loadFromImage(staticImage, sf::IntRect(std::max(0,-x), std::max(0, -y), w, h));
		Screen::drawTexture(&t, PixelRect(realX, realY, w, h));
	//}

	/*
		Java

		PixelPosition tmp = Camera.get().gamePositionToPixelPosition(new GamePosition());
		PixelSize imageSize = new PixelSize(getUncastedGame().getMapImage().getWidth(), getUncastedGame().getMapImage().getHeight());
		int x = -tmp.getX();
		int y = -tmp.getY();
		int realX = Math.max(0, -x);
		int realY = Math.max(0, -y);
		int w = imageSize.getX() - Math.max(0, x) - Math.max(0, imageSize.getX() - (x+Screen.WIDTH));
		int h = imageSize.getY() - Math.max(0, y) - Math.max(0, imageSize.getY() - (y+Screen.HEIGHT));
		if (w <= 0 || h <= 0 || realX < 0 || realY < 0 || realX+w > imageSize.getX() || realY+h > imageSize.getY())
		{
			Debug.warn("GameInterface.renderMap(): outside of raster x: " + realX + ", y: " + realY + ", w: " + w + ", h: " + h);
		}
		else
		{
			BufferedImage subImage = getUncastedGame().getMapImage().getSubimage(Math.max(0, x), Math.max(0, y), w, h);
			Screen.g().drawImage(subImage, realX, realY, w, h, null);
		}
	*/
}
