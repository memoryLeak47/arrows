#ifndef __VOIDTILE_CLASS__
#define __VOIDTILE_CLASS__

#include <entity/Tile.hpp>

class VoidTile : public Tile
{
	public:
		VoidTile(const GameVector&);
		virtual sf::Texture* getTexture() const override;
		virtual float getCollisionPriority(Entity* e) { return -100; }
		virtual std::string toString() const override;
};

#endif
