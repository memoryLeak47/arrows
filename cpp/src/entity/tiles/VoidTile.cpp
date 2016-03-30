#include "VoidTile.hpp"

VoidTile::VoidTile(const GameVector& pos)
	: Tile(new RectBody(pos))
{}
