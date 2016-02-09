#ifndef __ITEMICON_CLASS__
#define __ITEMICON_CLASS__

#include "ChoosableIcon.hpp"

class ItemIcon : public ChoosableIcon
{
	public:
		ItemIcon(int, LobbyPlayer*, LobbyMenu*, ComponentContainer*, const PixelRect&);
		virtual int getChoosePhase() const override;
		virtual void onClick(int) override;
		virtual TextureID getTextureID() const override;
	private:
		int number;
};

#endif
