#ifndef __PLAYERPANELSSKILLICON_CLASS__
#define __PLAYERPANELSSKILLICON_CLASS__

class LobbyPlayer;
class LobbyMenu;
class ComponentContainer;
class PixelRect;

#include "PlayerPanelsIcon.hpp"
#include <graphics/TextureID.hpp>

class PlayerPanelsSkillIcon : public PlayerPanelsIcon
{
	public:
		PlayerPanelsSkillIcon(int, LobbyPlayer*, LobbyMenu*, ComponentContainer*, const PixelRect&);
		virtual int getChoosePhase() const override;
		virtual void onClick(int) override;
		virtual TextureID getTextureID() const override;
	private:
		int number;
};

#endif
