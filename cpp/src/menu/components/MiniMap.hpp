#ifndef __MINIMAP_CLASS__
#define __MINIMAP_CLASS__

class ComponentContainer;
class PixelRect;

#include <menu/MenuComponent.hpp>
#include <vector>
#include <SFML/Graphics/Texture.hpp>

class MiniMap : public MenuComponent
{
	public:
		MiniMap(ComponentContainer*, const PixelRect&);
		virtual ~MiniMap();
		virtual void render() const override;
		void updateMap(const std::vector<std::vector<int>>&);
	private:
		std::vector<std::vector<int>> ints;
		sf::Texture* tileMapTexture;
};

#endif
