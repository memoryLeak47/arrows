#include "Icon.hpp"

#include "../../core/Screen.hpp"
#include "../../misc/Debug.hpp"

Icon::Icon(ComponentContainer* c, const PixelRect& r) : MenuComponent(c, r)
{}

void Icon::render() const
{
	/* // TODO
	if (!getImageID().isValid())
	{
		Debug::error("Icon::render() tries to render null IconID");
		return;
	}
	*/
	Screen::drawImageID(getImageID(), getAbsoluteRect());
}
