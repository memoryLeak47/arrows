#include "ItemIcon.hpp"

ItemIcon::ItemIcon(int n, LobbyPlayer* p, LobbyMenu* m, ComponentContainer* c, const PixelRect& r) : ChoosableIcon(p, m, c, r), number(n)
{}

int ItemIcon::getChoosePhase() const
{
	return ITEM_PHASE;
}

ImageID ItemIcon::getImageID() const
{
	// TODO
	return ImageID(0, 0);
}
