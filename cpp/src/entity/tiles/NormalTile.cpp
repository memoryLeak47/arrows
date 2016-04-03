#include "NormalTile.hpp"

extern TextureID NORMALTILE_TID;

NormalTile::NormalTile(const GameVector& pos)
	: Tile(new RectBody(pos))
{}

TextureID NormalTile::getTextureID() const
{
	return NORMALTILE_TID;
}
