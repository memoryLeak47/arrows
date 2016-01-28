#include "LoginMenu.h"

LoginMenu::LoginMenu() : Menu(PixelRect(0, 0, 800, 600))
{
	addComponent(new Button(this, PixelRect(40, 40, 60, 20), "Login"));
}
