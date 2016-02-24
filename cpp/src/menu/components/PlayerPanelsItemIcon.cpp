#include "PlayerPanelsItemIcon.hpp"

#include "../menues/ChoosePlayerPropertyMenu.hpp"
#include "../../core/Main.hpp"
#include "../../misc/Debug.hpp"
#include "../../player/property/item/Item.hpp"

extern TextureID VOID_ICON;

PlayerPanelsItemIcon::PlayerPanelsItemIcon(int n, LobbyPlayer* p, LobbyMenu* m, ComponentContainer* c, const PixelRect& r) : PlayerPanelsIcon(p, m, c, r), number(n)
{}

int PlayerPanelsItemIcon::getChoosePhase() const
{
	return ITEM_PHASE;
}

void PlayerPanelsItemIcon::onClick(int mouseButton)
{
	if (isChoosable())
	{
		const std::vector<Item*>& items = Item::getAllItems();
		std::vector<PlayerProperty*> tmp;
		for (int i = 0; i < items.size(); i++)
		{
			tmp.push_back(items[i]);
		}
		Main::getMenuList()->addMenu(new ChoosePlayerPropertyMenu(getLobbyMenu(), getLobbyMenu()->getLocalPlayer()->getItemUserPacket(), tmp));
	}
}

TextureID PlayerPanelsItemIcon::getTextureID() const
{
	if ((getPlayer()->getItemUserPacket() == NULL) ||
	    (getPlayer()->getItemUserPacket()->getPlayerProperties()[number] == NULL))
	{
		return VOID_ICON;
	}
	return getPlayer()->getItemUserPacket()->getPlayerProperties()[number]->getIconTextureID();
}
