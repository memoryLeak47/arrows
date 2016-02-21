#include "PlayerPanelsAvatarIcon.hpp"

#include "../menues/ChoosePlayerPropertyMenu.hpp"
#include "../../core/Main.hpp"
#include "../../misc/Debug.hpp"
#include "../../player/property/avatar/Avatar.hpp"

extern TextureID VOID_ICON;

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
		std::vector<PlayerProperty*> props;
		for (int i = 0; i < Avatar::getAmount(); i++)
		{
			props.push_back(Avatar::get(i));
		}
		Main::getMenuList()->addMenu(new ChoosePlayerPropertyMenu(getLobbyMenu(), getLobbyMenu()->getLocalPlayer()->getAvatarUserPacket(), props));
	}
}

TextureID PlayerPanelsAvatarIcon::getTextureID() const
{
	if ((getPlayer()->getAvatarUserPacket() == NULL) ||
	    (getPlayer()->getAvatarUserPacket()->getPlayerProperties()[0] == NULL))
	{
		return VOID_ICON;
	}
	return getPlayer()->getAvatarUserPacket()->getPlayerProperties()[0]->getIconTextureID();
}
