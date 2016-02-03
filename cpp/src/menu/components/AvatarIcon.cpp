#include "AvatarIcon.hpp"

extern int VOID_ICON;

AvatarIcon::AvatarIcon(LobbyPlayer* p, LobbyMenu* m, ComponentContainer* c, const PixelRect& r) : ChoosableIcon(p, m, c, r)
{}

int AvatarIcon::getChoosePhase() const
{
	return AVATAR_PHASE;
}

TextureID AvatarIcon::getTextureID() const
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
