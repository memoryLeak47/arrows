#include "ItemIcon.hpp"

extern int VOID_ICON;

ItemIcon::ItemIcon(int n, LobbyPlayer* p, LobbyMenu* m, ComponentContainer* c, const PixelRect& r) : ChoosableIcon(p, m, c, r), number(n)
{}

int ItemIcon::getChoosePhase() const
{
	return ITEM_PHASE;
}

TextureID ItemIcon::getTextureID() const
{
	// TODO
	return VOID_ICON;
}
