#ifndef __PLAYERPANELSAVATARICON_CLASS__
#define __PLAYERPANELSAVATARICON_CLASS__

class LobbyPlayer;
class LobbyMenu;
class ComponentContainer;
class PixelRect;

#include "PlayerPanelsIcon.hpp"
#include <graphics/TextureID.hpp>

class PlayerPanelsAvatarIcon : public PlayerPanelsIcon
{
	public:
		PlayerPanelsAvatarIcon(LobbyPlayer*, LobbyMenu*, ComponentContainer*, const PixelRect&);
		virtual int getChoosePhase() const override;
		virtual void onClick(int) override;
		virtual TextureID getTextureID() const override;
};

#endif
