#ifndef __MINIMAP_CLASS__
#define __MINIMAP_CLASS__

#include <SFML/Graphics.hpp>

#include "../MenuComponent.hpp"

class MiniMap : public MenuComponent
{
	public:
		MiniMap(ComponentContainer*, const PixelRect&);
		virtual void render() const override;
	private:
		sf::Texture* tileMapTexture;
};

#endif
