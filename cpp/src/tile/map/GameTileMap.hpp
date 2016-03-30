#ifndef __GAMETILEMAP_CLASS__
#define __GAMETILEMAP_CLASS__

#include "LobbyTileMap.hpp"

#include <vector>

class GameRect;
class Tile;

class GameTileMap
{
	public:
		GameTileMap(LobbyTileMap*);
		virtual ~GameTileMap();
		const std::vector<Tile*> getIntersectionTiles(const GameRect&) const;
	private:
		std::vector<std::vector<Tile*>> tiles;
};

#include "../../math/game/GameRect.hpp"
#include "../../entity/Tile.hpp"

#endif
