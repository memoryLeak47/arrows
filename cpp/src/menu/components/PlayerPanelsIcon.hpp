#ifndef __PLAYERPANELSICON_CLASS__
#define __PLAYERPANELSICON_CLASS__

#include "Icon.hpp"

class LobbyPlayer;
class LobbyMenu;

class PlayerPanelsIcon : public Icon
{
	public:
		PlayerPanelsIcon(LobbyPlayer*, LobbyMenu*, ComponentContainer*, const PixelRect&);
		virtual void render() const override;
		bool isChoosable() const;
		virtual int getChoosePhase() const = 0;
	protected:
		LobbyPlayer* getPlayer() const;
		LobbyMenu* getLobbyMenu() const;
	private:
		LobbyPlayer* player;
		LobbyMenu* lobby;

};

#include <player/LobbyPlayer.hpp>
#include <menu/menues/LobbyMenu.hpp>

#endif
