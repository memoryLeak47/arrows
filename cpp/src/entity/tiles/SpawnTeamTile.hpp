#ifndef __SPAWNTEAMTILE_CLASS__
#define __SPAWNTEAMTILE_CLASS__

class Team;
class GameVector;

#include <entity/Tile.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string>

class SpawnTeamTile : public Tile
{
	public:
		SpawnTeamTile(Team*, const GameVector&);
		virtual ~SpawnTeamTile() {}
		CREATE_GETMEMSIZE(SpawnTeamTile)
		virtual sf::Texture* getTexture() const override;
		virtual float getCollisionPriority(Entity* e) const override;
		virtual bool isSpawnTeamTile() const override;
		Team* getTeam() const;
		virtual std::string toString() const override;
	private:
		Team* team;
};

#endif
