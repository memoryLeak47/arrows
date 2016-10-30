#include "RubberTile.hpp"

#include <graphics/GraphicsManager.hpp>

RubberTile::RubberTile(const GameVector& pos)
	: Tile(pos)
{}

Sponge RubberTile::getSponge() const
{
	return Sponge{5, 0.9f};
}

sf::Texture* RubberTile::getTexture() const
{
	return GraphicsManager::getTexture(RUBBERTILE_GID);
}

std::string RubberTile::toString() const
{
	return "RubberTile: " + getPosition().toString();
}
