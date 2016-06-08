#include "CollisionHandler.hpp"

#include "../misc/Debug.hpp"

void CollisionHandler::handleCollisionEvent(CollisionEvent* ev)
{
	int collisionType = std::max(ev->getEntity1()->getCollisionType(), ev->getEntity2()->getCollisionType());
	switch (collisionType)
	{
		case COLLISIONTYPE_SOLID:
			handleCollisionEventSolid(ev);
			break;
		case COLLISIONTYPE_IGNORE:
			// do nothing, unsuccessfully
			break;
	}
}

void CollisionHandler::handleCollisionEventSolid(CollisionEvent*)
{
	Debug::warn("CollisionHandler::handleCollisionEventSolid(): TODO");
}
