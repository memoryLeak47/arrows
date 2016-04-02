#include "SpawnTeamTile.hpp"

extern TextureID SPAWNTEAMTILE;

SpawnTeamTile::SpawnTeamTile(Team* team, const GameVector& pos)
	: Tile(pos), team(team)
{}

TextureID SpawnTeamTile::getTextureID() const
{
	return SPAWNTEAMTILE;
}
