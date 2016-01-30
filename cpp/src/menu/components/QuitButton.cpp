#include "QuitButton.h"

#include "../../misc/Debug.h"
#include "../../core/Main.h"

QuitButton::QuitButton(ComponentContainer* parent, const PixelVector& v) : Button(parent, PixelRect(v, PixelVector(100, 30)), "Quit")
{}

void QuitButton::onClick(int mouseButton)
{
	Main::exit();
}
