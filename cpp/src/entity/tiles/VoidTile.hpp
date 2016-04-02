#ifndef __VOIDTILE_CLASS__
#define __VOIDTILE_CLASS__

#include "../Tile.hpp"

class VoidTile : public Tile
{
	public:
		VoidTile(const GameVector&);
		virtual void handleCollisions() override {}
		virtual TextureID getTextureID() const override;
};

#endif
