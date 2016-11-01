#include "SpawnTeamTile.hpp"

#include <graphics/GraphicsManager.hpp>

SpawnTeamTile::SpawnTeamTile(Team* team, const GameVector& pos)
	: Tile(pos), team(team)
{}

sf::Texture* SpawnTeamTile::getTexture() const
{
	return GraphicsManager::getTexture(SPAWNTEAMTILE_GID);
}

bool SpawnTeamTile::isSpawnTeamTile() const
{
	return true;
}

Team* SpawnTeamTile::getTeam() const
{
	return team;
}

std::string SpawnTeamTile::toString() const
{
	return "SpawnTeamTile";
}

float SpawnTeamTile::getCollisionPriority(Entity* e) const
{
	return -1000;
}
