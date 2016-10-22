#include "NormalTile.hpp"

#include <graphics/GraphicsManager.hpp>
#include <collision/RectBody.hpp>

NormalTile::NormalTile(const GameVector& pos)
	: Tile(new RectBody(pos))
{}

sf::Texture* NormalTile::getTexture() const
{
	return GraphicsManager::getTexture(NORMALTILE_GID);
}

std::string NormalTile::toString() const
{
	return "NormalTile: " + getBody()->getPosition().toString();
}
