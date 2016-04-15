#ifndef __COLLISIONLINE_CLASS__
#define __COLLISIONLINE_CLASS__

#include "../math/game/GameVector.hpp"

class CollisionLine
{
	public:
		CollisionLine(const GameVector&, const GameVector&);
		virtual ~CollisionLine() {}
		bool isValid() const;
	private:
		GameVector point1, point2;
};

#include "../math/game/GameVector.hpp"

#endif
