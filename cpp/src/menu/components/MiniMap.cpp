#include "MiniMap.hpp"

#include <misc/Global.hpp>
#include <graphics/GraphicsManager.hpp>
#include <entity/Tile.hpp>

#include <core/Main.hpp>
#include <core/Screen.hpp>

MiniMap::MiniMap(ComponentContainer* c, const PixelRect& r) : MenuComponent(c, r)
{
	tileMapTexture = nullptr;
}

MiniMap::~MiniMap()
{
	deleteAndNullptr(tileMapTexture);
}

void MiniMap::render() const
{
	if (tileMapTexture == nullptr)
	{
		Screen::drawGraphicsID(getAbsoluteRect(), GraphicsIDs::VOID_ICON);
	}
	else
	{
		Screen::drawTexture(tileMapTexture, getAbsoluteRect());
	}
}

void MiniMap::updateMap(const std::vector<std::vector<TileID>>& tileIDs_arg)
{
	tileIDs = tileIDs_arg;

	sf::Image image;
	image.create((int) tileIDs.size(), (int) tileIDs[0].size(), sf::Color::Green); // random color :D

	for (unsigned int x = 0; x < tileIDs.size(); x++)
	{
		for (unsigned int y = 0; y < tileIDs[0].size(); y++)
		{
			image.setPixel(x, y, Converter::colorStringToColor(Tile::colorStringByTileID(tileIDs[x][y]))); // drittes Argument: TileID -> Color
		}
	}

	if (tileMapTexture == nullptr)
	{
		tileMapTexture = new sf::Texture();
	}

	if (!tileMapTexture->loadFromImage(image))
	{
		Debug::warn("MiniMap::updateMap(): Couldn't update tileMapTexture");
	}
}
