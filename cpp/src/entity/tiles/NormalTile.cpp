#include "NormalTile.hpp"

#include <graphics/GraphicsManager.hpp>

NormalTile::NormalTile(const GameVector& pos)
	: Tile(pos)
{}

sf::Texture* NormalTile::getTexture() const
{
	return GraphicsManager::getTexture(GraphicsIDs::NORMALTILE);
}

std::string NormalTile::toString() const
{
	return "NormalTile: " + getPosition().toString();
}
