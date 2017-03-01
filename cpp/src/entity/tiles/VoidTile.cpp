#include "VoidTile.hpp"

#include <graphics/GraphicsManager.hpp>

VoidTile::VoidTile(const GameVector& pos)
	: Tile(pos)
{}

sf::Texture* VoidTile::getTexture() const
{
	return GraphicsManager::getTexture(GraphicsIDs::VOIDTILE);
}

std::string VoidTile::toString() const
{
	return "VoidTile";
}

float VoidTile::getCollisionPriority(Entity* e) const
{
	return -1000;
}
