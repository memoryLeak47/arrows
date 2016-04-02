#include "NormalTile.hpp"

extern TextureID NORMALTILE;

NormalTile::NormalTile(const GameVector& pos)
	: Tile(new RectBody(pos))
{}

TextureID NormalTile::getTextureID() const
{
	return NORMALTILE;
}
