#ifndef __GAMEINTERFACE_CLASS__
#define __GAMEINTERFACE_CLASS__

#include "../menu/NetworkingMenu.hpp"
#include "../tile/map/GameTileMap.hpp"

class LobbyTileMap;
class LobbyPlayer;
class GamePlayer;

class GameInterface : public NetworkingMenu
{
	public:
		GameInterface(LobbyTileMap*, const std::vector<LobbyPlayer*>&);
		virtual ~GameInterface();
		virtual void tick() override;
	private:
		std::vector<GamePlayer*> players;
		GameTileMap* tileMap;
};

#include "../tile/map/LobbyTileMap.hpp"
#include "../player/LobbyPlayer.hpp"
#include "../player/GamePlayer.hpp"

#endif
