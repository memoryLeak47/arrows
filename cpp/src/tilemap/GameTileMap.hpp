/*
	Tiles teilt sich in einen äußeren Vector A und viele innere Vectoren I.
	In jedem I-Vector liegt eine Spalte der Map, sodass ein Tile über tiles[x][y] angesprochen werden kann.
	Der A-Vector enthält also alle Spalten der Map.

	width:
		Gibt die Anzahl der Tiles in X-Richtung an. Dies entspricht tiles.size()

	height:
		Gibt die Anzahl der Tiles in Y-Richtung an. Dies entspricht tiles[0].size()

	TILESIZE:
		Gibt an, wieviele Pixel ein Tile einnimmt (nur für das rendern des staticImage)
*/

#ifndef __GAMETILEMAP_CLASS__
#define __GAMETILEMAP_CLASS__

class LobbyTileMap;
class Tile;
class GameRect;
class View;
class GameVector;
class Team;

#include <vector>
#include <SFML/Graphics/Image.hpp>

class GameTileMap
{
	public:
		GameTileMap(LobbyTileMap*);
		virtual ~GameTileMap();
		const std::vector<Tile*> getIntersectionTiles(const GameRect&) const;
		bool obstacleAt(unsigned int x, unsigned int y) const;
		bool isValidIndex(unsigned int x, unsigned int y) const;

		unsigned int getWidth() const;
		unsigned int getHeight() const;

		void render(const View&) const;
		GameVector teamToSpawnPosition(Team*);
	private:
		std::vector<GameVector> spawnPositions;
		void updateFullImage();
		void loadFromLobbyTileMap(LobbyTileMap*);

		std::vector<std::vector<Tile*>> tiles;
		sf::Image staticImage;
};

#endif
