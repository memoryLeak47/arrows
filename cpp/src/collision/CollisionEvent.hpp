#ifndef __COLLISIONEVENT_CLASS__
#define __COLLISIONEVENT_CLASS__

#include <vector>
#include <string>

class Entity;
class GameVector;

class CollisionEvent
{
	public:
		CollisionEvent(Entity* e1, Entity* e2, float timeUntilFameEnds, bool isEnter, const std::vector<GameVector>& colPoints);
		Entity* getEntity1() const;
		Entity* getEntity2() const;
		float getTimeUntilFrameEnds() const;
		bool isEnterEvent() const;
		const std::vector<GameVector>& getCollisionPoints() const;
		std::string toString() const;
	private:
		Entity* entity1;
		Entity* entity2;
		float timeUntilFrameEnds;
		bool isEnter;
		std::vector<GameVector> collisionPoints;
};

#include "../entity/Entity.hpp"
#include "../math/game/GameVector.hpp"

#endif
