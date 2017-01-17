#include "LobbyTileMap.hpp"

#include <SFML/Graphics.hpp>
#include <entity/Tile.hpp>
#include <misc/Global.hpp>

LobbyTileMap::LobbyTileMap()
{}

LobbyTileMap::LobbyTileMap(const std::vector<std::vector<TileID>>& tileIDs_arg)
{
	tileIDs = tileIDs_arg;
}

void LobbyTileMap::updateMap(const std::vector<std::vector<TileID>>& tileIDs_arg)
{
	tileIDs = tileIDs_arg;
}

std::vector<std::vector<TileID>> LobbyTileMap::getTileIDsByFile(const std::string& path)
{
	sf::Image image;
	image.loadFromFile(path);
	std::vector<std::vector<TileID>> tileIDs;

	tileIDs.reserve(image.getSize().x);
	for (unsigned int x = 0; x < image.getSize().x; x++)
	{
		tileIDs.push_back(std::vector<TileID>()); // Spalten werden in den vector geschrieben
		tileIDs.back().reserve(image.getSize().y);
		for (unsigned int y = 0; y < image.getSize().y; y++)
		{
			sf::Color c = image.getPixel(x, y);
			std::string s = Converter::colorToColorString(c);
			TileID t = Tile::colorStringToTileID(s);
			tileIDs[x].push_back(t); // Einzelne Werte werden in die jeweilige Spalte geschrieben
		}
	}
	return tileIDs;
}

std::vector<std::vector<TileID>> LobbyTileMap::getTileIDs() const
{
	return tileIDs;
}

bool LobbyTileMap::isValid() const
{
	return getTileIDs().size() > 0;
}
