#ifndef __LAVATILE_CLASS__
#define __LAVATILE_CLASS__

class GameVector;

#include <entity/Tile.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string>

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
