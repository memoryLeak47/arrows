#ifndef __NORMALTILE_CLASS__
#define __NORMALTILE_CLASS__

#include <entity/Tile.hpp>

class NormalTile : public Tile
{
	public:
		NormalTile(const GameVector&);
		virtual sf::Texture* getTexture() const override;
		virtual std::string toString() const override;
};

#endif
