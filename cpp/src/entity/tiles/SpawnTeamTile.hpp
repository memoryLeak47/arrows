#ifndef __SPAWNTEAMTILE_CLASS__
#define __SPAWNTEAMTILE_CLASS__

#include <entity/Tile.hpp>

class Team;

class SpawnTeamTile : public Tile
{
	public:
		SpawnTeamTile(Team*, const GameVector&);
		virtual ~SpawnTeamTile() {}
		virtual sf::Texture* getTexture() const override;
		virtual float getCollisionPriority(Entity* e) { return -100; }
		virtual bool isSpawnTeamTile() const override;
		Team* getTeam() const;
		virtual std::string toString() const override;
	private:
		Team* team;
};

#include <player/property/Team.hpp>

#endif
