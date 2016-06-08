#include "LavaTile.hpp"

LavaTile::LavaTile(const GameVector& pos)
	: Tile(pos)
{}

sf::Texture* LavaTile::getTexture() const
{
	return GraphicsManager::getTexture(LAVATILE_GID);
}

std::string LavaTile::toString() const
{
	return "LavaTile";
}
