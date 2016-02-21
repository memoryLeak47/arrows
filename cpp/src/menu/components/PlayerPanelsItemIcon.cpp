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
		std::vector<PlayerProperty*> props;
		for (int i = 0; i < Item::getAmount(); i++)
		{
			props.push_back(Item::get(i));
		}
		Main::getMenuList()->addMenu(new ChoosePlayerPropertyMenu(getLobbyMenu(), getLobbyMenu()->getLocalPlayer()->getItemUserPacket(), props));
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
