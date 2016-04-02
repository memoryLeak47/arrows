/*
	width/height:
		Gibt die Anzahl der Tiles an.
*/

#ifndef __GAMETILEMAP_CLASS__
#define __GAMETILEMAP_CLASS__

#include <vector>
#include <SFML/Graphics.hpp>

#include "LobbyTileMap.hpp"

class GameRect;
class Tile;

class GameTileMap
{
	public:
		GameTileMap(LobbyTileMap*);
		virtual ~GameTileMap();
		const std::vector<Tile*> getIntersectionTiles(const GameRect&) const;

		int getWidth() const;
		int getHeigth() const;
	private:
		void updateFullTexture();
		void loadFromLobbyTileMap(LobbyTileMap*);

		std::vector<std::vector<Tile*>> tiles;
		sf::Texture staticTexture;
};

#include "../../math/game/GameRect.hpp"
#include "../../entity/Tile.hpp"

#endif
