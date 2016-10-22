#include "VoidTile.hpp"

#include <graphics/GraphicsManager.hpp>

VoidTile::VoidTile(const GameVector& pos)
	: Tile(new RectBody(pos))
{}

sf::Texture* VoidTile::getTexture() const
{
	return GraphicsManager::getTexture(VOIDTILE_GID);
}

std::string VoidTile::toString() const
{
	return "VoidTile";
}
