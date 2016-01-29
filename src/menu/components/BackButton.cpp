#include "BackButton.h"

#include "../../misc/Debug.h"
#include "../../core/Main.h"

BackButton::BackButton(ComponentContainer* parent, const PixelVector& v) : Button(parent, PixelRect(v, PixelVector(100, 30)), "Back")
{}

void BackButton::onClick(int mouseButton)
{
	Main::getMenuList()->back();
}
