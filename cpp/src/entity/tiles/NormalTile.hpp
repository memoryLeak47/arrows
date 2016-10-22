#ifndef __NORMALTILE_CLASS__
#define __NORMALTILE_CLASS__

class GameVector;

#include <entity/Tile.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string>

class NormalTile : public Tile
{
	public:
		NormalTile(const GameVector&);
		virtual sf::Texture* getTexture() const override;
		virtual std::string toString() const override;
};

#endif
