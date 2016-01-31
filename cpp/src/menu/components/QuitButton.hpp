#ifndef __QUITBUTTON_CLASS__
#define __QUITBUTTON_CLASS__

#include "Button.hpp"

class QuitButton : public Button
{
	public:
		QuitButton(ComponentContainer*, const PixelVector&);
		void onClick(int mouseButton) override;
};

#endif
