#ifndef __FRAME_CLASS__
#define __FRAME_CLASS__

#include <vector>

class GameTileMap;
class DynamicEntity;
class CollisionEvent;
class Entity;
class Idler;
class Mob;
class Tile;
class GamePlayer;
class LobbyTileMap;
class LobbyPlayer;
class RestrictedGameInterface;

class Frame
{
	public:
		Frame(LobbyTileMap* map, const std::vector<LobbyPlayer*>& lobbyPlayers, RestrictedGameInterface* restrictedGameInterface);
		~Frame();
		void tickEntities();
		void tickPhysics();

		unsigned int getDynamicEntityAmount();
		DynamicEntity* getDynamicEntity(unsigned int);
		const GameTileMap* getGameTileMap() const;

		CollisionEvent* cutFirstEvent(std::vector<CollisionEvent*>* events);
		void moveAllEntities(float time);
		void updateChanged(std::vector<CollisionEvent*>* events, float timeLeft);
		void update(Entity* e1, Entity* e2, std::vector<CollisionEvent*>* events, float timeLeft);
		void addEventsBetween(Entity* e1, Entity* e2, std::vector<CollisionEvent*>* events, float timeLeft);
		void removeEventsBetween(Entity* e1, Entity* e2, std::vector<CollisionEvent*>* events);
	private:
		std::vector<GamePlayer*> players;
		std::vector<Idler*> idlers;
		std::vector<Mob*> mobs;
		std::vector<Tile*> tiles;
		GameTileMap* tileMap;

	friend class GameInterface;
	friend class ClientGameInterface;
	friend class ServerGameInterface;
	friend class RestrictedGameInterface;
};

#endif
