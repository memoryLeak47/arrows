#ifndef __QUITBUTTON_CLASS__
#define __QUITBUTTON_CLASS__

#include "Button.h"

class QuitButton : public Button
{
	public:
		QuitButton(ComponentContainer*, const PixelVector&);
		void onClick(int mouseButton) override;
};

#endif
