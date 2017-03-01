#include "Tile.hpp"

#include <entity/EntityGivethrough.hpp>
#include <collision/RectShape.hpp>
#include <misc/Global.hpp>
#include <team/Team.hpp>
#include "tiles/NormalTile.hpp"
#include "tiles/RubberTile.hpp"
#include "tiles/VoidTile.hpp"
#include "tiles/LavaTile.hpp"
#include "tiles/SpawnTeamTile.hpp"
#include <cmath>

Tile::Tile(const EntityGivethrough& gt)
	: Entity(gt)
{}

Tile::Tile(const GameVector& pos)
	: Entity(EntityGivethrough(new RectShape(this), pos, GameVector(1.f, 1.f)))
{}

bool Tile::hasToBeCloned() const
{
	return false;
}

std::vector<FrameCloneable**> Tile::getClonePointers() const
{
	return {};
}

bool Tile::hasChanged() const
{
	return false;
}

void Tile::setChanged(bool b) {}

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

void Tile::addWrapperPartner(Entity*)
{}

void Tile::removeWrapperPartner(Entity*)
{}

const std::vector<Entity*>& Tile::getCollisionPartners() const
{
	static const std::vector<Entity*> v;
	return v;
}

const std::vector<Entity*>& Tile::getWrapperPartners() const
{
	static const std::vector<Entity*> v;
	return v;
}

bool Tile::hasCollisionPartner(Entity*) const
{
	return false;
}

bool Tile::hasWrapperPartner(Entity*) const
{
	return false;
}

Tile* Tile::createByTileID(const TileID tid, const GameVector& position)
{
	switch (tid)
	{
		#define X(name, tid, color) case TileIDs::tid: return new name(position);
		#define Y(name, tid, color) case TileIDs::tid: return new name(position);
		#include "TileID.list"
		#undef X
		#undef Y

		#define X(teamID, name, color) case TileIDs::SPAWN_TEAM_TILE_##teamID: return new SpawnTeamTile(Team::get(TeamIDs::teamID), position);
		#define Y(teamID, name, color) case TileIDs::SPAWN_TEAM_TILE_##teamID: return new SpawnTeamTile(Team::get(TeamIDs::teamID), position);
		#include <team/TeamID.list>
		#undef X
		#undef Y
		default:
			Debug::warn("no Tile with TileID=" + Converter::intToString((int) tid));
			return nullptr;
	}
}

TileID Tile::colorStringToTileID(std::string color_arg)
{
	#define X(name, tid, color) if ((#color) == color_arg) return TileIDs::tid;
	#define Y(name, tid, color) if ((#color) == color_arg) return TileIDs::tid;
	#include "TileID.list"
	#undef X
	#undef Y

	#define X(teamID, name, color) if ((#color) == color_arg) return TileIDs::SPAWN_TEAM_TILE_##teamID;
	#define Y(teamID, name, color) if ((#color) == color_arg) return TileIDs::SPAWN_TEAM_TILE_##teamID;
	#include <team/TeamID.list>
	#undef X
	#undef Y
	Debug::warn("no TileID with color=" + color_arg);
	return (TileID) 0;
}

std::string Tile::colorStringByTileID(const TileID tid)
{
	switch (tid)
	{
		#define X(name, tid, color) case TileIDs::tid: return (#color);
		#define Y(name, tid, color) case TileIDs::tid: return (#color);
		#include "TileID.list"
		#undef X
		#undef Y

		#define X(teamID, name, color) case TileIDs::SPAWN_TEAM_TILE_##teamID: return (#color);
		#define Y(teamID, name, color) case TileIDs::SPAWN_TEAM_TILE_##teamID: return (#color);
		#include <team/TeamID.list>
		#undef X
		#undef Y
		default:
			Debug::warn("no colorString by TileID=" + Converter::intToString((int) tid));
			return nullptr;
	}
}

float Tile::getMass() const
{
	return INFINITY;
}
