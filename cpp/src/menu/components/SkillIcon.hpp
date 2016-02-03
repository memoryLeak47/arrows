#ifndef __SKILLICON_CLASS__
#define __SKILLICON_CLASS__

#include "ChoosableIcon.hpp"

class SkillIcon : public ChoosableIcon
{
	public:
		SkillIcon(int, LobbyPlayer*, LobbyMenu*, ComponentContainer*, const PixelRect&);
		virtual int getChoosePhase() const override;
		virtual ImageID getImageID() const override;
	private:
		int number;
};

#endif
