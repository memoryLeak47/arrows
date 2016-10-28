#include "RubberTile.hpp"

#include <graphics/GraphicsManager.hpp>
#include <collision/RectBody.hpp>

RubberTile::RubberTile(const GameVector& pos)
	: Tile(new RectBody(pos))
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
	return "RubberTile: " + getBody()->getPosition().toString();
}
