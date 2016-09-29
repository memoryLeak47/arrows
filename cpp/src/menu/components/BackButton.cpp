#include "BackButton.hpp"

#include <misc/Debug.hpp>
#include <core/Main.hpp>

BackButton::BackButton(ComponentContainer* parent, const PixelVector& v) : Button(parent, PixelRect(v, PixelVector(100, 30)), "Back")
{}

void BackButton::onPress()
{
	Main::getMenuList()->back();
}
