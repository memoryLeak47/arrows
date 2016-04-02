#ifndef __TILE_CLASS__
#define __TILE_CLASS__

#include "Entity.hpp"

class RectBody;
class GameVector;
class Debug;

class Tile : public Entity
{
	public:
		Tile(Body*);
		Tile(const GameVector&);
		virtual ~Tile() {}
		virtual void handleCollisions() override {}

		static Tile* createByColorID(const int, const GameVector&);
};

#include "../math/game/GameVector.hpp"
#include "../misc/Debug.hpp"
#include "../collision/RectBody.hpp"

#endif
