#ifndef __NORMALTILE_CLASS__
#define __NORMALTILE_CLASS__

#include "../Tile.hpp"

class NormalTile : public Tile
{
	public:
		NormalTile(const GameVector&);
		virtual void handleCollisions() override {}
		virtual sf::Texture* getTexture() const override;
};

#endif
