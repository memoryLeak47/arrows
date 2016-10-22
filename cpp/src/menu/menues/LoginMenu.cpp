#include "LoginMenu.hpp"

#include <misc/Global.hpp>
#include "MainMenu.hpp"
#include <menu/MenuList.hpp>
#include <misc/Account.hpp>
#include <core/Main.hpp>
#include <menu/components/Button.hpp>
#include <menu/components/QuitButton.hpp>
#include <menu/components/Label.hpp>
#include <menu/components/EditField.hpp>
#include <menu/components/PasswordField.hpp>

LoginMenu::LoginMenu() : Menu()
{
	addComponent(new Label(this, PixelRect(350, 20, 100, 20), "Login"));

	addComponent(usernameField = new EditField(this, PixelRect(350, 200, 100, 20), "Username"));
	addComponent(passwordField = new PasswordField(this, PixelRect(350, 230, 100, 20), "Password"));

	class LoginButton : public Button
	{
		public:
			LoginButton(LoginMenu* c, const PixelRect& r, const std::string& s) : Button(c, r, s) {}
			virtual void onPress() override
			{
				((LoginMenu*)getParent())->login();
			}
	};

	class SigninButton : public Button
	{
		public:
			SigninButton(LoginMenu* c, const PixelRect& r, const std::string& s) : Button(c, r, s) {}
			virtual void onPress() override
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
	Account* account = Account::authenticate(usernameField->getText(), passwordField->getText());
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
	if (Account::isNameFree(usernameField->getText()))
	{
		Account* account = new Account(usernameField->getText(), passwordField->getText());
		Account::add(account);
		Main::setAccount(account);
		Main::getMenuList()->addMenu(new MainMenu());
	}
	else
	{
		popup("Username already used.");
	}
}
