#include "CollisionEvent.hpp"

CollisionEvent::CollisionEvent(Entity* e1, Entity* e2, float timeUntilFrameEnds, bool isEnter)
	: entity1(e1), entity2(e2), timeUntilFrameEnds(timeUntilFrameEnds), isEnter(isEnter)
{}

Entity* CollisionEvent::getEntity1()
{
	return entity1;
}

Entity* CollisionEvent::getEntity2()
{
	return entity2;
}

float CollisionEvent::getTimeUntilFrameEnds()
{
	return timeUntilFrameEnds;
}

bool CollisionEvent::isEnterEvent()
{
	return isEnter;
}
