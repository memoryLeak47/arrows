#include "GameTileMap.hpp"

#include "../../misc/Debug.hpp"

GameTileMap::GameTileMap(LobbyTileMap* lobbyMap)
{}

const std::vector<Tile*> GameTileMap::getIntersectionTiles(const GameRect& gameRect) const
{
	Debug::warn("GameTileMap::createIntersectionTiles(): TODO");
	return std::vector<Tile*>();
}
