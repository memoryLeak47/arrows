#include "PlayerPanelsIcon.hpp"

#include <core/Screen.hpp>
#include <menu/menues/LobbyMenu.hpp>
#include <player/LobbyPlayer.hpp>
#include <network/packets/LockPacket.hpp>

PlayerPanelsIcon::PlayerPanelsIcon(LobbyPlayer* p, LobbyMenu* m, ComponentContainer* c, const PixelRect& r) : Icon(c, r), player(p), lobby(m)
{}

void PlayerPanelsIcon::render() const
{
	Icon::render();
	if (isChoosable())
	{
		// Hervorhebung. Zeichnet weißes durchsichtiges Viereck auf das Icon
		Screen::fillRect(getAbsoluteRect(), sf::Color(255, 255, 255, 100));
	}
}

bool PlayerPanelsIcon::isChoosable() const
{
	return getLobbyMenu()->getPhase() == getChoosePhase()
	    && getLobbyMenu()->getLocalPlayer() == getPlayer()
	    && !getPlayer()->getLockPacket()->isLocked();
}

LobbyMenu* PlayerPanelsIcon::getLobbyMenu() const
{
	return lobby;
}

LobbyPlayer* PlayerPanelsIcon::getPlayer() const
{
	return player;
}
