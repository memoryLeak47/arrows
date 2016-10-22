#ifndef __LOGINMENU_CLASS__
#define __LOGINMENU_CLASS__

class EditField;
class PasswordField;

#include <menu/Menu.hpp>

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

#endif
