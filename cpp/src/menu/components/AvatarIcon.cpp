#include "AvatarIcon.hpp"

AvatarIcon::AvatarIcon(LobbyPlayer* p, LobbyMenu* m, ComponentContainer* c, const PixelRect& r) : ChoosableIcon(p, m, c, r)
{}

int AvatarIcon::getChoosePhase() const
{
	return AVATAR_PHASE;
}

ImageID AvatarIcon::getImageID() const
{
	/*
	if ((getPlayer()->getAvatarPacket() == NULL) || (getPlayer()->getAvatarPacket()->getAvatar() == NULL))
	{
		return ImageFile::get(VOID_ICON).getImageID();
	}
	return player.getAvatarPacket().getAvatar().getIconImageID();
	*/
	return ImageID(0, 0);
	// TODO
}
