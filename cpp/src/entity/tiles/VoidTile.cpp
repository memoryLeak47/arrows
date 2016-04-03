#include "VoidTile.hpp"

extern TextureID VOIDTILE_TID;

VoidTile::VoidTile(const GameVector& pos)
	: Tile(new RectBody(pos))
{}

TextureID VoidTile::getTextureID() const
{
	return VOIDTILE_TID;
}
