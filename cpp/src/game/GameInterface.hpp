#ifndef __GAMEINTERFACE_CLASS__
#define __GAMEINTERFACE_CLASS__

#include "../menu/NetworkingMenu.hpp"
#include "../tile/map/GameTileMap.hpp"
#include "../view/View.hpp"

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
	private:
		// functions
		void renderMap() const;
		void renderBars() const;
		void renderEntities() const;
		GameTileMap* getGameTileMap() const;
		const View& getView() const;

		// elements
		std::vector<Mob*> mobs;
		std::vector<Tile*> tiles;
		std::vector<Bullet*> bullets;
		View view;
		GameTileMap* tileMap;
};

#include "../tile/map/LobbyTileMap.hpp"
#include "../player/LobbyPlayer.hpp"
#include "../entity/Mob.hpp"
#include "../entity/Tile.hpp"
#include "../entity/Bullet.hpp"

#endif
