#ifndef __PLAYERPANELSITEMICON_CLASS__
#define __PLAYERPANELSITEMICON_CLASS__

#include "PlayerPanelsIcon.hpp"

class PlayerPanelsItemIcon : public PlayerPanelsIcon
{
	public:
		PlayerPanelsItemIcon(int, LobbyPlayer*, LobbyMenu*, ComponentContainer*, const PixelRect&);
		virtual int getChoosePhase() const override;
		virtual void onClick(int) override;
		virtual GraphicsID getGraphicsID() const override;
	private:
		int number;
};

#endif
