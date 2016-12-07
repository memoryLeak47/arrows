#ifndef __MINIMAP_CLASS__
#define __MINIMAP_CLASS__

class ComponentContainer;
class PixelRect;

#include <menu/MenuComponent.hpp>
#include <vector>
#include <SFML/Graphics/Texture.hpp>
#include <entity/TileID.hpp>

class MiniMap : public MenuComponent
{
	public:
		MiniMap(ComponentContainer*, const PixelRect&);
		virtual ~MiniMap();
		virtual void render() const override;
		void updateMap(const std::vector<std::vector<TileID>>&);
	private:
		std::vector<std::vector<TileID>> tileIDs;
		sf::Texture* tileMapTexture;
};

#endif
