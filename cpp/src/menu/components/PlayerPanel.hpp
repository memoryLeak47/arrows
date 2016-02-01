#ifndef __PLAYERPANEL_CLASS__
#define __PLAYERPANEL_CLASS__

#include "Panel.hpp"

class TeamPanel;
class LobbyPlayer;

class PlayerPanel : public Panel
{
	public:
		PlayerPanel(TeamPanel*, const PixelRect&, LobbyPlayer*);
	private:
		LobbyPlayer* player;
};

#include "TeamPanel.hpp"
#include "../../player/LobbyPlayer.hpp"

#endif
