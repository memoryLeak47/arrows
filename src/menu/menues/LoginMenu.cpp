#include "LoginMenu.h"

#include "../components/Button.h"
#include "../components/Label.h"
#include "../components/EditField.h"

LoginMenu::LoginMenu() : Menu()
{
	addComponent(new Label(this, PixelRect(350, 20, 100, 20), "Login"));

	addComponent(usernameField = new EditField(this, PixelRect(350, 200, 100, 20), "Username"));
	addComponent(passwordField = new EditField(this, PixelRect(350, 230, 100, 20), "Password"));

	addComponent(new Button(this, PixelRect(350, 260, 40, 20), "Log in"));
	addComponent(new Button(this, PixelRect(410, 260, 40, 20), "Sign in"));

	addComponent(new Button(this, PixelRect(20, 500, 100, 30), "Quit"));


}
