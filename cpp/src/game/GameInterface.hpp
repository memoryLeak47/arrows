#ifndef __GAMEINTERFACE_CLASS__
#define __GAMEINTERFACE_CLASS__

#include <vector>

#include <menu/Menu.hpp>
#include <network/NetworkInterface.hpp>

#include <view/View.hpp>
#include <controller/Actions.hpp>

class GameTileMap;
class LobbyTileMap;
class GamePlayer;
class LobbyPlayer;
class DynamicEntity;
class Idler;
class Mob;
class Tile;
class Bullet;

class CollisionEvent;

class GameInterface : public Menu, public NetworkInterface
{
	public:
		GameInterface(LobbyTileMap*, const std::vector<LobbyPlayer*>&);
		virtual ~GameInterface();
		virtual void tick() override;
		virtual void render() const override;
	protected:
		int ipToID(sf::IpAddress*) const;
		virtual GamePlayer* getLocalPlayer() const = 0;
		unsigned int getDynamicEntityAmount();
		DynamicEntity* getDynamicEntity(unsigned int);
		GameTileMap* getGameTileMap() const;
		Actions calcActions() const;

		std::vector<GamePlayer*> players;
		std::vector<Idler*> idlers;
		// std::vector<Bullet*> bullets;
		std::vector<Mob*> mobs;
		std::vector<Tile*> tiles;
	private:
		// functions
		void tickEntities();
		void tickPhysics();
		void renderMap() const;
		void renderBars() const;
		void renderEntities() const;
		const View& getView() const;

		// physics/collision-system
		CollisionEvent* cutFirstEvent(std::vector<CollisionEvent*>* events);
		void moveAllEntities(float time);
		void updateChanged(std::vector<CollisionEvent*>* events, float timeLeft);
		void update(Entity* e1, Entity* e2, std::vector<CollisionEvent*>* events, float timeLeft);
		void addEventsBetween(Entity* e1, Entity* e2, std::vector<CollisionEvent*>* events, float timeLeft);
		void removeEventsBetween(Entity* e1, Entity* e2, std::vector<CollisionEvent*>* events);

		// elements
		View view;
		GameTileMap* tileMap;
};

#include <tile/map/GameTileMap.hpp>
#include <tile/map/LobbyTileMap.hpp>
#include <player/GamePlayer.hpp>
#include <player/LobbyPlayer.hpp>
#include <entity/DynamicEntity.hpp>
#include <entity/Idler.hpp>
#include <entity/Mob.hpp>
#include <entity/Tile.hpp>
#include <entity/Bullet.hpp>
#include <collision/CollisionEvent.hpp>

#endif
