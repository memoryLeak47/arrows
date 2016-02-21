#include "PlayerPanelsAvatarIcon.hpp"

extern TextureID VOID_ICON;

PlayerPanelsAvatarIcon::PlayerPanelsAvatarIcon(LobbyPlayer* p, LobbyMenu* m, ComponentContainer* c, const PixelRect& r) : PlayerPanelsIcon(p, m, c, r)
{}

int PlayerPanelsAvatarIcon::getChoosePhase() const
{
	return AVATAR_PHASE;
}

TextureID PlayerPanelsAvatarIcon::getTextureID() const
{
	/*
	if ((getPlayer()->getAvatarPacket() == NULL) || (getPlayer()->getAvatarPacket()->getAvatar() == NULL))
	{
		return ImageFile::get(VOID_ICON).getTextureID();
	}
	return player.getAvatarPacket().getAvatar().getIconTextureID();
	*/
	return VOID_ICON;
	// TODO
}
