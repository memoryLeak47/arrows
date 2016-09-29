#ifndef __LOBBYMINIMAP_CLASS__
#define __LOBBYMINIMAP_CLASS__

#include "MiniMap.hpp"

class LobbyMenu;

class LobbyMiniMap : public MiniMap
{
	public:
		LobbyMiniMap(LobbyMenu*, const PixelRect&);
};

#include <menu/menues/LobbyMenu.hpp>

#endif
