#ifndef __PLAYERPANELSAVATARICON_CLASS__
#define __PLAYERPANELSAVATARICON_CLASS__

#include "PlayerPanelsIcon.hpp"

class PlayerPanelsAvatarIcon : public PlayerPanelsIcon
{
	public:
		PlayerPanelsAvatarIcon(LobbyPlayer*, LobbyMenu*, ComponentContainer*, const PixelRect&);
		virtual int getChoosePhase() const override;
		virtual TextureID getTextureID() const override;
};

#endif
