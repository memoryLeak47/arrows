#ifndef __JOINSERVERMENU_CLASS__
#define __JOINSERVERMENU_CLASS__

class EditField;

#include <menu/Menu.hpp>

class JoinServerMenu : public Menu
{
	public:
		JoinServerMenu();
		void joinServer(); // called by the join-server-button
	private:
		EditField* ipField;
};

#endif
