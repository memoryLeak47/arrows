#ifndef __COLLISIONEVENT_CLASS__
#define __COLLISIONEVENT_CLASS__

class Entity;

#include <string>

class CollisionEvent
{
	public:
		CollisionEvent(Entity* e1, Entity* e2, float timeUntilFameEnds);
		Entity* getEntity1() const;
		Entity* getEntity2() const;
		float getTimeUntilFrameEnds() const;
		std::string toString() const;
	private:
		Entity* entity1;
		Entity* entity2;
		float timeUntilFrameEnds;
};

#endif
