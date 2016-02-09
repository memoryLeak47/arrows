#include "ItemIcon.hpp"

#include "../menues/ChoosePlayerPropertyMenu.hpp"
#include "../../core/Main.hpp"
#include "../../misc/Debug.hpp"
#include "../../player/property/item/Item.hpp"

extern int VOID_ICON;

ItemIcon::ItemIcon(int n, LobbyPlayer* p, LobbyMenu* m, ComponentContainer* c, const PixelRect& r) : ChoosableIcon(p, m, c, r), number(n)
{}

int ItemIcon::getChoosePhase() const
{
	return ITEM_PHASE;
}

void ItemIcon::onClick(int mouseButton)
{
	if (isChoosable())
	{
		std::vector<PlayerProperty*> props;
		for (int i = 0; i < Item::getAmount(); i++)
		{
			props.push_back(Item::get(i));
		}
		Main::getMenuList()->addMenu(new ChoosePlayerPropertyMenu(getLobbyMenu(), getLobbyMenu()->getLocalPlayer()->getItemUserPacket(), props));
	}
}

TextureID ItemIcon::getTextureID() const
{
	// TODO
	return VOID_ICON;
}
