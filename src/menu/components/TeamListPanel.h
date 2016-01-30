#ifndef __TEAMLISTPANEL_CLASS__
#define __TEAMLISTPANEL_CLASS__

#include "Panel.h"

class LobbyMenu;

class TeamListPanel : public Panel
{
	public:
		TeamListPanel(LobbyMenu*, const PixelRect&);
};

#include "../menues/LobbyMenu.h"

#endif
