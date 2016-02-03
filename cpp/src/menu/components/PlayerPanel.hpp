#ifndef __PLAYERPANEL_CLASS__
#define __PLAYERPANEL_CLASS__

#define SKILL_ICON_SIZE 15
#define ITEM_ICON_SIZE 15
#define AVATAR_ICON_SIZE 45

#include "Panel.hpp"

class TeamPanel;
class LobbyPlayer;
class LobbyMenu;

class PlayerPanel : public Panel
{
	public:
		PlayerPanel(LobbyPlayer*, LobbyMenu*, TeamPanel*, const PixelRect&);
		virtual void render() const override;
		LobbyPlayer* getPlayer() const;
		LobbyMenu* getLobbyMenu() const;
	private:
		LobbyPlayer* player;
		LobbyMenu* lobby;
};

#include "TeamPanel.hpp"
#include "../../player/LobbyPlayer.hpp"
#include "../menues/LobbyMenu.hpp"

#endif
