#include "PlayerPanelsAvatarIcon.hpp"

#include <misc/Global.hpp>
#include <core/Main.hpp>
#include <menu/MenuList.hpp>
#include <avatar/LobbyAvatar.hpp>
#include <menu/menues/ChoosePlayerPropertyMenu.hpp>
#include <menu/menues/LobbyMenu.hpp> // for AVATAR_PHASE
#include <network/packets/AvatarPacket.hpp>
#include <player/LobbyPlayer.hpp>

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
		const std::vector<LobbyAvatar*>& avatars = LobbyAvatar::getAllLobbyAvatars();
		std::vector<PlayerProperty*> tmp;
		for (unsigned int i = 0; i < avatars.size(); i++)
		{
			tmp.push_back(avatars[i]);
		}
		Main::getMenuList()->addMenu(new ChoosePlayerPropertyMenu(getLobbyMenu(), new AvatarPacket(*getLobbyMenu()->getLocalPlayer()->getAvatarPacket()), tmp));
	}
}

TextureID PlayerPanelsAvatarIcon::getTextureID() const
{
	if ((getPlayer()->getAvatarPacket() == nullptr) ||
	    (getPlayer()->getAvatarPacket()->getPlayerProperties()[0] == nullptr))
	{
		return GraphicsIDs::VOID_ICON;
	}
	return getPlayer()->getAvatarPacket()->getPlayerProperties()[0]->getIconTextureID();
}
