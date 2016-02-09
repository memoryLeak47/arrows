#ifndef __LOBBYTILEMAP_CLASS__
#define __LOBBYTILEMAP_CLASS__

#include <vector>
#include <string>

class LobbyTileMap
{
	public:
		LobbyTileMap();
		LobbyTileMap(const std::vector<std::vector<int>>&);
		void updateMap(const std::vector<std::vector<int>>&);
		static std::vector<std::vector<int>> getIntsByFile(const std::string&);
		std::vector<std::vector<int>> getInts() const;
	private:
		std::vector<std::vector<int>> ints;
};

#endif
