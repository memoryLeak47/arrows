#include "LoginMenu.h"

#include "MainMenu.h"
#include "../../misc/Account.h"
#include "../../misc/Debug.h"
#include "../../core/Main.h"
#include "../components/Button.h"
#include "../components/QuitButton.h"
#include "../components/Label.h"

LoginMenu::LoginMenu() : Menu()
{
	addComponent(new Label(this, PixelRect(350, 20, 100, 20), "Login"));

	addComponent(usernameField = new EditField(this, PixelRect(350, 200, 100, 20), "Username"));
	addComponent(passwordField = new PasswordField(this, PixelRect(350, 230, 100, 20), "Password"));

	class LoginButton : public Button
	{
		public:
			LoginButton(LoginMenu* c, const PixelRect& r, const std::string& s) : Button(c, r, s) {}
			void onClick(int mouseButton)
			{
				((LoginMenu*)getParent())->login();
			}
	};

	class SigninButton : public Button
	{
		public:
			SigninButton(LoginMenu* c, const PixelRect& r, const std::string& s) : Button(c, r, s) {}
			void onClick(int mouseButton)
			{
				((LoginMenu*)getParent())->signin();
			}
	};

	addComponent(new LoginButton(this, PixelRect(350, 260, 40, 20), "Log in"));
	addComponent(new SigninButton(this, PixelRect(410, 260, 40, 20), "Sign in"));

	addComponent(new QuitButton(this, PixelVector(20, 500)));


}


void LoginMenu::login()
{
	Account* account = Account::get(usernameField->getText(), passwordField->getText());
	if (account != NULL)
	{
		Main::setAccount(account);
		Main::getMenuList()->addMenu(new MainMenu());
	}
	else
	{
		popup("wrong username password combination");
	}
}

void LoginMenu::signin()
{
	if (Account::add(usernameField->getText(), passwordField->getText()))
	{
		Main::getMenuList()->addMenu(new MainMenu());
	}
	else
	{
		popup("Username already used.");
	}
}
