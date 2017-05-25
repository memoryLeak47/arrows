#ifndef __FRAME_CLASS__
#define __FRAME_CLASS__

#include <vector>
#include <deque>

#include <map>
#include "FrameCloneable.hpp"
#include <game/Calendar.hpp>
#include <game/message/MessageListener.hpp>
#include <game/message/messages/AddIdlerMessage.hpp>
#include <game/message/messages/DestroyMessage.hpp>

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
class Message;

class Frame : public FrameCloneable, public MessageListener
{
	public:
		Frame(LobbyTileMap* map, const std::vector<LobbyPlayer*>& lobbyPlayers);
		virtual ~Frame();

		Frame* clone() const;

		void tick();

		unsigned int getDynamicEntityAmount() const;
		DynamicEntity* getDynamicEntity(unsigned int);
		const GameTileMap* getGameTileMap() const;

		void applyEntries(std::vector<Calendar::Entry>);

		// apply Messages
		virtual void applyMessage(const AddIdlerMessage& m) override;
		virtual void applyMessage(const DestroyMessage& m) override;
	private:
		void moveAllEntities(float time);
		void updateChanged(std::deque<CollisionEvent*>* events, float timeLeft);
		void update(Entity* e1, Entity* e2, std::deque<CollisionEvent*>* events, float timeLeft);
		void addEventsBetween(Entity* e1, Entity* e2, std::deque<CollisionEvent*>* events, float timeLeft);
		void removeEventsBetween(Entity* e1, Entity* e2, std::deque<CollisionEvent*>* events);
		void tickEntities();
		void tickPhysics();

		// messages
		void pollAndProcessMessages();
		void processMessage(Message* m);

		std::vector<GamePlayer*> $$clone_list$$ players $!clone_list$$;
		std::vector<Idler*> $$clone_list$$ idlers $!clone_list$$;
		std::vector<Mob*> $$clone_list$$ mobs $!clone_list$$;
		GameTileMap* tileMap;

	friend class GameInterface;
	friend class ClientGameInterface;
	friend class ServerGameInterface;
};

#endif
