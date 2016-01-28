#ifndef __LOGINMENU_CLASS__
#define __LOGINMENU_CLASS__

#include "../Menu.h"
class EditField;

class LoginMenu : public Menu
{
	public:
		LoginMenu();
		void login(); // called by the login button
		void signin(); // called by the signin button
	private:
		EditField* usernameField;
		EditField* passwordField;
};

#include "../components/EditField.h"

#endif
