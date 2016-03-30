#include "NormalTile.hpp"

NormalTile::NormalTile(const GameVector& pos)
	: Tile(new RectBody(pos))
{}
