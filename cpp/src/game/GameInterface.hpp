#ifndef __GAMEINTERFACE_CLASS__
#define __GAMEINTERFACE_CLASS__

#include "../menu/NetworkingMenu.hpp"
#include "../tile/map/GameTileMap.hpp"

class LobbyTileMap;
class LobbyPlayer;
class Mob;
class Tile;
class Bullet;

class GameInterface : public NetworkingMenu
{
	public:
		GameInterface(LobbyTileMap*, const std::vector<LobbyPlayer*>&);
		virtual ~GameInterface();
		virtual void tick() override;
		virtual void render() const override;
		GameTileMap* getGameTileMap() const;
	private:
		void renderMap() const;
		void renderBars() const;
		void renderEntities() const;
		std::vector<Mob*> mobs;
		std::vector<Tile*> tiles;
		std::vector<Bullet*> bullets;
		GameTileMap* tileMap;
};

#include "../tile/map/LobbyTileMap.hpp"
#include "../player/LobbyPlayer.hpp"
#include "../entity/Mob.hpp"
#include "../entity/Tile.hpp"
#include "../entity/Bullet.hpp"

#endif
