#ifndef __LOGINMENU_CLASS__
#define __LOGINMENU_CLASS__

#include "../Menu.h"
class EditField;

class LoginMenu : public Menu
{
	public:
		LoginMenu();
	private:
		EditField* usernameField;
		EditField* passwordField;
};

#include "../components/EditField.h"

#endif
