#ifndef __GAMEINTERFACE_CLASS__
#define __GAMEINTERFACE_CLASS__

#include "../menu/NetworkingMenu.hpp"
#include "../tile/map/GameTileMap.hpp"

class LobbyTileMap;

class GameInterface : public NetworkingMenu
{
	public:
		GameInterface(LobbyTileMap*);
		virtual void tick() override;
	private:
		GameTileMap* tileMap;
};

#include "../tile/map/LobbyTileMap.hpp"

#endif
