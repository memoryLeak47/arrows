#ifndef __LOGINMENU_CLASS__
#define __LOGINMENU_CLASS__

#include "../Menu.h"
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

#include "../components/EditField.h"
#include "../components/PasswordField.h"

#endif
