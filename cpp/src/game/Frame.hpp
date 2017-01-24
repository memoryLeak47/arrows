#ifndef __FRAME_CLASS__
#define __FRAME_CLASS__

#include <vector>
#include <deque>
#include "FrameCloneable.hpp"

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

class Frame : public FrameCloneable
{
	public:
		Frame(LobbyTileMap* map, const std::vector<LobbyPlayer*>& lobbyPlayers, RestrictedGameInterface* restrictedGameInterface);
		Frame() = default;
		~Frame();

		Frame* clone() const;

		void tick();

		unsigned int getDynamicEntityAmount() const;
		DynamicEntity* getDynamicEntity(unsigned int);
		const GameTileMap* getGameTileMap() const;

		void moveAllEntities(float time);
		void updateChanged(std::deque<CollisionEvent*>* events, float timeLeft);
		void update(Entity* e1, Entity* e2, std::deque<CollisionEvent*>* events, float timeLeft);
		void addEventsBetween(Entity* e1, Entity* e2, std::deque<CollisionEvent*>* events, float timeLeft);
		void removeEventsBetween(Entity* e1, Entity* e2, std::deque<CollisionEvent*>* events);
	protected:
		virtual std::vector<FrameCloneable**> getClonePointers() const override;
		virtual unsigned int getMemSize() const override;
		virtual bool hasToBeCloned() const override;
	private:
		void tickEntities();
		void tickPhysics();

		std::vector<GamePlayer*> players;
		public: // XXX remove public XXX
			std::vector<Idler*> idlers;
		std::vector<Mob*> mobs;
		GameTileMap* tileMap;

	friend class GameInterface;
	friend class ClientGameInterface;
	friend class ServerGameInterface;
	friend class RestrictedGameInterface;
};

#endif
