#include "PlayerPanelsItemIcon.hpp"

#include <misc/Global.hpp>
#include <core/Main.hpp>
#include <menu/MenuList.hpp>
#include <item/LobbyItem.hpp>
#include <menu/menues/ChoosePlayerPropertyMenu.hpp>
#include <menu/menues/LobbyMenu.hpp> // for ITEM_PHASE
#include <network/packets/ItemPacket.hpp>
#include <player/LobbyPlayer.hpp>

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
		const std::vector<LobbyItem*>& items = LobbyItem::getAllLobbyItems();
		std::vector<PlayerProperty*> tmp;
		for (unsigned int i = 0; i < items.size(); i++)
		{
			tmp.push_back(items[i]);
		}
		Main::getMenuList()->addMenu(new ChoosePlayerPropertyMenu(getLobbyMenu(), new ItemPacket(*getLobbyMenu()->getLocalPlayer()->getItemPacket()), tmp));
	}
}

TextureID PlayerPanelsItemIcon::getTextureID() const
{
	if ((getPlayer()->getItemPacket() == nullptr) ||
	    (getPlayer()->getItemPacket()->getPlayerProperties()[number] == nullptr))
	{
		return VOID_ICON_GID;
	}
	return getPlayer()->getItemPacket()->getPlayerProperties()[number]->getIconTextureID();
}
