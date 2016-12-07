#ifndef __LOBBYTILEMAP_CLASS__
#define __LOBBYTILEMAP_CLASS__

#include <vector>
#include <string>
#include <entity/TileID.hpp>

class LobbyTileMap
{
	public:
		LobbyTileMap();
		LobbyTileMap(const std::vector<std::vector<TileID>>&);
		void updateMap(const std::vector<std::vector<TileID>>&);
		static std::vector<std::vector<TileID>> getTileIDsByFile(const std::string&);
		std::vector<std::vector<TileID>> getTileIDs() const;
		bool isValid() const;
	private:
		std::vector<std::vector<TileID>> tileIDs;
};

#endif
