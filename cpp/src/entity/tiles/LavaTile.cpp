#include "LavaTile.hpp"

extern TextureID LAVATILE_TID;

LavaTile::LavaTile(const GameVector& pos)
	: Tile(pos)
{}

TextureID LavaTile::getTextureID() const
{
	return LAVATILE_TID;
}
