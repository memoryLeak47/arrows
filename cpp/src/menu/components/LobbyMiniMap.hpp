#ifndef __LOBBYMINIMAP_CLASS__
#define __LOBBYMINIMAP_CLASS__

class LobbyMenu;
class PixelRect;

#include "MiniMap.hpp"

class LobbyMiniMap : public MiniMap
{
	public:
		LobbyMiniMap(LobbyMenu*, const PixelRect&);
};

#endif
