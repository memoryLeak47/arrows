#include "ChoosableIcon.hpp"

#include "../../core/Screen.hpp"

ChoosableIcon::ChoosableIcon(LobbyPlayer* p, LobbyMenu* m, ComponentContainer* c, const PixelRect& r) : Icon(c, r), player(p), lobby(m)
{}

void ChoosableIcon::render() const
{
	Icon::render();
	if (isChoosable())
	{
		// Hervorhebung. Zeichnet weißes durchsichtiges Viereck auf das Icon
		Screen::drawRect(getAbsoluteRect(), sf::Color(255, 255, 255, 100));
	}
}

bool ChoosableIcon::isChoosable() const
{
	return getLobbyMenu()->getPhase() == getChoosePhase()
	    && getLobbyMenu()->getLocalPlayer() == getPlayer()
	    && !getPlayer()->getLockUserPacket()->isLocked();
}

LobbyMenu* ChoosableIcon::getLobbyMenu() const
{
	return lobby;
}

LobbyPlayer* ChoosableIcon::getPlayer() const
{
	return player;
}
