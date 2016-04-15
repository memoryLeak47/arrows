#ifndef __COLLISIONDETECTOR_CLASS__
#define __COLLISIONDETECTOR_CLASS__

class GameVector;
class Body;
class RectBody;
class CircleBody;
class CollisionLine;

class CollisionDetector
{
	public:
		static CollisionLine getCollisionLine(Body*, Body*);
	private:
		static CollisionLine rectCollision(RectBody*, RectBody*);
		static CollisionLine rectCircleCollision(RectBody*, CircleBody*);
		static CollisionLine circleCollision(CircleBody*, CircleBody*);
};

#include "../math/game/GameVector.hpp"
#include "Collision.hpp"
#include "Body.hpp"
#include "RectBody.hpp"
#include "CircleBody.hpp"
#include "CollisionLine.hpp"

#endif
