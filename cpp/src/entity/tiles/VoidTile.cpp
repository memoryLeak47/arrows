#include "VoidTile.hpp"

extern TextureID VOIDTILE;

VoidTile::VoidTile(const GameVector& pos)
	: Tile(new RectBody(pos))
{}

TextureID VoidTile::getTextureID() const
{
	return VOIDTILE;
}
