#ifndef __COLLISIONEVENT_CLASS__
#define __COLLISIONEVENT_CLASS__

#include <vector>
#include <string>

class Entity;
class GameVector;

enum CollisionEventType
{COLLISIONEVENTTYPE_ENTER, COLLISIONEVENTTYPE_EXIT, COLLISIONEVENTTYPE_STAY};

class CollisionEvent
{
	public:
		CollisionEvent(Entity* e1, Entity* e2, float timeUntilFameEnds, CollisionEventType type, const std::vector<GameVector>& colPoints);
		Entity* getEntity1() const;
		Entity* getEntity2() const;
		float getTimeUntilFrameEnds() const;
		CollisionEventType getType() const;
		const std::vector<GameVector>& getCollisionPoints() const;
		std::string toString() const;
	private:
		Entity* entity1;
		Entity* entity2;
		float timeUntilFrameEnds;
		CollisionEventType type;
		std::vector<GameVector> collisionPoints;
};

#include "../entity/Entity.hpp"
#include "../math/game/GameVector.hpp"

#endif
