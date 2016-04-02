#ifndef __LAVATILE_CLASS__
#define __LAVATILE_CLASS__

#include "../Tile.hpp"

class LavaTile : public Tile
{
	public:
		LavaTile(const GameVector&);
		virtual ~LavaTile() {}
		virtual TextureID getTextureID() const override;
};

#endif
