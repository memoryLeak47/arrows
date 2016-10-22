#include "PlayerPanelsAvatarIcon.hpp"

#include <misc/Global.hpp>
#include <core/Main.hpp>
#include <menu/MenuList.hpp>
#include <player/property/avatar/Avatar.hpp>
#include <menu/menues/ChoosePlayerPropertyMenu.hpp>

PlayerPanelsAvatarIcon::PlayerPanelsAvatarIcon(LobbyPlayer* p, LobbyMenu* m, ComponentContainer* c, const PixelRect& r) : PlayerPanelsIcon(p, m, c, r)
{}

int PlayerPanelsAvatarIcon::getChoosePhase() const
{
	return AVATAR_PHASE;
}

void PlayerPanelsAvatarIcon::onClick(int mouseButton)
{
	if (isChoosable())
	{
		const std::vector<Avatar*>& avatars = Avatar::getAllAvatars();
		std::vector<PlayerProperty*> tmp;
		for (unsigned int i = 0; i < avatars.size(); i++)
		{
			tmp.push_back(avatars[i]);
		}
		Main::getMenuList()->addMenu(new ChoosePlayerPropertyMenu(getLobbyMenu(), new AvatarUserPacket(*getLobbyMenu()->getLocalPlayer()->getAvatarUserPacket()), tmp));
	}
}

TextureID PlayerPanelsAvatarIcon::getTextureID() const
{
	if ((getPlayer()->getAvatarUserPacket() == NULL) ||
	    (getPlayer()->getAvatarUserPacket()->getPlayerProperties()[0] == NULL))
	{
		return VOID_ICON_GID;
	}
	return getPlayer()->getAvatarUserPacket()->getPlayerProperties()[0]->getIconTextureID();
}
