#include "NormalTile.hpp"

#include <graphics/GraphicsManager.hpp>

NormalTile::NormalTile(const GameVector& pos)
	: Tile(pos)
{}

sf::Texture* NormalTile::getTexture() const
{
	return GraphicsManager::getTexture(NORMALTILE_GID);
}

std::string NormalTile::toString() const
{
	return "NormalTile: " + getPosition().toString();
}
