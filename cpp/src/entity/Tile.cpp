#include "Tile.hpp"

#include "../misc/Converter.hpp"
#include "tiles/NormalTile.hpp"
#include "tiles/VoidTile.hpp"


static int NORMAL_BLOCK_ID = Converter::colorStringToInt("000000");
static int VOID_BLOCK_ID = Converter::colorStringToInt("ffffff");

Tile::Tile(Body* body)
	: Entity(body)
{}

Tile* Tile::createByColorID(const int id, const GameVector& position)
{
	if (id == NORMAL_BLOCK_ID)
	{
		return new NormalTile(position);
	}
	else if (id == VOID_BLOCK_ID)
	{
		return new VoidTile(position);
	}
	Debug::warn("Tile::createByColorID(): No Block_ID = " + id);
	return NULL;
}
