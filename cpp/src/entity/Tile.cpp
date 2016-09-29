#include "Tile.hpp"

#include <misc/Converter.hpp>
#include <misc/Debug.hpp>
#include <player/property/Team.hpp>
#include "tiles/NormalTile.hpp"
#include "tiles/VoidTile.hpp"
#include "tiles/LavaTile.hpp"
#include "tiles/SpawnTeamTile.hpp"
#include <cmath>

static int NORMAL_BLOCK_ID = Converter::colorStringToInt("000000");
static int VOID_BLOCK_ID = Converter::colorStringToInt("ffffff");
static int LAVA_BLOCK_ID = Converter::colorStringToInt("ffbb00");

Tile::Tile(Body* body)
	: Entity(body)
{}

Tile::Tile(const GameVector& pos)
	: Entity(new RectBody(pos, GameVector(1, 1)))
{}

EntityType Tile::getEntityType() const
{
	return EntityType::TILE;
}

bool Tile::isSpawnTeamTile() const
{
	return false;
}

void Tile::renderToImage(sf::Image& image, int x, int y) const
{
	if (rendersStatic())
	{
		image.copy(getTexture()->copyToImage(), x, y);
	}
}

bool Tile::rendersStatic() const
{
	return true;
}

void Tile::addCollisionPartner(Entity*)
{}

void Tile::removeCollisionPartner(Entity*)
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
	else if (id == LAVA_BLOCK_ID)
	{
		return new LavaTile(position);
	}

	for (unsigned int i = 0; i < Team::getAmount(); i++)
	{
		if (Team::get(i)->getColorID() == id)
		{
			return new SpawnTeamTile(Team::get(i), position);
		}
	}
	Debug::warn("Tile::createByColorID(): No Block_ID = " + Converter::intToString(id));
	return NULL;
}

float Tile::getMass() const
{
	return INFINITY;
}

std::pair<float, GameVector> Tile::getBackingAndMomentum(GameVector escapeVector, const std::vector<GameVector> &points)
{
	return std::pair<float, GameVector>(getMass(), GameVector(0,0));
}
