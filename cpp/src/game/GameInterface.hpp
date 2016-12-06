#ifndef __GAMEINTERFACE_CLASS__
#define __GAMEINTERFACE_CLASS__

class LobbyTileMap;
class LobbyPlayer;
class GamePlayer;
class DynamicEntity;
class GameTileMap;
class Idler;
class Mob;
class Tile;
class CollisionEvent;

#include <menu/Menu.hpp>
#include <network/NetworkInterface.hpp>
#include <vector>
#include <SFML/Network/IpAddress.hpp>
#include <controller/Actions.hpp>
#include <view/View.hpp>
#include "RestrictedGameInterface.hpp"

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
		void tickEntities();
		void tickPhysics();

		std::vector<GamePlayer*> players;
		std::vector<Idler*> idlers;
		// std::vector<Bullet*> bullets;
		std::vector<Mob*> mobs;
		std::vector<Tile*> tiles;
		int frameCounter;
	private:
		// functions
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
		RestrictedGameInterface restrictedGameInterface;

	friend class RestrictedGameInterface;
};

#endif
