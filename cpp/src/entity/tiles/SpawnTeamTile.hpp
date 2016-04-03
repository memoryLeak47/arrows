#ifndef __SPAWNTEAMTILE_CLASS__
#define __SPAWNTEAMTILE_CLASS__

#include "../Tile.hpp"

class Team;

class SpawnTeamTile : public Tile
{
	public:
		SpawnTeamTile(Team*, const GameVector&);
		virtual ~SpawnTeamTile() {}
		virtual sf::Texture* getTexture() const override;
		virtual bool isSpawnTeamTile() const override;
		Team* getTeam() const;
	private:
		Team* team;
};

#include "../../player/property/Team.hpp"

#endif
