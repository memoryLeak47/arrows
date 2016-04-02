#ifndef __SPAWNTEAMTILE_CLASS__
#define __SPAWNTEAMTILE_CLASS__

#include "../Tile.hpp"

class Team;

class SpawnTeamTile : public Tile
{
	public:
		SpawnTeamTile(Team*, const GameVector&);
		virtual ~SpawnTeamTile() {}
		virtual TextureID getTextureID() const override;
	private:
		Team* team;
};

#include "../../player/property/Team.hpp"

#endif
