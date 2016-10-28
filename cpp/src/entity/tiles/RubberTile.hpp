#ifndef __RUBBERTILE_CLASS__
#define __RUBBERTILE_CLASS__

class GameVector;

#include <entity/Tile.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string>

class RubberTile : public Tile
{
	public:
		RubberTile(const GameVector&);
		virtual ~RubberTile() {}

		virtual Sponge getSponge() const override;
		virtual sf::Texture* getTexture() const override;
		virtual std::string toString() const override;
};

#endif
