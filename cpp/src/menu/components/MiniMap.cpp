#include "MiniMap.hpp"

#include <misc/Global.hpp>
#include <graphics/GraphicsManager.hpp>

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
		Screen::drawGraphicsID(getAbsoluteRect(), VOID_ICON_GID);
	}
	else
	{
		Screen::drawTexture(tileMapTexture, getAbsoluteRect());
	}
}

void MiniMap::updateMap(const std::vector<std::vector<int>>& ints)
{
	this->ints = ints;

	sf::Image image;
	image.create((int)ints.size(), (int)ints[0].size(), sf::Color::Green); // random color :D

	for (unsigned int x = 0; x < ints.size(); x++)
	{
		for (unsigned int y = 0; y < ints[0].size(); y++)
		{
			image.setPixel(x, y, Converter::intToColor(ints[x][y])); // drittes Argument: int -> Color
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
