#ifndef __LOBBYMINIMAP_CLASS__
#define __LOBBYMINIMAP_CLASS__

#include "MiniMap.h"
class LobbyMenu;

class LobbyMiniMap : public MiniMap
{
	public:
		LobbyMiniMap(LobbyMenu*, const PixelRect&);
};

#include "../menues/LobbyMenu.h"

#endif
