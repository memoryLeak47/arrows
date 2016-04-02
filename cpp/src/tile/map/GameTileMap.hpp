/*
	width/height:
		Gibt die Anzahl der Tiles an.

	TILESIZE:
		Gibt an, wieviele Pixel ein Tile einnimmt (nur für das rendern der staticTexture)
*/

#ifndef __GAMETILEMAP_CLASS__
#define __GAMETILEMAP_CLASS__

#include <vector>
#include <SFML/Graphics.hpp>

#include "LobbyTileMap.hpp"

#define TILESIZE 40

class GameRect;
class Tile;

class GameTileMap
{
	public:
		GameTileMap(LobbyTileMap*);
		virtual ~GameTileMap();
		const std::vector<Tile*> getIntersectionTiles(const GameRect&) const;

		int getWidth() const;
		int getHeight() const;
		const sf::Texture* getStaticTexture() const;
	private:
		void updateFullTexture();
		void loadFromLobbyTileMap(LobbyTileMap*);

		std::vector<std::vector<Tile*>> tiles;
		sf::Texture staticTexture;
};

#include "../../math/game/GameRect.hpp"
#include "../../entity/Tile.hpp"

#endif
