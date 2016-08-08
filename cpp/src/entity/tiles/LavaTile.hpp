#ifndef __LAVATILE_CLASS__
#define __LAVATILE_CLASS__

#include "../Tile.hpp"

class LavaTile : public Tile
{
	public:
		LavaTile(const GameVector&);
		virtual ~LavaTile() {}
		virtual sf::Texture* getTexture() const override;
		virtual std::string toString() const override;
		virtual CollisionType getCollisionType() const override;
};

#endif
