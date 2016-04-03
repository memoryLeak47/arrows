#include "NormalTile.hpp"

NormalTile::NormalTile(const GameVector& pos)
	: Tile(new RectBody(pos))
{}

sf::Texture* NormalTile::getTexture() const
{
	return GraphicsManager::getTexture(NORMALTILE_GID);
}
