#ifndef __COLLISIONEVENT_CLASS__
#define __COLLISIONEVENT_CLASS__

class Entity;

class CollisionEvent
{
	public:
		CollisionEvent(Entity* e1, Entity* e2, float timeUntilFameEnds, bool isEnter);
		Entity* getEntity1();
		Entity* getEntity2();
		float getTimeUntilFrameEnds();
		bool isEnterEvent();
	private:
		Entity* entity1;
		Entity* entity2;
		float timeUntilFrameEnds;
		bool isEnter;
};

#include "../entity/Entity.hpp"

#endif
