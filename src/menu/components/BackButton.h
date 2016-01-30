#ifndef __BACKBUTTON_CLASS__
#define __BACKBUTTON_CLASS__

#include "Button.h"

class BackButton : public Button
{
	public:
		BackButton(ComponentContainer*, const PixelVector&);
		void onClick(int mouseButton) override;
};

#endif
