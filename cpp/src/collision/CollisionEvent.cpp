#include "CollisionEvent.hpp"

#include "../misc/Converter.hpp"

CollisionEvent::CollisionEvent(Entity* e1, Entity* e2, float timeUntilFrameEnds, CollisionEventType typeArg, const std::vector<GameVector>& colPoints)
	: entity1(e1), entity2(e2), timeUntilFrameEnds(timeUntilFrameEnds), type(typeArg), collisionPoints(colPoints)
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

CollisionEventType CollisionEvent::getType() const
{
	return type;
}

const std::vector<GameVector>& CollisionEvent::getCollisionPoints() const
{
	return collisionPoints;
}

std::string CollisionEvent::toString() const
{
	return "(" + entity1->toString() + ", " + entity2->toString() + ", " + Converter::floatToString(timeUntilFrameEnds) + ", " + (type == COLLISIONEVENTTYPE_ENTER? "enter" : (type == COLLISIONEVENTTYPE_EXIT? "exit" : "stay")) + ")";
}
