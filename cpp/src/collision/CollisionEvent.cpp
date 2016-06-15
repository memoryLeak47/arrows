#include "CollisionEvent.hpp"

CollisionEvent::CollisionEvent(Entity* e1, Entity* e2, float timeUntilFrameEnds, bool isEnter, const std::vector<GameVector>& colPoints)
	: entity1(e1), entity2(e2), timeUntilFrameEnds(timeUntilFrameEnds), isEnter(isEnter), collisionPoints(colPoints)
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

bool CollisionEvent::isEnterEvent() const
{
	return isEnter;
}

const std::vector<GameVector>& CollisionEvent::getCollisionPoints() const
{
	return collisionPoints;
}
