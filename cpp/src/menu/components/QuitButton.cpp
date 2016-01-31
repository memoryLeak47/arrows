#include "QuitButton.hpp"

#include "../../misc/Debug.hpp"
#include "../../core/Main.hpp"

QuitButton::QuitButton(ComponentContainer* parent, const PixelVector& v) : Button(parent, PixelRect(v, PixelVector(100, 30)), "Quit")
{}

void QuitButton::onClick(int mouseButton)
{
	Main::exit();
}
