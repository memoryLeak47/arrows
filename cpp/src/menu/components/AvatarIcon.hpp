#ifndef __AVATARICON_CLASS__
#define __AVATARICON_CLASS__

#include "ChoosableIcon.hpp"

class AvatarIcon : public ChoosableIcon
{
	public:
		AvatarIcon(LobbyPlayer*, LobbyMenu*, ComponentContainer*, const PixelRect&);
		virtual int getChoosePhase() const override;
		virtual TextureID getTextureID() const override;
};

#endif
