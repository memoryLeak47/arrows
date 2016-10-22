#ifndef __QUITBUTTON_CLASS__
#define __QUITBUTTON_CLASS__

class ComponentContainer;
class PixelVector;

#include "Button.hpp"

class QuitButton : public Button
{
	public:
		QuitButton(ComponentContainer*, const PixelVector&);
		virtual void onPress() override;
};

#endif
