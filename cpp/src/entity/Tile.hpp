#ifndef __TILE_CLASS__
#define __TILE_CLASS__

#include "Entity.hpp"

class Tile : public Entity
{
	public:
		Tile(Body*);
		virtual ~Tile() {}
};

#endif
