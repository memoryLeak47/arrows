#ifndef __MINIMAP_CLASS__
#define __MINIMAP_CLASS__

#include <SFML/Graphics.hpp>

#include "../MenuComponent.hpp"

class MiniMap : public MenuComponent
{
	public:
		MiniMap(ComponentContainer*, const PixelRect&);
		virtual void render() const override;
		void updateMap(const std::vector<std::vector<int>>&);
	private:
		std::vector<std::vector<int>> ints;
		sf::Texture* tileMapTexture;
};

#endif
