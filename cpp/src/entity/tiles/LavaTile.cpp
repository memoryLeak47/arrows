#include "LavaTile.hpp"

extern TextureID LAVATILE;

LavaTile::LavaTile(const GameVector& pos)
	: Tile(pos)
{}

TextureID LavaTile::getTextureID() const
{
	return LAVATILE;
}
