#ifndef __COLLISIONDETECTOR_CLASS__
#define __COLLISIONDETECTOR_CLASS__

class GameVector;
class Body;
class RectBody;
class CircleBody;

class CollisionDetector
{
	public:
		static GameVector getCollisionPoint(Body*, Body*);
	private:
		static GameVector rectCollision(RectBody*, RectBody*);
		static GameVector rectCircleCollision(RectBody*, CircleBody*);
		static GameVector circleCollision(CircleBody*, CircleBody*);

		static bool unrotatedRectCollision(RectBody*, RectBody*);
		static bool checkWrapper(Body*, Body*);
};

#include "../math/game/GameVector.hpp"
#include "Collision.hpp"
#include "Body.hpp"
#include "RectBody.hpp"
#include "CircleBody.hpp"

#endif
