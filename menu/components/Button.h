#ifndef __BUTTON_CLASS__
#define __BUTTON_CLASS__

#include "../MenuComponent.h"

class Button : public MenuComponent
{
	public:
		Button();
		virtual void render(); // override
};

#include "../../core/Screen.h"
#include "../../misc/Debug.h"

#endif
