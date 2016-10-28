#ifndef __PLAYERPANEL_CLASS__
#define __PLAYERPANEL_CLASS__

constexpr int SKILL_ICON_SIZE = 15;
constexpr int ITEM_ICON_SIZE = 15;
constexpr int AVATAR_ICON_SIZE = 45;

class LobbyPlayer;
class LobbyMenu;
class TeamPanel;
class PixelRect;

#include "Panel.hpp"

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

#endif
