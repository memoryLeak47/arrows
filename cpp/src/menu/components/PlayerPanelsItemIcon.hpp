#ifndef __PLAYERPANELSITEMICON_CLASS__
#define __PLAYERPANELSITEMICON_CLASS__

class LobbyPlayer;
class LobbyMenu;
class ComponentContainer;
class PixelRect;

#include "PlayerPanelsIcon.hpp"
#include <graphics/TextureID.hpp>

class PlayerPanelsItemIcon : public PlayerPanelsIcon
{
	public:
		PlayerPanelsItemIcon(int, LobbyPlayer*, LobbyMenu*, ComponentContainer*, const PixelRect&);
		virtual int getChoosePhase() const override;
		virtual void onClick(int) override;
		virtual TextureID getTextureID() const override;
	private:
		int number;
};

#endif
