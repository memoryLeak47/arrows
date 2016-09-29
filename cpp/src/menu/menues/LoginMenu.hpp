#ifndef __LOGINMENU_CLASS__
#define __LOGINMENU_CLASS__

#include <menu/Menu.hpp>

class EditField;
class PasswordField;

class LoginMenu : public Menu
{
	public:
		LoginMenu();
		void login(); // called by the login button
		void signin(); // called by the signin button
	private:
		EditField* usernameField;
		PasswordField* passwordField;
};

#include <menu/components/EditField.hpp>
#include <menu/components/PasswordField.hpp>

#endif
