#ifndef __BACKBUTTON_CLASS__
#define __BACKBUTTON_CLASS__

class ComponentContainer;
class PixelVector;

#include "Button.hpp"

class BackButton : public Button
{
	public:
		BackButton(ComponentContainer*, const PixelVector&);
		virtual void onPress() override;
};

#endif
