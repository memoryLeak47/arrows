#include "CollisionEvent.hpp"

#include "../misc/Converter.hpp"

CollisionEvent::CollisionEvent(Entity* e1, Entity* e2, float timeUntilFrameEnds)
	: entity1(e1), entity2(e2), timeUntilFrameEnds(timeUntilFrameEnds)
{}

Entity* CollisionEvent::getEntity1() const
{
	return entity1;
}

Entity* CollisionEvent::getEntity2() const
{
	return entity2;
}

float CollisionEvent::getTimeUntilFrameEnds() const
{
	return timeUntilFrameEnds;
}

std::string CollisionEvent::toString() const
{
	return "(" + entity1->toString() + ", " + entity2->toString() + ", " + Converter::floatToString(timeUntilFrameEnds) + ")";
}
